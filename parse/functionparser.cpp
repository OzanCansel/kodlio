#include "functionparser.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QStringRef>

FunctionParser::FunctionParser()
{
    //    _functionNameSelector = QString("[a-zA-Z]+(\\d)*");
    _functionNameSelector = QString("[a-zA-Z]+");
    _doubleSelector =   QString("[0-9]+(\\.[0-9]+)?");
    _skipWhiteSpace =   group(group("\\s").append("*"));
    _stringSelector =   group("\".*\"");
    _notCommentSelector =  group("(?!(\\s*((\\/\\/)|(\\/\\*))))");

    //(?!(\s*((\/\/)|(\/\*))))
    _parameterSingleSelector = group(QString(_functionNameSelector).append("|").append(_doubleSelector));
    _parameterSelector = group(QString(_skipWhiteSpace).
                               append(group(QString(_functionNameSelector).append("|").append(_doubleSelector).append("|").append(_stringSelector)))
                               .append(_skipWhiteSpace).append(group("\\,").append("?"))).append("*");

    _functionCompleteSelector =     group(
                QString()
                .append(group(_functionNameSelector))
                .append(_skipWhiteSpace)
                .append("\\(")
                .append(_skipWhiteSpace)
                .append(group(_parameterSelector))
                .append(_skipWhiteSpace)
                .append("\\)")
                .append(_skipWhiteSpace)
                .append("\\;")
                .append(_notCommentSelector)
                );
}

QList<FunctionUsageParsed>  FunctionParser::extractFunctions(QString &text){
    QList<FunctionUsageParsed>  functions;
    QRegularExpression  funcRegex(_functionCompleteSelector);
    QRegularExpressionMatchIterator it = funcRegex.globalMatch(text );

    while(it.hasNext()){
        FunctionUsageParsed func;
        QRegularExpressionMatch match = it.next();

        QRegularExpression  nameSelector(_functionNameSelector);
        QRegularExpression  paramsSelector(_parameterSingleSelector);

        QString     cap = match.captured(0);
        QString     funcName = nameSelector.match(match.captured(0)).captured(0);
        int         paramsStartIdx = cap.indexOf("(") + 1;
        int         paramsEndIdx = cap.indexOf(")");
        QString     funcParamsText = QStringRef(&cap , paramsStartIdx , paramsEndIdx - paramsStartIdx).toString();
        QRegularExpressionMatchIterator paramIt = paramsSelector.globalMatch(funcParamsText);

        QStringList params;

        while(paramIt.hasNext()){
            QRegularExpressionMatch match = paramIt.next();

            params << match.captured(0);

            //Fonksiyon argumanı ekleniyor.
            func.addArgument(match.captured(0));
        }

        func.setFunctionName(funcName); //Fonksiyon adı atanıyor
        func.setMatchIdx(match.capturedStart(0));

        functions.append(func);
    }

    return functions;
}

QString FunctionParser::group(QString str){
    return QString("(").append(str).append(")");
}
