#ifndef KODLIOASISTANT_H
#define KODLIOASISTANT_H

#include <QQuickItem>
#include <QQuickTextDocument>
#include <QTextDocument>
#include <QTimer>
#include <QList>
#include "generate/func/funcdescgenerator.h"

class KodlioAsistant : public QQuickItem    {

    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument* textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
    Q_PROPERTY(int cooldown READ cooldown WRITE setCooldown NOTIFY cooldownChanged)

public:

    static void         registerQmlType();
    KodlioAsistant(QQuickItem *parent = Q_NULLPTR);
    void                setTextDocument(QQuickTextDocument* document);
    void                setCooldown(int val);
    QQuickTextDocument* textDocument();
    int                 cooldown();

signals:

    void                textDocumentChanged();
    void                cooldownChanged();
    void                parseStarted();
    void                newComment(QVariantMap map);
    void                parseEnd();

public slots:

    void                modified(bool modified);
    void                parseRequired();

private:

    QQuickTextDocument          *_doc;
    QTimer                      _parseCooldown;
    QList<FuncDescGenerator*>   _generators;

};

#endif // KODLIOASISTANT_H
