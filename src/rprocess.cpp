#include "rprocess.h"

RProcess::RProcess(){
}

int RProcess::runWait(QString command , int timeout){
    _stdErr.clear();
    _stdOut.clear();
    start(command);

    int     result  =   waitForFinished(timeout);
    _stdErr =   readAllStandardError();
    _stdOut =   readAllStandardOutput();

    return result;
}

void RProcess::onStdErr(){
    _stdErr = QString(readAllStandardError());
}

void RProcess::onStdOut(){
    _stdOut = QString(readAllStandardOutput());
}

QString RProcess::stdErr(){
    return _stdErr;
}

QString RProcess::stdOut(){
    return _stdOut;
}

bool RProcess::hasStdOut(){
    return !_stdOut.isEmpty();
}

bool RProcess::hasStdErr(){
    return !_stdErr.isEmpty();
}
