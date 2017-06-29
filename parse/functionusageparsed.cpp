#include "functionusageparsed.h"

FunctionUsageParsed::FunctionUsageParsed(QQuickItem *parent) : QQuickItem(parent){
    _matchIdx = -1;
}

FunctionUsageParsed::FunctionUsageParsed(const FunctionUsageParsed &other){
    _functionName = other.functionName();
    _args = other.args();
    _matchIdx = other.matchIdx();
}

QString FunctionUsageParsed::functionName() const{
    return _functionName;
}

QStringList FunctionUsageParsed::args() const{
    return _args;
}

void FunctionUsageParsed::setArguments(QStringList args){
    _args = args;
}

void FunctionUsageParsed::setFunctionName(QString funcName){
    _functionName = funcName;
}

void FunctionUsageParsed::addArgument(QString arg){
    _args.append(arg);
}

FunctionUsageParsed& FunctionUsageParsed::operator =(const FunctionUsageParsed &other){
    _args = other.args();
    _functionName = other.functionName();
    return *this;
}

void FunctionUsageParsed::setMatchIdx(int val){
    _matchIdx = val;
}

int FunctionUsageParsed::matchIdx() const{
    return _matchIdx;
}
