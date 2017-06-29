#include "sdkextractor.h"
#include "shprocess.h"
#include "directorymanager.h"
#include <QDebug>
#include <QStandardPaths>
#include <QCoreApplication>

QString SdkExtractor::_sdkPath;

SdkExtractor::SdkExtractor(QObject *parent ) : QObject(parent)
{
    _sdkPath        =   QCoreApplication::applicationDirPath().append("/sdk");
}

bool SdkExtractor::checkSdk(){

}

bool SdkExtractor::extractSdk(){

    //Sdk dosyaları kopyalanıyor
    DirectoryManager::copy(":/sdk-lib" , SdkExtractor::_sdkPath);


}

bool SdkExtractor::removeSdk(){
    ShProcess   process;

    process.shSync("rm -rf sdk");
}

QString SdkExtractor::arduinoCorePath(){
    QString corePath = QString(_sdkPath).append("/arduino/cores/arduino");

    return corePath;
}

QString  SdkExtractor::avrBinPath(){
    return "";
//    return QString(_sdkPath).append("/avr-tools");
}

QString SdkExtractor::variantsStandardPath(){
    return QString(_sdkPath).append("/arduino/variants/standard");
}

QString SdkExtractor::avrdudeConfPath(){
    return QString(_sdkPath).append("/avrdude.conf");
}
