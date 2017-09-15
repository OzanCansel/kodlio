#ifndef DELAYDESCGENERATOR_H
#define DELAYDESCGENERATOR_H

#include    "funcdescgenerator.h"

class DelayDescGenerator : public  FuncDescGenerator
{

public:

    DelayDescGenerator();
    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed , QString &desc);

};

#endif // DELAYDESCGENERATOR_H
