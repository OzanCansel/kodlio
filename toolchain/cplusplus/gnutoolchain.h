#ifndef GNUTOOLCHAIN_H
#define GNUTOOLCHAIN_H

#include "toolchain/toolchainV2.h"

class GnuToolChain : public ToolchainV2
{

public:

    GnuToolChain(QQuickItem *parent = Q_NULLPTR);

public slots:

    void    run(RunOptions *options) Q_DECL_OVERRIDE;
    void    compile(QString folder , CompileOptions *opts) Q_DECL_OVERRIDE;

};

#endif // GNUTOOLCHAIN_H
