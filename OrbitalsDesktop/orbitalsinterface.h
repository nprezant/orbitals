#ifndef ORBITALSINTERFACE_H
#define ORBITALSINTERFACE_H

#include <QtCore>
#include <QQmlListProperty>

#include "orbitalsystem.h"
#include "orbitalchangedata.h"
#include "qqmlvector.h"

class OrbitalsInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString systemName READ systemName WRITE setSystemName NOTIFY systemNameChanged)
    Q_PROPERTY(QQmlListProperty<OrbitalChangeData> orbitalChangeDataList READ orbitalChangeDataList NOTIFY orbitalChangeDataListChanged)

public:
    OrbitalsInterface()
        : systemName_("Harry Potter"),
          orbitalSystem_(OrbitalSystem::Earth())
        {
        }

    QString systemName() const;
    void setSystemName(const QString& newName);

    QQmlListProperty<OrbitalChangeData> orbitalChangeDataList()
    {
        return orbitalChangeDataVector_.QQmlListPropertyView();
    }

    Q_INVOKABLE void addOrbital();
    Q_INVOKABLE void incrementTime();

Q_SIGNALS:
    void systemNameChanged();
    void orbitalChangeDataListChanged();

private:
    QString systemName_;
    OrbitalSystem orbitalSystem_;
    QQmlVector<OrbitalChangeData> orbitalChangeDataVector_;

};

#endif // ORBITALSINTERFACE_H