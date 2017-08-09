#include "roboskoprunner.h"
#include "roboskopenvironment.h"
#include "serial/serialport.h"
#include "exception/runerror.h"
#include <QDebug>
#include <QtCore>

void RoboskopRunner::registerQmlType(){
    qmlRegisterType<RoboskopRunner>("Kodlio" , 1 , 0 , "RoboskopRunner");
}

RoboskopRunner::RoboskopRunner(QQuickItem* parent) : Runner(parent)
{

}

void RoboskopRunner::run(RunOptions *opts){
    Q_UNUSED(opts)
    setBusy(true);
    sendInfo("Yükleme başlatılıyor");
    sendProgress(0);
    QString board = opts->get("board").toString();
    QString portName = opts->get("port").toString();
    AvrRunner           runner;
    QTemporaryDir       firmwareDir;
    QString             validatorPath = firmwareDir.filePath("validator-uno.hex");
    if(!QFile::copy(":/res/firmware/validator-uno.hex" , validatorPath)){
        sendRunError();
        sendStdErr("Yükleme esnasında hata !");
        return;
    }
    opts->set("file" , validatorPath);

    //%10 tamamlandi
    sendProgress(0.1);
    //Roboskop yazilimini kontrol eden firmware yukleniyor
    runner.run(opts);

    QSerialPort  port;
    port.setPortName(portName);

    //Port acilamadiysa 3 kez deneniyor
    if(!port.open(QSerialPort::ReadWrite)){
        //Port aciliyor
        for(int i = 0; i < 3 && !port.open(QSerialPort::ReadWrite); i++){
            QThread::msleep(250);
        }

        if(!port.isOpen()){
            sendRunError();
            sendStdErr("Yüklenecek port açılamıyor.");
            sendProgress(-1);
            return;
        }
    }

    sendProgress(0.25);
    bool responded = port.waitForReadyRead(3000);

    //Eger ki hazir cevabi gelmediyse
    if(!responded){
        sendRunError();
        sendStdErr("Yükleme esnasında hata oluştu.");
        sendProgress(-1);
        return;
    }

    QString readed = QString::fromLatin1(port.readAll());

    //Key kontrol ediliyor
    if(!readed.contains("a")){
        sendRunError();
        sendStdErr("Yükleme esnasında hata oluştu");
        sendProgress(-1);
        return;
    }

    sendProgress(0.35);

    port.write(QString("{~}").toLatin1());

    responded = port.waitForReadyRead(1000);

    //Eger key geri donmediyse geri donuluyor
    if(!responded){
        sendRunError();
        sendStdErr("Yükleme esnasında hata oluştu.");
        sendProgress(-1);
        return;
    }

    sendProgress(0.4);

    //Key okunuyor
    QString key = QString::fromLatin1(port.readAll());

    //Key dogru ise roboskop firmwarei yukleniyor
    if(key != "8jNjk1'}CLt,O8y"){
        sendRunError();
        sendStdErr("Sadece Roboskop işlemcilerine yükleme yapılabilir.");
        sendProgress(-1);
        return;
    }

    port.close();

    sendProgress(0.5);

    QString roboskopFirmwarePath = firmwareDir.filePath("firmware-uno.hex");

    if(!QFile::copy(":/res/firmware/firmware-uno.hex" , roboskopFirmwarePath)){
        sendRunError();
        sendStdErr("Roboskop yazılımı yüklenirken hata oluştu.");
        sendProgress(-1);
        return;
    }

    sendProgress(0.65);

    opts->set("file" , roboskopFirmwarePath);

    try{
        runner.run(opts);
    }   catch(RunError &err){
        sendRunError();
        return;
    }

    sendProgress(1);
    setBusy(false);
    sendInfo("Yükleme başarıyla tamamlandı.");
    sendRunSuccess();
}
