#include "compilererrorparser.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QStringRef>
#include "parse/parsehelper.h"


CompilerErrorParser::CompilerErrorParser(QQuickItem *parent) : QQuickItem(parent)
{

}

void    CompilerErrorParser::extractErrors(QString text){

    QRegularExpression  errorExpression(":\\d+:\\d+: error:[^\\^]+");
    QRegularExpressionMatchIterator iterator =  errorExpression.globalMatch(text);

    while(iterator.hasNext()){
        QRegularExpressionMatch match =  iterator.next();
        QString columnNumSeperatorExp(":");

        QString fullError = match.captured(0);
        qDebug() << "Full " << fullError;
        QRegularExpressionMatch secondMatch = ParseHelper::nthMatch(fullError , columnNumSeperatorExp , 1);
        int lineNumEndIdx =  secondMatch.capturedStart(0);
        int columnNumStartIdx = secondMatch.capturedEnd(0);
        int lineNum = QStringRef(&fullError , 1 , lineNumEndIdx - 1).toInt();
        int columnNumEndIdx = ParseHelper::nthMatch(fullError , columnNumSeperatorExp , 2).capturedStart(0);
        int columnNum = QStringRef(&fullError , columnNumStartIdx , columnNumEndIdx - columnNumStartIdx).toInt();
        QString errorText = QRegularExpression("error:[^\\^]+").match(fullError).captured(0);
        errorText = errorText.right(errorText.length() - 7);

        qDebug() << "Error Line -> " << lineNum << " Column -> " << columnNum << " Error -> " << errorText;

        QVariantHash map;
        map["lineNumber"]       = lineNum;
        map["columnNumber"]     = columnNum;
        map["error"]            = errorText;

        emit errorOccurred(map);
    }
}
