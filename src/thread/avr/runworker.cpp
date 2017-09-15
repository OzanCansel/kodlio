#include "runworker.h"

RunWorker::RunWorker(AvrRunner *runner , QObject *parent) : QObject(parent)
{
    _runner = runner;
}
