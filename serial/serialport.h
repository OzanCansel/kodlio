#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QHash>

class SerialPort : public QObject
{

    Q_OBJECT
    Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
    Q_PROPERTY(bool open READ open WRITE setOpen NOTIFY openChanged)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)

public:

    static void registerQmlType();
    SerialPort(QObject *parent = Q_NULLPTR);

    bool            open();
    void            setOpen(bool val);
    QString         portName();
    void            setPortName(QString val);

signals:

    void            textIncome(QString text);
    void            baudRateChanged();
    void            openChanged();
    void            portNameChanged();

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
    void                errorOccurred(QSerialPort::SerialPortError error);

private:

    QSerialPort         _port;
    QHash<int , int>    _baudRateHash;
    QList<int>          _vendorIdFilter;

    bool                _debugEnabled;
    int                 _baudRate;
    QString             _portName;
    void                applyConf();

};

#endif // SERIALPORT_H
