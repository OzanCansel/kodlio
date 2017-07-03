#include "compiler.h"
#include "roboskopenvironment.h"
#include "exception/compileerror.h"
#include <QDebug>
#include <QDir>

Compiler::Compiler(QQuickItem *parent) : QQuickItem(parent)
{
    _conf = new CompileConfiguration(this);
}

void Compiler::compileCFile(QString inputFilePath, QString outputFilePath , QStringList include , CompileConfiguration *conf){
    QString     executable(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrBin).append(QDir::separator()).append("avr-gcc "));
    QString     stdOut , stdErr;

    executable.append(conf->getCParameters())
            .append(" ");
    foreach (QString inc, include) {
        executable.append("-I").append(inc).append(" ");
    }
    executable.append(inputFilePath)
            .append(" -o ")
            .append(outputFilePath);
    if(_debugEnabled)   qDebug() << "Komut " << executable;

    emit commandOutput(executable);

    bool result = RoboskopProcess::startProcess(executable , stdOut , stdErr);

    if(!stdOut.isEmpty())   {
        emit stdOutput(stdOut);
        if(_debugEnabled)   qDebug() << "Compiler::compileCFile() stdOut -> " << stdOut;
    }
    if(!stdErr.isEmpty())   {
        emit stdError(stdErr);
        if(_debugEnabled)   qDebug() << "Compiler::compileCFile() stdErr -> " << stdErr;

        throw new CompileError(stdErr);
    }
}

void Compiler::compileCFile(QString inputFilePath, QString outputFilePath, QStringList includes){
    compileCFile(inputFilePath , outputFilePath , includes , configuration());
}

void Compiler::compileCppFile(QString inputFilePath, QString outputFilePath, QStringList includes, CompileConfiguration *conf){
    QString     command(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrBin).append(QDir::separator()).append("avr-g++ "));
    QString     stdOut , stdErr;
    command.append(conf->getCppParameters()).append(" ");
    foreach (QString inc, includes) {
        command.append("-I").append(inc).append(" ");
    }
    command.append(inputFilePath)
            .append(" -o ")
            .append(outputFilePath);

    if(_debugEnabled)   qDebug() << "Komut " << command;

    emit commandOutput(command);

    bool result = RoboskopProcess::startProcess(command , stdOut , stdErr);

    if(!stdOut.isEmpty())   {
        emit stdOutput(stdOut);
        if(_debugEnabled)   qDebug() << "Compiler::compileCppFile() stdOut -> " << stdOut;
    }
    if(!stdErr.isEmpty())   {
        emit stdError(stdErr);
        if(_debugEnabled)   qDebug() << "Compiler::compileCppFile() stdErr -> " << stdErr;

        CompileError(stdErr).raise();
    }
}

void Compiler::compileCppFile(QString inputFilePath, QString outputFilePath, QStringList includes){
    compileCppFile(inputFilePath , outputFilePath , includes , configuration());
}

void Compiler::compileSFile(QString inputFilePath, QString outputFilePath, QStringList includes, CompileConfiguration *conf){
    QString     command(QDir(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrBin)).filePath("avr-gcc "));
    QString     stdOut, stdErr;
    command.append(conf->getSParameters()).append(" ");
    foreach (QString inc, includes) {
        command.append("-I").append(inc).append(" ");
    }
    command.append(inputFilePath)
            .append(" -o ")
            .append(outputFilePath);
    if(_debugEnabled)   qDebug() << "Komut " << command;

    emit commandOutput(command);

    bool result = RoboskopProcess::startProcess(command , stdOut, stdErr);

    if(!stdOut.isEmpty())   {
        emit stdOutput(stdOut);
        if(_debugEnabled)   qDebug() << "Compiler::compileSFile() stdOut -> " << stdOut;
    }
    if(!stdErr.isEmpty())   {
        emit stdError(stdErr);
        if(_debugEnabled)   qDebug() << "Compiler::compileSFile() stdErr -> " << stdErr;

        throw new CompileError(stdErr);
    }
}

void Compiler::compileSFile(QString inputFilePath, QString outputFilePath, QStringList includes){
    compileSFile(inputFilePath , outputFilePath , includes , configuration());
}

void Compiler::archiveObjFiles(QString inputFPath, QString outputFPath, CompileConfiguration *conf){
    QString     command(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrBin).append(QDir::separator()).append("avr-gcc-ar "));
    QString     stdOut , stdErr;
    command.append(conf->getArchiveParameters())
            .append(" ")
            .append(outputFPath)
            .append(" ")
            .append(inputFPath);

    if(_debugEnabled)   qDebug() << "Komut " << command;

    emit commandOutput(command);

    bool result = RoboskopProcess::startProcess(command , stdOut , stdErr);

    if(!stdOut.isEmpty())   {
        emit stdOutput(stdOut);
        if(_debugEnabled)   qDebug() << "Compiler::archiveObjFiles() stdOut -> " << stdOut;
    }
    if(!stdErr.isEmpty())   {
        emit stdError(stdErr);
        if(_debugEnabled)   qDebug() << "Compiler::archiveObjFiles() stdErr -> " << stdErr;

        throw new CompileError(stdErr);
    }
}

void Compiler::archiveObjFiles(QString inputFPath, QString outputFPath){
    archiveObjFiles(inputFPath , outputFPath , configuration());
}

void Compiler::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

void Compiler::linkThemTogether(QString mainObjFile, QString archivedLibPath, QString objFolder, QString outputFilePath , CompileConfiguration *conf){
    QString elfOutputPath = QString(mainObjFile).append(".elf");
    QString eepOutputPath = QString(mainObjFile).append(".eep");
    QString     command1(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrBin).append(QDir::separator()).append("avr-gcc "));
    QString     stdOut,  stdErr;
    command1.append(conf->getElfParameters())
            .append(" -o ")
            .append(elfOutputPath)
            .append(" ")
            .append(mainObjFile)
            .append(" ")
            .append(archivedLibPath)
            .append(" -L")
            .append(objFolder)
            .append(" -lm");

    if(_debugEnabled)   qDebug() << "Komut " << command1;

    emit commandOutput(command1);

    bool result =  RoboskopProcess::startProcess(command1 , stdOut , stdErr);

    if(!stdOut.isEmpty())   {
        emit stdOutput(stdOut);
        if(_debugEnabled)   qDebug() << "Compiler::linkThemTogether() Step 1 stdOut -> " << stdOut;
    }
    if(!stdErr.isEmpty())   {
        emit stdError(stdErr);
        if(_debugEnabled)   qDebug() << "Compiler::linkTemTogether() Step 1 stdErr -> " << stdErr;

        throw new CompileError(stdErr);
    }

    QString     command2(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrBin).append(QDir::separator()).append("avr-objcopy "));

    command2.append(conf->getEepParameters())
            .append(" ")
            .append(elfOutputPath)
            .append(" ")
            .append(eepOutputPath);

    if(_debugEnabled)   qDebug() << "Komut " << command2;
    emit commandOutput(command2);   //Çalıştırılan komut broadcast ediliyor
    result = RoboskopProcess::startProcess(command2 , stdOut , stdErr);
    if(!stdOut.isEmpty())   {
        emit stdOutput(stdOut);
        if(_debugEnabled)   qDebug() << "Compiler::linkThemTogether() Step 2 stdOut -> " << stdOut;
    }
    if(!stdErr.isEmpty())   {
        emit stdError(stdErr);
        if(_debugEnabled)   qDebug() << "Compiler::linkThemTogether() Step 2 stdErr -> " << stdErr;

        throw new CompileError(stdErr);
    }

    QString     command3(RoboskopEnvironment::getInstance()->path(RoboskopEnvironment::AvrBin).append(QDir::separator()).append("avr-objcopy "));

    command3.append(conf->getHexParameters())
            .append(" ")
            .append(elfOutputPath)
            .append(" ")
            .append(outputFilePath);

    if(_debugEnabled)   qDebug() << "Komut " << command3;
    emit commandOutput(command3);   //Çalıştırılan komut broadcast ediliyor
    result = RoboskopProcess::startProcess(command3 , stdOut , stdErr);
    if(!stdOut.isEmpty())   {
        emit stdOutput(stdOut);
        if(_debugEnabled)   qDebug() << "Compiler::linkThemTogether() Step 3 stdOut -> " << stdOut;
    }
    if(!stdErr.isEmpty())   {
        emit stdError(stdErr);
        if(_debugEnabled)   qDebug() << "Compiler::linkThemTogether() Step 3 stdErr -> " << stdErr;

        throw new CompileError(stdErr);
    }

}

void Compiler::linkThemTogether(QString mainObjFile, QString archivedLibPath, QString objFolder, QString outputFilePath){
    linkThemTogether(mainObjFile ,  archivedLibPath , objFolder , outputFilePath , configuration());
}

void Compiler::setConfiguration(CompileConfiguration *configuration){
    _conf = configuration;
}

CompileConfiguration* Compiler::configuration(){
    return _conf;
}
