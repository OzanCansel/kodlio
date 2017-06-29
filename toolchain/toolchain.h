#ifndef TOOLCHAIN_H
#define TOOLCHAIN_H

#include <QObject>
#include <QStringList>
#include "toolchain/compiler.h"
#include "toolchain/programmer.h"

class Toolchain : public QObject
{

    Q_OBJECT

public:

    Toolchain(Compiler *compiler , Programmer *programmer, QObject *parent = Q_NULLPTR);

    QString     compileFolderRecursively(QString rootPath , QString outputPath , QStringList extraFolders = QStringList());
    bool        uploadHex(QString buildFolderPath);
    void        setDebugEnabled(bool enabled);

signals:

    void        compileStart();
    void        compileEnd(bool success);
    void        compileProgress(double progress);
    void        stdOutput(QString output);

private:

    bool        _debugEnabled;
    Compiler    *_compiler;
    Programmer  *_programmer;

    bool        copyFilesRecursively(QString rootPath , QString destPath , QString pattern , QStringList *l);
    QStringList extractDependecies(const QString &rootPath) const;
    QString     extractFileName(QString path);
    QString     extractFileExtension(QString path);

};

#endif // TOOLCHAIN_H
