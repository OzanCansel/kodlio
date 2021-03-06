#include "runner.h"
#include <QtQml>

void Runner::registerQmlType(){
    qmlRegisterType<Runner>("Kodlio" , 1 , 0 , "Runner");
}

Runner::Runner(QQuickItem *parent)
    : QQuickItem(parent) ,
      m_busy(false)
{
    setRunnerState(None);
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

void Runner::sendProgress(double val){
    if(debugEnabled())  qDebug() << "Runner progress() -> " << val;

    emit progress(val);
}

void Runner::setDebugEnabled(bool enabled){
    m_debugEnabled = enabled;
}

bool Runner::debugEnabled(){
    return m_debugEnabled;
}

Runner::RunnerState Runner::runnerState(){
    return _state;
}

void Runner::setRunnerState(RunnerState state){
    _state = state;

    emit runnerStateChanged();
}

bool Runner::busy(){
    return m_busy;
}

void  Runner::setBusy(bool val){
    m_busy = val;

    emit busyChanged();
}
