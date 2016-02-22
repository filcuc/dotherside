#include "DOtherSide/DosQObjectWrapper.h"
#include "DOtherSide/DosIQObjectImpl.h"
#include "DOtherSide/DosQMetaObject.h"
#include "DOtherSide/DosQObject.h"
#include <QDebug>
#include <QtQml/qqml.h>
#include <private/qmetaobjectbuilder_p.h>

QMetaObject* createMetaObject()
{
    QMetaObjectBuilder builder;
    builder.setSuperClass(&QObject::staticMetaObject);
    builder.setClassName("DosQObjectWrapper");
    builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);

    QMetaMethodBuilder signal = builder.addSignal("nameChanged()");
    QMetaPropertyBuilder property = builder.addProperty("name", "QString", signal.index());
    property.setWritable(true);
    property.setConstant(false);
    property.setReadable(true);

    return builder.toMetaObject();
}

class WrapperMetaObject : public QAbstractDynamicMetaObject
{
public:
    WrapperMetaObject(QObject* parent);

protected:
    int metaCall(QMetaObject::Call c, int id, void **a) override;

private:
    QObject* m_parent;
};

WrapperMetaObject::WrapperMetaObject(QObject* parent)
    : m_parent(parent)
{
    *static_cast<QMetaObject *>(this) = *createMetaObject();
    QObjectPrivate *objPriv = QObjectPrivate::get(m_parent);
    objPriv->metaObject = this;
}

int WrapperMetaObject::metaCall(QMetaObject::Call c, int idx, void **args)
{
    switch (c) {
    case QMetaObject::ReadProperty: {
        if (idx < propertyOffset())
            return m_parent->qt_metacall(c, idx, args);
        QVariant temp("Filippo Cucchetto");
        QMetaType::construct(QMetaType::QString, args[0], temp.constData());
        break;
    }
    case QMetaObject::WriteProperty: {
        if (idx < propertyOffset())
            return m_parent->qt_metacall(c, idx, args);
        int index = indexOfSignal("nameChanged()");
        activate(m_parent, index, args);
        break;
    }
    case QMetaObject::InvokeMetaMethod: {
        if (idx < methodOffset())
            return m_parent->qt_metacall(c, idx, args);
        break;
    }
    default:
        break;
    }
    return -1;
}

namespace DOS {

template<int, int>
class DosQObjectWrapper : public QObject
{
public:
    DosQObjectWrapper(QObject *parent = nullptr);

    ~DosQObjectWrapper();

    static const QmlRegisterType& qmlRegisterType();
    static void setQmlRegisterType(QmlRegisterType data);
    static void setStaticMetaObject(const QMetaObject& metaObject);
    static void setId(int id);

    static QMetaObject staticMetaObject;

private:
    static int m_id;
    static QmlRegisterType m_data;
};

template<int N, int M>
QMetaObject DosQObjectWrapper<N,M>::staticMetaObject = QMetaObject();

template<int N, int M>
QmlRegisterType DosQObjectWrapper<N,M>::m_data;

template<int N, int M>
int DosQObjectWrapper<N,M>::m_id = -1;

template<int N, int M>
DosQObjectWrapper<N,M>::DosQObjectWrapper(QObject *parent)
    : QObject(parent)
{
    new WrapperMetaObject(this);
}

template<int N, int M>
DosQObjectWrapper<N,M>::~DosQObjectWrapper()
{}

template<int N, int M>
void DosQObjectWrapper<N,M>::setQmlRegisterType(QmlRegisterType data)
{
    m_data = std::move(data);
}

template<int N, int M>
void DosQObjectWrapper<N,M>::setStaticMetaObject(const QMetaObject &metaObject)
{
    staticMetaObject = *createMetaObject();
}

template<int N, int M>
void DosQObjectWrapper<N,M>::setId(int id)
{
    m_id = id;
}

template<int N, int M>
const QmlRegisterType& DosQObjectWrapper<N,M>::qmlRegisterType()
{
    return m_data;
}

template<int N>
using RegisterTypeQObject = DosQObjectWrapper<N, 0>;

template<int N>
int dosQmlRegisterType(QmlRegisterType args)
{
    RegisterTypeQObject<N>::setQmlRegisterType(std::move(args));
    const QmlRegisterType& type = RegisterTypeQObject<N>::qmlRegisterType();
    RegisterTypeQObject<N>::setStaticMetaObject(*(type.staticMetaObject->metaObject()));
    int result = qmlRegisterType<RegisterTypeQObject<N>>(type.uri.c_str(), type.major, type.minor, type.qml.c_str());
    RegisterTypeQObject<N>::setId(result);
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

template<int N>
using RegisterSingletonTypeQObject = DosQObjectWrapper<N, 1>;

template<int N>
QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    return new RegisterSingletonTypeQObject<N>();
}

template<int N>
int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    using Func = QObject*(*)(QQmlEngine*, QJSEngine*);
    Func f = singletontype_provider<N>;

    RegisterSingletonTypeQObject<N>::setQmlRegisterType(std::move(args));
    const QmlRegisterType& type = RegisterSingletonTypeQObject<N>::qmlRegisterType();
    RegisterSingletonTypeQObject<N>::setStaticMetaObject(*(type.staticMetaObject->metaObject()));
    int result = qmlRegisterSingletonType<RegisterSingletonTypeQObject<N>>(type.uri.c_str(), type.major, type.minor, type.qml.c_str(), f);
    RegisterSingletonTypeQObject<N>::setId(result);
    return result;
}

template<int N>
struct DosQmlRegisterSingletonHelper
{
    static int Register(int i, QmlRegisterType args)
    {
        if (i > N)
            return -1;
        else if (i == N)
            return dosQmlRegisterSingletonType<N>(std::move(args));
        else
            return DosQmlRegisterSingletonHelper<N-1>::Register(i, std::move(args));
    }
};

template<>
struct DosQmlRegisterSingletonHelper<0>
{
    static int Register(int i, QmlRegisterType args)
    {
        return i == 0 ? dosQmlRegisterSingletonType<0>(std::move(args)) : -1;
    }
};

int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    static int i = 0;
    return DosQmlRegisterSingletonHelper<35>::Register(i++, std::move(args));
}



}
