#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QQuickItem>
#include <QThread>
#include <QNetworkConfigurationManager>
#include <QQuickTextDocument>
#include <QFileSystemModel>
#include "directorymanager.h"
#include "thread/compileworker.h"
#include "thread/uploadworker.h"
#include "highlight/arduinohighlighter.h"
#include "cloudapi/cloud.h"
#include "thread/compileworkerv2.h"
#include "thread/compileanduploadworkerv2.h"

class ProjectManager : public QQuickItem
{

    Q_OBJECT
    QThread     compilingThread;
    QThread     uploadThread;

    Q_PROPERTY(QString projectName READ projectName NOTIFY projectNameChanged)
    Q_PROPERTY(bool compilerOutputEnabled READ compilerOutputEnabled WRITE setCompilerOutputEnabled NOTIFY compilerOutputEnabledChanged)
    Q_PROPERTY(bool compilerErrorOutputEnabled READ compilerErrorOutputEnabled WRITE setCompilerErrorOutputEnabled NOTIFY compilerErrorOutputEnabledChanged)
    Q_PROPERTY(QQuickTextDocument* document READ document WRITE setDocument)
    Q_PROPERTY(bool modified READ modified NOTIFY modifiedChanged)
    Q_PROPERTY(QFileSystemModel* projectFsModel READ projectFsModel NOTIFY projectFsModelChanged)
    Q_PROPERTY(QModelIndex  rootIndex READ rootIndex NOTIFY rootIndexChanged)
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly NOTIFY readOnlyChanged)

public:

    ProjectManager(DirectoryManager *man, Toolchain *toolchain, QQuickItem *parent = Q_NULLPTR);
    ~ProjectManager();

    QString             projectName();
    void                setProjectName(QString name);
    void                setCompilerOutputEnabled(bool val);
    void                setCompilerErrorOutputEnabled(bool val);
    bool                compilerOutputEnabled();
    bool                compilerErrorOutputEnabled();
    bool                modified();
    bool                isOnline();
    bool                loggedIn();
    bool                readOnly();
    void                setReadOnly(bool val);
    QQuickTextDocument* document();
    void                setDocument(QQuickTextDocument  *doc);
    void                setDirManager(DirectoryManager *dir);
    QFileSystemModel*   projectFsModel();
    QModelIndex         rootIndex();

signals:

    void        compileProjectSignal(const QString &rootFolder, const QString &outputFolder, QStringList l);
    void        compileAndUploadProjectSignal(const QString & , const QString &);
    void        compilerStandardOutput(QString output);
    void        compilerErrorOutput(QString output);
    void        projectNameChanged();
    void        projectOpened();
    void        compilerOutputEnabledChanged();
    void        compilerErrorOutputEnabledChanged();
    void        modifiedChanged();
    void        rootIndexChanged();
    void        projectFsModelChanged();
    void        readOnlyChanged();

public slots:

    bool        createProject(QString dirPath);
    bool        createProject(QString dirPath , QString content);
    QString     createProject(QString name , QString folderPath , QString content);
    QString     createNewClass(QString className , QString relativePath);
    bool        openProject(QString dirPath);
    bool        projectExists(QString path);
    void        writeProj(QVariantList l);
    void        compileProject(QString buildFolder = QString());
    void        compileAndUploadProject(QString buildFolder = QString());
    void        saveFile();
    void        setEditorText(QString str);
    void        refresh();

private slots:

    void        onModificationChanged(bool val);

private:

    DirectoryManager    *_directoryManager;
    AvrCompiler         *_compiler;
    Toolchain           *_toolchain;
    CompileWorkerV2     *_compileWorker;
    CompileAndUploadWorkerV2        *_uploadWorker;
    QQuickTextDocument  *_document;
    QFileSystemModel    *_model;

    QString             _projectBuildDir;
    QString             _projectName;
    bool                _readOnly;
    ArduinoHighlighter         _highlighter;
    QString         getDefaultBuildPath(QString path);

};

#endif // PROJECTMANAGER_H
