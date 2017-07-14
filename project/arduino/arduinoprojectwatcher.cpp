#include "arduinoprojectwatcher.h"
#include "file/fileutil.h"
#include "parse/functionparser.h"
#include "traverse/filetraverse.h"
#include <QtQml>

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

//    QStringList projFiles = _watcher.files();
//    FunctionParser  fParser;

//    foreach (QString fileName, projFiles) {
//        QString content =   FileUtil::readContent(fileName);
//        QString signature = "void";
//        QString setupF = "setup";
//        QString loopF = "loop";
//        bool setupFExists = fParser.functionExists(content , signature , setupF);
//        bool loopFExists = fParser.functionExists(content , signature , loopF);

//        if(setupFExists && loopFExists){
//            return fileName;
//        }
//    }

    return "sketch.cpp";
}
