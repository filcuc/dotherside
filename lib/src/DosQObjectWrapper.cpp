#include "DOtherSide/DosQObjectWrapper.h"
#include "DOtherSide/DosIQObjectImpl.h"
#include "DOtherSide/DosQMetaObject.h"
#include "DOtherSide/DosQObject.h"
#include <QDebug>
#include <QtQml/qqml.h>

namespace DOS {

template<int>
class DosQObjectWrapper : public QObject
{
public:
    static const QMetaObject staticMetaObject;

    DosQObjectWrapper(QObject *parent = nullptr);
    ~DosQObjectWrapper();

    const QMetaObject* metaObject() const override;
    int qt_metacall(QMetaObject::Call, int, void **) override;

    static const QmlRegisterType& qmlRegisterType();
    static void setQmlRegisterType(QmlRegisterType data);
    static void setStaticMetaObject(const QMetaObject& metaObject);
    static void setId(int id);

private:
    void* m_dObject;
    DosQObject* m_impl;
    static int m_id;
    static QmlRegisterType m_data;
};

template<int N>
const QMetaObject DosQObjectWrapper<N>::staticMetaObject = QObject::staticMetaObject;

template<int N>
QmlRegisterType DosQObjectWrapper<N>::m_data;

template<int N>
int DosQObjectWrapper<N>::m_id = -1;

template<int N>
DosQObjectWrapper<N>::DosQObjectWrapper(QObject *parent)
    : QObject(parent)
    , m_dObject(nullptr)
    , m_impl(nullptr)
{
    void* impl = nullptr;
    m_data.createDObject(m_id, &m_dObject, &impl);
    m_impl = static_cast<DosQObject*>(impl);
    Q_ASSERT(m_dObject);
    Q_ASSERT(m_impl);
}

template<int N>
DosQObjectWrapper<N>::~DosQObjectWrapper()
{
    m_data.deleteDObject(m_id, m_dObject);
    m_dObject = nullptr;
    m_impl = nullptr;
}

template<int N>
const QMetaObject *DosQObjectWrapper<N>::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

template<int N>
int DosQObjectWrapper<N>::qt_metacall(QMetaObject::Call call, int index, void **args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(call, index, args);
}

template<int N>
void DosQObjectWrapper<N>::setQmlRegisterType(QmlRegisterType data)
{
    m_data = std::move(data);
}

template<int N>
void DosQObjectWrapper<N>::setStaticMetaObject(const QMetaObject &metaObject)
{
    *(const_cast<QMetaObject*>(&staticMetaObject)) = metaObject;
}

template<int N>
void DosQObjectWrapper<N>::setId(int id)
{
    m_id = id;
}

template<int N>
const QmlRegisterType& DosQObjectWrapper<N>::qmlRegisterType()
{
    return m_data;
}

template<int N>
int dosQmlRegisterType(QmlRegisterType args)
{
    DosQObjectWrapper<N>::setQmlRegisterType(std::move(args));
    const QmlRegisterType& type = DosQObjectWrapper<N>::qmlRegisterType();
    DosQObjectWrapper<N>::setStaticMetaObject(*(type.staticMetaObject->metaObject()));
    int result = qmlRegisterType<DosQObjectWrapper<N>>(type.uri.c_str(), type.major, type.minor, type.qml.c_str());
    DosQObjectWrapper<N>::setId(result);
    return result;
}

template<int N>
struct DosQmlRegisterHelper
{
    static int Register(int i, QmlRegisterType args)
    {
        if (i > N)
            return -1;
        else if (i == N)
            return dosQmlRegisterType<N>(std::move(args));
        else
            return DosQmlRegisterHelper<N-1>::Register(i, std::move(args));
    }
};

template<>
struct DosQmlRegisterHelper<0>
{
    static int Register(int i, QmlRegisterType args)
    {
        return i == 0 ? dosQmlRegisterType<0>(std::move(args)) : -1;
    }
};


int dosQmlRegisterType(QmlRegisterType args)
{
    static int i = 0;
    return DosQmlRegisterHelper<35>::Register(i++, std::move(args));
}



}
