#ifndef COMPILEWORKER_V2_H
#define COMPILEWORKER_V2_H

#include <QObject>
#include "toolchain/avr/avrtoolchain.h"
#include "toolchain/avr/avrcompileoptions.h"

class CompileWorkerV2 : public QObject
{

    Q_OBJECT

public:

    CompileWorkerV2(AvrToolchain *toolchain , QObject *parent = Q_NULLPTR);

public slots:

    void    compile(const QString &file , CompileOptions* opts);

private:

    AvrToolchain*   _toolchain;

};

#endif // COMPILEWORKER_H
