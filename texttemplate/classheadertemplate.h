#ifndef HEADERTEMPLATE_H
#define HEADERTEMPLATE_H

#include "texttemplate.h"

class ClassHeaderTemplate :  public TextTemplate
{

public:

    ClassHeaderTemplate();
    void    setClassName(QString className);

};

#endif // HEADERTEMPLATE_H
