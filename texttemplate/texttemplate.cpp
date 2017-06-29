#include "texttemplate.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

TextTemplate::TextTemplate()
{

}

void TextTemplate::setValue(QString key, QString value){
    _hash[key] = value;
}

QString TextTemplate::getValue(QString key){
    return _hash[key];
}

QString TextTemplate::extract(){

    QString processed = _textTemplate;

    foreach (QString key, _hash.keys()) {
        QString pattern = QString("<<").append(key).append(">>");
        QRegularExpression  re(pattern);

        processed = _textTemplate.replace(re , _hash.value(key));
    }

    return processed;
}

void TextTemplate::setTemplate(QString t){
    _textTemplate = t;
}
