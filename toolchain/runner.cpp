#include "runner.h"
#include <QtQml>

void Runner::registerQmlType(){
    qmlRegisterType<Runner>("Kodlio" , 1 , 0 , "Runner");
}

Runner::Runner(QQuickItem *parent) : QQuickItem(parent)
{

}

void Runner::run(RunOptions *opts){

}

void Runner::sendRunSuccess(){
    if(debugEnabled())  qDebug() << "Runner successfully ran";
    emit runSuccess();
}


void Runner::sendRunError(){
    if(debugEnabled())  qDebug() << "Runner sendRunError()";
    emit runError();
}

void Runner::sendCommandOutput(QString output){
    if(debugEnabled())  qDebug() << "Runner commandOutput() -> " << output;
    emit commandOutput(output);
}

void Runner::sendInfo(QString output){
    if(debugEnabled()) qDebug() << "Runner sendInfo() -> " << output;
    emit infoOutput(output);
}

void Runner::sendStdOutput(QString output){
    if(debugEnabled())  qDebug() << "Runner sendStdOutput() -> " << output;
    emit stdOutput(output);
}

void Runner::sendStdErr(QString output){
    if(debugEnabled())  qDebug() << "Runner sendStderr() -> " << output;
    emit stdErr(output);
}

void Runner::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

bool Runner::debugEnabled(){
    return _debugEnabled;
}
