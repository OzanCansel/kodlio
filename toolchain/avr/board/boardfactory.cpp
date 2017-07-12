#include "boardfactory.h"
#include "unoboard.h"

BoardFactory::BoardFactory(QObject *parent) :QObject(parent)
{

}

ArduinoBoard* BoardFactory::create(QString name){
    if(name == "uno")
        return new UnoBoard();

    return Q_NULLPTR;
}
