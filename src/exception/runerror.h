#ifndef RUNERROR_H
#define RUNERROR_H

#include <QException>
#include <QDebug>

class RunError : public QException
{

public:

    RunError(QString message);
    void    raise() const{
        qDebug() << "RunError -> " << _message;
        throw *this;
    }
    RunError*   clone() const { return new RunError(*this);}

private:

    QString _message;
};

#endif // RUNERROR_H
