#ifndef TONEDESCGENERATORO2_H
#define TONEDESCGENERATORO2_H

#include "funcdescgenerator.h"

class ToneDescGeneratorO2 : public FuncDescGenerator
{

public:

    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed,  QString &desc);

};

#endif // TONEDESCGENERATORO2_H
