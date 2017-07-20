#ifndef CPPTEMPLATE_H
#define CPPTEMPLATE_H

#include "texttemplate.h"
#define CREATED_DATE_LABEL      "createdDate"
#define FILENAME_LABEL          "fileName"

class GenericFileTemplate : public TextTemplate
{

public:

    GenericFileTemplate();
    void        setDate(QString date);
    void        setFileName(QString fileName);

};

#endif // CPPTEMPLATE_H
