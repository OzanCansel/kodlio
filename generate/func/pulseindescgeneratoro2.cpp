#include "pulseindescgeneratoro2.h"
#include "parse/parsehelper.h"

QString PulseInDescGeneratorO2::name(){
    return "pulseIn";
}

int PulseInDescGeneratorO2::argsCount(){
    return 3;
}

bool PulseInDescGeneratorO2::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString     pinArg = parsed.args().at(0);
    QString     signal = parsed.args().at(1);
    QString     timeout = parsed.args().at(2);

    desc.append("Pin ")
            .append(ParseHelper::quoteIfNotNumber(pinArg))
            .append(" üzerinden ")
            .append(signal)
            .append(" sinyali bekleniyor ve ")
            .append(timeout)
            .append("us içinde gelmezse 0 döndürülüyor.");

}
