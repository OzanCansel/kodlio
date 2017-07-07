#include "filetree.h"
#include <QtQml>

void FileTree::registerQmlType(){
    qmlRegisterType<FileTree>("Kodlio" , 1 , 0 , "FileTree");
}

FileTree::FileTree(QQuickItem *parent) : QQuickItem(parent){

}

QModelIndex FileTree::rootIndex(){
    //Bos index donduruluyor
    if(_rootPath.isEmpty())
        return QModelIndex();

    return _model.index(_rootPath);
}

QFileSystemModel* FileTree::model(){
    return &_model;
}

QString FileTree::rootPath(){
    return _rootPath;
}

void FileTree::setRootPath(QString path){
    _rootPath = path;
    _model.setRootPath(path);
    emit rootPathChanged();
    emit rootIndexChanged();
    emit modelChanged();
}


QString FileTree::fileName(QModelIndex idx){
    QFileInfo   info    =   _model.fileInfo(idx);

    if(info.isFile())
        return info.filePath();
    else
        return QString();
}
