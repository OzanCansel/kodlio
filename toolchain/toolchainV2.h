#ifndef TOOLCHAIN_V2_H
#define TOOLCHAIN_V2_H

#include <QString>
#include <QQuickItem>
#include "compileoptions.h"
#include "runoptions.h"
#include "compilerv2.h"
#include "runner.h"

class ToolchainV2 : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)


public:

    static void     registerQmlType();
    ToolchainV2(QQuickItem *parent = Q_NULLPTR);
    bool            busy();

public slots:

    virtual void            compile(QString file ,  CompileOptions* opts);
    virtual void            run(RunOptions*  options);
    virtual CompilerV2*     compiler();
    virtual Runner*         runner();
    void                    setDebugEnabled(bool enabled);
    bool                    debugEnabled();

protected:

    void    sendStdOutput(QString out);
    void    sendStdError(QString err);
    void    sendCommandOutput(QString command);
    void    sendInfo(QString out);
    void    sendCompileSuccess();
    void    sendCompileError();
    void    sendProgress(double val);
    void    sendBuildStarted();
    void    setBusy(bool enabled);

signals:

    void    stdOutput(QString output);
    void    stdError(QString output);
    void    commandOutput(QString output);
    void    infoOutput(QString output);
    void    compileError();
    void    compileSuccess();
    void    buildStarted();
    void    buildEnd();
    void    progress(double value);
    void    busyChanged();

private:

    bool    _debugEnabled;
    bool                    _busy;


};

#endif // ITOOLCHAIN_H
