#include "environment.h"
#include <QCoreApplication>

Environment::Environment(QQuickItem *parent) : QQuickItem(parent)   {
    set("appStartDir" , QCoreApplication::applicationDirPath());
    set("toolsDir" , get("appStartDir").append("/tools"));
}

QString    Environment::get(QString key){
    return _map[key];
}

void    Environment::set(QString key, QString value){
    _map[key]= value;
}

bool Environment::isAssigned(QString key){
    return _map.keys().contains(key);
}
