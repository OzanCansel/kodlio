#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <QObject>
#include "toolchain/programmerconfiguration.h"

class Programmer    :   public  QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(ProgrammerConfiguration *configuration READ configuration WRITE setConfiguration NOTIFY configurationChanged)

public:

    Programmer(QQuickItem *parent = Q_NULLPTR);
    void        upload(QString hexFilePath , ProgrammerConfiguration *conf);
    void        upload(QString hexFilePath);
    void        setDebugEnabled(bool enabled);
    ProgrammerConfiguration*    configuration();
    void        setConfiguration(ProgrammerConfiguration *conf);

public slots:

    void        setProgrammerConfiguration(ProgrammerConfiguration *conf);

signals:

    void        commandOutput(QString text);
    void        stdOutput(QString text);
    void        stdError(QString text);
    void        configurationChanged();

private:

    ProgrammerConfiguration *_conf;
    bool        _debugEnabled;

};

#endif // PROGRAMMER_H
