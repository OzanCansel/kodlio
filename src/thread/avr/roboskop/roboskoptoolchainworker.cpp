#include "roboskoptoolchainworker.h"

RoboskopToolchainWorker::RoboskopToolchainWorker(QObject* parent) : QObject(parent) {
    _runner = nullptr;
}

void RoboskopToolchainWorker::setRunner(Runner *runner){
    _runner = runner;
}

void RoboskopToolchainWorker::uploadFirmware(RunOptions *opts){
    if(_runner == nullptr)
        return;

    _runner->run(opts);
}
