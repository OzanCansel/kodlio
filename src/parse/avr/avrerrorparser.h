#ifndef AVRERRORPARSER_H
#define AVRERRORPARSER_H

#include "parse/errorparser.h"

class AvrErrorParser : public ErrorParser
{

    Q_OBJECT

public:

    static void                 registerQmlType();
    AvrErrorParser(QQuickItem* parent = Q_NULLPTR);
    void                        parse(QString &err) Q_DECL_OVERRIDE;
};

#endif // AVRERRORPARSER_H
