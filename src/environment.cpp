#include "environment.h"
#include <QCoreApplication>
#include "exception/environmentvariablenotset.h"

void Environment::registerQmlType(){
    qmlRegisterType<Environment>("Kodlio" , 1 , 0 , "Environment");
}

Environment::Environment(QQuickItem *parent) : QQuickItem(parent)   {
    set("appStartDir" , QCoreApplication::applicationDirPath());
    set("toolsDir" , appStartDir().append("/tools"));
    set("sdkDir" , appStartDir().append("/sdk"));
}

QString    Environment::get(QString key , bool ensureExists){

    //Mevcut olup olmadigi kontrol ediliyor
    if(ensureExists && !isAssigned(key))
        EnvironmentVariableNotSet(key).raise();

    return _map[key];
}

void    Environment::set(QString key, QString value){
    _map[key]= value;
}

bool Environment::isAssigned(QString key){
    return _map.keys().contains(key);
}

QString Environment::appStartDir(){
    return get("appStartDir" , true);
}

QString Environment::toolsDir(){
    return get("toolsDir" , true);
}

QString Environment::sdkDir(){
    return  get("sdkDir" , true);
}
