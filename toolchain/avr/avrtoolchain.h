#ifndef AVRTOOLCHAIN_H
#define AVRTOOLCHAIN_H

#include <QQuickItem>
#include "toolchain/toolchain.h"
#include "toolchain/toolchainV2.h"


class AvrToolchain : public ToolchainV2
{

public:

    AvrToolchain(QQuickItem *parent = Q_NULLPTR);

    virtual void    compile(QString folder, CompileOptions *opts);
    virtual void    run(RunOptions *options);

};

#endif // AVRTOOLCHAIN_H
