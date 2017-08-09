#ifndef ROBOSKOPRUNNER_H
#define ROBOSKOPRUNNER_H

#include "toolchain/runner.h"
#include "toolchain/avr/avrrunner.h"

class RoboskopRunner : public Runner
{

public:

    static void     registerQmlType();
    RoboskopRunner(QQuickItem* parent = nullptr);
    void        run( RunOptions*    opts);

};

#endif // ROBOSKOPRUNNER_H
