#include "projecttraverse.h"
#include <QDir>
#include <QtQml>

void ProjectTraverse::registerQmlType(){
    qmlRegisterType<ProjectTraverse>("Kodlio", 1, 0, "ProjectTraverse");
}

ProjectTraverse::ProjectTraverse(QQuickItem *parent) : QQuickItem(parent){

}

QVariantMap    ProjectTraverse::readProjects(QString dirPath , QString filterPattern){
    QDir    currDir(dirPath);

    QStringList l = currDir.entryList(QDir::Files);
    if(l.contains("sketch.cpp") || l.indexOf("^.+\.ino$") != -1){
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
