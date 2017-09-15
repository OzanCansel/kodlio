#ifndef AVRCOMPILER_V2_H
#define AVRCOMPILER_V2_H

#include "toolchain/compilerv2.h"
#include "toolchain/compileoptions.h"
#include "toolchain/runoptions.h"
#include "arduinoLibManager/librarymanager.h"

class AvrCompilerV2 : public CompilerV2
{

public:

    static void registerQmlType();
    AvrCompilerV2(QQuickItem *parent = Q_NULLPTR);

public slots:

    void        generateObjFile(QString &file , QString &output , QStringList &includes , QString &boardName);
    void        archiveFiles(QStringList &objFiles , QString &output);
    QString     generateHex(QString &archiveFile, QString &buildFolder , QStringList &generatedObjFile);
    void        run(RunOptions *opts);

private:

    LibraryManager  manager;
    QStringList     _allowedExtensions;

};

#endif // AVRCOMPILER_V2_H
