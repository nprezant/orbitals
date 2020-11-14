#ifndef ORBITALSINTERFACE_H
#define ORBITALSINTERFACE_H

#include <QtCore>
#include "orbitalsystem.h"

class OrbitalsInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString systemName READ systemName WRITE setSystemName NOTIFY systemNameChanged)

public:
    OrbitalsInterface()
        : systemName_("Harry Potter")
        {
        }

    QString systemName() const;
    void setSystemName(const QString& newName);

    Q_INVOKABLE void incrementTime();

Q_SIGNALS:
    void systemNameChanged();

private:
    QString systemName_;

};

#endif // ORBITALSINTERFACE_H