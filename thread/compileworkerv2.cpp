#include "compileworkerv2.h"

CompileWorkerV2::CompileWorkerV2(Toolchain *toolchain , QObject *parent) : QObject(parent){
    _toolchain = toolchain;
}

void CompileWorkerV2::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}
