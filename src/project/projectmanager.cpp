#include "projectmanager.h"
#include <QDir>

void ProjectManager::registerQmlType(){
    qmlRegisterType<ProjectManager>("Kodlio" , 1 , 0 , "ProjectManager");
}

ProjectManager::ProjectManager(QQuickItem *parent) : QQuickItem(parent)
{

}

void ProjectManager::createProject(ProjectOptions *opts){

}

void ProjectManager::removeProject(ProjectOptions *opts){

}

void ProjectManager::sendProjectCreateError(QString err){
    if(debugEnabled())  qDebug() << "ProjectManager::sendProjectCreateError " << err;
    emit projectCreateError(err);
}

void ProjectManager::sendProjectRemoveError(QString err){
    if(debugEnabled())  qDebug() << "ProjectMAnager::sendProjectRemoveError " << err;
    emit projectRemoveError(err);
}

void ProjectManager::sendProjectCreated(){
    if(debugEnabled())  qDebug() << "Project olusturldu";
    emit projectCreated();
}

void ProjectManager::sendProjectRemoved(){
    if(debugEnabled())  qDebug() << "Projec silindi";
    emit projectRemoved();
}

bool ProjectManager::debugEnabled(){
    return _debugEnabled;
}

void ProjectManager::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

void ProjectManager::setProjectRoot(QString root){
    _projectRoot = root;

    setProjectName(QDir(root).dirName());
    projectOpenedChanged();
    emit projectRootChanged();
}

//Getter
QString ProjectManager::projectRoot(){
    return _projectRoot;
}

QString ProjectManager::projectName(){
    return _projectName;
}

bool ProjectManager::projectOpened(){
    return !_projectRoot.isEmpty();
}

void ProjectManager::setProjectName(QString val){
    _projectName = val;
    emit projectNameChanged();
}

void ProjectManager::openProject(ProjectOptions *opts){
    setProjectRoot(opts->root());
}

void ProjectManager::copyProject(QString from, QString to){
    File    f;

    f.copyDirectoryRecursively(from , to , QStringList() << "*.cpp" << "*.cxx" << "*.cc" << "*.h" << "*.ino" , true);
}
