#include "programmerconfiguration.h"
#include "roboskopenvironment.h"

void ProgrammerConfiguration::registerQmlType(){
    qmlRegisterType<ProgrammerConfiguration>("Roboskop" , 1 , 0 , "ProgrammerConfiguration");
}

ProgrammerConfiguration::ProgrammerConfiguration(QQuickItem *parent) : QQuickItem(parent)
{

}

QString ProgrammerConfiguration::getAvrdudeParameters(){
    return QString("-C").append(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrDudeConf)).append(" -v -patmega328p -carduino -P").append(_port).append(" -b115200 -D");
}

void ProgrammerConfiguration::setPortName(QString val){
    _port = val;
}


QString ProgrammerConfiguration::portName(){
    return _port;
}
