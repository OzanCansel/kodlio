#ifndef TEXTTEMPLATE_H
#define TEXTTEMPLATE_H

#include <QHash>

class TextTemplate
{

public:

    TextTemplate();

    void            setValue(QString key , QString value);
    QString         getValue(QString key);
    QString         extract();
    void            setTemplate(QString t);

protected:

    QString                   _textTemplate;

private:

    QHash<QString ,  QString> _hash;

};

#endif // TEXTTEMPLATE_H
