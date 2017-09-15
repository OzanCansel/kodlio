#ifndef LINENUMBER_H
#define LINENUMBER_H

#include <QQuickItem>
#include <QQuickTextDocument>

class LineNumber : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument*  textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
    Q_PROPERTY(int lineStart READ lineStart WRITE setLineStart NOTIFY lineStartChanged)
    Q_PROPERTY(int lineEnd READ lineEnd WRITE setLineEnd NOTIFY lineEndChanged)

public:

    static void             registerQmlType();
    LineNumber(QQuickItem *parent = Q_NULLPTR);
    int                     lineStart();
    int                     lineEnd();
    QQuickTextDocument*     textDocument();
    void                    setLineStart(int val);
    void                    setLineEnd(int val);
    void                    setTextDocument(QQuickTextDocument* document);

public slots:

    int                     matchIdx(int lineNumber);
    int                     matchIdxToLineNumber(int pos);

signals:

    void                    textDocumentChanged();
    void                    lineStartChanged();
    void                    lineEndChanged();

private:

    QQuickTextDocument*     _doc;
    int                     _lineStart;
    int                     _lineEnd;

};

#endif // LINENUMBER_H
