#include "avrtoolchainworker.h"
#include "exception/runerror.h"

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

    try{
        _runner->run(opts);
    }   catch(RunError &err){

    }
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
