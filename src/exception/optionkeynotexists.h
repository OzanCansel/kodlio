#ifndef OPTIONKEYNOTEXISTS_H
#define OPTIONKEYNOTEXISTS_H

#include <QException>
#include <QDebug>

class OptionKeyNotExists : public QException
{

public:

    OptionKeyNotExists(QString key);

    void    raise() const {
        qDebug() << _key << " bulunamadi";
        throw *this;
    }
    OptionKeyNotExists* clone() const {return new OptionKeyNotExists(*this);}

private:

    QString     _key;
};

#endif // OPTIONKEYNOTEXISTS_H
