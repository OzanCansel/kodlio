#ifndef AVRTOOLCHAIN_H
#define AVRTOOLCHAIN_H

#include <QQuickItem>
#include "toolchain/toolchain.h"
#include "toolchain/toolchainV2.h"
#include "avrcompilerV2.h"


class AvrToolchain : public ToolchainV2
{

public:

    AvrToolchain(QQuickItem *parent = Q_NULLPTR);

    virtual void    compile(QString folder, CompileOptions *opts);
    void    extractDependencies(QString file , QList<ArduinoLibDescription*>    &dependantLibs);
    void            mergeDependencies(QList<ArduinoLibDescription*> &root , QList<ArduinoLibDescription*> &merged);
    virtual void    run(RunOptions *options);
    void            map();
    virtual CompilerV2*    compiler();

private:

    AvrCompilerV2   _compiler;
    QHash<QString , ArduinoLibDescription*> _headerToLibMap;
    LibraryManager  _libManager;

};

#endif // AVRTOOLCHAIN_H
