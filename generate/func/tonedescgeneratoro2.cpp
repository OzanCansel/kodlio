#include "tonedescgeneratoro2.h"
#include "parse/parsehelper.h"

QString ToneDescGeneratorO2::name(){
    return "tone";
}

int     ToneDescGeneratorO2::argsCount(){
    return 3;
}

bool    ToneDescGeneratorO2::generate(const FunctionUsageParsed &parsed, QString &desc){

    QString     pinArg = parsed.args().at(0);
    QString     frequencyArg = parsed.args().at(1);
    QString     durationArg = parsed.args().at(2);

    desc.append("Pin ")
            .append(ParseHelper::quoteIfNotNumber(pinArg))
            .append(" üzerinden ")
            .append(frequencyArg)
            .append(" hz frekansında ")
            .append(ParseHelper::quoteIfNotNumber(durationArg))
            .append("ms süreliğine dalga üretiliyor.");

}
