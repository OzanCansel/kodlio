#ifndef ROBOSKOPTOOLCHAINWORKER_H
#define ROBOSKOPTOOLCHAINWORKER_H

#include <QObject>
#include "toolchain/avr/roboskop/roboskoprunner.h"

class RoboskopToolchainWorker : public  QObject
{

    Q_OBJECT

public:

    RoboskopToolchainWorker(QObject* parent = nullptr);
    void    setRunner(Runner *runner);

public slots:

    void    uploadFirmware(RunOptions *opts);

private:

    Runner* _runner;

};

#endif // ROBOSKOPTOOLCHAINWORKER_H
