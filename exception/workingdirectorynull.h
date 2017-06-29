#ifndef WORKINGDIRECTORYNULL_H
#define WORKINGDIRECTORYNULL_H

#include <QException>

class WorkingDirectoryNull : public QException
{

public:

    void    raise() const { throw *this; }
    WorkingDirectoryNull    *clone() const {    return new WorkingDirectoryNull(*this); }

};

#endif // WORKINGDIRECTORYNULL_H
