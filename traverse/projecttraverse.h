#ifndef PROJECTREADER_H
#define PROJECTREADER_H

#include <QQuickItem>
#include <QVariantList>
#include <QVariantMap>
#include <QVariant>

class ProjectTraverse :  public QQuickItem
{

    Q_OBJECT

public:

    static  void registerQmlType();

    ProjectTraverse(QQuickItem *parent = Q_NULLPTR);

public slots:

    QVariantHash    readProjects( QString root , QString filterPattern);

};

#endif // PROJECTREADER_H
