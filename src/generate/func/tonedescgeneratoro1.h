#ifndef TONEGENERATOR_H
#define TONEGENERATOR_H

#include "funcdescgenerator.h"

class ToneDescGeneratorO1 : public FuncDescGenerator
{

public:

    QString     name();
    int         argsCount();
    virtual bool        generate(const FunctionUsageParsed &parsed , QString& desc);

};

#endif // TONEGENERATOR_H
