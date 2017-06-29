#ifndef COMPILEWORKERV2_H
#define COMPILEWORKERV2_H

#include <QThread>
#include <QDebug>
#include "toolchain/toolchain.h"
#include "roboskopenvironment.h"

class CompileWorkerV2 : public QObject
{

    Q_OBJECT

    QThread     workerThread;

public:

    CompileWorkerV2(Toolchain   *toolChain ,  QObject *parent = Q_NULLPTR);
    void        setDebugEnabled(bool enabled);

public slots:

    void doWork(const QString &rootDir , const QString &outputPath , QStringList l){

        if(_debugEnabled)
            qDebug() << "CompileWorkerV2.doWork() RootDir -> " <<  rootDir << " OutputPath -> " << outputPath << " ExtraFolder -> " << l;

        l.append(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::ArduinoCore));
        _toolchain->compileFolderRecursively(rootDir , outputPath , l);

        emit resultReady(true);
    }

signals:

    void        resultReady(bool success);

private:

    Toolchain   *_toolchain;

    bool        _debugEnabled;

};

#endif // COMPILEWORKERV2_H
