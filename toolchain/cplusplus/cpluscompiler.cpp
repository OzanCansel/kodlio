#include "cpluscompiler.h"
#include "rprocess.h"
#include "cplusenvironment.h"

CPlusCompiler::CPlusCompiler(QQuickItem *parent) : CompilerV2(parent)
{
    _env    =   new CPlusEnvironment(this);
}

void CPlusCompiler::generateObjectCode(QString file , QString outputPath , CompileOptions *options){
    QString     command(_env->get("g++"));

    if(!outputPath.contains(".o"))
        throw "GenerateObjectCode() - outputPath .o uzantili olmalidir!";

    command.append(" -c -g ")
            .append(file)
            .append(" -o ")
            .append(outputPath);

    sendCommandOutput(command);
    RProcess process;

    process.runWait(command , 10000);

    sendStdError(process.stdErr());
    sendStdOutput(process.stdOut());
}

void CPlusCompiler::createExecutable(QString outputName, QStringList objFiles){
    QString     command(_env->get("g++"));

    command.append(" -g -o ")
            .append(outputName)
            .append(" ");

    foreach (QString objectFile, objFiles) {
        command.append(objectFile)
                .append(" ");
    }


    sendCommandOutput(command);
    RProcess    process;

    process.runWait(command , 10000);

    sendStdError(process.stdErr());
    sendStdOutput(process.stdOut());
}
