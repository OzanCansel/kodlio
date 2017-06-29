#include "projectmanager.h"
#include "toolchain/unocompiler.h"
#include "texttemplate/classcpptemplate.h"
#include "texttemplate/classheadertemplate.h"
#include "settings/editorsettings.h"

ProjectManager::ProjectManager(DirectoryManager *man, Toolchain *toolchain , QQuickItem *parent) : QQuickItem(parent)
{
    _directoryManager   =   man;
    _toolchain          =   toolchain;
    _compiler           =   new UnoCompiler();
    _model              =   new QFileSystemModel();
    _readOnly           =   false;


    _compiler->setDebugEnabled(true);
    _compiler->setErrorOutputEnabled(true);
    _compiler->setStandardOutputEnabled(true);

    _compileWorker = new CompileWorkerV2(_toolchain);
    _uploadWorker = new CompileAndUploadWorkerV2(_toolchain);
    _compileWorker ->moveToThread(&compilingThread);
    _uploadWorker->moveToThread(&uploadThread);

    connect(this , SIGNAL(compileProjectSignal(QString,QString,QStringList)) , _compileWorker , SLOT(doWork(QString,QString,QStringList)));
    connect(this , SIGNAL(compileAndUploadProjectSignal(QString,QString)) , _uploadWorker , SLOT(doWork(QString,QString)));

    compilingThread.start();
    uploadThread.start();

    //Değişkenlere default değerleri atanıyor
    _document       =   Q_NULLPTR;

    QString dir = _directoryManager->createTempDirectory();

    createProject(dir);
    openProject(dir);
}

ProjectManager::~ProjectManager(){
    compilingThread.quit();
    compilingThread.wait();
    uploadThread.quit();
    uploadThread.wait();
}

bool ProjectManager::createProject(QString dirPath){
    bool success = _directoryManager->createProject(dirPath);

    if(!success)
        qDebug() << " Proje yaratılamadı. ";

    return success;
}

bool ProjectManager::createProject(QString dirPath , QString content){
    bool success = _directoryManager->createProject(dirPath , content);

    if(!success)
        qDebug() << " Proje yaratılamadı. ";

    return success;
}

QString ProjectManager::createProject(QString projName , QString folderPath , QString content){
    QString     completePath = QDir(folderPath).filePath(projName);
    qDebug() << "Complete path -> " <<  completePath;
    bool success = _directoryManager->createProject(completePath);

    return completePath;
}

bool ProjectManager::openProject(QString dirPath){

    bool isValid = _directoryManager->isProjectDirectory(dirPath);

    if(!isValid)
        return false;

    _directoryManager->setWorkingDirectory(dirPath);
    _model->setRootPath(dirPath);
    _projectBuildDir.clear();

    QString     mainFileContent = _directoryManager->mainFileContent();
    setProjectName(_directoryManager->projectName(dirPath));

    emit projectOpened();
    emit rootIndexChanged();

    if(_document != Q_NULLPTR){
        _document->textDocument()->setPlainText(mainFileContent);
    }

    return true;
}

void ProjectManager::compileProject(QString buildFolder){

    QString rootDir = _directoryManager->workingDirectory();

    if(buildFolder.isEmpty()){
        QDir buildDir(rootDir);
        buildDir.cdUp();

        buildFolder = buildDir.filePath(QString("build-").append(projectName()));
        buildDir.mkpath(buildFolder);
        _projectBuildDir    =   buildFolder;
    }

    emit compileProjectSignal(rootDir , buildFolder , QStringList());
}

void ProjectManager::compileAndUploadProject(QString buildFolder){

    QString rootDir = _directoryManager->workingDirectory();

    if(buildFolder.isEmpty()){
        buildFolder = getDefaultBuildPath(rootDir);
    }

    emit compileAndUploadProjectSignal(rootDir , buildFolder);
}

void ProjectManager::setProjectName(QString name){
    _projectName = name;

    emit projectNameChanged();
}

QString ProjectManager::projectName(){
    return _projectName;
}

bool ProjectManager::compilerOutputEnabled(){
    return _compiler->standardOutputEnabled();
}

bool ProjectManager::compilerErrorOutputEnabled(){
    return _compiler->errorOutputEnabled();
}

void ProjectManager::setCompilerOutputEnabled(bool val){
    _compiler->setStandardOutputEnabled(val);

    emit compilerOutputEnabledChanged();
}

void ProjectManager::setCompilerErrorOutputEnabled(bool val){
    _compiler->setErrorOutputEnabled(val);

    emit compilerErrorOutputEnabledChanged();
}

QQuickTextDocument* ProjectManager::document(){
    return _document;
}

void ProjectManager::setDocument(QQuickTextDocument *doc){

    _document = doc;

    _highlighter.setDocument(_document->textDocument());

    _document->textDocument()->setPlainText(_directoryManager->mainFileContent());
    _document->textDocument()->setModified(false);
//    QTextOption opt = _document->textDocument()->defaultTextOption();
//    opt.setTabStop(EditorSettings::getInstance()->tabSize() * 10);
//    _document->textDocument()->setDefaultTextOption(opt);
//    qDebug() << " Tab Stop ";

    connect(_document->textDocument(), SIGNAL(modificationChanged(bool)) , this , SLOT(onModificationChanged(bool)));
}

void ProjectManager::onModificationChanged(bool val){
    emit modifiedChanged();
}

void ProjectManager::saveFile(){

    _directoryManager->save(_document->textDocument()->toPlainText());
    _document->textDocument()->setModified(false);
}

bool ProjectManager::modified(){
    if(_document != NULL)
        return _document->textDocument()->isModified();
    else
        return false;
}

void ProjectManager::setDirManager(DirectoryManager *dir){
    _directoryManager = dir;
}

void ProjectManager::setEditorText(QString str){
    _document->textDocument()->setPlainText(str);
}

QString ProjectManager::createNewClass(QString className, QString relativePath){
    QDir dir(_directoryManager->workingDirectory());

    dir.mkpath(relativePath);
    dir.cd(relativePath);

    QString cppFilePath     =   dir.filePath(className).append(".cpp");
    QString headerFilePath  =   dir.filePath(className).append(".h");

    ClassHeaderTemplate headerTemplate;
    ClassCppTemplate    cppTemplate;
    headerTemplate.setClassName(className);
    cppTemplate.setClassName(className);

    _directoryManager->createFile(cppFilePath , cppTemplate.extract());
    _directoryManager->createFile(headerFilePath , headerTemplate.extract());

    return QString();
}

QFileSystemModel*    ProjectManager::projectFsModel(){
    return _model;
}

QModelIndex ProjectManager::rootIndex(){
    return _model->index(_directoryManager->workingDirectory());
}

QString ProjectManager::getDefaultBuildPath(QString path){
    QDir buildDir(path);
    buildDir.cdUp();

    QString buildFolder = buildDir.filePath(QString("build-").append(projectName()));
    buildDir.mkpath(buildFolder);

    return buildFolder;
}

bool ProjectManager::projectExists(QString path){
    return QFile(QDir(path).filePath("sketch.cpp")).exists();
}

void ProjectManager::writeProj(QVariantList l){

    //Klasörler oluşturuluyor
    foreach (QVariant variant, l) {
        QVariantMap fileInf = variant.toMap();

        if(fileInf["isFile"].toBool())
            continue;
        QString folderPath = _directoryManager->workingDirectory().append(fileInf["rPath"].toString());
        QDir(_directoryManager->workingDirectory()).mkpath(folderPath);
    }

    //Dosyalar yazılıyor
    foreach (QVariant variant, l) {
        QVariantMap fileInf = variant.toMap();

        if(!fileInf["isFile"].toBool())
            continue;

        QString rootPath = _directoryManager->workingDirectory();
        QFile   fPath(QString(rootPath).append(fileInf["rPath"].toString()));

        if(!fPath.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
            qDebug() << fPath.fileName() << " dosya açılamıyor.";
            return;
        }

        QTextStream stream(&fPath);

        stream << fileInf["content"].toString();

        fPath.close();
    }
}

void ProjectManager::refresh(){
    setEditorText(_directoryManager->mainFileContent());
}

bool ProjectManager::readOnly(){
    return  _readOnly;
}
void ProjectManager::setReadOnly(bool val){
    _readOnly = val;
    emit readOnlyChanged();
}
