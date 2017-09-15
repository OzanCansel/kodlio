#ifndef TEXTTEMPLATE_H
#define TEXTTEMPLATE_H

#include <QHash>

class TextTemplate
{

public:

    TextTemplate(QString    fileName);
    TextTemplate();

    void            setFile(QString file);
    void            setValue(QString key , QString value);
    QString         getValue(QString key);
    QString         extract();
    void            setTemplate(QString t);

protected:

    QString                   _textTemplate;

private:

    QHash<QString ,  QString> _hash;
    QString         _fileName;

    void            readContent();

};

#endif // TEXTTEMPLATE_H
