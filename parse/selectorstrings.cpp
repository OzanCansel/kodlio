#include "selectorstrings.h"

SelectorStrings::SelectorStrings()
{

    _doubleSelector         =   QString("[0-9]+(\\.[0-9]+)?");
    _variableNameSelector   =   QString("[a-zA-Z]+(\\d)*");
    _skipWhiteSpace         =   group(group("\\s").append("*"));

}

QString SelectorStrings::group(QString str){
    return QString("(").append(str).append(")");
}

QString SelectorStrings::doubleSelector(){
    return _doubleSelector;
}

QString SelectorStrings::variableNameSelector(){
    return _variableNameSelector;
}

QString SelectorStrings::skipWhiteSpace(){
    return _skipWhiteSpace;
}
