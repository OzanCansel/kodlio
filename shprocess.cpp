#include "shprocess.h"

ShProcess::ShProcess(QObject *parent) : QProcess(parent)
{

}

bool ShProcess::shSync(QString command , int timeout){
//    start("sh" , QStringList() << "-c" << command);
    start(command);

    return waitForFinished(timeout);
}
