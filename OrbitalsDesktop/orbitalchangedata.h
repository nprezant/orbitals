#ifndef ORBITALCHANGEDATA_H
#define ORBITALCHANGEDATA_H

#include <QtCore>

class OrbitalChangeData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int index MEMBER index)
    Q_PROPERTY(ChangeType changeType MEMBER changeType)
    Q_PROPERTY(double positionX MEMBER positionX)
    Q_PROPERTY(double positionY MEMBER positionY)
    Q_PROPERTY(double positionZ MEMBER positionZ)

public:
    enum ChangeType { Add, Remove, Update, };
    Q_ENUM(ChangeType)

    int index;
    ChangeType changeType;
    double positionX;
    double positionY;
    double positionZ;

    OrbitalChangeData(int index, ChangeType changeType, double positionX, double positionY, double positionZ)
        : index(index), changeType(changeType), positionX(positionX), positionY(positionY), positionZ(positionZ)
    {}

    OrbitalChangeData() // This is required for compilation, probably for the QQmlListProperty
    {}
};

#endif // ORBITALCHANGEDATA_H