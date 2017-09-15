#include "pulseindescgeneratoro1.h"
#include "parse/parsehelper.h"

QString PulseInDescGeneratorO1::name(){
    return "pulseIn";
}

int PulseInDescGeneratorO1::argsCount(){
    return 2;
}

bool PulseInDescGeneratorO1::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString     pinArg = parsed.args().at(0);
    QString     signal = parsed.args().at(1);

    desc.append("Pin ")
            .append(ParseHelper::quoteIfNotNumber(pinArg))
            .append(" için ")
            .append(signal)
            .append(" sinyali bekleniyor.");
}
