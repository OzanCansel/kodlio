#include "tonedescgeneratoro1.h"
#include "parse/parsehelper.h"

QString ToneDescGeneratorO1::name(){
    return "tone";
}

int     ToneDescGeneratorO1::argsCount(){
    return 2;
}

bool    ToneDescGeneratorO1::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString     pinArg = parsed.args().at(0);
    QString     frequencyArg = parsed.args().at(1);

    desc.append("Pin ")
            .append(ParseHelper::quoteIfNotNumber(pinArg))
            .append(" üzerinden ")
            .append(frequencyArg)
            .append(" hz frekansında dalga üretiliyor.");

}
