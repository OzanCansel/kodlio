#include "internetaccessibility.h"
#include <QtQml>

void InternetAccessibility::registerQmlType(){
    qmlRegisterType<InternetAccessibility>("Kodlio" , 1 , 0 , "InternetAccessibility");
}


InternetAccessibility::InternetAccessibility(QQuickItem *parent) : QQuickItem(parent){
    connect(&_man , SIGNAL(onlineStateChanged(bool)) , this , SLOT(internetStatusChanged(bool)));
    setOnline(_man.isOnline());
}

bool InternetAccessibility::online(){
    return _online;
}

//Setter
void InternetAccessibility::setOnline(bool enabled){
    _online = enabled;

    emit onlineChanged();
}

//Slots
void InternetAccessibility::internetStatusChanged(bool enabled){
    setOnline(enabled);
}
