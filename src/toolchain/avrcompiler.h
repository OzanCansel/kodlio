#ifndef AVRCOMPILER_H
#define AVRCOMPILER_H

#include <QObject>
#include <QProcess>

class AvrCompiler : public QObject
{

    Q_OBJECT

public:

    AvrCompiler(QObject  *parent = Q_NULLPTR);

    bool        compileProject(QString projFolder);
    bool        uploadProject(QString projFolder);
    bool        compileCoreFiles(QString outputFolder);
    bool        compileCFile(QString inputPath , QString outputFolder);
    bool        compileSFile(QString inputPath , QString outputPath);
    bool        compileCppFile(QString inputFile , QString outputFiles);
    bool        archiveObjectCodeToLib(QString inputFile , QString outputFileWithoutExtension);
    bool        generateObjectCode(QString inputFile , QString outputPath);
    bool        generateElfFile(QString inputFile , QString libFile , QString output);
    bool        generateEepFile(QString inputFile);
    bool        generateHexFile(QString inputFile);
    bool        uploadHexFile(QString inputFile , QString port);

    bool        standardOutputEnabled();
    bool        errorOutputEnabled();
    void        setStandardOutputEnabled(bool enabled);
    void        setErrorOutputEnabled(bool enabled);
    void        setDebugEnabled(bool enabled);


signals:

    void        standardOutput(QString text);
    void        errorOutput(QString text);

protected:


    virtual QString     getCppParameters() = 0;
    virtual QString     getCParameters() = 0;
    virtual QString     getSParameters() = 0;
    virtual QString     getLinkParameters() = 0;
    virtual QString     getEepFileCompilingArgs() = 0;
    virtual QString     getHexFileCompilingArgs() = 0;
    virtual QString     getUploadHexArgs(QString port) = 0;

    QString     _archivedLibPath;
    QStringList coreFiles;
    QString     extractFileNameWithExtension(QString &fileFullPath);
    QString     getFileExtension(QString &fullPath);
    QString     getArduinoCoreFilesPath();
    QString     getArduinoStandardVariantsPath();
    QString     getErrorOutput(QProcess &process);

private:

    bool        _errorOutputEnabled;
    bool        _standardOutputEnabled;
    bool        _debugEnabled;

};

#endif // AVRCOMPILER_H
