#include "compilerv2.h"

CompilerV2::CompilerV2(QQuickItem *parent) : QQuickItem(parent){

}

void CompilerV2::sendStdOutput(QString output){
    if(debugEnabled() && !output.isEmpty()) qDebug() << "CompilerV2 out -> " << output;
    emit stdOutput(output);
}

void CompilerV2::sendStdError(QString err){
    if(debugEnabled() && !err.isEmpty()) qDebug() << "CompilerV2 err -> " << err;
    emit stdError(err);
}

void CompilerV2::sendCommandOutput(QString &command){
    if(debugEnabled() && !command.isEmpty()) qDebug() << "CompilerV2 command ->" << command;
    emit commandOutput(command);
}

void CompilerV2::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

bool CompilerV2::debugEnabled(){
    return _debugEnabled;
}
