#include "includedheaders.h"
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

IncludedHeaders::IncludedHeaders(QQuickItem *parent) : QQuickItem(parent)
{

}

QStringList IncludedHeaders::retrieveHeaders(QString &fileContent){
    QString     includeExpression   =   "#include((\\s)*)(<|\\\")((\\d|[a-zA-Z]|\\.)+)(h?)(\\>|\\\")";
    QStringList headers;
    QRegularExpression  expr(includeExpression);
    QRegularExpressionMatchIterator it = expr.globalMatch(fileContent);

    while(it.hasNext()){
        QRegularExpressionMatch match = it.next();
        QRegularExpression      bracketMatch("<|\\\"");
        QString includeStatement = match.captured(0);
        int headerStart = bracketMatch.match(includeStatement).capturedEnd(0);
        QStringRef  headerRef(&includeStatement , headerStart , includeStatement.length() - headerStart -1);
        QString headerName = headerRef.toString();

        //Eger .h olmadan yazilmissa ekleniyor
        if(!headerName.contains(".h"))
            headerName.append(".h");

    }

    return headers;
}
