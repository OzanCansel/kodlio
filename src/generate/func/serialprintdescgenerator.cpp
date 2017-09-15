#include "serialprintdescgenerator.h"

QString SerialPrintDescGenerator::name(){
    return "print|println";
}

int  SerialPrintDescGenerator::argsCount(){
    return 1;
}

bool SerialPrintDescGenerator::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString text = parsed.args().at(0);

    desc.append("{ ")
            .append(text)
            .append(" } seri porta yazılıyor.");
}
