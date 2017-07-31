#ifndef RUNNER_H
#define RUNNER_H

#include <QQuickItem>
#include "toolchain/runoptions.h"

class Runner : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(RunnerState runnerState READ runnerState NOTIFY runnerStateChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

public:

    enum    RunnerState{
        None,
        Spawning,
        Started
    };
    Q_ENUMS(RunnerState)

    static void     registerQmlType();
    Runner(QQuickItem *parent = Q_NULLPTR);
    void            setDebugEnabled(bool enabled);
    bool            debugEnabled();
    bool            busy();
    RunnerState     runnerState();

public slots:

    virtual void    run(RunOptions *opts);

protected:

    void    sendCommandOutput(QString output);
    void    sendInfo(QString output);
    void    sendStdOutput(QString output);
    void    sendStdErr(QString output);
    void    sendRunSuccess();
    void    sendRunError();
    void    setRunnerState(RunnerState state);
    void    setBusy(bool val);

signals:

    void    commandOutput(QString output);
    void    infoOutput(QString output);
    void    stdOutput(QString output);
    void    stdErr(QString output);
    void    runSuccess();
    void    runError();
    void    runnerStateChanged();
    void    busyChanged();

private:

    RunnerState _state;
    bool        _busy;
    bool        _debugEnabled;

};

#endif // RUNNER_H
