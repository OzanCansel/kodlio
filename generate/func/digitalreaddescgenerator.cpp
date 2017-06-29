#include "digitalreaddescgenerator.h"
#include "parse/parsehelper.h"

QString DigitalReadDescGenerator::name(){
    return "digitalRead";
}

int     DigitalReadDescGenerator::argsCount(){
    return 1;
}

bool    DigitalReadDescGenerator::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString pinArg = parsed.args().at(0);
    if(ParseHelper::isNumber(pinArg)){
        desc.append("Pin ")
                .append(pinArg)
                .append(" dijital(1 veya 0) değer okunuyor.");
    }
    else{
        desc.append("Pin \n")
                .append(pinArg)
                .append("\" dijital(1 veya 0) değer okunuyor.");
    }
}
