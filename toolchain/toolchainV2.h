#ifndef TOOLCHAIN_V2_H
#define TOOLCHAIN_V2_H

#include <QString>
#include <QQuickItem>
#include "compileoptions.h"
#include "runoptions.h"
#include "compilerv2.h"


class ToolchainV2 : public QQuickItem
{

    Q_OBJECT

public:

    static void     registerQmlType();
    ToolchainV2(QQuickItem *parent = Q_NULLPTR);

public slots:

    virtual void    compile(QString folder ,  CompileOptions* opts);
    virtual void    run(RunOptions*  options);
    virtual CompilerV2*    compiler();
    void            setDebugEnabled(bool enabled);
    bool            debugEnabled();

protected:

    void    sendStdOutput(QString &out);
    void    sendStdError(QString &err);
    void    sendCommandOutput(QString command);

signals:

    void    stdOutput(QString out);
    void    stdError(QString err);
    void    commandOutput(QString command);

private:

    bool    _debugEnabled;

};

#endif // ITOOLCHAIN_H
