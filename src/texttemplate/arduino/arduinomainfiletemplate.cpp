#include "arduinomainfiletemplate.h"
#include "environment.h"

ArduinoMainFileTemplate::ArduinoMainFileTemplate()   {
    QString templatePath = QString("%0/template/arduino/mainFile").arg(Environment().appStartDir());
    setFile(templatePath);
}

void ArduinoMainFileTemplate::setDate(QString date){
    setValue(CREATED_DATE_LABEL , date);
}

void ArduinoMainFileTemplate::setFileName(QString f){
    setValue(FILENAME_LABEL , f);
}
