#include "avrtoolchainenvironment.h"

AvrToolchainEnvironment::AvrToolchainEnvironment(QQuickItem *parent) : Environment(parent)
{
    set("coreLibs" , sdkDir().append("/arduino/avr/cores/arduino"));
    set("variantsBase" , sdkDir().append("/arduino/avr/variants"));
}

QString AvrToolchainEnvironment::coreLibs(){
    return get("coreLibs" , true);
}

QString AvrToolchainEnvironment::standardVariants(){
    return variants("standard");
}

QString AvrToolchainEnvironment::variants(QString boardName){
    return get("variantsBase" , true).append("/").append(boardName);
}
