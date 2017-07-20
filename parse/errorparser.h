#ifndef ERRORPARSER_H
#define ERRORPARSER_H

#include <QQuickItem>
#include <QVariantList>
#include <QVariant>
#include "toolchain/compilerv2.h"

#define     FILE_PATH               "file"
#define     ROW_LABEL               "row"
#define     COLUMN_LABEL            "column"
#define     MESSAGE_LABEL           "message"

class ErrorParser : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(CompilerV2* compiler READ compiler WRITE setCompiler NOTIFY compilerChanged)

public:

    static void registerQmlType();
    ErrorParser(QQuickItem *parent = Q_NULLPTR);

    virtual void            parse(QString &err);
    void                    setCompiler(CompilerV2  *compiler);
    void                    sendStdError(QVariantHash &map);
    CompilerV2*             compiler();

public slots:

    void        stdError(QString err);
    void        compilerError();

signals:

    void        compilerChanged();
    void        errorOccurred(QVariantHash   error);

private:

    CompilerV2* _compiler;
    QString     _err;

};

#endif // ERRORPARSER_H
