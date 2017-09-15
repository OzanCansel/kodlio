#include "analogreaddescgenerator.h"
#include "parse/parsehelper.h"


QString AnalogReadDescGenerator::name(){
    return "analogRead";
}

int  AnalogReadDescGenerator::argsCount(){
    return 1;
}

bool    AnalogReadDescGenerator::generate(const FunctionUsageParsed &parsed, QString &desc){

    QString     pinArg = parsed.args().at(0);

    if(ParseHelper::isNumber(pinArg)){
        desc.append("Pin ")
                .append(pinArg)
                .append(" analog değer okunuyor.(Değer aralığı [0,1023])");
    }else{
        desc.append("Pin \"")
                .append(pinArg)
                .append("\" analog değer okunuyor.(Değer aralığı [0,1023])");

    }
}
