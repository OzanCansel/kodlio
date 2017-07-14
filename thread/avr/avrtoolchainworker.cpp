#include "avrtoolchainworker.h"

AvrToolchainWorker::AvrToolchainWorker(QObject *parent) : QObject(parent)
{
    _toolchain = Q_NULLPTR;
    _runner = Q_NULLPTR;
}

void AvrToolchainWorker::compile(QString file, CompileOptions *opts){
    if(_toolchain == Q_NULLPTR)
        return;

    _toolchain->compile(file , opts);
}

void AvrToolchainWorker::run(RunOptions *opts){

    if(_runner == Q_NULLPTR)
        return;

    _runner->run(opts);
}

void AvrToolchainWorker::setToolchain(AvrToolchain *toolchain){
    _toolchain = toolchain;
}

void AvrToolchainWorker::setRunner(AvrRunner *runner){
    _runner = runner;
}

void AvrToolchainWorker::hello(){
    while(true){

    }
}
