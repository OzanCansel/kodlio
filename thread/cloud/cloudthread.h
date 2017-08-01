#ifndef CLOUDTHREAD_H
#define CLOUDTHREAD_H

#include <QQuickItem>
#include <QThread>
#include "cloudworker.h"
#include "cloudapi/cloud.h"

class CloudThread : public QQuickItem
{
    Q_OBJECT
    QThread     cloudThread;
    Q_PROPERTY(Cloud* cloud READ cloud WRITE setCloud NOTIFY cloudChanged)

public:

    static void     registerQmlType();
    CloudThread(QQuickItem *parent = Q_NULLPTR);
    ~CloudThread();

    Cloud*          cloud();
    void            setCloud(Cloud* cloud);

public slots:

    void            uploadProject(QString root);

signals:

    void            cloudChanged();
    void            uploadProjectSignal(QString root);


private:

    Cloud*          _cloud;
    CloudWorker*    _worker;

};

#endif // CLOUDTHREAD_H
