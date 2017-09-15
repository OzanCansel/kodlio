#include "pinmodedescgenerator.h"
#include "parse/parsehelper.h"

QString PinModeDescGenerator::name(){
    return "pinMode";
}

int PinModeDescGenerator::argsCount(){
    return 2;
}

bool PinModeDescGenerator::generate(const FunctionUsageParsed &parsed, QString &desc){
    QString pinNumArg   =   parsed.args().at(0);
    QString confArg     =   parsed.args().at(1);

    if(ParseHelper::isNumber(pinNumArg)){
        desc.append("Pin ")
                .append(pinNumArg);
    }else{
        desc.append("Pin\"")
                .append(pinNumArg)
                .append("\"");
    }

    if(confArg == "OUTPUT"){
        desc.append(" sinyal göndermek için ayarlanıyor.(OUTPUT)");
    }else if(confArg == "INPUT"){
        desc.append(" sinyal okumak için ayarlanıyor.(INPUT) ");
    }else{
        desc.append(" ")
                .append(confArg)
                .append(" olarak ayarlanıyor.");
    }
}
