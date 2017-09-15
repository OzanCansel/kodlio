#include "roboskoptoolchainthread.h"

void RoboskopToolchainThread::registerQmlType(){
    qmlRegisterType<RoboskopToolchainThread>("Kodlio" , 1 , 0 , "RoboskopToolchainThread");
}

RoboskopToolchainThread::RoboskopToolchainThread(QQuickItem *parent) : QQuickItem(parent)
{
    _runner = nullptr;

    _worker = new RoboskopToolchainWorker();
    _worker->moveToThread(&backgroundThread);

    connect(this , SIGNAL(runSignal(RunOptions*)) , _worker , SLOT(uploadFirmware(RunOptions*)));
    backgroundThread.start();
}

void RoboskopToolchainThread::run(RunOptions *opts) {
    emit runSignal(opts);
}

//Getter
Runner* RoboskopToolchainThread::runner(){
    return _runner;
}

//Setter
void RoboskopToolchainThread::setRunner(Runner *runner){
    _runner = runner;
    _worker->setRunner(runner);
    emit runnerChanged();
}
