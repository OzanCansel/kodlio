#ifndef TEMPDIRECTORYCREATIONFAILED_H
#define TEMPDIRECTORYCREATIONFAILED_H

#include <QException>

class TempDirectoryCreationFailed : public QException
{

public:

    void    raise() const { throw *this; }
    TempDirectoryCreationFailed    *clone() const {    return new TempDirectoryCreationFailed(*this); }

};

#endif // TEMPDIRECTORYCREATIONFAILED_H
