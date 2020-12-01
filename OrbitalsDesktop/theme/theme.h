#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QQmlEngine>

class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontFamilyChanged)
    Q_PROPERTY(QString bgColor READ bgColor WRITE setBgColor NOTIFY bgColorChanged)

public:
    explicit Theme(QObject *parent = nullptr)
        : QObject(parent)
        , m_fontFamily("Avenir")
        , m_bgColor("#b195bf")
    {
    }
    static void registerTypes(const char *uri);
    static QObject *singletonProvider(QQmlEngine *, QJSEngine *);

    QString fontFamily() const;
    QString bgColor() const; 

public slots:
    void setFontFamily(QString fontFamily);
    void setBgColor(QString bgColor);

signals:
    void fontFamilyChanged(QString fontFamily);
    void bgColorChanged(QString bgColor);

private:
    QString m_fontFamily;
    QString m_bgColor;
};

#endif // THEME_H