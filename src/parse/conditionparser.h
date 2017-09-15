#ifndef CONDITIONPARSER_H
#define CONDITIONPARSER_H

#include <QString>
#include "selectorstrings.h"

class ConditionParser
{
public:

    ConditionParser();
    void        parse(QString &text);

private:

    SelectorStrings patterns;


    QString _compareExpression;
    QString _comparatorSelector;

};

#endif // CONDITIONPARSER_H
