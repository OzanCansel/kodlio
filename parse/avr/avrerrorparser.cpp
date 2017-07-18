#include "avrerrorparser.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

void AvrErrorParser::registerQmlType(){
    qmlRegisterType<AvrErrorParser>("Kodlio" , 1 , 0 , "AvrErrorParser");
}

AvrErrorParser::AvrErrorParser(QQuickItem *parent) : ErrorParser(parent)
{

}

void AvrErrorParser::parse(QString &err){
    QStringList  errors = err.split("^");
    errors.removeAt(errors.length() - 1);
    QRegularExpression   rowAndColumnMatch("(.*):(\\d+):(\\d+):");

    foreach (QString singleError, errors) {
        QRegularExpressionMatch  positionMatch = rowAndColumnMatch.match(singleError);
        QVariantMap  map;

        QString fPath = positionMatch.captured(1);
        int  rowNumber = positionMatch.captured(2).toInt();
        int  columnNumber = positionMatch.captured(3).toInt();

        QString message = QString(singleError.right(singleError.length() - positionMatch.capturedEnd(3) -1)).trimmed().append("^");

        map[FILE_PATH]  =   QVariant(fPath);
        map[ROW_LABEL]   =   QVariant(rowNumber);
        map[COLUMN_LABEL]=   QVariant(columnNumber);
        map[MESSAGE_LABEL] = QVariant(message);

        sendStdError(map);
    }
}
