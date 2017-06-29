#include "directorymanager.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QStringRef>
#include "exception/invalidprojectdirectory.h"
#include "exception/workingdirectorynotset.h"
#include "exception/tempdirectorycreationfailed.h"

DirectoryManager::DirectoryManager()
{

}

bool DirectoryManager::isProjectDirectory(QString dir){
    QDir projDir(dir);

    bool exist = projDir.exists();

    //Eğer dizin mevcut değilse false döndürülüyor
    if(!exist)
        return false;

    QStringList list = projDir.entryList(QStringList() << "*.cpp");

    if(list.contains("sketch.cpp"))
        return true;

    return false;
}

bool DirectoryManager::createProject(QString dir){
    QDir    projectDir;

    bool    mkSuccess = projectDir.mkpath(dir);

    //Dizin oluşturulamadıysa false döndürülüyor
    if(!mkSuccess)
        return false;

    projectDir.cd(dir);

    QString sketchPath = projectDir.absolutePath().append("/sketch.cpp");

    QFile   sketchFile(sketchPath);

    //Eğer dosya açılamadıysa false döndürülüyor
    if(!sketchFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }

    QTextStream     stream(&sketchFile);

    QString temp;

    temp.append("// Roboskop - ")
            .append(QDateTime::currentDateTime().toString("dd MMM yyyy hh:mm:ss "))
            .append("\n\n")
            .append("#include <Arduino.h>\n\n")
            .append("void setup();\n")
            .append("void loop();\n\n\n")
            .append("void setup()\n")
            .append("{\n\n}\n\n")
            .append("void loop()\n")
            .append("{\n\n}\n");

    stream << temp;

    sketchFile.close();

    return true;
}

bool DirectoryManager::createProject(QString dir , QString content){
    QDir    projectDir;
    bool    mkSuccess = projectDir.mkpath(dir);

    //Dizin oluşturulamadıysa false döndürülüyor
    if(!mkSuccess)
        return false;
    projectDir.cd(dir);
    QString sketchPath = projectDir.absolutePath().append(QDir::separator()).append("sketch.cpp");
    QFile   sketchFile(sketchPath);

    //Eğer dosya açılamadıysa false döndürülüyor
    if(!sketchFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }

    QTextStream     stream(&sketchFile);
    stream << content;
    sketchFile.close();
    return true;
}

void DirectoryManager::setWorkingDirectory(QString dir){
    _workingDirectory = dir;

}

QString DirectoryManager::createTempDirectory(){

//    if(_workingDirectory.isNull() || _workingDirectory.isEmpty())
//        throw   WorkingDirectoryNotSet();

    QTemporaryDir   tempDir;
    tempDir.setAutoRemove(false);

    //Eğer ki geçiçi klasör yaratılamadıysa hata döndürülüyor
    if(!tempDir.isValid())
        throw TempDirectoryCreationFailed();

    return tempDir.path();
}

QString DirectoryManager::mainFileContent(){
    QFile       file(QString(_workingDirectory).append("/sketch.cpp"));

    if(!file.open(QIODevice::ReadOnly ))
        return "";

    QTextStream ss(&file);

    QString content = ss.readAll();

    file.close();

    return content;
}

void DirectoryManager::save(QString content){
    QFile       sketchFile(QString(_workingDirectory).append("/sketch.cpp"));

    if(!sketchFile.open(QIODevice::WriteOnly))
        return;

    QTextStream     ss(&sketchFile);

    ss << content;

    sketchFile.close();
}

QString DirectoryManager::workingDirectory(){
    return QString(_workingDirectory);
}

QString DirectoryManager::getMainFileAbsolutePath(){
    return QString(_workingDirectory).append("/sketch.cpp");
}

void DirectoryManager::copy(QString src, QString dst){
    QDir dir(src);

    if (! dir.exists()){
        bool    created = QDir().mkpath(src);

        if(!created)
            return;
    }

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = dst + QDir::separator() + d;
        bool created = QDir().mkpath(dst_path);
        copy(src+ QDir::separator() + d, dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QString sourceFile = src + QDir::separator() + f;
        QString destinationFile = dst + QDir::separator() + f;
        bool copyResult = QFile::copy(sourceFile, destinationFile);
    }
}

QString DirectoryManager::projectName(QString folder){
    bool res = isProjectDirectory(folder);

    if(!res)
        return "";

    folder = folder.trimmed();
    int idx = folder.lastIndexOf("/");

    QString str = folder.right(folder.length() - idx - 1);

    return str;
}

bool DirectoryManager::createFile(QString path, QString content){

    QDir    dir(path);
    dir.cdUp();

    QDir().mkpath(dir.absolutePath());

    QFile   f(path);

    if(!f.open(QIODevice::ReadWrite)){
        qDebug() << "DirectoryManager.createFile(QString path, QString content) -> " << path << " oluşturulamadı.";

        return false;
    }

    QTextStream ss(&f);

    ss << content;

    f.close();

    return true;
}
