#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QQuickItem>
#include "projectoptions.h"

class ProjectManager : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString projectRoot READ projectRoot WRITE setProjectRoot NOTIFY projectRootChanged)

public:

    static void     registerQmlType();
    ProjectManager(QQuickItem *parent = Q_NULLPTR);
    void            setProjectRoot(QString root);
    QString         projectRoot();
    void            sendProjectCreateError(QString err);
    void            sendProjectRemoveError(QString err);
    void            sendProjectCreated();
    void            sendProjectRemoved();
    bool            debugEnabled();
    void            setDebugEnabled(bool enabled);

public slots:

    virtual void    createProject(ProjectOptions *opts);
    virtual void    removeProject(ProjectOptions *opts);

signals:

    void            projectCreated();
    void            projectRemoved();
    void            projectCreateError(QString error);
    void            projectRemoveError(QString error);
    void            projectRootChanged();

private:

    bool            _debugEnabled;
    QString         _projectRoot;

};

#endif // PROJECTMANAGER_H
