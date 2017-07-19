#ifndef ARDUINOLIBDESCRIPTION_H
#define ARDUINOLIBDESCRIPTION_H

#include <QJsonObject>
#include <QQuickItem>

class ArduinoLibDescription : public  QQuickItem
{

    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString version READ version NOTIFY versionChanged)
    Q_PROPERTY(QString author READ author NOTIFY authorChanged)
    Q_PROPERTY(QString maintainer READ maintainer NOTIFY maintainerChanged)
    Q_PROPERTY(QString sentence READ sentence NOTIFY sentenceChanged)
    Q_PROPERTY(QString paragraph READ paragraph NOTIFY paragraphChanged)
    Q_PROPERTY(QString website READ website NOTIFY websiteChanged)
    Q_PROPERTY(QString category READ category NOTIFY categoryChanged)
    Q_PROPERTY(QString url READ url NOTIFY urlChanged)
    Q_PROPERTY(QString archivedFileName READ archivedFileName NOTIFY archivedFileNameChanged)
    Q_PROPERTY(QString localDir READ localDir NOTIFY localDirChanged)
    Q_PROPERTY(bool    isRemovable READ isRemovable NOTIFY isRemovableChanged)

public:

    static void     registerQmlType();
    ArduinoLibDescription(QQuickItem *parent = Q_NULLPTR);
    ArduinoLibDescription(QString rootDir , QString name , bool isRemovable = false, QQuickItem *parent = Q_NULLPTR);
    ArduinoLibDescription(const ArduinoLibDescription &other);
    ArduinoLibDescription &operator =(const ArduinoLibDescription &other);

    bool        isRemovable();
    void        setRemovable(bool val);
    void        deserialize(QJsonObject &obj);
    void        deserialize(QString &fileName);
    QVariantMap asVariant();
    QString     name() const;
    QString     version() const;
    QString     author() const;
    QString     maintainer() const;
    QString     sentence() const ;
    QString     paragraph() const;
    QString     website() const;
    QString     category() const;
    QString     url() const;
    QString     archivedFileName() const;
    QString     localDir() const;
    QString     srcDir() const;
    QStringList headerPaths() const;
    QStringList headerFolders();


signals:

    void        nameChanged();
    void        versionChanged();
    void        authorChanged();
    void        maintainerChanged();
    void        sentenceChanged();
    void        paragraphChanged();
    void        websiteChanged();
    void        categoryChanged();
    void        urlChanged();
    void        archivedFileNameChanged();
    void        localDirChanged();
    void        isRemovableChanged();

protected:

    void        setName(QString val);
    void        setVersion(QString val);
    void        setAuthor(QString val);
    void        setMaintainer(QString val);
    void        setSentence(QString val);
    void        setParagraph(QString val);
    void        setWebsite(QString val);
    void        setCategory(QString val);
    void        setUrl(QString val);
    void        setArchivedFileName(QString val);

private:

    QString     _name;\
    QString     _version;
    QString     _author;
    QString     _maintainer;
    QString     _sentence;
    QString     _paragraph;
    QString     _website;
    QString     _category;
    QString     _url;
    QString     _archivedFileName;
    QString     _libDir;
    bool        _isRemovable;

};

#endif // ARDUINOLIBDESCRIPTION_H
