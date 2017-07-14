#ifndef RUNWORKER_H
#define RUNWORKER_H

#include <QObject>
#include "toolchain/avr/avrrunner.h"

class RunWorker : public QObject
{

    Q_OBJECT

public:

    RunWorker(AvrRunner *runner , QObject *parent = Q_NULLPTR);

private:

    AvrRunner*  _runner;

};

#endif // RUNWORKER_H
