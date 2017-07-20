#include "texttemplate.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "file/fileutil.h"
#include "exception/filenotexists.h"
#include "exception/filecouldnotopen.h"

TextTemplate::TextTemplate(){

}

TextTemplate::TextTemplate(QString fileName)    {
    _fileName = fileName;
    readContent();
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

void TextTemplate::readContent(){
    try{
    _textTemplate = FileUtil::readContent(_fileName);
    } catch(FileCouldNotOpen&){

    } catch(FileNotExists& ){

    }
}

void TextTemplate::setFile(QString file){
    _fileName = file;
    readContent();
}
