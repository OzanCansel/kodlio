#ifndef UNOBOARD_H
#define UNOBOARD_H

#include "arduinoboard.h"

class UnoBoard : public ArduinoBoard
{

public:

    UnoBoard(QObject *parent = Q_NULLPTR);
    QString     name();
    QString     cFileCompileDefaultParams();
    QString     cppFileCompileDefaultParams();
    QString     sFileCompileDefaultParams();



};

#endif // UNOBOARD_H
