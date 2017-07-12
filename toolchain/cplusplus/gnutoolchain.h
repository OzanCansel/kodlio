#ifndef GNUTOOLCHAIN_H
#define GNUTOOLCHAIN_H

#include "toolchain/toolchainV2.h"
#include "cpluscompiler.h"

class GnuToolChain : public ToolchainV2
{

public:

    GnuToolChain(QQuickItem *parent = Q_NULLPTR);
    CompilerV2*  compiler();


public slots:

    void    run(RunOptions *options) Q_DECL_OVERRIDE;
    void    compile(QString folder , CompileOptions *opts) Q_DECL_OVERRIDE;

private:

    CPlusCompiler   _compiler;

};

#endif // GNUTOOLCHAIN_H
