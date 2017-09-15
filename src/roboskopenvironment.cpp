#include "roboskopenvironment.h"
#include <QDebug>

RoboskopEnvironment* RoboskopEnvironment::self = Q_NULLPTR;

RoboskopEnvironment* RoboskopEnvironment::getInstance(){
    if(self == Q_NULLPTR)
        self = new RoboskopEnvironment();

    return self;
}

RoboskopEnvironment::RoboskopEnvironment(QObject *parent) : QObject(parent)
{
    _baseDir = QDir(QCoreApplication::applicationDirPath());

    _map[AvrBin] = _baseDir.filePath("sdk/tools/avr/bin");
    _map[ArduinoCore] = _baseDir.filePath("sdk/arduino/avr/cores/arduino");
    _map[Variants] = _baseDir.filePath("sdk/arduino/avr/variants");
    _map[AvrDudeConf] = _baseDir.filePath("sdk/tools/avr/etc/avrdude.conf");
    _map[ArduinoLibraries] = _baseDir.filePath("sdk/arduino/avr/libraries");
}

QString RoboskopEnvironment::getAvrBinPath(){
    return _baseDir.filePath("sdk/tools/avr/bin");
}

QString RoboskopEnvironment::getCoreEnvironment(){
    return _baseDir.filePath("sdk/arduino/avr/cores/arduino");
}

QString RoboskopEnvironment::getVariantsPath(QString type){
    return _baseDir.filePath("sdk/arduino/avr/variants/").append(type);
}

QString RoboskopEnvironment::getLibrariesPath(){
    return _baseDir.filePath("sdk/arduino/avr/libraries");
}

QString RoboskopEnvironment::getAvrDudeConf(){
    return _baseDir.filePath("sdk/tools/avr/etc/avrdude.conf");
}

QString RoboskopEnvironment::path(Paths path){
    return _map.value(path);
}

QString RoboskopEnvironment::print(){
    QString str;
    foreach (Paths p, _map.keys()) {
        str += p + " " + _map.value(p) + "\n";
    }

    return str;
}

QString RoboskopEnvironment::appDirPath(){
    return QCoreApplication::applicationDirPath();
}
