#ifndef ARDUINOPROJECTWATCHERR_H
#define ARDUINOPROJECTWATCHERR_H

#include "project/projectwatcher.h"

class ArduinoProjectWatcher : public ProjectWatcher {

    Q_OBJECT

public:

    static void registerQmlType();
    ArduinoProjectWatcher(QQuickItem *parent = Q_NULLPTR);

public slots:

    QString     retrieveMainFile();

};

#endif // ARDUINOPROJECTWATCHERR_H
