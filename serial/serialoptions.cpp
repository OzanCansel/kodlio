#include "serialoptions.h"
#include "osinfo.h"
#include <QtQml>

void SerialOptions::registerQmlType(){
    qmlRegisterType<SerialOptions>("Kodlio" , 1 , 0 , "SerialOptions");
}

SerialOptions::SerialOptions(QQuickItem *parent) : Options(parent)
{   }

QString SerialOptions::baudRate() const{
    return get("baudRate").toString();
}

QString SerialOptions::portName() const{
    return get("portName").toString();
}

void SerialOptions::setBaudRate(QString val){
    set("baudRate" , QVariant(val));
    emit baudRateChanged();
}

void SerialOptions::setPortName(QString val){

    if(OsInfo::isLinux() && !val.isEmpty() && !val.contains("/dev/"))
        val = QString("/dev/%0").arg(val);

    set("portName" , QVariant(val));

    emit portNameChanged();
}
