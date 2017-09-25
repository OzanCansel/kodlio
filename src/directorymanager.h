#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include <QObject>
#include <QTemporaryDir>

class DirectoryManager : public QObject
{

    Q_OBJECT

public:

    DirectoryManager();

    static void         copy(QString sourceDir , QString destionationDir);

public slots:

    QString             workingDirectory();
    QString             projectName(QString folder);
    void                setWorkingDirectory(QString dir);
    bool                isProjectDirectory(QString dir);
    bool                createProject(QString dir);
    bool                createProject(QString dir , QString content);
    QString             createTempDirectory();
    QString             mainFileContent();
    QString             getMainFileAbsolutePath();
    bool                createFile(QString path , QString content);
    void                save(QString content);

private:

    QString     _workingDirectory;

};

#endif // DIRECTORYMANAGER_H
