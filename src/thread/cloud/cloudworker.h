#ifndef CLOUDWORKER_H
#define CLOUDWORKER_H

#include <QObject>
#include "cloudapi/cloud.h"

class CloudWorker : public QObject
{
    Q_OBJECT
public:

    explicit CloudWorker( QObject *parent = nullptr);
    void    setCloud(Cloud* val);

public slots:

    void        uploadProject(QString root);

private:

    Cloud*  _cloud;

};

#endif // CLOUDWORKER_H
