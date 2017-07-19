#include "file.h"
#include <QFile>

void File::registerQmlType(){
    qmlRegisterType<File>("Kodlio" , 1 , 0 , "File");
}

File::File(QQuickItem *parent) : QQuickItem(parent)
{

}

bool File::createFile(QString path){
    QFile   f(path);

    return f.open(QIODevice::ReadWrite);
}

bool File::removeFile(QString path){
    QFile   f(path);

    return f.remove();
}
