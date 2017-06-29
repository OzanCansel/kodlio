#ifndef UPLOADWORKERV2_H
#define UPLOADWORKERV2_H

#include <QThread>
#include <QDebug>
#include "toolchain/toolchain.h"
#include "roboskopenvironment.h"

class CompileAndUploadWorkerV2 :  public QObject
{

    Q_OBJECT

public:

    CompileAndUploadWorkerV2(Toolchain *toolchain , QObject *parent = Q_NULLPTR);
    void    setDebugEnabled(bool enabled);

public slots:

    void doWork(const QString &buildFolder, const QString &outputPath){
        if(_debugEnabled)
            qDebug() << "UploadWorkerV2.doWork() hexFile -> " << buildFolder;

        _toolchain->compileFolderRecursively(buildFolder , outputPath , QStringList() << RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::ArduinoCore));

        _toolchain->uploadHex(QDir(outputPath).filePath("roboskop.hex"));

        emit resultReady(true);
    }

signals:

    void    resultReady(bool success);

private:

    Toolchain   *_toolchain;
    bool        _debugEnabled;

};

#endif // UPLOADWORKERV2_H
