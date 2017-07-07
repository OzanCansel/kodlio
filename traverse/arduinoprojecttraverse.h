#ifndef ARDUINOPROJECTINTERNALTRAVERSE_H
#define ARDUINOPROJECTINTERNALTRAVERSE_H

#include "filetraverse.h"

class ArduinoProjectTraverse : public FileTraverse
{
    Q_OBJECT
    Q_PROPERTY(QString rootDir READ rootDir WRITE setRootDir NOTIFY rootDirChanged)

public:

    ArduinoProjectTraverse(QQuickItem *parent = Q_NULLPTR);
    QString     rootDir();
    void        setRootDir(QString val);

public slots:

signals:

    void        rootDirChanged();

private:

    QString                     _rootDir;
    QList<TraversedFileInfo>    _files;

};

#endif // ARDUINOPROJECTINTERNALTRAVERSE_H
