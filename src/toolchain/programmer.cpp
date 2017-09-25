#include "programmer.h"
#include <QDebug>
#include <QRegularExpression>
#include "roboskopprocess.h"
#include "roboskopenvironment.h"

Programmer::Programmer(QQuickItem *parent) : QQuickItem(parent)
{
    _conf = new ProgrammerConfiguration(this);
}

void Programmer::upload(QString hexFilePath, ProgrammerConfiguration *conf){
    QString command = RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrBin).append(QDir::separator()).append("avrdude ");
    QString stdOut , stdErr;
    command.append(conf->getAvrdudeParameters())
            .append(" -Uflash:w:")
            .append(hexFilePath)
            .append(":i");

    if(_debugEnabled)   qDebug() << command;

    emit commandOutput(command);

    RoboskopProcess::startProcess(command , stdOut , stdErr);

    if(!stdOut.isEmpty()){

        if (_debugEnabled)  qDebug() << "Programmer::upload() stdOut -> " << stdOut;

        emit stdOutput(stdOut);
    }
    if(!stdErr.isEmpty()){

        if(stdErr.contains("ser_open(): can't open")){
            emit stdError(stdErr);
            return;
        }

        if(_debugEnabled)   qDebug() << "Programmer::upload() stdErr -> " << stdErr;

        emit stdOutput(stdErr);
    }
}

void Programmer::upload(QString hexFilePath){
    if(_conf != Q_NULLPTR)
        upload(hexFilePath , _conf);
}


void Programmer::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

void Programmer::setProgrammerConfiguration(ProgrammerConfiguration *conf){
    _conf = conf;
}

ProgrammerConfiguration* Programmer::configuration(){
    return _conf;
}

void Programmer::setConfiguration(ProgrammerConfiguration *conf){
    _conf = conf;
}
