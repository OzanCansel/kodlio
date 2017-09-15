#include "arduinoprojecttraverse.h"

ArduinoProjectTraverse::ArduinoProjectTraverse(QQuickItem *parent) : FileTraverse(parent)    {

}

void ArduinoProjectTraverse::setRootDir(QString val){
    _rootDir = val;
    _files = traverseRecursively(_rootDir);
    emit rootDirChanged();
}

QString ArduinoProjectTraverse::rootDir(){
    return _rootDir;
}

