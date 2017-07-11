#ifndef AVRCOMPILER_H
#define AVRCOMPILER_H

#include "toolchain/compilerv2.h"
#include "toolchain/compileoptions.h"
#include "toolchain/runoptions.h"
#include "arduinoLibManager/librarymanager.h"

class AvrCompiler : public CompilerV2
{

public:

    AvrCompiler(QQuickItem *parent = Q_NULLPTR);

public slots:

    void        compile(QString file , CompileOptions*    opts);
    QStringList extractDependencies(QString file);
    void        mapLibraries();
    void        run(RunOptions *opts);

};

#endif // AVRCOMPILER_H
