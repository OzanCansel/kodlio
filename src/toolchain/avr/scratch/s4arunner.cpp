#include "s4arunner.h"
#include "toolchain/avr/avrrunner.h"
#include "exception/runerror.h"
#include <QTemporaryDir>

void S4ARunner::registerQmlType(){
    qmlRegisterType<S4ARunner>("Kodlio" , 1 , 0 , "S4ARunner");
}

S4ARunner::S4ARunner(QQuickItem* parent) : Runner(parent)
{

}

void S4ARunner::run(RunOptions *opts){
    setBusy(true);
    sendInfo("Yükleme başlatılıyor");
    AvrRunner       runner;
    QTemporaryDir   firmwareDir;
    QString         firmwarePath = firmwareDir.filePath("s4afirmware.hex");

    //Firmware kopyalanirken hata olusursa
    if(!QFile::copy(":/res/firmware/s4afirmware.hex" , firmwarePath)){
        sendRunError();
        sendStdErr("Yukleme sirasinda hata !");
        setBusy(false);
        sendProgress(-1);
        return;
    }

    opts->set("file" , firmwarePath);

    sendProgress(0.2);

    try{
        runner.run(opts);
    } catch(RunError &err){
        Q_UNUSED(err)
        sendRunError();
        sendProgress(-1);
        setBusy(false);
        return;
    }

    sendProgress(1);
    setBusy(false);
    sendInfo("Stracth yazılımı başarıyla yüklendi.");
    sendRunSuccess();
}
