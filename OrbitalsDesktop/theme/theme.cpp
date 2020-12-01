#include "theme.h"

#include <QtQml>

static Theme *s_instance = nullptr;

void Theme::registerTypes(const char *uri)
{
    qmlRegisterSingletonType<Theme>(uri, 1, 0, "Theme", Theme::singletonProvider);
}

QObject *Theme::singletonProvider(QQmlEngine *qmlEngine, QJSEngine *)
{
    if (!s_instance) {
        s_instance = new Theme(qmlEngine);
    }
    return s_instance;
}

QString Theme::fontFamily() const
{
    return m_fontFamily;
}

void Theme::setFontFamily(QString fontFamily)
{
    if (m_fontFamily == fontFamily)
        return;

    m_fontFamily = fontFamily;
    emit fontFamilyChanged(m_fontFamily);
}

QString Theme::bgColor() const
{
    return m_bgColor;
}

void Theme::setBgColor(QString bgColor)
{
    if (m_bgColor == bgColor)
        return;

    m_bgColor = bgColor;
    emit bgColorChanged(m_bgColor);
}

QString Theme::bgColorDarkened() const
{
    return m_bgColorDarkened;
}

void Theme::setBgColorDarkened(QString bgColorDarkened)
{
    if (m_bgColorDarkened == bgColorDarkened)
        return;

    m_bgColorDarkened = bgColorDarkened;
    emit bgColorDarkenedChanged(m_bgColorDarkened);
}

QString Theme::fgColor() const
{
    return m_fgColor;
}

void Theme::setFgColor(QString fgColor)
{
    if (m_fgColor == fgColor)
        return;

    m_fgColor = fgColor;
    emit fgColorChanged(m_fgColor);
}

QString Theme::borderColor() const
{
    return m_borderColor;
}

void Theme::setBorderColor(QString borderColor)
{
    if (m_borderColor == borderColor)
        return;

    m_borderColor = borderColor;
    emit borderColorChanged(m_borderColor);
}

int Theme::borderRadius() const
{
    return m_borderRadius;
}

void Theme::setBorderRadius(int borderRadius)
{
    if (m_borderRadius == borderRadius)
        return;

    m_borderRadius = borderRadius;
    emit borderRadusChanged(m_borderRadius);
}