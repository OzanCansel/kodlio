#ifndef COMPILEERROR_H
#define COMPILEERROR_H

#include <QException>

class CompileError : public QException
{

public:

    CompileError(QString err);

    void    raise() const { throw *this; }
    CompileError    *clone() const { return new CompileError(*this); }

    QString     err;

};

#endif // COMPILEERROR_H
