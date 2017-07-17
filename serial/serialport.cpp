#include "serialport.h"
#include <QDebug>
#include <QtQml>

void SerialPort::registerQmlType(){
    qmlRegisterType<SerialPort>("Kodlio" , 1 , 0 , "SerialPort");
}

SerialPort::SerialPort(QObject  *parent) : QObject(parent)
{
    connect(&_port , SIGNAL(readyRead()) , this , SLOT(serialPortIncome()));

    _baudRateHash.insert(115200 , QSerialPort::Baud115200);
    _baudRateHash.insert(57600 , QSerialPort::Baud57600);
    _baudRateHash.insert(38400 , QSerialPort::Baud38400);
    _baudRateHash.insert(19200 , QSerialPort::Baud19200);
    _baudRateHash.insert(9600 , QSerialPort::Baud9600);
    _baudRateHash.insert(4800 , QSerialPort::Baud4800);

    _vendorIdFilter.append(6790);

    _vendorIdFilter << 6790 << 9025 << 67 << 10755 << 0x2341 << 0x2341 << 0x2A03;

    setBaudRate(9600);
}

QStringList SerialPort::listSerialPort(){
    QStringList l;

    foreach (QSerialPortInfo inf, QSerialPortInfo::availablePorts()) {
        if(!_vendorIdFilter.contains(inf.vendorIdentifier()))
            continue;

        l.append(inf.portName());

        if(_debugEnabled){
            qDebug() << inf.portName() << " Vendor ID : "  << inf.vendorIdentifier() << " Product ID" << inf.productIdentifier();
        }
    }

    return l;
}

bool SerialPort::connectToArduino(QString port){

    if(_port.isOpen())
        _port.close();

    _port.setPortName(port);
    if(!_port.open(QSerialPort::ReadWrite)){
        qDebug() << port << " açılamadı.";
        return false;
    }else{
        qDebug() << port << " ile bağlantı kuruldu.";
    }

    _port.setBaudRate(QSerialPort::Baud9600);
    _port.setDataBits(QSerialPort::Data8);
    _port.setParity(QSerialPort::NoParity);
    _port.setStopBits(QSerialPort::OneStop);
    _port.setFlowControl(QSerialPort::NoFlowControl);

    return true;
}

void SerialPort::close(){
    qDebug() << _port.portName() << " kapatıldı.";
    _port.close();
}


void SerialPort::send(QByteArray arr){
    if(_port.isWritable()){
        _port.write(arr);

        if(_debugEnabled)
            qDebug() << _port.portName() << " <- " << QString(arr);
    }
}

void SerialPort::send(QString txt){
    if(_port.isWritable()){
        _port.write(txt.toLatin1());

        if(_debugEnabled)
            qDebug() << _port.portName() << " <- " << txt;
    }
}

void SerialPort::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

void SerialPort::setBaudRate(int baudRate){

    if(!_baudRateHash.contains(baudRate)){
        qDebug() << baudRate << " bilinmeyen baud rate";
        return;
    }

    _baudRate = baudRate;
    _port.setBaudRate(_baudRateHash.value(_baudRate));
    emit baudRateChanged();
}

int SerialPort::baudRate(){
    return _baudRate;
}


//PRIVATE SLOT
void SerialPort::serialPortIncome(){

    QString read(_port.readAll());

    if(_debugEnabled)
        qDebug() << _port.portName() << " -> " << read;

    emit textIncome(read);
}

