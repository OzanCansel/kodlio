#ifndef SERIALOPTIONS_H
#define SERIALOPTIONS_H

#include "options.h"
#include <QQuickItem>

class SerialOptions : public Options
{

    Q_OBJECT
    Q_PROPERTY(QString baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)

public:

    static void registerQmlType();
    SerialOptions(QQuickItem *parent = Q_NULLPTR);
    QString     baudRate() const;
    QString     portName() const;
    void        setBaudRate(QString val);
    void        setPortName(QString val);

signals:

    void        baudRateChanged();
    void        portNameChanged();

};

#endif // SERIALOPTIONS_H
