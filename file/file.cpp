#include "file.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include "texttemplate/genericfiletemplate.h"

static QObject* singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine){
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    File    *file = new File();
    return file;
}

void File::registerQmlType(){
    qmlRegisterType<File>("Kodlio" , 1 , 0 , "File");
    qmlRegisterSingletonType<File>("Kodlio" , 1 , 0 , "FileSingleton" , singletonProvider);
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

bool File::createGenericTemplatedFile(QString path){
    QFile   f(path);

    if(!f.open(QIODevice::WriteOnly)){
        return false;
    }

    QFileInfo   fInfo(path);
    QTextStream ss(&f);
    GenericFileTemplate genericFileTemplate;
    genericFileTemplate.setFileName(fInfo.fileName());
    ss << genericFileTemplate.extract();

    f.close();
    return true;
}

bool File::createDir(QString root , QString newFolder){
    QDir    dir(root);

    if(!dir.exists() || dir.exists(newFolder)){
        return false;
    }

    return dir.mkdir(newFolder);
}
