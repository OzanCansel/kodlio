#include "arduinolibrarytraverse.h"

ArduinoLibraryTraverse::ArduinoLibraryTraverse(QQuickItem *parent) : FileTraverse(parent)
{

}

void ArduinoLibraryTraverse::setWorkingDir(QString dir){
    _dir = dir;
}

QList<ArduinoLibDescription*> ArduinoLibraryTraverse::retrieveLibraries(){
    QList<ArduinoLibDescription*>   descriptions;

    QList<TraversedFileInfo>    files = traverseRecursively(_dir);

    foreach (TraversedFileInfo file, files) {
        if(file.info().fileName() == "library.properties"){
            ArduinoLibDescription   *desc = new ArduinoLibDescription(this);
            QString     fPath = file.info().filePath();
            desc->deserialize(fPath);
            descriptions.append(desc);
        }
    }

    return descriptions;
}
