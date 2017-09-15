#include "notonedescgenerator.h"
#include "parse/parsehelper.h"

QString NoToneDescGenerator::name(){
    return "noTone";
}

int NoToneDescGenerator::argsCount(){
    return 1;
}

bool NoToneDescGenerator::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString pinArg = parsed.args().at(0);

    desc.append("Pin ")
            .append(ParseHelper::quoteIfNotNumber(pinArg))
            .append(" susturuluyor");

}
