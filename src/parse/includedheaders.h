#ifndef INCLUDEDHEADERS_H
#define INCLUDEDHEADERS_H

#include <QQuickItem>

class IncludedHeaders : public QQuickItem
{

public:

    IncludedHeaders(QQuickItem *parent = Q_NULLPTR);
    QStringList     retrieveBracketHeaders(QString &fileContent);
    QStringList     retrieveDoubleQuotedHeader(QString &fileContent);

};

#endif // INCLUDEDHEADERS_H
