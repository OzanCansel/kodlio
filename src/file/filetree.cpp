#include "filetree.h"
#include "file/fileinfo.h"
#include <QtQml>

void FileTree::registerQmlType(){
    qmlRegisterType<FileTree>("Kodlio" , 1 , 0 , "FileTree");
}

FileTree::FileTree(QQuickItem *parent) : QQuickItem(parent){
    _model.setRootPath("/");
}

QModelIndex FileTree::rootIndex(){
    //Bos index donduruluyor
    if(_rootPath.isEmpty())
        return QModelIndex();

    QModelIndex index = _model.index(_rootPath);
    return index;
}

QFileSystemModel* FileTree::model(){
    return &_model;
}

QString FileTree::rootPath(){
    return _rootPath;
}

void FileTree::setRootPath(QString path){
    if(path.isEmpty())
        return;

    _rootPath = path;

    emit rootPathChanged();
    emit rootIndexChanged();
}

QString FileTree::fileName(QModelIndex idx) {
    QFileInfo   info    =   _model.fileInfo(idx);

    return info.filePath();
}
