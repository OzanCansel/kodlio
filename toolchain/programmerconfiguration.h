#ifndef PROGRAMMERCONFIGURATION_H
#define PROGRAMMERCONFIGURATION_H

#include <QString>
#include <QQuickItem>

class ProgrammerConfiguration : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)

public:

    static void     registerQmlType();
    ProgrammerConfiguration(QQuickItem *parent = Q_NULLPTR);

    QString     getAvrdudeParameters();
    void        setPortName(QString val);
    QString     portName();

signals:

    void        portNameChanged();

private:

    QString     _port;

};

#endif // PROGRAMMERCONFIGURATION_H
