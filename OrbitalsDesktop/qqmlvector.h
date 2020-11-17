#ifndef QQMLVECTOR_H
#define QQMLVECTOR_H

#include <QtCore>
#include <QQmlListProperty>

class QObjectDerivative : public QObject
{
    // Cannot template a class that contains the Q_OBJECT macro.
    // Solution is to subclass it.
    Q_OBJECT
};

template<class TData>
class QQmlVector : public QObjectDerivative
{

public:
    QQmlVector()
        : data_({})
    {
    }

    inline QQmlListProperty<TData> QQmlListPropertyView()
    {
        return
        {
            this, // Object defining scope of the list property
            this, // Property available in list->data, therefore list->data is a QQmlVector
            &QQmlVector::append,
            &QQmlVector::count,
            &QQmlVector::at,
            &QQmlVector::clear,
            &QQmlVector::replace,
            &QQmlVector::removeLast
        };
    }

    void append(TData* o)
    {
        data_.append(o);
    }
    int count() const
    {
        return data_.count();
    }
    TData *at(int index) const
    {
        return data_.at(index);
    }
    void clear()
    {
        data_.clear();
    }
    void replace(int index, TData* o)
    {
        data_[index] = o;
    }
    void removeLast()
    {
        data_.removeLast();
    }

private:
    using QQmlList = QQmlListProperty<TData>;

    static void append(QQmlList* list, TData* o)
    {
        reinterpret_cast<QQmlVector*>(list->data)->append(o);
    }
    static int count(QQmlList* list)
    {
        return reinterpret_cast<QQmlVector*>(list->data)->count();
    }
    static TData* at(QQmlList* list, int index)
    {
        return reinterpret_cast<QQmlVector*>(list->data)->at(index);
    }
    static void clear(QQmlList* list)
    {
        reinterpret_cast<QQmlVector*>(list->data)->clear();
    }
    static void replace(QQmlList* list, int index, TData* o)
    {
        reinterpret_cast<QQmlVector*>(list->data)->replace(index, o);
    }
    static void removeLast(QQmlList* list)
    {
        reinterpret_cast<QQmlVector*>(list->data)->removeLast();
    }

    QVector<TData *> data_;
};


#endif // QQMLVECTOR_H