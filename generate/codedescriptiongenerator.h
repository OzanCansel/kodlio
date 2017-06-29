#ifndef CODEDESCRIPTIONGENERATOR_H
#define CODEDESCRIPTIONGENERATOR_H

#include <QQuickItem>
#include <QVariantMap>
#include "codedescriptioninfo.h"
#include "func/funcdescgenerator.h"
#include "parse/functionparser.h"
#include "parse/functionusageparsed.h"

class CodeDescriptionGenerator : public QQuickItem
{

    Q_OBJECT

public:

    CodeDescriptionGenerator(QQuickItem *parent = Q_NULLPTR);

public slots    :

    void    retrieveFunctionDescriptions(QString text);

signals :

    void    descriptionAppend(QVariantMap description);

private :

    QList<FuncDescGenerator*>   _generators;
    FunctionParser              _parser;

};

#endif // CODEDESCRIPTIONGENERATOR_H
