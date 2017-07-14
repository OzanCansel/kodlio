#include "avrrunoptions.h"
#include <QtQml>

void AvrRunOptions::registerQmlType(){
    qmlRegisterType<AvrRunOptions>("Kodlio" , 1 , 0 , "AvrRunOptions");
}

AvrRunOptions::AvrRunOptions(QQuickItem* parent) : RunOptions(parent)  {

}

void AvrRunOptions::setBoard(QString val){
    set("board" , val);

    emit boardChanged();
}

void AvrRunOptions::setPort(QString val){
    set("port" , val);

    emit portChanged();
}

void AvrRunOptions::setHexFile(QString val){
    set("file" , val);

    emit hexFileChanged();
}

QString AvrRunOptions::board(){
    return get("board").toString();
}

QString AvrRunOptions::port(){
    return get("port").toString();
}

QString AvrRunOptions::hexFile(){
    return  get("file").toString();
}
