#include "delaydescgenerator.h"
#include "parse/parsehelper.h"

DelayDescGenerator::DelayDescGenerator()
{

}

QString DelayDescGenerator::name(){
    return "delay";
}

int     DelayDescGenerator::argsCount(){
    return 1;
}

bool    DelayDescGenerator::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString durationArg = parsed.args().at(0);

    if(ParseHelper::isNumber(durationArg)){
        desc.append(durationArg)
                .append(" milisaniye bekleniyor.");
    }else{
        desc.append("\"")
                .append(durationArg)
                .append("\" kadar bekleniyor.");
    }
}
