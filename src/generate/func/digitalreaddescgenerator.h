#ifndef DIGITALREADDESCGENERATOR_H
#define DIGITALREADDESCGENERATOR_H

#include "funcdescgenerator.h"

class DigitalReadDescGenerator  :   public  FuncDescGenerator
{

public:

    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed, QString &desc);


};

#endif // DIGITALREADDESCGENERATOR_H
