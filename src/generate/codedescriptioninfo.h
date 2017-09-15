#ifndef CODEDESCRIPTIONINFO_H
#define CODEDESCRIPTIONINFO_H

#include <QQuickItem>

class CodeDescriptionInfo :  public QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(int  lineNumber READ lineNumber WRITE setLineNumber NOTIFY lineNumberChanged)

public:

    static  void    registerQmlType();
    CodeDescriptionInfo(QQuickItem *parent = Q_NULLPTR);
    CodeDescriptionInfo(const CodeDescriptionInfo &other);
    int         lineNumber() const;
    QString     description() const;
    void        setLineNumber(int val);
    void        setDescription(QString val);
    CodeDescriptionInfo& operator =(const CodeDescriptionInfo& other);

signals:

    void        lineNumberChanged();
    void        descriptionChanged();

private:

    int         _lineNumber;
    QString     _description;

};

#endif // CODEDESCRIPTIONINFO_H
