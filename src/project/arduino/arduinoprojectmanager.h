#ifndef ARDUINOPROJECTMANAGER_H
#define ARDUINOPROJECTMANAGER_H

#include <QQuickItem>
#include "../projectmanager.h"

class ArduinoProjectManager : public ProjectManager
{

    Q_OBJECT

public:

    static void registerQmlType();
    ArduinoProjectManager(QQuickItem *parent = Q_NULLPTR);
    void        createProject(ProjectOptions *opts);
    void        removeProject(ProjectOptions *opts);

};

#endif // ARDUINOPROJECTMANAGER_H
