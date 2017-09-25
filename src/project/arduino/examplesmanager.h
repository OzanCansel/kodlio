#ifndef EXAMPLESMANAGER_H
#define EXAMPLESMANAGER_H

#include <QQuickItem>
#include "arduinoLibManager/librarymanager.h"

class ExamplesManager : public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(LibraryManager*  libManager READ libManager WRITE setLibManager NOTIFY libManagerChanged)

public:

    static void         registerQmlType();
    ExamplesManager(QQuickItem* parent = nullptr);
    LibraryManager*     libManager();
    void                setLibManager(LibraryManager*   manager);

public slots:

    QVariantMap         load();

signals:

    void                libManagerChanged();

private:

    LibraryManager      *m_manager;
    QVariantMap         m_map;

};

#endif // EXAMPLESMANAGER_H
