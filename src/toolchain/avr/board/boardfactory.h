#ifndef BOARDFACTORY_H
#define BOARDFACTORY_H

#include <QObject>
#include "boardfactory.h"
#include "arduinoboard.h"

class BoardFactory : public QObject
{

public:

    BoardFactory(QObject *parent = Q_NULLPTR);
    ArduinoBoard*       create(QString name);

};

#endif // BOARDFACTORY_H
