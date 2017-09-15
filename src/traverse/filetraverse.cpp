#include "filetraverse.h"
#include <QDir>

FileTraverse::FileTraverse(QQuickItem *parent) : QQuickItem(parent)
{

}

QList<TraversedFileInfo>    FileTraverse::traverseRecursively(QString folder , int depth){
    QDir    currDir(folder);
    QList<TraversedFileInfo>    traversedFiles;

    traversedFiles.append(TraversedFileInfo(QFileInfo(folder) , depth));

    QFileInfoList   infos   =   currDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot );

    foreach (QFileInfo info, infos) {
        //Klasorse fonksiyon tekrar cagiriliyor
        if(info.isDir()){
            traversedFiles.append(traverseRecursively(info.filePath() , depth + 1));
        }else{
            traversedFiles.append(TraversedFileInfo(info , depth));
        }
    }

    return traversedFiles;
}
