#include "projectwatcher.h"

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
