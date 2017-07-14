#ifndef AVRCOMPILEOPTIONS_H
#define AVRCOMPILEOPTIONS_H

#include "toolchain/compileoptions.h"

class AvrCompileOptions : public CompileOptions
{

    Q_OBJECT
    Q_PROPERTY(QString board READ board WRITE setBoard NOTIFY boardChanged)

public:

    static void     registerQmlType();
    AvrCompileOptions(QQuickItem *parent = Q_NULLPTR);
    QString         board();
    void            setBoard(QString val);

signals:

    void    boardChanged();

};

#endif // AVRCOMPILEOPTIONS_H
