#ifndef AVRTOOLCHAINTHREAD_H
#define AVRTOOLCHAINTHREAD_H

#include <QQuickItem>
#include <QThread>
#include "compileworkerV2.h"
#include "avrtoolchainworker.h"

class AvrToolchainThread : public  QQuickItem
{

    Q_OBJECT
    QThread             backgroundThread;
    Q_PROPERTY(AvrToolchain* toolchain READ toolchain WRITE setToolchain NOTIFY toolchainChanged)
    Q_PROPERTY(AvrRunner* runner READ runner WRITE setRunner NOTIFY runnerChanged)


public:

    static void     registerQmlType();
    AvrToolchainThread(QQuickItem *parent = Q_NULLPTR);
    AvrToolchain*   toolchain();
    AvrRunner*      runner();
    void            setToolchain(AvrToolchain *t);
    void            setRunner(AvrRunner* val);

public slots:

    void            compile(QString file , CompileOptions *opts);
    void            run(RunOptions *opts);

signals:

    void            compileSignal(QString file , CompileOptions *opts);
    void            runSignal(RunOptions *opts);
    void            runnerChanged();
    void            toolchainChanged();

private:

    AvrToolchainWorker  *_worker;
    AvrToolchain*       _toolchain;
    AvrRunner*          _runner;

};

#endif // AVRTOOLCHAINTHREAD_H
