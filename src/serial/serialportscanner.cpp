#include "serialportscanner.h"
#include <QtQml>
#include <QSerialPortInfo>

void SerialPortScanner::registerQmlType(){
    qmlRegisterType<SerialPortScanner>("Kodlio" , 1 , 0 , "SerialPortScanner");
}

SerialPortScanner::SerialPortScanner(QQuickItem *parent)  : QQuickItem(parent){
    PortInfo    uno;
    uno.board = "Arduino Uno";
    uno.pairs << IdPair(0x2341 , 0x0043) << IdPair(0x2341 , 0x0001)
              << IdPair(0x2A03 , 0x0043) << IdPair(0x2341 , 0x0243)
                << IdPair(0x1A86,0x7523);
    _definedBoards << uno;
}

void SerialPortScanner::refresh(){
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    //Temizleniyor
    _variants.clear();


    foreach (QSerialPortInfo info, infos) {

        QString boardName = retrieveBoardName(info.vendorIdentifier() , info.productIdentifier());

        //Eger board bulunamadiysa pas geciliyor
        if(boardName.isEmpty())
            continue;

        QVariantMap map;

        map["portName"]     =   info.portName();
        map["boardName"]    =   boardName;

        _variants.append(map);
    }

    emit portsChanged();
}

QVariantList SerialPortScanner::ports(){
    return _variants;
}

QString SerialPortScanner::retrieveBoardName(int vid, int pid){

    foreach (PortInfo info, _definedBoards) {
        foreach (IdPair pair, info.pairs) {
            if(pair.pid == pid && pair.vid == vid)
                return info.board;
        }
    }

    return QString();
}
