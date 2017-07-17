#include "toolchainV2.h"
#include <QtQml>

void ToolchainV2::registerQmlType(){
    qmlRegisterType<ToolchainV2>("Kodlio" , 1 , 0 , "Toolchain");
}

ToolchainV2::ToolchainV2(QQuickItem *parent) : QQuickItem(parent){

}

void ToolchainV2::compile(QString folder, CompileOptions *opts){

}

void  ToolchainV2::run(RunOptions *options){

}

void ToolchainV2::setDebugEnabled(bool enabled){
    _debugEnabled = enabled;
}

bool ToolchainV2::debugEnabled(){
    return _debugEnabled;
}

void ToolchainV2::sendCommandOutput(QString command){
    if(debugEnabled()) qDebug() << command;
    emit commandOutput(command);
}

void ToolchainV2::sendStdError(QString err){
    if(debugEnabled()) qDebug() << err;
    emit stdError(err);
}

void ToolchainV2::sendStdOutput(QString out){
    if(debugEnabled()) qDebug() << out;
    emit stdOutput(out);
}

void ToolchainV2::sendInfo(QString out){
    if(debugEnabled())  qDebug() << "Info -> " << out;
    emit infoOutput(out);
}

void ToolchainV2::sendCompileSuccess(){
    emit compileSuccess();
}

void ToolchainV2::sendCompileError(){
    emit compileError();
}

CompilerV2* ToolchainV2::compiler(){
    return Q_NULLPTR;
}

Runner* ToolchainV2::runner(){
    return Q_NULLPTR;
}
