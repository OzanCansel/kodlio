#include "options.h"

void Options::registerQmlType(){
    qmlRegisterType<Options>("Kodlio" , 1 , 0 , "Options");
}

Options::Options(QQuickItem *parent) : QQuickItem(parent){

}

void Options::set(QString key, QVariantMap val){
    _map[key]   =   val;
}

void Options::set(QString key, QVariant val){
    _map[key]   =   val;
}

QVariant Options::get(QString key){
    return _map.value(key , QVariant());
}
