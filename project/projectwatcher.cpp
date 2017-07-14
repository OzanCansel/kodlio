#include "projectwatcher.h"
#include <QtQml>

void ProjectWatcher::registerQmlType(){
    qmlRegisterType<ProjectWatcher>("Kodlio" , 1 , 0 , "ProjectWatcher");
}

ProjectWatcher::ProjectWatcher(QQuickItem *parent) : QQuickItem(parent)
{

}

void ProjectWatcher::setRootDir(QString dir){

    _rootDir = dir;

    _watcher.addPath(rootDir());

    emit rootDirChanged();
}

QString ProjectWatcher::rootDir(){
    return _rootDir;
}
