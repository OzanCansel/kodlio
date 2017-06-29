#ifndef OSINFO_H
#define OSINFO_H

#include <QString>
#include <QQuickItem>

class OsInfo : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString os READ os NOTIFY osChanged)

public:

    static QString  osName();
    QString     os();

signals:

    void    osChanged();

};

#endif // OSINFO_H
