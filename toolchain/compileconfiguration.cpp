#include "compileconfiguration.h"

void CompileConfiguration::registerQmlType(){
    qmlRegisterType<CompileConfiguration>("Roboskop" , 1 , 0 , "CompileConfiguration");
}

CompileConfiguration::CompileConfiguration(QObject *parent) :  QObject(parent)
{
}

QString CompileConfiguration::getCParameters(){
    return "-c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10613 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}

QString CompileConfiguration::getCppParameters(){
    return "-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10613 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}

QString CompileConfiguration::getSParameters(){
    return "-c -g -x assembler-with-cpp -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10613 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}

QString CompileConfiguration::getArchiveParameters(){
    return "rcs";
}

QString CompileConfiguration::getElfParameters(){
    return "-Os -Wl,--gc-sections -mmcu=atmega328p";
}

QString CompileConfiguration::getHexParameters(){
    return "-O ihex -R .eeprom";
}

QString CompileConfiguration::getEepParameters(){
    return "-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0";
}
