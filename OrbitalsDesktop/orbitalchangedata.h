#ifndef ORBITALCHANGEDATA_H
#define ORBITALCHANGEDATA_H

#include <QtCore>
#include "orbitalsystem.h"

class OrbitalChangeData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int index MEMBER index)
    Q_PROPERTY(ChangeType changeType MEMBER changeType)

    Q_PROPERTY(double positionX MEMBER positionX)
    Q_PROPERTY(double positionY MEMBER positionY)
    Q_PROPERTY(double positionZ MEMBER positionZ)

    Q_PROPERTY(double velocityX MEMBER velocityX)
    Q_PROPERTY(double velocityY MEMBER velocityY)
    Q_PROPERTY(double velocityZ MEMBER velocityZ)

public:
    enum ChangeType { Add, Remove, Update, };
    Q_ENUM(ChangeType)

    int index;
    ChangeType changeType;

    double positionX;
    double positionY;
    double positionZ;

    double velocityX;
    double velocityY;
    double velocityZ;

    OrbitalChangeData(int index, ChangeType changeType, Vector3 position, Vector3 velocity)
        : index(index)
        , changeType(changeType)
        , positionX(position.X)
        , positionY(position.Y)
        , positionZ(position.Z)
        , velocityX(velocity.X)
        , velocityY(velocity.Y)
        , velocityZ(velocity.Z)
    {}

    OrbitalChangeData() // This is required for compilation, probably for the QQmlListProperty
    {}
};

#endif // ORBITALCHANGEDATA_H