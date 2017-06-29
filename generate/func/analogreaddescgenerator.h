#ifndef ANALOGREADDESCGENERATOR_H
#define ANALOGREADDESCGENERATOR_H

#include "funcdescgenerator.h"

class AnalogReadDescGenerator : public FuncDescGenerator
{
public:

    QString name();
    int     argsCount();
    bool    generate(const FunctionUsageParsed &parsed, QString &desc);
};

#endif // ANALOGREADDESCGENERATOR_H
