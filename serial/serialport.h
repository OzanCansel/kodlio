#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QHash>

class SerialPort : public QObject
{

    Q_OBJECT

public:

    static void registerQmlType();
    SerialPort(QObject *parent = Q_NULLPTR);
    Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)

signals:

    void            textIncome(QString text);
    void            baudRateChanged();

public slots:

    QStringList     listSerialPort();
    bool            connectToArduino(QString port);
    void            send(QByteArray arr);
    void            send(QString txt);
    void            setDebugEnabled(bool enabled);
    void            close();
    int             baudRate();
    void            setBaudRate(int baudRate);

private slots:

    void                serialPortIncome();

private:

    QSerialPort         _port;
    QHash<int , int>    _baudRateHash;
    QList<int>          _vendorIdFilter;

    bool                _debugEnabled;
    int                 _baudRate;

};

#endif // SERIALPORT_H
