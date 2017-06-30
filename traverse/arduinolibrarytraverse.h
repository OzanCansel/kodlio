#ifndef ARDUINOLIBRARYTRAVERSE_H
#define ARDUINOLIBRARYTRAVERSE_H

#include "filetraverse.h"
#include "arduinoLibManager/arduinolibdescription.h"

class ArduinoLibraryTraverse : public FileTraverse
{

    Q_OBJECT

public:

    ArduinoLibraryTraverse(QQuickItem *parent = Q_NULLPTR);
    void        setWorkingDir(QString dir);

public slots:

    QList<ArduinoLibDescription*>  retrieveLibraries();

private:

    QString         _dir;

};

#endif // ARDUINOLIBRARYTRAVERSE_H
