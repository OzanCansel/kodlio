#ifndef DOCUMENTCONTENT_H
#define DOCUMENTCONTENT_H

#include <QQuickItem>
#include <QQuickTextDocument>

class DocumentContent : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString absolutePath READ absolutePath WRITE setAbsolutePath NOTIFY absolutePathChanged)
    Q_PROPERTY(QString content READ content NOTIFY contentChanged)
    Q_PROPERTY(QQuickTextDocument* textDocument READ textDocument WRITE setTextDocument)

public:

    static void         registerQmlType();
    DocumentContent(QQuickItem *parent = Q_NULLPTR);
    void                setAbsolutePath(QString val);
    void                setContent(QString val);
    void                setTextDocument(QQuickTextDocument *doc);
    QString             absolutePath();
    QString             content();
    QQuickTextDocument* textDocument();

public slots:

    bool                save();
    QString             fileName();

signals:

    void                absolutePathChanged();
    void                contentChanged();
    void                fileNotFound();
    void                fileReadError();

private:

    QString             _path;
    QString             _content;
    QQuickTextDocument  *_doc;

};

#endif // DOCUMENTCONTENT_H
