#ifndef PARSEHELPER_H
#define PARSEHELPER_H

#include <QString>
#include <QQuickItem>

class ParseHelper : public QQuickItem
{

    Q_OBJECT

public:

    static bool     isNumber(QString &text);
    static int      calculateLineNumber(QString &text , int endIdx);
    static QRegularExpressionMatch      nthMatch(QString &text , QString &expr , int nthOccurrence);
    static QString  quoteIfNotNumber(QString &text);


public slots:

    int     calculatePosition(QString text , int lineNumber);
    bool    isVariable(QString text);

};

#endif // PARSEHELPER_H
