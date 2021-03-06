#ifndef AVRTOOLCHAIN_H
#define AVRTOOLCHAIN_H

#include <QQuickItem>
#include <QThread>
#include "toolchain/toolchainV2.h"
#include "arduinoLibManager/arduinolibdescription.h"
#include "avrcompilerV2.h"
#include "avrrunner.h"
#include "arduinoLibManager/librarymanager.h"

#define PROGRESS_EXTRACT_DEPENDENCIES           0.1
#define PROGRESS_COMPILE_LIB_TOTAL_PORTION      0.3
#define PROGRESS_COMPILE_SOURCE_TOTAL_PORTION   0.4
#define PROGRESS_ARCHIVE_TOTAL_PORTION          0.2

class AvrToolchain : public ToolchainV2
{

    Q_OBJECT
    Q_PROPERTY(QString compiledHexFile READ compiledHexFile WRITE setCompiledHexFile NOTIFY compiledHexFileChanged)
    Q_PROPERTY(LibraryManager* libManager READ libManager WRITE setLibManager NOTIFY libManagerChanged)

public:

    static void     registerQmlType();
    AvrToolchain(QQuickItem *parent = Q_NULLPTR);

    typedef  struct{
        QString                 headerPath;
        QString                 headerName;
        ArduinoLibDescription   *desc;
    } HeaderMapInfo;

    virtual void            compile(QString file, CompileOptions *opts);
    void                    compileLib(ArduinoLibDescription *desc , QString &outputFolder , QString &boardName , QStringList &generateObjectFiles);
    void                    extractDependencies(QString file , QList<ArduinoLibDescription*>    &dependantLibs , QStringList &discoredFiles);
    void                    mergeDependencies(QList<ArduinoLibDescription*> &root , QList<ArduinoLibDescription*> &merged);
    virtual void            run(RunOptions *options);
    void                    map();
    QString                 compiledHexFile();
    void                    setCompiledHexFile(QString path);
    void                    setLibManager(LibraryManager* libManager);
    HeaderMapInfo           getHeaderMap(QString headerName);
    LibraryManager*         libManager();
    virtual CompilerV2*     compiler();
    virtual Runner*         runner();
    bool                    preprocessInoFile(QString filePath , QString outputFile);


public slots:

    void                    librariesChanged(ArduinoLibDescription* desc);

signals:

    void                    compiledHexFileChanged();
    void                    libManagerChanged();

private:

    AvrCompilerV2           _compiler;
    AvrRunner               _runner;
    QStringList             _headers;
    QStringList             _compatibleSourceExtensions;
    QList<HeaderMapInfo>    _headerMaps;
    LibraryManager*         _libManager;
    QThread                 _compilerThread;
    QString                 _lastHexFile;

    bool            isHeaderFile(QString &fileName);
    bool            isSourceFile(QString &fileName);
    bool            isInoFile(QString &fileName);
    bool            possibleSourceFiles(QString &headerName , QStringList &sourceFile);
    QDir            mkpath(QString path);
};

#endif // AVRTOOLCHAIN_H
