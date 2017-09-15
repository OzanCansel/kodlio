#ifndef CPLUSCOMPILER_H
#define CPLUSCOMPILER_H

#include <QString>
#include "toolchain/compilerv2.h"
#include "toolchain/compileoptions.h"
#include "environment.h"

class CPlusCompiler : public CompilerV2
{

public:

    CPlusCompiler(QQuickItem *parent = Q_NULLPTR);

    void    generateObjectCode(QString file , QString outputPath , CompileOptions *options);
    void    createExecutable(QString output , QStringList objectFiles);
    void    setEnv(Environment  *env);

private:

    Environment *_env;

};

#endif // CPLUSCOMPILER_H
