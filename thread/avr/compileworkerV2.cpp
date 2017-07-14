#include "compileworkerV2.h"

CompileWorkerV2::CompileWorkerV2(AvrToolchain   *toolchain , QObject *parent) : QObject(parent)  {
    _toolchain = toolchain;
}

void CompileWorkerV2::compile(const QString &file, CompileOptions *opts){
    _toolchain->compile(file , opts);
}
