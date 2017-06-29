#include "compileanduploadworkerv2.h"

CompileAndUploadWorkerV2::CompileAndUploadWorkerV2 (Toolchain *toolchain, QObject *parent) : QObject(parent)
{
    _debugEnabled = false;
    _toolchain  =   toolchain;
}

void CompileAndUploadWorkerV2::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}
