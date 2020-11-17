#ifndef ORBITALCHANGEDATA_H
#define ORBITALCHANGEDATA_H

#include <QtCore>

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

#endif // ORBITALCHANGEDATA_H