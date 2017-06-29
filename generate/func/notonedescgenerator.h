#ifndef NOTONEDESCGENERATOR_H
#define NOTONEDESCGENERATOR_H

#include "funcdescgenerator.h"

class NoToneDescGenerator : public FuncDescGenerator
{

public:

    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed, QString &desc);

};

#endif // NOTONEDESCGENERATOR_H
