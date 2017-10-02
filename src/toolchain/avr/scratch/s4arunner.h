#ifndef S4ARUNNER_H
#define S4ARUNNER_H

#include "toolchain/runner.h"

class S4ARunner : public Runner
{

public:

    static void     registerQmlType();
    S4ARunner(QQuickItem* parent = nullptr);
    void            run(RunOptions* opts);

};

#endif // S4ARUNNER_H
