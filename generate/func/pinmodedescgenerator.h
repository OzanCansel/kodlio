#ifndef PINMODEDESCGENERATOR_H
#define PINMODEDESCGENERATOR_H

#include "funcdescgenerator.h"

class PinModeDescGenerator : public  FuncDescGenerator
{
public:

    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed, QString &desc);

};

#endif // PINMODEDESCGENERATOR_H
