#include "arduinoprojectwatcher.h"
#include "file/fileutil.h"
#include "parse/functionparser.h"
#include "traverse/filetraverse.h"
#include <QtQml>
#include <QDir>

void ArduinoProjectWatcher::registerQmlType(){
    qmlRegisterType<ArduinoProjectWatcher>("Kodlio" , 1 , 0 , "ArduinoProjectWatcher");
}

ArduinoProjectWatcher::ArduinoProjectWatcher(QQuickItem *parent) : ProjectWatcher(parent)
{

}

QString ArduinoProjectWatcher::retrieveMainFile(){

    //Eger sketch.cpp dosyasi varsa main file olarak belirtiliyor
    if(QDir(rootDir()).exists("sketch.cpp")){
        return QDir(rootDir()).filePath("sketch.cpp");
    }

    foreach(QString file , QDir(rootDir()).entryList(QDir::Files)){
        if(file.endsWith(".ino"))
            return QDir(rootDir()).filePath(file);
    }

    return "sketch.cpp";
}
