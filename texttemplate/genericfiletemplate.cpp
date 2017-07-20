#include "genericfiletemplate.h"
#include "environment.h"
#include <QDateTime>

GenericFileTemplate::GenericFileTemplate()  {
    QString templatePath = QString("%0/template/genericFileTemplate").arg(Environment().appStartDir());
    setFile(templatePath);
    QString date = QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm");
    setDate(date);
}

void GenericFileTemplate::setDate(QString date){
    setValue(CREATED_DATE_LABEL , date);
}

void GenericFileTemplate::setFileName(QString f){
    setValue(FILENAME_LABEL , f);
}
