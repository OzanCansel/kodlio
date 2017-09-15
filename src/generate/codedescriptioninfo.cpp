#include "codedescriptioninfo.h"

void CodeDescriptionInfo::registerQmlType()
{
    qmlRegisterType<CodeDescriptionInfo>("Roboskop" , 1 , 0 , "CodeDescriptionInfo");
}

CodeDescriptionInfo::CodeDescriptionInfo(QQuickItem *parent) : QQuickItem(parent)
{

}

CodeDescriptionInfo::CodeDescriptionInfo(const CodeDescriptionInfo &other){
    _lineNumber = other.lineNumber();
    _description = other.description();
}

void CodeDescriptionInfo::setLineNumber(int val){
    _lineNumber = val;
    emit lineNumberChanged();
}

void CodeDescriptionInfo::setDescription(QString val){
    _description = val;
    emit descriptionChanged();
}

int CodeDescriptionInfo::lineNumber() const{
    return  _lineNumber;
}

QString CodeDescriptionInfo::description() const{
    return  _description;
}

CodeDescriptionInfo& CodeDescriptionInfo::operator =(const CodeDescriptionInfo &other){
    _description = other.description();
    _lineNumber = other.lineNumber();
    return *this;
}
