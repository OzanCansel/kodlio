#ifndef PULSEINDESCGENERATORO2_H
#define PULSEINDESCGENERATORO2_H

#include "funcdescgenerator.h"

class PulseInDescGeneratorO2 : public FuncDescGenerator
{
public:

    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed, QString &desc);
};

#endif // PULSEINDESCGENERATORO2_H
