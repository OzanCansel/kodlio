#include "projecttraverse.h"
#include <QDir>
#include <QtQml>

void ProjectTraverse::registerQmlType(){
    qmlRegisterType<ProjectTraverse>("Roboskop", 1, 0, "ProjectTraverse");
}

ProjectTraverse::ProjectTraverse(QQuickItem *parent) : QQuickItem(parent){

}

QVariantMap    ProjectTraverse::readProjects(QString dirPath , QString filterPattern){
    QDir    currDir(dirPath);

    if(currDir.entryList(QDir::Files).contains("sketch.cpp")){
        QVariantMap variant;

        variant["name"]         =   QVariant(currDir.dirName());
        variant["path"]         =   QVariant(currDir.absolutePath());
        variant["isCategory"]   =   QVariant(false);

        return variant;
    }

    QVariantMap    variant;
    variant["isCategory"]   =   QVariant(true);

    foreach (QString nestedFolder, currDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        variant[nestedFolder] = readProjects(currDir.filePath(nestedFolder) , filterPattern);
    }

    return variant;
}
