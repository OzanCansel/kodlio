#ifndef DOCUMENTSTYLE_H
#define DOCUMENTSTYLE_H

#include <QQuickItem>
#include <QQuickTextDocument>
#include "editorsettings.h"

class DocumentStyle : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument*  textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
    Q_PROPERTY(EditorSettings*  editorSettings READ editorSettings WRITE setEditorSettings NOTIFY editorSettingsChanged)

public:

    static void         registerQmlType();
    DocumentStyle(QQuickItem *parent = Q_NULLPTR);
    void                setTextDocument(QQuickTextDocument *doc);
    QQuickTextDocument* textDocument();
    EditorSettings*     editorSettings();
    void                setEditorSettings(EditorSettings*   val);

signals:

    void            textDocumentChanged();
    void            editorSettingsChanged();

private slots:

    void            tabSizeChanged();
    void            familyChanged();
    void            pointSizeChanged();

private:

    QQuickTextDocument* _doc;
    EditorSettings*     _settings;
    int                 _tabSize;
    int                 _pointSize;
    QString             _family;

    void                applySettingsToDoc();
    void                applyInitialSettings();
    void                applyTabSize();
    void                applyFont();

};

#endif // DOCUMENTSTYLE_H
