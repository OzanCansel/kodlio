#ifndef ENVIRONMENTVARIABLENOTSET_H
#define ENVIRONMENTVARIABLENOTSET_H

#include <QException>
#include <QDebug>

class EnvironmentVariableNotSet : public  QException
{
public:

    EnvironmentVariableNotSet(QString variableName);
    void    raise() const {
        qDebug() << "Environment Hata -> " << _variableName << " atanmamis !";
        throw *this;
    }
    EnvironmentVariableNotSet    *clone() const {    return new EnvironmentVariableNotSet(*this); }

private:

    QString     _variableName;
};

#endif // ENVIRONMENTVARIABLENOTSET_H
