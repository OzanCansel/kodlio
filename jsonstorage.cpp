#include "jsonstorage.h"
#include <QDebug>

JsonStorage::JsonStorage(QString file , QObject *parent) : QObject(parent)
{
    _file = file;
}

JsonStorage::JsonStorage(QObject *parent) : QObject(parent){

}

void JsonStorage::setFile(QString fileName){
    _file = fileName;
}

bool JsonStorage::load(){
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

bool JsonStorage::save(){

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

void JsonStorage::set(QString key, QVariant variant){
    _map[key] = variant;
}

QVariant JsonStorage::get(QString key){
    return  _map[key];
}

