#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include <QString>
#include <QObject>
#include <QVariant>
#include <QHash>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QTextStream>

class JsonStorage : public QObject
{

public:

    JsonStorage(QString file , QObject *parent = Q_NULLPTR);
    JsonStorage(QObject *parent = Q_NULLPTR);

    void            set(QString key , QVariant variant);
    void            setFile(QString fileName);
    QVariant        get(QString key);
    bool            load();
    bool            save();

private:

    QVariantHash                _map;
    QString                     _file;

};

#endif // JSONSTORAGE_H
