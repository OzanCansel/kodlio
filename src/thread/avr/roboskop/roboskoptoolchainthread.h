#ifndef ROBOSKOPTOOLCHAINTHREAD_H
#define ROBOSKOPTOOLCHAINTHREAD_H

#include <QThread>
#include "toolchain/avr/roboskop/roboskoprunner.h"
#include "toolchain/runoptions.h"
#include "roboskoptoolchainworker.h"

class RoboskopToolchainThread : public QQuickItem
{

    Q_OBJECT
    QThread     backgroundThread;
    Q_PROPERTY(Runner* runner READ runner WRITE setRunner NOTIFY runnerChanged)

public:

    static void     registerQmlType();
    RoboskopToolchainThread(QQuickItem* parent = nullptr);
    ~RoboskopToolchainThread();
    Runner*         runner();
    void            setRunner(Runner* runner);

public slots:

    void            run(RunOptions* opts);

signals:

    void            runnerChanged();
    void            runSignal(RunOptions *opts);

private:

    Runner*         _runner;
    RoboskopToolchainWorker* _worker;
};

#endif // ROBOSKOPTOOLCHAINTHREAD_H
