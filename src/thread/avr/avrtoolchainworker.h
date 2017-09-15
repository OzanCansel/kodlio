#ifndef AVRTOOLCHAINWORKER_H
#define AVRTOOLCHAINWORKER_H

#include <QObject>
#include "toolchain/avr/avrtoolchain.h"
#include "toolchain/avr/avrrunner.h"

class AvrToolchainWorker : public QObject
{

    Q_OBJECT

public:

    AvrToolchainWorker(QObject *parent = Q_NULLPTR);
    void            setToolchain(AvrToolchain *toolchain);
    void            setRunner(AvrRunner *runner);

public slots:

    void            compile(QString file , CompileOptions *opts);
    void            run(RunOptions* opts);
    void            hello();

private:

    AvrToolchain*   _toolchain;
    AvrRunner*      _runner;

};

#endif // AVRTOOLCHAINWORKER_H
