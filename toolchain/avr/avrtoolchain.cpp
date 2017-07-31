#include "avrtoolchain.h"
#include "parse/includedheaders.h"
#include "traverse/filetraverse.h"
#include "exception/boardnotspecified.h"
#include "exception/filenotexists.h"
#include "exception/filecouldnotopen.h"
#include "exception/compileerror.h"
#include "file/fileutil.h"
#include "collection/stringlistutil.h"
#include <QDir>
#include <QtQml>

void AvrToolchain::registerQmlType(){
    qmlRegisterType<AvrToolchain>("Kodlio" , 1 , 0 , "AvrToolchain");
}

AvrToolchain::AvrToolchain(QQuickItem *parent) : ToolchainV2(parent)    {
    //    map();
    _compatibleSourceExtensions << ".c" << ".S" << ".cpp";
    _libManager = Q_NULLPTR;
}


void AvrToolchain::run(RunOptions *options) {
    //calistiriliyor
    _runner.run(options);
}

void AvrToolchain::compile(QString file, CompileOptions *opts)    {

    QFileInfo   mainFileInfo(file);
    QVariant    buildDirVariant = opts->get("buildDir");
    QString     buildDirPath;
    QString     libBuildDirPath;
    QString     boardBuildDirPath;
    QVariant    board = opts->get("board");
    QString     boardName;
    QStringList projectSources;
    QString     srcDir = mainFileInfo.absolutePath();
    QList<ArduinoLibDescription*>   projectLibDependencies;
    QStringList                     discovered;
    QStringList                     includes;
    double      progress = 0;

    //Progress baslatiliyor
    sendBuildStarted();
    sendProgress(0);
    setBusy(true); //Toolchain mesgul

    //Eger board secilmemisse
    if(board.isNull()){
        //Hata firlatiliyor

        setBusy(false);
        BoardNotSpecified("AvrToolchain::compile board secilmemis").raise();
    }   else    {
        boardName = board.toString();
    }

    //Eger build folder belirtilmemisse
    if(buildDirVariant.isNull()){
        QDir srcDir(mainFileInfo.absolutePath());
        QString buildDirName = srcDir.dirName().append("-derleme");
        srcDir.cdUp();

        if(!srcDir.exists(buildDirName)){
            srcDir.mkdir(buildDirName);
        }

        //Build klasorune giriliyor
        srcDir.cd(buildDirName);

        if(!srcDir.exists(boardName))
            srcDir.mkdir(boardName);

        buildDirPath =   srcDir.absolutePath();
    }   else   {
        buildDirPath = buildDirVariant.toString();
    }

    boardBuildDirPath = QDir(buildDirPath).filePath(boardName);
    libBuildDirPath = QDir(boardBuildDirPath).filePath("libs");

    //Kullanilmasi gereken kutuphaneler belirleniyor
    extractDependencies(file , projectLibDependencies , discovered);

    foreach (ArduinoLibDescription *desc, projectLibDependencies) {
        QString     output = QString("%0 kütüphanesi kullanılıyor. Dizin : %1").arg(desc->name()).arg(desc->localDir());
        sendInfo(output);

        foreach (QString includeFolder, desc->headerFolders()) {
            if(!includes.contains(includeFolder))
                includes.append(includeFolder);
        }
    }

    //Proje calisma klasoru ekleniyor
    includes.append(srcDir);


    QStringList generatedObjectFiles;
    QStringList arduinoObjectFiles;

    foreach (QString discoveredFile, discovered) {
        //Headersa eselesen source dosyalari araniyor
        if(isSourceFile(discoveredFile) && discoveredFile.contains(srcDir))   {
            projectSources.append(discoveredFile);
        }
    }

    progress += PROGRESS_EXTRACT_DEPENDENCIES;
    sendProgress(progress);

    double  libProgressStep =  PROGRESS_COMPILE_LIB_TOTAL_PORTION / (double)projectLibDependencies.length();
    double  compileProgressStep =   PROGRESS_COMPILE_SOURCE_TOTAL_PORTION / (double) projectSources.length();
    double  archiveProgressstep = PROGRESS_ARCHIVE_TOTAL_PORTION / (double) projectSources.length();

    sendInfo("Kütüphaneler derleniyor...");

    //Kutuphaneler derleniyor
    foreach (ArduinoLibDescription* desc, projectLibDependencies) {
        try {
            QDir    libBuildDir(libBuildDirPath);
            QString libBuildPath = libBuildDir.filePath(desc->name());
            mkpath(libBuildPath);

            //Arduino kutuphaneleri farkli bir koleksiyona ekleniyor
            if(desc->name() == "Arduino")
                compileLib(desc , libBuildPath , boardName ,arduinoObjectFiles);
            else
                compileLib(desc , libBuildPath , boardName , generatedObjectFiles);

            progress += libProgressStep;
            sendProgress(progress);
        }catch(CompileError &err){
            sendStdError("");
            sendCompileError();
            sendProgress(-1);
            setBusy(false);
            return;
        }
    }

    progress = PROGRESS_EXTRACT_DEPENDENCIES + PROGRESS_COMPILE_LIB_TOTAL_PORTION;
    sendProgress(progress);

    sendInfo("Dosyalar derleniyor");
    foreach (QString sourceFile, projectSources) {

        QFileInfo   sourceInfo(sourceFile);

        sendInfo(QString("%0 derleniyor").arg(QDir(srcDir).relativeFilePath(sourceInfo.filePath())));
        //<boardBuildDir>/<fileName>.o
        QString     output = QString("%0/%1.o").arg(boardBuildDirPath).arg(sourceInfo.fileName());

        try{
            _compiler.generateObjFile(sourceFile , output , includes , boardName);
            generatedObjectFiles.append(output);
            progress += compileProgressStep;
            sendProgress(progress);
        } catch (CompileError &err){
            sendStdError(err.err());
            sendCompileError();
            sendProgress(-1);
            setBusy(false);
            return;
        }
    }

    progress = PROGRESS_EXTRACT_DEPENDENCIES + PROGRESS_COMPILE_LIB_TOTAL_PORTION + PROGRESS_COMPILE_SOURCE_TOTAL_PORTION;
    sendProgress(progress);

    //Arsivleme asamasina geciliyor
    QDir    boardBuildDir(boardBuildDirPath);
    QString archivedLibPath = boardBuildDir.filePath("archive.a");
    QStringList l;

    sendInfo("Arşivleniyor...");

    try {
        _compiler.archiveFiles(arduinoObjectFiles , archivedLibPath);
        progress += archiveProgressstep;
        sendProgress(progress);
    }   catch(CompileError&)    {
        sendStdError("Kütüphaneler arşivlenirken hata oluştu.");
        sendCompileError();
        setBusy(false);
        return;
    }

    progress = PROGRESS_EXTRACT_DEPENDENCIES + PROGRESS_COMPILE_LIB_TOTAL_PORTION + PROGRESS_COMPILE_SOURCE_TOTAL_PORTION + PROGRESS_ARCHIVE_TOTAL_PORTION;
    sendProgress(progress);

    sendInfo("Hex dosyası üretiliyor...");
    try{
        setCompiledHexFile(_compiler.generateHex(archivedLibPath , boardBuildDirPath , generatedObjectFiles));
    }catch(CompileError& err){
        sendStdError("Hex dosyasi üretilirken hata oluştu.");
        sendStdError(err.err());
        sendCompileError();
        setBusy(false);
        return;
    }

    sendProgress(1);
    sendCompileSuccess();
    setBusy(false);
}

CompilerV2*    AvrToolchain::compiler(){
    return &_compiler;
}

void AvrToolchain::extractDependencies(QString file , QList<ArduinoLibDescription*> &libs , QStringList &discoredFiles){

    //Dosya onceden incelenmisse geri donuluyor
    if(discoredFiles.contains(file)){
        return;
    }
    else    {
        //Incelenen dosyalara ekleniyor
        discoredFiles.append(file);
    }

    IncludedHeaders headerParser;

    QFileInfo   fInfo(file);
    QString     fileContent;

    try {
        fileContent = FileUtil::readContent(file);
    } catch (FileNotExists&){
        return;
    }

    QStringList bracketHeaders = headerParser.retrieveBracketHeaders(fileContent);
    QStringList quotedHeaders = headerParser.retrieveDoubleQuotedHeader(fileContent);

    foreach (QString header, bracketHeaders) {
        bool    headerExists = _headers.contains(header);

        //Header mevcut degilse atlaniyor
        if(!headerExists)
            continue;

        ArduinoLibDescription   *lib = getHeaderMap(header).desc;
        bool libExists = libs.contains(lib);

        if(libExists)
            continue;

        //Eger header kutuphanelerde mevcut ve kutuphane daha onceden eklenmediyse
        libs.append(lib);

        //Kutuphanenin bagimliklari da kontrol ediliyor
        foreach (QString headerFile, lib->headerPaths()) {
            extractDependencies(headerFile , libs , discoredFiles);
        }
    }

    foreach (QString quoted, quotedHeaders) {
        QStringList sources;
        QString cleaned = QDir::cleanPath(QDir(fInfo.absolutePath()).filePath(quoted));
        extractDependencies(cleaned , libs , discoredFiles);
        possibleSourceFiles(cleaned , sources);
        //Header ile eslesen uyumlu kaynak dosyalari derleniyor. (.cpp , .s , .c gibi)
        foreach (QString srcFile, sources) {
            extractDependencies(srcFile , libs , discoredFiles);
        }
    }
}

void AvrToolchain::map(){
    if(_libManager == Q_NULLPTR)
        return

                _headerMaps.clear();
    _headers.clear();
    _libManager->retrieveLocalLibraries();

    QList<ArduinoLibDescription*>   libs = _libManager->getLocalLibs();

    foreach (ArduinoLibDescription *libDesc, libs) {
        foreach (QString headerFPath, libDesc->headerPaths()) {
            QFileInfo   fInfo(headerFPath);

            HeaderMapInfo   info;
            info.headerPath = fInfo.filePath();
            info.headerName = fInfo.fileName();
            info.desc = libDesc;
            _headers.append(fInfo.fileName());

            _headerMaps.append(info);
        }
    }
}

void AvrToolchain::mergeDependencies(QList<ArduinoLibDescription *> &root, QList<ArduinoLibDescription *> &merged){
    foreach (ArduinoLibDescription *lib, merged) {
        //Eger mevcut degilse ekleniyor
        if(!root.contains(lib)){
            root.append(lib);
        }
    }
}

AvrToolchain::HeaderMapInfo   AvrToolchain::getHeaderMap(QString headerName){
    foreach (HeaderMapInfo info, _headerMaps) {
        if(info.headerName == headerName)
            return info;
    }
}

void AvrToolchain::compileLib(ArduinoLibDescription *desc, QString &outputFolder , QString &boardName , QStringList &generatedObjectFiles){

    sendInfo(QString("%0 kütüphanesi derleniyor...").arg(desc->name()));
    FileTraverse    traverser;

    QList<TraversedFileInfo> traversedInfos = traverser.traverseRecursively(desc->srcDir());
    QStringList     includes;
    QStringList     discoveredFiles;
    QList<ArduinoLibDescription *>  dependencies;
    QString         srcDir = desc->srcDir();

    foreach (TraversedFileInfo traversedFile, traversedInfos) {
        QFileInfo   fInfo = traversedFile.info();

        QString filePath = fInfo.filePath();
        if(isSourceFile(filePath) || isHeaderFile(filePath)){
            extractDependencies(fInfo.filePath() , dependencies , discoveredFiles );
        }
    }

    //Include pathler belirleniyor
    foreach (ArduinoLibDescription *lib, dependencies) {
        QStringList headerFolders = lib->headerFolders();
        StringListUtil::merge(includes , headerFolders);
    }

    //Kutuphanenin ana dizini ekleniyor
    includes.append(srcDir);

    QDir    baseDir(desc->srcDir());
    foreach (QString discovered, discoveredFiles) {
        if(isSourceFile(discovered) && discovered.contains(srcDir)){
            QString relativePath = baseDir.relativeFilePath(discovered);
            QString outputFilePath = QDir::cleanPath(QDir(outputFolder).filePath(relativePath));
            QString folder = QFileInfo(outputFilePath).absolutePath();
            mkpath(folder);
            //<outputFolder>/<fileName>
            QString outputPath = QString("%0.o").arg(outputFilePath);
            _compiler.generateObjFile(discovered , outputPath , includes , boardName);
            if(!generatedObjectFiles.contains(outputPath))
                generatedObjectFiles.append(outputPath);
        }
    }
}

bool AvrToolchain::isHeaderFile(QString &fileName){
    return fileName.endsWith(".h");
}

bool AvrToolchain::isSourceFile(QString &fileName){

    foreach (QString extension, _compatibleSourceExtensions) {
        if(fileName.endsWith(extension))
            return true;
    }

    return false;
}

bool AvrToolchain::possibleSourceFiles(QString &headerName , QStringList &sourceFile){

    bool    exists = false;

    foreach (QString extension, _compatibleSourceExtensions) {
        QString file = QString(headerName).replace(".h" , extension);

        if(QFile(file).exists()){
            sourceFile.append(file);

            if(!exists)
                exists = true;
        }
    }

    return exists;
}

QString AvrToolchain::compiledHexFile(){
    return _lastHexFile;
}

void AvrToolchain::setCompiledHexFile(QString path){
    _lastHexFile = path;

    emit compiledHexFileChanged();
}

Runner* AvrToolchain::runner(){
    return &_runner;
}

void AvrToolchain::setLibManager(LibraryManager *libManager){
    _libManager = libManager;
    if(_libManager != Q_NULLPTR){
        connect(_libManager , SIGNAL(libRemovedSuccessfully(ArduinoLibDescription*)) , this , SLOT(librariesChanged(ArduinoLibDescription*)));
        connect(_libManager , SIGNAL(libInstalledSuccessfully(ArduinoLibDescription*)) , this , SLOT(librariesChanged(ArduinoLibDescription*)));
        map();
    }
    emit libManagerChanged();
}

LibraryManager* AvrToolchain::libManager(){
    return _libManager;
}

void AvrToolchain::librariesChanged(ArduinoLibDescription *desc){
    map();
}

QDir AvrToolchain::mkpath(QString path){
    QDir dir(path);
    if(dir.exists())
        return dir;
    else
        dir.mkpath(path);
    return dir;
}
