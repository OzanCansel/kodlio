#ifndef FUNCUSAGEGENERATOR_H
#define FUNCUSAGEGENERATOR_H

#include "funcdescgenerator.h"

class DigitalWriteDescGenerator : public FuncDescGenerator
{

public:


    int     argsCount();
    QString name();
    bool    generate(const FunctionUsageParsed &parsed , QString& desc);

};

#endif // FUNCUSAGEGENERATOR_H
