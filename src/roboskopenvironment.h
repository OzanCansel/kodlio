#ifndef ROBOSKOPENVIRONMENT_H
#define ROBOSKOPENVIRONMENT_H

#include <QCoreApplication>
#include <QDir>
#include <QHash>
#include <QObject>

class RoboskopEnvironment : public QObject
{

    Q_OBJECT

public:

    static      RoboskopEnvironment*    getInstance();
    static      RoboskopEnvironment*    self;

    enum    Paths{  AvrBin , ArduinoCore , ArduinoLibraries, Variants , AvrDudeConf };
    RoboskopEnvironment(QObject *parent = Q_NULLPTR);

public slots:

    QString     appDirPath();
    QString     getAvrBinPath();
    QString     getCoreEnvironment();
    QString     getLibrariesPath();
    QString     getVariantsPath(QString type);
    QString     getAvrDudeConf();
    QString     path(Paths path);
    QString     print();

private:

    QDir                    _baseDir;
    QHash<Paths , QString > _map;

};

#endif // ROBOSKOPENVIRONMENT_H
