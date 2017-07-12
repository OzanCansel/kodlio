#include "avrenvironment.h"

AvrEnvironment::AvrEnvironment(QQuickItem *parent) : Environment(parent)
{
    set("g++" , sdkDir().append("/tools/avr/bin/avr-g++"));
    set("gcc" , sdkDir().append("/tools/avr/bin/avr-gcc"));
    set("gcc-ar" , sdkDir().append("/tools/avr/bin/avr-gcc-ar"));
    set("objcopy" , sdkDir().append("/tools/avr/bin/avr-objcopy"));
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
