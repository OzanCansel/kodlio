#ifndef ARDUINOBOARD_H
#define ARDUINOBOARD_H

#include <QObject>
#include <QHash>

class ArduinoBoard : public QObject
{

    Q_OBJECT

public:

    ArduinoBoard(QObject *parent = Q_NULLPTR);

    virtual QString     name() = 0;
    virtual QString     objectCodeParams(QString &extension);
    virtual QString     cFileCompileDefaultParams() = 0;
    virtual QString     cppFileCompileDefaultParams() = 0;
    virtual QString     sFileCompileDefaultParams() = 0;
    virtual QString     elfParams();
    virtual QString     eepParams();
    virtual QString     hexParams();

protected:

    QHash<QString, QString> _objectCodeParamsMap;

};

#endif // ARDUINOBOARD_H
