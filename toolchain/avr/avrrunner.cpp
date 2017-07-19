#include "avrrunner.h"
#include "board/arduinoboard.h"
#include "board/boardfactory.h"
#include "avrenvironment.h"
#include "exception/runerror.h"
#include "exception/portnamenotspecified.h"
#include <QProcess>

void AvrRunner::registerQmlType(){
    qmlRegisterType<AvrRunner>("Kodlio" , 1 , 0 , "AvrRunner");
}

AvrRunner::AvrRunner(QQuickItem *parent) : Runner(parent)  {

}

void AvrRunner::run( RunOptions *opts){

    setRunnerState(Spawning);
    QString  file = opts->get("file" , true).toString();
    QString  boardName = opts->get("board" , true).toString();
    QString  portName = opts->get("port" , true).toString();
    ArduinoBoard*   board = BoardFactory().create(boardName);\
    AvrEnvironment  env;
    ArduinoBoard::AvrDudeConfParams params = board->avrDudeConfParams();

    //Port belirtilmemisse hata firlatiliyor
    if(portName.isEmpty())
        PortNameNotSpecified().raise();

    //<avrdudePath> -C<avrdudeConfPath> -v -patmega328p -carduino -P<portName> -b<baudRate> -D -Uflash:w:<hexFilePath>:i
    QString command = QString("%0 -C%1 %2 -P%3 -b%4 -D -Uflash:w:%5:i").arg(env.avrdude())
            .arg(env.avrdudeConf())
                 .arg(params.params)
                 .arg(portName)
                 .arg(params.baudRate)
                 .arg(file);

    //Output gonderiliyor
    sendCommandOutput(command);

    QProcess    process;

    process.start(command);
    bool interrupted = !process.waitForFinished();

    if(interrupted || process.exitCode() != 0){
        QString     err = process.readAllStandardError();
        sendStdErr("Hex dosyası yüklenirken hata oluştu.");
        sendStdErr(err);
        sendRunError();

        //Hata firlatiliyor
        RunError(err).raise();
    }   else    {
        //AvrDude error olarak yaziyor outputunu
        QString output = process.readAllStandardError();

        sendStdOutput(output);
    }

    setRunnerState(Started);
    //Calistirildi
    sendRunSuccess();
}
