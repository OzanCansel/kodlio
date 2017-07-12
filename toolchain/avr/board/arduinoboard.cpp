#include "arduinoboard.h"

ArduinoBoard::ArduinoBoard(QObject *parent) : QObject(parent)
{

}

QString ArduinoBoard::objectCodeParams(QString &extension){
    return _objectCodeParamsMap.value(extension , QString());
}

QString ArduinoBoard::elfParams(){
    return "-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p";
}

QString ArduinoBoard::eepParams(){
    return "-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0";
}

QString ArduinoBoard::hexParams(){
    return "-O ihex -R .eeprom";
}
