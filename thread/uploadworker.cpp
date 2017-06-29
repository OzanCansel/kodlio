#include "uploadworker.h"

UploadWorker::UploadWorker(AvrCompiler *compiler , QObject *parent) : QObject(parent)
{
    _compiler = compiler;
}
