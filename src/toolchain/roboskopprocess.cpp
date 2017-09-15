#include "roboskopprocess.h"
#include "roboskopenvironment.h"
#include <QDebug>
#include <QProcessEnvironment>

RoboskopProcess::RoboskopProcess(QObject *parent) : QProcess(parent)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    RoboskopEnvironment *rEnv = RoboskopEnvironment::getInstance();
    env.insert("PATH" , rEnv->path(RoboskopEnvironment::AvrBin).append(":").append(env.value("PATH")));

    setProcessEnvironment(env);
}

bool RoboskopProcess::startProcess(QString command , QStringList args){
    RoboskopProcess process;

    process.start(command , args);

    bool result = process.waitForFinished();

    qDebug() << QString(process.readAllStandardError()) << QString(process.readAllStandardOutput());

    return result;
}

bool RoboskopProcess::startProcess(QString command , QString &stdOut,  QString &stdErr){
    RoboskopProcess process;

    process.start(command);

    process.waitForFinished();

    stdOut.append(process.readAllStandardOutput());
    stdErr.append(process.readAllStandardError());

    if(!stdErr.isEmpty()){
        qDebug() << stdErr;
    }

    return stdErr.isEmpty();
}
