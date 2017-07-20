#ifndef PROJECTCREATEOPTIONS_H
#define PROJECTCREATEOPTIONS_H

#include "options.h"
#define  ROOT_LABEL             "root"
#define  PROJECT_NAME_LABEL     "projectName"

class ProjectOptions : public Options
{

    Q_OBJECT
    Q_PROPERTY(QString root READ root WRITE setRoot NOTIFY rootChanged)
    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)

public:

    static void     registerQmlType();
    ProjectOptions(QQuickItem *parent= Q_NULLPTR);
    QString         root();
    QString         projectName();
    void            setRoot(QString root);
    void            setProjectName(QString projectName);

signals:

    void        rootChanged();
    void        projectNameChanged();

};

#endif // PROJECTCREATEOPTIONS_H
