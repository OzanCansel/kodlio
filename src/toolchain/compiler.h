#ifndef COMPILER_H
#define COMPILER_H

#include <QObject>
#include "roboskopprocess.h"
#include "compileconfiguration.h"

class Compiler : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(CompileConfiguration *configuration READ configuration WRITE setConfiguration NOTIFY configurationChaned)

public:

    Compiler(QQuickItem *parent = Q_NULLPTR);

    void    compileCFile(QString inputFilePath , QString outputFilePath , QStringList includes , CompileConfiguration *conf);
    void    compileCFile(QString inputFilePath , QString outputFilePath , QStringList includes);
    void    compileCppFile(QString inputFilePath , QString outputFilePath,  QStringList includes , CompileConfiguration *conf);
    void    compileCppFile(QString inputFilePath , QString outputFilePath , QStringList includes);
    void    compileSFile(QString inputFilePath , QString outputFilePath , QStringList includes , CompileConfiguration *conf);
    void    compileSFile(QString inputFilePath, QString outputFilePath , QStringList includes);
    void    archiveObjFiles(QString inputFPath , QString outputFPath , CompileConfiguration *conf);
    void    archiveObjFiles(QString inputFPath , QString outputFPath);
    void    linkThemTogether(QString mainObjFile , QString archivedLibPath , QString objFolder , QString outputFilePath , CompileConfiguration *conf);
    void    linkThemTogether(QString mainObjFile, QString archivedLibPath, QString objFolder, QString outputFilePath);
    void    setDebugEnabled(bool debug);
    CompileConfiguration*   configuration();
    void    setConfiguration(CompileConfiguration *configuration);

signals:

    void        commandOutput(QString text);
    void        stdOutput(QString text);
    void        stdError(QString text);
    void        configurationChaned();

private:

    bool        _debugEnabled;
    CompileConfiguration    *_conf;

};

#endif // COMPILER_H
