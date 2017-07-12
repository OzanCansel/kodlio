#include "avrtoolchain.h"
#include "parse/includedheaders.h"
#include "traverse/filetraverse.h"
#include "exception/boardnotspecified.h"
#include "file/fileutil.h"
#include <QDir>

AvrToolchain::AvrToolchain(QQuickItem *parent) : ToolchainV2(parent)    {

}


void AvrToolchain::run(RunOptions *options) {

}

void AvrToolchain::compile(QString folder, CompileOptions *opts)    {
    FileTraverse traverser;
    QList<TraversedFileInfo> fInfo = traverser.traverseRecursively(folder);
    QList<ArduinoLibDescription *>  projectLibDependencies;
    QVariant    buildDirVariant = opts->get("buildDir");
    QString     buildDir;
    QVariant    board = opts->get("board");
    QString     boardName;

    //Eger board secilmemisse
    if(board.isNull()){
        //Hata firlatiliyor
        BoardNotSpecified("AvrToolchain::compile board secilmemis").raise();
    }else{
        boardName = board.toString();
    }

    //Eger build folder belirtilmemisse
    if(buildDirVariant.isNull()){
        QDir srcDir(folder);
        QString buildDirName = srcDir.dirName().append("-derleme");
        srcDir.cdUp();

        if(!srcDir.exists(buildDirName)){
            srcDir.mkdir(buildDirName);
        }

        //Build klasorune giriliyor
        srcDir.cd(buildDirName);
        buildDir =   srcDir.absolutePath();
    }else{
        buildDir = buildDirVariant.toString();
    }

    foreach (TraversedFileInfo traversedFile, fInfo) {
        QFileInfo   fInfo = traversedFile.info();
        if(fInfo.fileName().endsWith(".h") || fInfo.fileName().endsWith(".cpp")){
            QString fPath= fInfo.filePath();
            QList<ArduinoLibDescription*>   dependencies;

            extractDependencies(fPath , dependencies);
            mergeDependencies(projectLibDependencies , dependencies);

            QStringList includes;
            QString     objOutPath = QString("%0/%1.o").arg(buildDir).arg(fInfo.fileName());
            QString     inputFilePath = fInfo.filePath();

            foreach (ArduinoLibDescription* dependency, dependencies) {
                includes = dependency->headerFolders();
            }

            _compiler.generateObjFile(inputFilePath , objOutPath , includes , boardName);
        }
    }
}


CompilerV2*    AvrToolchain::compiler(){
    return &_compiler;
}

void AvrToolchain::extractDependencies(QString file , QList<ArduinoLibDescription*> &libs){
    IncludedHeaders headerParser;

    QString     fileContent = FileUtil::readContent(file);
    QStringList headers = headerParser.retrieveHeaders(fileContent);

    foreach (QString header, headers) {
        bool    headerExists = _headerToLibMap.keys().contains(header);
        bool    libExists   = headerExists && libs.contains(_headerToLibMap.value(header));

        ArduinoLibDescription   *lib;
        //Eger header kutuphanelerde mevcut ve kutuphane daha onceden eklenmediyse
        if(headerExists && !libExists){
            libs.append(lib);

            //Kutuphanenin bagimliklari da kontrol ediliyor
            foreach (QString headerFile, lib->headerPaths()) {
                extractDependencies(headerFile , libs);
            }
        }
    }
}

void AvrToolchain::map(){
    _libManager.retrieveLocalLibraries();

    QList<ArduinoLibDescription*>   libs = _libManager.getLocalLibs();

    foreach (ArduinoLibDescription *libDesc, libs) {
        foreach (QString headerName, libDesc->headerPaths()) {
            _headerToLibMap[headerName] = libDesc;
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
