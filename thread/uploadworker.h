#ifndef UPLOADWORKER_H
#define UPLOADWORKER_H

#include <QObject>
#include <QThread>
#include "toolchain/avrcompiler.h"

class UploadWorker : public QObject
{

    Q_OBJECT
    QThread     workerThread;


public:

    UploadWorker(AvrCompiler    *compiler , QObject *parent = Q_NULLPTR);

public slots:

    void    doWork(const QString &compilingDir){

        //Proje derleniyor
        bool success = _compiler->compileProject(compilingDir);

        //Eğer derleme sırasında hata oluşmuşsa sonuç  başarısız olarak geri döndürülüyor
        if(!success){
            emit resultReady(false);

            return;
        }\

        //Proje yükleniyor
        success = _compiler->uploadProject(compilingDir);

        //sonuç döndürülüyor
        emit resultReady(success);
    }

signals:

    void    resultReady(bool success);

private:

    AvrCompiler         *_compiler;

};

#endif // UPLOADWORKER_H
