#ifndef COMPILETHREAD_H
#define COMPILETHREAD_H

#include <QThread>
#include "toolchain/avrcompiler.h"

class CompileWorker :   public QObject
{

    Q_OBJECT
    QThread     workerThread;

public:

    CompileWorker(AvrCompiler *compiler , QObject *parent = Q_NULLPTR);

public slots:

    void    doWork(const QString &compilingDir){

        _compiler->compileProject(compilingDir);

        emit resultReady(true);
    }

signals:

    void    resultReady(bool success);

private:

    AvrCompiler     *_compiler;

};

#endif // COMPILETHREAD_H
