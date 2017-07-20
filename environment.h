#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QVariant>
#include <QQuickItem>

class Environment : public QQuickItem
{

    Q_OBJECT

public:


    Environment(QQuickItem *parent = Q_NULLPTR);

public slots:

    bool            isAssigned(QString key);
    void            set(QString key , QString value);
    QString         get(QString key , bool ensureExists = false);
    QString         appStartDir();
    QString         toolsDir();
    QString         sdkDir();

protected   :

    QHash<QString , QString>         _map;

};

#endif // ENVIRONMENT_H
