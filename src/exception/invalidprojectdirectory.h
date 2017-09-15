#ifndef INVALIDPROJECTDIRECTORY_H
#define INVALIDPROJECTDIRECTORY_H

#include <QException>

class InvalidProjectDirectory : public QException
{

public:

    void    raise() const { throw *this; }
    InvalidProjectDirectory    *clone() const {    return new InvalidProjectDirectory(*this); }

};

#endif // INVALIDPROJECTDIRECTORY_H
