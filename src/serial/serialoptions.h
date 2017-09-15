#ifndef SERIALOPTIONS_H
#define SERIALOPTIONS_H

#include "options.h"
#include <QQuickItem>

class SerialOptions : public Options
{

    Q_OBJECT
    Q_PROPERTY(QString baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(bool uploading READ uploading WRITE setUploading NOTIFY uploadingChanged)

public:

    static void registerQmlType();
    SerialOptions(QQuickItem *parent = Q_NULLPTR);
    QString     baudRate() const;
    QString     portName() const;
    bool        uploading();
    void        setBaudRate(QString val);
    void        setPortName(QString val);
    void        setUploading(bool val);

signals:

    void        baudRateChanged();
    void        portNameChanged();
    void        uploadingChanged();

private:

    bool        _uploading;

};

#endif // SERIALOPTIONS_H
