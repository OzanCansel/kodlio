#include "zip7zextractor.h"
#include "zipenvironment.h"
#include "exception/environmentvariablenotset.h"
#include "rprocess.h"
#include "exception/unziperror.h"
#include <QDebug>

bool Zip7zExtractor::unzip(QString zipFile, QString outputFolder , bool overwrite){
    ZipEnvironment  env;

    //Degisken kontrol ediliyor
    if(!env.isAssigned("zipExecutable"))
        EnvironmentVariableNotSet("zipExecutable").raise();

    QString     zipExecutablePath = env.get("zipExecutable");
    QString     command;

    command.append(zipExecutablePath)
            .append(" x ")
            .append(zipFile)
            .append(" -o")
            .append(outputFolder);

    if(overwrite)
        command.append(" -aoa");
    else
        command.append(" -aos");

    if(debugEnabled())
        qDebug() << "Zip7zExtractor::unzip() Komut calistiriliyor -> " << command;

    //Dosyalar cikartiliyor
    RProcess    process;
    process.runWait(command , -1);

    bool    operationSuccessfull = process.exitCode() == 0;

    //Cikarma islemi tamamlamanamadiysa konsole yaziliyor.
    if(!operationSuccessfull){
        qDebug()  << "Zip7zExtractor::unzip() Dosya cikarma islemi sirasinda hata !.";
    }

    if(debugEnabled()){
        qDebug() << "Zip7zExtractor::unzip() exitCode -> " << process.exitCode();

        if(process.hasStdOut()) qDebug() << "Zip7zExtractor::unzip() stdOut -> " << process.stdOut();
        if(process.hasStdErr()) qDebug() << "Zip7zExtractor::unzip() stdErr -> " << process.stdErr();
    }

    return operationSuccessfull;
}
