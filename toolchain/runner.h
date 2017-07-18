#ifndef RUNNER_H
#define RUNNER_H

#include <QQuickItem>
#include "toolchain/runoptions.h"

class Runner : public QQuickItem
{

    Q_OBJECT

public:

    static void     registerQmlType();
    Runner(QQuickItem *parent = Q_NULLPTR);
    void            setDebugEnabled(bool enabled);
    bool            debugEnabled();

public slots:

    virtual void    run(RunOptions *opts);

protected:

    void    sendCommandOutput(QString output);
    void    sendInfo(QString output);
    void    sendStdOutput(QString output);
    void    sendStdErr(QString output);
    void    sendRunSuccess();
    void    sendRunError();

signals:

    void    commandOutput(QString output);
    void    infoOutput(QString output);
    void    stdOutput(QString output);
    void    stdErr(QString output);
    void    runSuccess();
    void    runError();

private:

    bool    _debugEnabled;

};

#endif // RUNNER_H
