#include "serialbegindescgenerator.h"
#include "parse/parsehelper.h"


QString     SerialBeginDescGenerator::name(){
    return "begin";
}

int     SerialBeginDescGenerator::argsCount(){
    return 1;
}

bool    SerialBeginDescGenerator::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString baudRateArg = parsed.args().at(0);

    desc.append("Seri port ")
            .append(baudRateArg)
            .append(" bağlantı hızı ile başlatılıyor.");

}
