#ifndef SERIALBEGINDESCGENERATOR_H
#define SERIALBEGINDESCGENERATOR_H

#include "funcdescgenerator.h"

class SerialBeginDescGenerator :  public FuncDescGenerator
{

public:

    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed, QString &desc);

};

#endif // SERIALBEGINDESCGENERATOR_H
