#ifndef PULSEINDESCGENERATOR_H
#define PULSEINDESCGENERATOR_H

#include "funcdescgenerator.h"

class PulseInDescGeneratorO1 : public FuncDescGenerator
{
public:
    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed, QString &desc);
};

#endif // PULSEINDESCGENERATOR_H
