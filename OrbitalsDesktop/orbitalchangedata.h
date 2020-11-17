#ifndef ORBITALCHANGEDATA_H
#define ORBITALCHANGEDATA_H

#include <QtCore>

class OrbitalChangeData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint32 test READ test)
    Q_PROPERTY(qint32 index MEMBER index)
    Q_PROPERTY(ChangeType changeType MEMBER changeType)
    Q_PROPERTY(qreal positionX MEMBER positionX)
    Q_PROPERTY(qreal positionY MEMBER positionY)
    Q_PROPERTY(qreal positionZ MEMBER positionZ)

public:
    enum ChangeType { Insert, Remove, Update, };
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

    inline int test()
    {
        return 1;
    }
};

#endif // ORBITALCHANGEDATA_H