#ifndef PROJECTWATCHER_H
#define PROJECTWATCHER_H

#include <QQuickItem>
#include <QFileSystemWatcher>

class ProjectWatcher : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString rootDir READ rootDir WRITE setRootDir NOTIFY rootDirChanged)

public:

    ProjectWatcher(QQuickItem *parent = Q_NULLPTR);
    QString     rootDir();
    void        setRootDir(QString dir);

signals:

    void        rootDirChanged();

protected:

    QFileSystemWatcher  _watcher;

private:

    QString     _rootDir;

};

#endif // PROJECTWATCHER_H
