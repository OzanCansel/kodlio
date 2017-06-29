#ifndef SERIALPRINTDESCGENERATOR_H
#define SERIALPRINTDESCGENERATOR_H

#include "funcdescgenerator.h"

class SerialPrintDescGenerator : public  FuncDescGenerator
{

public:

    QString     name();
    int         argsCount();
    bool        generate(const FunctionUsageParsed &parsed, QString &desc);

};

#endif // SERIALPRINTDESCGENERATOR_H
