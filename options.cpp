#include "options.h"
#include "exception/optionkeynotexists.h"
#include <QJsonObject>
#include <QJsonDocument>

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

QVariant Options::get(QString key, bool ensureExists) const{
    if(ensureExists && !_map.keys().contains(key))
        OptionKeyNotExists(key).raise();

    return _map.value(key);
}

bool Options::load(){
    QFile   file(_file);

    if(!file.exists()){
        qDebug() << _file <<" mevcut değil.";

        return false;
    }

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << _file << " açılamıyor.";

        return false;
    }

    QTextStream ss(&file);

    QJsonObject   jObj =     QJsonDocument::fromJson(ss.readAll().toLatin1()).object();

    foreach (QString key, jObj.keys()) {
        _map[key] =  jObj[key].toVariant();
    }

    return true;
}

bool Options::save(){

    if(_file.isEmpty())
        return false;

    QJsonDocument   doc(QJsonObject::fromVariantHash(_map));
    QFile           file(_file);

    if(!file.open(QIODevice::WriteOnly)){
        qDebug() << "Dosya açılamıyor hata!";

        return false;
    }

    QTextStream ss(&file);

    ss << doc.toJson(QJsonDocument::Compact);

    file.close();

    return true;
}

void Options::setFile(QString val){
    _file = val;
}

QString Options::file(){
    return _file;
}
