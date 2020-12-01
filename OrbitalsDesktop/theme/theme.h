#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QQmlEngine>

class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontFamilyChanged)
    Q_PROPERTY(QString bgColor READ bgColor WRITE setBgColor NOTIFY bgColorChanged)
    Q_PROPERTY(QString bgColorDarkened READ bgColorDarkened WRITE setBgColorDarkened NOTIFY bgColorDarkenedChanged)
    Q_PROPERTY(QString fgColor READ fgColor WRITE setFgColor NOTIFY fgColorChanged)
    Q_PROPERTY(QString borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius NOTIFY borderRadusChanged)

public:
    explicit Theme(QObject *parent = nullptr)
        : QObject(parent)
        , m_fontFamily("Avenir")
        , m_bgColor("#b195bf")
        , m_bgColorDarkened("#807287")
        , m_fgColor("#848895")
        , m_borderColor("#D9FFFFFF")
        , m_borderRadius(5)
    {
    }
    static void registerTypes(const char *uri);
    static QObject *singletonProvider(QQmlEngine *, QJSEngine *);

    QString fontFamily() const;
    QString bgColor() const;
    QString bgColorDarkened() const;
    QString fgColor() const;
    QString borderColor() const;
    int borderRadius() const;

public slots:
    void setFontFamily(QString fontFamily);
    void setBgColor(QString bgColor);
    void setBgColorDarkened(QString bgColorDarkened);
    void setFgColor(QString fgColor);
    void setBorderColor(QString borderColor);
    void setBorderRadius(int radius);
    

signals:
    void fontFamilyChanged(QString fontFamily);
    void bgColorChanged(QString bgColor);
    void bgColorDarkenedChanged(QString bgColorDarkened);
    void fgColorChanged(QString fgColor);
    void borderColorChanged(QString borderColor);
    void borderRadusChanged(int fgColor);

private:
    QString m_fontFamily;
    QString m_bgColor;
    QString m_bgColorDarkened;
    QString m_fgColor;
    QString m_borderColor;
    int m_borderRadius;
};

#endif // THEME_H