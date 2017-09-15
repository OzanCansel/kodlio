#include "unoboard.h"

UnoBoard::UnoBoard(QObject *parent) :  ArduinoBoard(parent)
{
    _objectCodeParamsMap[".c"] = cFileCompileDefaultParams();
    _objectCodeParamsMap[".S"] = sFileCompileDefaultParams();
    _objectCodeParamsMap[".cpp"] = cppFileCompileDefaultParams();
}

QString UnoBoard::name(){
    return "uno";
}

QString     UnoBoard::cFileCompileDefaultParams(){
    return "-c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10803 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}

QString UnoBoard::cppFileCompileDefaultParams(){
    return "-c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10803 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}

QString UnoBoard::sFileCompileDefaultParams(){
    return "-c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10803 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR";
}
