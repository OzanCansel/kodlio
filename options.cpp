#include "options.h"

Options::Options(QQuickItem *parent) : QQuickItem(parent){

}

void Options::set(QString key, QVariantMap val){
    _map[key]   =   val;
}

void Options::set(QString key, QVariant val){
    _map[key]   =   val;
}

QVariant Options::get(QString key){
    if(!_map.contains(key))
        return QVariant();

    return _map[key];
}
