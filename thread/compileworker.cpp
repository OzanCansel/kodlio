#include "compileworker.h"

CompileWorker::CompileWorker(AvrCompiler *compiler, QObject    *parent) : QObject(parent)
{
    _compiler = compiler;
}
