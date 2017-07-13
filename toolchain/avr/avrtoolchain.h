#ifndef AVRTOOLCHAIN_H
#define AVRTOOLCHAIN_H

#include <QQuickItem>
#include "toolchain/toolchain.h"
#include "toolchain/toolchainV2.h"
#include "arduinoLibManager/arduinolibdescription.h"
#include "avrcompilerV2.h"


class AvrToolchain : public ToolchainV2
{

public:

    static void     registerQmlType();
    AvrToolchain(QQuickItem *parent = Q_NULLPTR);

    typedef  struct{
        QString                 headerPath;
        QString                 headerName;
        ArduinoLibDescription   *desc;
    } HeaderMapInfo;

    virtual void            compile(QString file, CompileOptions *opts);
    void                    compileLib(ArduinoLibDescription *desc , QString &outputFolder , QString &boardName);
    void                    extractDependencies(QString file , QList<ArduinoLibDescription*>    &dependantLibs , QStringList &discoredFiles);
    void                    mergeDependencies(QList<ArduinoLibDescription*> &root , QList<ArduinoLibDescription*> &merged);
    virtual void            run(RunOptions *options);
    void                    map();
    HeaderMapInfo           getHeaderMap(QString headerName);
    virtual CompilerV2*     compiler();

private:

    AvrCompilerV2   _compiler;
    QStringList     _headers;
    QStringList     _compatibleSourceExtensions;
    QList<HeaderMapInfo>    _headerMaps;
    LibraryManager  _libManager;

    bool            isHeaderFile(QString &fileName);
    bool            isSourceFile(QString &fileName);
    bool            possibleSourceFiles(QString &headerName , QStringList &sourceFile);


};

#endif // AVRTOOLCHAIN_H
