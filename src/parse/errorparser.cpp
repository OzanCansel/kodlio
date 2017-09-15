#include "errorparser.h"
#include <QtQml>

void ErrorParser::registerQmlType(){
    qmlRegisterType<ErrorParser>("Kodlio" , 1 , 0 , "ErrorParser");
}

ErrorParser::ErrorParser(QQuickItem* parent) : QQuickItem(parent)
{
}

void    ErrorParser::parse(QString &err){

}

void ErrorParser::setCompiler(CompilerV2 *compiler){
    _compiler = compiler;
    connect(_compiler , SIGNAL(stdError(QString)) , this , SLOT(stdError(QString)));
    connect(_compiler , SIGNAL(compileError()) , this , SLOT(compilerError()));
    emit compilerChanged();
}

CompilerV2* ErrorParser::compiler(){
    return _compiler;
}


//Slots
void ErrorParser::clear(){
    _err.clear();
}

void ErrorParser::stdError(QString errStr){
    _err.append(errStr);
}

void ErrorParser::compilerError(){
    parse(_err);
}

void ErrorParser::sendStdError(QVariantMap &map){
    emit errorOccurred(map);
}
