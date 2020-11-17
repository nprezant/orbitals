#ifndef ORBITALSINTERFACE_H
#define ORBITALSINTERFACE_H

#include <QtCore>
#include <QQmlListProperty>
#include "orbitalsystem.h"

class OrbitalChangeData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ChangeType changeType READ changeType)
    Q_PROPERTY(int index READ index)

public:
    OrbitalChangeData()
    {}

    enum ChangeType { Insert, Remove, Update, };
    Q_ENUM(ChangeType)

    inline ChangeType changeType()
    {
        return ChangeType::Insert;
    }

    inline int index()
    {
        return 1;
    }
};

class OrbitalsInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString systemName READ systemName WRITE setSystemName NOTIFY systemNameChanged)
    Q_PROPERTY(QQmlListProperty<OrbitalChangeData> orbitalChangeDataList READ orbitalChangeDataList NOTIFY orbitalSystemChanged)

public:
    OrbitalsInterface()
        : systemName_("Harry Potter"),
          orbitalSystem_(OrbitalSystem::Earth())
        {
        }

    QString systemName() const;
    void setSystemName(const QString& newName);

    // TODO refactor this and all associated methods into it's own class/file
    QQmlListProperty<OrbitalChangeData> orbitalChangeDataList()
    {
        return
        {
            this, this,
            &OrbitalsInterface::appendChangeData,
            &OrbitalsInterface::changeDataCount,
            &OrbitalsInterface::orbitalChangeData,
            &OrbitalsInterface::clearChangeData,
            &OrbitalsInterface::replaceChangeData,
            &OrbitalsInterface::removeLastChangeData,
        };
    }
    void appendChangeData(OrbitalChangeData* o)
    {
        orbitalChangeData_.append(o);
    }
    int changeDataCount() const
    {
        return orbitalChangeData_.count();
    }
    OrbitalChangeData *orbitalChangeData(int index) const
    {
        return orbitalChangeData_.at(index);
    }
    void clearChangeData()
    {
        orbitalChangeData_.clear();
    }
    void replaceChangeData(int index, OrbitalChangeData* o)
    {
        orbitalChangeData_[index] = o;
    }
    void removeLastChangeData()
    {
        orbitalChangeData_.removeLast();
    }

    Q_INVOKABLE void addOrbital();
    Q_INVOKABLE void incrementTime();

Q_SIGNALS:
    void systemNameChanged();
    void orbitalSystemChanged(const QQmlListProperty<OrbitalChangeData>& orbitalChangeDataList);

private:
    using QmlChangeDataList = QQmlListProperty<OrbitalChangeData>;

    static void appendChangeData(QmlChangeDataList* list, OrbitalChangeData* o)
    {
        reinterpret_cast<OrbitalsInterface*>(list->data)->appendChangeData(o);
    }
    static int changeDataCount(QmlChangeDataList* list)
    {
        return reinterpret_cast<OrbitalsInterface*>(list->data)->changeDataCount();
    }
    static OrbitalChangeData* orbitalChangeData(QmlChangeDataList* list, int index)
    {
        return reinterpret_cast<OrbitalsInterface*>(list->data)->orbitalChangeData(index);
    }
    static void clearChangeData(QmlChangeDataList* list)
    {
        reinterpret_cast<OrbitalsInterface*>(list->data)->clearChangeData();
    }
    static void replaceChangeData(QmlChangeDataList* list, int index, OrbitalChangeData* o)
    {
        reinterpret_cast<OrbitalsInterface*>(list->data)->replaceChangeData(index, o);
    }
    static void removeLastChangeData(QmlChangeDataList* list)
    {
        reinterpret_cast<OrbitalsInterface*>(list->data)->removeLastChangeData();
    }

    QString systemName_;
    OrbitalSystem orbitalSystem_;
    QVector<OrbitalChangeData *> orbitalChangeData_;

};

#endif // ORBITALSINTERFACE_H