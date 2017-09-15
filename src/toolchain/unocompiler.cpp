#include "unocompiler.h"

UnoCompiler::UnoCompiler(QObject *parent) : AvrCompiler(parent)
{

}

QString UnoCompiler::getCParameters(){
    return "-c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10613 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}

QString UnoCompiler::getCppParameters(){
    return "-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10613 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}

QString UnoCompiler::getSParameters(){
    return "-c -g -x assembler-with-cpp -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10613 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}


QString UnoCompiler::getLinkParameters(){
    return "-Os -Wl,--gc-sections -mmcu=atmega328p";
}

QString UnoCompiler::getEepFileCompilingArgs(){
    return "-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0";
}

QString UnoCompiler::getHexFileCompilingArgs(){
    return "-O ihex -R .eeprom";
}

QString UnoCompiler::getUploadHexArgs(QString port){
    return QString(" -v -patmega328p -carduino -P").append(port).append(" -b115200 -D -Uflash:w:");
}
