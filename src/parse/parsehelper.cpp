#include "parsehelper.h"
#include "selectorstrings.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

bool ParseHelper::isNumber(QString &text){
    QRegularExpression numberExpr("[0-9]+(\\.[0-9]+)?");
    QRegularExpressionMatch res = numberExpr.match(text);

    return res.hasMatch();
}

int ParseHelper::calculateLineNumber(QString &text, int endIdx){
    QRegularExpression  lineBreakExpression("[\\n]");
    QRegularExpressionMatchIterator iterator = lineBreakExpression.globalMatch(QStringRef(&text , 0 , endIdx));

    int lineNumber = 1;
    while(iterator.hasNext()){
        iterator.next();

        lineNumber++;
    }

    return lineNumber;
}

int ParseHelper::calculatePosition(QString text, int lineNumber){

    if(lineNumber == 1)
        return 0;

    QRegularExpression  lineBreakExpression("[\\n]");
    QRegularExpressionMatchIterator it = lineBreakExpression.globalMatch(text);

    int currIdx = 0;

    lineNumber -= 2;
    while(it.hasNext() && currIdx < lineNumber){
        it.next();
        currIdx++;
    }

    if(it.hasNext()){
        QRegularExpressionMatch match = it.next();

        int pos = match.capturedEnd(0);
        return pos;
    }

    return -1;
}

QString ParseHelper::quoteIfNotNumber(QString &text){
    if(isNumber(text))
        return text;
    else
        return QString("\"").append(text).append("\"");
}

QRegularExpressionMatch ParseHelper::nthMatch(QString& text, QString& expr, int nthOccurrence){
    QRegularExpression  expression(expr);
    QRegularExpressionMatchIterator it = expression.globalMatch(text);

    int idx = 0;
    while(it.hasNext()){
        if(idx == nthOccurrence )
            return it.next();
        else
            it.next();

        idx++;
    }

    return QRegularExpressionMatch();
}

bool    ParseHelper::isVariable(QString text){
    SelectorStrings str;
    QRegularExpression  expr(str.variableNameSelector());
    return expr.match(text).hasMatch();
}

