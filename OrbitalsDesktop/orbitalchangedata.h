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

    Q_PROPERTY(double theta MEMBER theta)
    Q_PROPERTY(double h MEMBER h)
    Q_PROPERTY(double e MEMBER e)
    Q_PROPERTY(double Omega MEMBER Omega)
    Q_PROPERTY(double inclination MEMBER inclination)
    Q_PROPERTY(double omega MEMBER omega)

    Q_PROPERTY(double time MEMBER time)

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

    double theta;
    double h;
    double e;
    double Omega;
    double inclination;
    double omega;

    double time;

    OrbitalChangeData(int index, ChangeType changeType, const Vector3 position, const Vector3 velocity, const ClassicalOrbitalElements elements, double time)
        : index(index)
        , changeType(changeType)
        , positionX(position.X)
        , positionY(position.Y)
        , positionZ(position.Z)
        , velocityX(velocity.X)
        , velocityY(velocity.Y)
        , velocityZ(velocity.Z)
        , theta(elements.theta)
        , h(elements.h)
        , e(elements.e)
        , Omega(elements.Omega)
        , inclination(elements.inclination)
        , omega(elements.omega)
        , time(time)
    {}

    OrbitalChangeData() // This is required for compilation, probably for the QQmlListProperty
    {}
};

#endif // ORBITALCHANGEDATA_H