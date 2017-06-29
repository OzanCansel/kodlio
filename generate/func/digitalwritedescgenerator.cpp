#include "digitalwritedescgenerator.h"
#include "parse/parsehelper.h"

bool DigitalWriteDescGenerator::generate(const FunctionUsageParsed &parsed , QString& desc){

    QString     pinArg = parsed.args().at(0);
    QString     signalArg = parsed.args().at(1);

    //İll parametre sabit bir sayıysa 13, 2 gibi
    if(ParseHelper::isNumber(pinArg)){
       desc.append("Pin ")
               .append(pinArg);
    }else{
        desc.append("Pin ")
                .append("\"")
                .append(pinArg)
                .append("\"");
    }

    if(signalArg == "HIGH"){
        desc.append(" sinyal gönderiliyor.(HIGH)");
    }
    else if(signalArg == "LOW"){
        desc.append(" sinyal kapatılıyor.(LOW)");
    }
    else{
        desc.append(" \"")
                .append(signalArg)
                .append("\" seviyesine çekiliyor");
    }
}

int DigitalWriteDescGenerator::argsCount(){
    return 2;
}

QString DigitalWriteDescGenerator::name(){
    return QString("digitalWrite");
}
