#include "avrenvironment.h"

AvrEnvironment::AvrEnvironment(QQuickItem *parent) : Environment(parent)    {
    set("g++" , sdkDir().append("/tools/avr/bin/avr-g++"));
    set("gcc" , sdkDir().append("/tools/avr/bin/avr-gcc"));
    set("gcc-ar" , sdkDir().append("/tools/avr/bin/avr-gcc-ar"));
    set("objcopy" , sdkDir().append("/tools/avr/bin/avr-objcopy"));
    set("arduino-core" , sdkDir().append("/arduino/avr/cores/arduino"));
    set("avrdude" , sdkDir().append("/tools/avr/bin/avrdude"));
    set("avrdude-conf" , sdkDir().append("/tools/avr/etc/avrdude.conf"));
    set("avr-includes" , sdkDir().append("/tools/avr/avr/include"));
    set("variants-root" , sdkDir().append("/arduino/avr/variants"));
    set("variants-uno" , get("variants-root" , true).append("/standard"));
}

QString AvrEnvironment::gPlusPlus(){
    return  get("g++");
}

QString AvrEnvironment::gcc(){
    return get("gcc");
}

QString AvrEnvironment::gccAr(){
    return get("gcc-ar");
}

QString AvrEnvironment::objcopy(){
    return get("objcopy");
}

QString AvrEnvironment::variants(QString &boardName){
    return get(QString("variants-%0").arg(boardName) , true);
}

QString AvrEnvironment::avrdude(){
    return get("avrdude");
}

QString AvrEnvironment::avrdudeConf(){
    return get("avrdude-conf");
}
