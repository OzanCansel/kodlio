#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QQuickItem>
#include "projectoptions.h"

class ProjectManager : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString projectRoot READ projectRoot WRITE setProjectRoot NOTIFY projectRootChanged)
    Q_PROPERTY(bool projectOpened READ projectOpened NOTIFY projectOpenedChanged)
    Q_PROPERTY(QString projectName READ projectName NOTIFY projectNameChanged)

public:

    static void     registerQmlType();
    ProjectManager(QQuickItem *parent = Q_NULLPTR);
    void            setProjectRoot(QString root);
    QString         projectRoot();
    QString         projectName();
    bool            projectOpened();
    void            sendProjectCreateError(QString err);
    void            sendProjectRemoveError(QString err);
    void            sendProjectCreated();
    void            sendProjectRemoved();
    bool            debugEnabled();
    void            setDebugEnabled(bool enabled);

public slots:

    virtual void    createProject(ProjectOptions *opts);
    virtual void    openProject(ProjectOptions* opts);
    virtual void    removeProject(ProjectOptions *opts);

signals:

    void            projectCreated();
    void            projectRemoved();
    void            projectCreateError(QString error);
    void            projectRemoveError(QString error);
    void            projectRootChanged();
    void            projectOpenedChanged();
    void            projectNameChanged();

private:

    bool            _debugEnabled;
    QString         _projectRoot;
    QString         _projectName;

    void            setProjectName(QString val);

};

#endif // PROJECTMANAGER_H
