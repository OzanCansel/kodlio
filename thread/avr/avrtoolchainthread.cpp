#include "avrtoolchainthread.h"
#include <QtQml>

void AvrToolchainThread::registerQmlType(){
    qmlRegisterType<AvrToolchainThread>("Kodlio" , 1 , 0 , "AvrToolchainThread");
}

AvrToolchainThread::AvrToolchainThread(QQuickItem *parent) : QQuickItem(parent)    {
    _toolchain = Q_NULLPTR;
    _runner = Q_NULLPTR;
    _worker = new AvrToolchainWorker();
    _worker->moveToThread(&backgroundThread);

    connect(this , SIGNAL(compileSignal(QString,CompileOptions*)) , _worker , SLOT(compile(QString,CompileOptions*)));
    connect(this , SIGNAL(runSignal(RunOptions*)), _worker , SLOT(run(RunOptions*)));

    backgroundThread.start();
}

AvrToolchainThread::~AvrToolchainThread(){
    backgroundThread.terminate();
    backgroundThread.wait();
}

void AvrToolchainThread::compile(QString file, CompileOptions *opts){
    _worker->setToolchain(_toolchain);
    emit compileSignal(file , opts);
}

void AvrToolchainThread::run(RunOptions* opts){
    _worker->setRunner(_runner);
    emit runSignal(opts);
}

AvrToolchain*   AvrToolchainThread::toolchain(){
    return _toolchain;
}

AvrRunner* AvrToolchainThread::runner(){
    return _runner;
}

void AvrToolchainThread::setToolchain(AvrToolchain *toolchain){
    _toolchain = toolchain;
    emit toolchainChanged();
}

void AvrToolchainThread::setRunner(AvrRunner *val){
    _runner = val;
    emit runnerChanged();
}
