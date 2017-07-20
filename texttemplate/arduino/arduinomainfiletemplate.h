#ifndef ARDUINOMAINFILETEMPLATE_H
#define ARDUINOMAINFILETEMPLATE_H

#include "../texttemplate.h"

#define CREATED_DATE_LABEL      "createdDate"
#define FILENAME_LABEL          "fileName"

class ArduinoMainFileTemplate : public TextTemplate {

public:

    ArduinoMainFileTemplate();
    void        setDate(QString date);
    void        setFileName(QString fileName);

};

#endif // ARDUINOMAINFILETEMPLATE_H
