#ifndef WORKINGDIRECTORYNOTSET_H
#define WORKINGDIRECTORYNOTSET_H

#include <QException>

class WorkingDirectoryNotSet : public QException
{

public:

    void    raise() const { throw *this; }
    WorkingDirectoryNotSet    *clone() const {    return new WorkingDirectoryNotSet(*this); }


};

#endif // WORKINGDIRECTORYNOTSET_H
