#include "toolchain.h"
#include <QDebug>
#include <QDir>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "roboskopenvironment.h"
#include "exception/compileerror.h"
#include "traverse/arduinolibrarytraverse.h"
#include "traverse/filetraverse.h"
#include "arduinoLibManager/librarymanager.h"
#include "avrtoolchainenvironment.h"

Toolchain::Toolchain(Compiler *compiler, Programmer *programmer, QObject *parent) : QObject(parent)
{
    _compiler = compiler;
    _programmer = programmer;
}

QString Toolchain::compileFolderRecursively(QString rootPath, QString outputPath , QStringList extraFolders){

    emit compileStart();

    QDir    path(rootPath);
    QDir    buildFolder(outputPath);
    QDir    buildHeaderFolder(buildFolder.filePath("header"));
    QDir    buildCppFolder(buildFolder.filePath("cpp"));
    QDir    objFolder(outputPath);

    QString objOutputPath = QString(outputPath);
    QString sketchCppPath = path.filePath("sketch.cpp");
    QString sketchOutputCppPath = buildFolder.filePath("sketch.cpp");
    QString hexFileAbsPath = objFolder.absoluteFilePath("roboskop.hex");
    QStringList sources;
    QStringList objFiles;


    buildFolder.removeRecursively();

    /*QStringList includes = QStringList() << buildHeaderFolder.absolutePath() << "/home/arnest/arduino-1.6.13/hardware/arduino/avr/variants/standard"*/;
    QStringList includes = QStringList() << buildHeaderFolder.absolutePath() << QDir(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::Variants)).filePath("standard");

    //Proje dizini ekleniyor
    if(!extraFolders.contains(rootPath)){
        extraFolders.push_front(rootPath);
    }

    QList<ArduinoLibDescription*>   dependencies = specifyLibraryDependencies(rootPath);

    //Gerekli kutuphaneler build klasorune ekleniyor
    foreach (ArduinoLibDescription *desc, dependencies) {
        //extraFolders << desc->localDir();
        includes << desc->srcDir();
    }

    //Headerlar kopyalanıyor
    foreach (QString path, extraFolders) {
        if(_debugEnabled)   qDebug() << "Headerlar kopyalanıyor. " << path << " -> " << buildHeaderFolder.absolutePath();
        copyFilesRecursively(path , buildHeaderFolder.absolutePath() , QString("\\.h") , Q_NULLPTR);
        if(_debugEnabled)   qDebug() << "Source dosyaları kopyalanıyor." << path << " -> " << buildCppFolder.absolutePath();
        copyFilesRecursively(path , buildCppFolder.absolutePath() , QString("\\.cpp|\\.c|\\.S") , &sources);
    }

    if(_debugEnabled)   qDebug() << sketchCppPath << " derleniyor..." << " -> " << sketchOutputCppPath;

    try {
        stdOutput("sketch.cpp derleniyor...");
        _compiler->compileCppFile(buildCppFolder.filePath("sketch.cpp") , buildFolder.filePath("sketch.cpp.o") , includes);
    }   catch(CompileError err) {
        if(_debugEnabled)   qDebug() << "Toolchain::compileFolderRecursively() sketch.cpp derlenirken hata oluştu. -> " << err.err;

        emit compileEnd(false);
        return err.err;
    }

    int     fIdx = 1;

    //Kutuphaneler derleniyor
    foreach (ArduinoLibDescription *dependency, dependencies) {
        try{
            if(_debugEnabled)   qDebug() << dependency->name() << " derleniyor...";
        compileLib(dependency->srcDir() , objOutputPath);
        }catch(CompileError &err){
            if(_debugEnabled)   qDebug() << "ToolChain::compileFolderRecursively()-compileLib() Derleme aşamasında hata oluştu. -> " << err.err;

            emit compileEnd(false);
            return err.err;
        }
    }

    //Dosyalar compile ediliyor
    foreach (QString srcFile, buildCppFolder.entryList()) {

        QString srcFilePath = buildCppFolder.filePath(srcFile);
        QString outputFilePath = QString(objOutputPath).append("/").append(srcFile).append(".o");
        QString extension = extractFileExtension(srcFilePath);

        try{
            if(extension == ".c"){
                if(_debugEnabled)
                    qDebug() << srcFilePath << " derleniyor..." << " -> " << outputFilePath;
                _compiler->compileCFile(srcFilePath , outputFilePath , includes);
            }
            else if(extension == ".S"){
                if(_debugEnabled)   qDebug() << srcFilePath << " derleniyor..." << " -> " << outputFilePath;
                _compiler->compileSFile(srcFilePath , outputFilePath , includes);
            }
            else if(extension == ".cpp"){
                if(_debugEnabled)   qDebug() << srcFilePath << " derleniyor..." << " -> " << outputFilePath;
                _compiler->compileCppFile(srcFilePath , outputFilePath , includes);
            }else{
                continue;
            }

            stdOutput(QString(srcFile).append(" derleniyor..."));


        }   catch(CompileError &err){

            if(_debugEnabled)   qDebug() << "ToolChain::compileFolderRecursively() Derleme aşamasında hata oluştu. -> " << err.err;

            emit compileEnd(false);
            return err.err;
        }

        double progress = (fIdx / (double)buildCppFolder.entryList().length()) * 0.5;
        emit compileProgress(progress);
        objFiles << outputFilePath;
        fIdx++;
    }

    QString archiveFPath = buildFolder.filePath("roboskop.a");

    //Index sıfırlanıyor
    fIdx = 1;

    foreach (QString f, objFiles) {
        if(_debugEnabled)   qDebug() << f << " arşivleniyor..." << " -> " << archiveFPath;

        try{
            _compiler->archiveObjFiles(f , archiveFPath);
        }   catch(CompileError err){
            if(_debugEnabled)   qDebug() << "Toolchain::compileFolderRecursively() Arşivleme aşamasında hata oluştu. -> " << err.err;

            emit compileEnd(false);
            return err.err;
        }

        double progress = (fIdx / (double)objFiles.length()) * 0.4 + 0.5;
        emit compileProgress(progress);
        fIdx++;
    }


    try{
        _compiler->linkThemTogether(QString(buildFolder.filePath("sketch.cpp.o")) , archiveFPath , objFolder.absolutePath() , hexFileAbsPath);
        emit compileProgress(1.0);
    }
    catch(CompileError err){
        if(_debugEnabled)   qDebug() << "Toolchain::compileFolderRecursively() Linking aşamasında hata olluştu. -> " << err.err;

        emit compileEnd(false);
        return err.err;
    }

    emit stdOutput("Derleme bitiriliyor...");
    emit compileEnd(true);
    return hexFileAbsPath;
}

bool Toolchain::uploadHex(QString hexPath){
    _programmer->upload(hexPath);
}

bool Toolchain::copyFilesRecursively(QString rootPath, QString destPath , QString pattern , QStringList *l){

    //Eğer ki dizin mevcut değilse oluşturuluyor
    if(!QFile::exists(destPath)){
        qDebug() <<  rootPath <<  " oluşturuluyor...";
        QDir().mkpath(destPath);
    }

    QDir    path(rootPath);

    foreach (QString nestedFolder, path.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString nestedPath = QDir(rootPath).filePath(nestedFolder);
        copyFilesRecursively( nestedPath , destPath , pattern , l);
    }

    qDebug() << path.entryList(QDir::Files);
    foreach (QString file, path.entryList(QDir::Files)) {

        QRegularExpression      re(pattern);
        QRegularExpressionMatch match = re.match(file);

        if(!match.hasMatch()){
            qDebug() << file << " pas geçiliyor.";

            continue;
        }

        QString destFile = QDir(destPath).filePath(file);
        QString filePath = QDir(rootPath).filePath(file);
        QFile::remove(destFile);
        bool copied = QFile::copy(filePath , destFile);

        if(l != Q_NULLPTR)
            l->append(destFile);

        if(_debugEnabled)
            qDebug() << copied << "  " << filePath << " -> " << destFile;
    }
}

QString Toolchain::extractFileName(QString path){
    int idx = path.lastIndexOf("/");

    QStringRef  fileName(&path , idx + 1 , path.length() - idx - 1);

    return fileName.toString();
}

void Toolchain::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

QString Toolchain::extractFileExtension(QString path){
    int idx = path.lastIndexOf(".");
    QString extension = path.right(path.length() - idx);

    return extension;
}

QList<ArduinoLibDescription*> Toolchain::specifyLibraryDependencies(QString rootPath){
    FileTraverse            traverser;
    LibraryManager          libManager;


    //Local kutuphaneler yukleniyor
    libManager.retrieveLocalLibraries();
    QList<ArduinoLibDescription*>*                  localLibs   =   libManager.localLibs();
    QList<TraversedFileInfo>                        files;
    QHash<QString , ArduinoLibDescription*>         headerMapping;
    QList<TraversedFileInfo>                        internalHeaderAndSources;
    QList<ArduinoLibDescription*>                   dependencies;
    QStringList                                     localHeaderNames;

    foreach (ArduinoLibDescription* desc , *localLibs) {
        QStringList headers = desc->headerNames();

        //Headerler map ediliyor
        foreach (QString header, headers) {
            headerMapping[header] = desc;
        }
    }

    //Headerler ve cppler ekleniyor
    extractHeaderAndSources(rootPath , internalHeaderAndSources , localHeaderNames);

    for (int i = 0; i < internalHeaderAndSources.length(); ++i) {
        TraversedFileInfo   sourceFile = internalHeaderAndSources.at(i);
        QFile       f(sourceFile.info().filePath());

        //Eger dosya acilamadiysa pas geciliyor
        if(!f.open(QIODevice::ReadOnly)){
            continue;
        }

        //Dosya icerigi okunuyor
        QTextStream     textStream(&f);
        QString     content = textStream.readAll();

        //Dosya icinde #include <headerName> ifadesi araniyor
        QString     includeExpression   =   "#include((\\s)*)(<|\\\")((\\d|[a-zA-Z]|\\.)+)(h?)(\\>|\\\")";
        QRegularExpression  expr(includeExpression);
        QRegularExpressionMatchIterator it = expr.globalMatch(content);

        //Eslesmeler okunuyor
        while(it.hasNext()){
            QRegularExpressionMatch match = it.next();
            QRegularExpression      bracketMatch("<|\\\"");
            QString includeStatement = match.captured(0);
            int headerStart = bracketMatch.match(includeStatement).capturedEnd(0);
            QStringRef  headerRef(&includeStatement , headerStart , includeStatement.length() - headerStart -1);
            QString headerName = headerRef.toString();

            //Eger .h olmadan yazilmissa ekleniyor
            if(!headerName.contains(".h"))
                headerName.append(".h");

            //Headerin projede olup olmadigi kontrol ediliyor
            bool included = localHeaderNames.contains(headerName);

            //Eger ki header mevcutsa pas geciliyor
            if(included)
                continue;

            //Header mevcut degilse kutuphanelerde araniyor
            bool found = headerMapping.keys().contains(headerName);

            //Kutuphanelerde bulunursa dependencylere ekleniyor
            if(found){
                ArduinoLibDescription* desc = headerMapping[headerName];
                ArduinoLibDescription* copiedDesc = new  ArduinoLibDescription(*desc);
                QString     libDir = copiedDesc->localDir();
                copiedDesc->setParent(this);

                //Bagimliliklara ekleniyor
                dependencies.append(copiedDesc);

                //Eklenen kutuphane lokal olarak goruluyor
                extractHeaderAndSources(libDir , internalHeaderAndSources , localHeaderNames);
                qDebug() << "L -> " << internalHeaderAndSources.length();
            }
        }
    }

    return dependencies;
}

void Toolchain::extractHeaderAndSources(QString &rootDir, QList<TraversedFileInfo> &files , QStringList &headerNames){
    FileTraverse    traverse;

    QList<TraversedFileInfo> traversedFiles = traverse.traverseRecursively(rootDir);

    foreach(TraversedFileInfo file , traversedFiles){
        QFileInfo   info    =  file.info();
        bool    isHeader = info.fileName().endsWith(".h");
        bool    isSource = info.fileName().endsWith(".cpp");

        //Header vea source ise kontrol edilecekler arasina ekleniyor
        if(isHeader || isSource)
            files.append(file);

        //Eger headers local header koleksiyonune ekleniyor
        if(isHeader)
            headerNames.append(file.info().fileName());
    }
}

//Implemente edilmedi, yarim su anda
QStringList Toolchain::compileLib(QString rootDir, QString outputDir){
    FileTraverse                    traverser;
    QList<TraversedFileInfo>        files           =   traverser.traverseRecursively(rootDir);
    QList<ArduinoLibDescription*>   dependencies    =   specifyLibraryDependencies(rootDir);
    AvrToolchainEnvironment         env;
    QStringList                     includes;

    //Arduino kutuphaneleri ekleniyor
    includes << rootDir <<env.coreLibs() << env.standardVariants();

    //Kutuphaneler ekleniyor
    foreach (ArduinoLibDescription* lib, dependencies) {
        QString     includePath = lib->srcDir();
        includes << includePath;
    }

    //cpp dosyalari derleniyor
    foreach (TraversedFileInfo file, files) {
        if(file.info().fileName().endsWith(".cpp")){
            QString     inputFPath = file.info().filePath();
            QString     outputFPath = QString(outputDir).append(file.info().fileName()).append(".o");

            //Cpp dosyasi derleniyor
            _compiler->compileCppFile(inputFPath , outputFPath , includes);
        }
    }

    return QStringList();
}
