#ifndef GENERATOR_H
#define GENERATOR_H

#include "parse/functionusageparsed.h"

class FuncDescGenerator
{

public:

    FuncDescGenerator();
    virtual QString     name() = 0;
    virtual int         argsCount() = 0;
    virtual bool        generate(const FunctionUsageParsed &parsed , QString& desc) = 0;

};

#endif // GENERATOR_H
