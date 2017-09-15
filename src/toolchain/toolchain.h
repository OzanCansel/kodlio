#ifndef TOOLCHAIN_H
#define TOOLCHAIN_H

#include <QObject>
#include <QStringList>
#include "toolchain/compiler.h"
#include "toolchain/programmer.h"
#include "arduinoLibManager/arduinolibdescription.h"
#include "traverse/traversedfileinfo.h"

class Toolchain : public QObject
{

    Q_OBJECT

public:

    Toolchain(Compiler *compiler , Programmer *programmer, QObject *parent = Q_NULLPTR);

    QString     compileFolderRecursively(QString rootPath , QString outputPath , QStringList extraFolders = QStringList());
    bool        uploadHex(QString buildFolderPath);
    void        setDebugEnabled(bool enabled);
    QStringList                     compileLib(QString rootDir , QString outputDir);

signals:

    void        compileStart();
    void        compileEnd(bool success);
    void        compileProgress(double progress);
    void        stdOutput(QString output);

private:

    bool        _debugEnabled;
    Compiler    *_compiler;
    Programmer  *_programmer;

    bool                            copyFilesRecursively(QString rootPath , QString destPath , QString pattern , QStringList *l);
    QStringList                     extractDependecies(const QString &rootPath) const;
    QList<ArduinoLibDescription*>   specifyLibraryDependencies(QString rootPath);
    QString                         extractFileName(QString path);
    QString                         extractFileExtension(QString path);
    void                            extractHeaderAndSources(QString &rootDir , QList<TraversedFileInfo> &files , QStringList &headerNames);

};

#endif // TOOLCHAIN_H
