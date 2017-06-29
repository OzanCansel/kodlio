#ifndef FUNCTIONPARSER_H
#define FUNCTIONPARSER_H

#include <QStringList>
#include <QQuickItem>
#include <QString>
#include "functionusageparsed.h"

class FunctionParser  : public QQuickItem
{

    Q_OBJECT

public:

    FunctionParser();

public slots:

    QList<FunctionUsageParsed>  extractFunctions(QString &text);

private:

    QString _functionNameSelector;
    QString _parameterSelector;
    QString _doubleSelector;
    QString _functionCompleteSelector;
    QString _skipWhiteSpace;
    QString _parameterSingleSelector;
    QString _stringSelector;
    QString _notCommentSelector;

    QString group(QString str);
};

#endif // FUNCTIONPARSER_H
