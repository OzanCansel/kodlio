#ifndef COMPILEERROR_H
#define COMPILEERROR_H

#include <QException>

class CompileError : public QException
{

public:

    CompileError(QString _err);

    QString     err();
    void    raise() const { throw *this; }
    CompileError    *clone() const { return new CompileError(*this); }

private:

    QString     _err;

};

#endif // COMPILEERROR_H
