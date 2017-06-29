#include "conditionparser.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>


ConditionParser::ConditionParser()
{
    _compareExpression = QString(patterns.skipWhiteSpace())
            .append(patterns.variableNameSelector())
            .append(patterns.skipWhiteSpace())
            .append(_comparatorSelector);
}


void ConditionParser::parse(QString &text){
    QRegularExpression  expression(_compareExpression);
}
