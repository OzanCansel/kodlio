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
    emit commandOutput(command);
}

void ToolchainV2::sendStdError(QString &err){
    emit stdError(err);
}

void ToolchainV2::sendStdOutput(QString &out){
    emit stdOutput(out);
}
