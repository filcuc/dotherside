#include "DOtherSide/DosQMetaObject.h"
#include "DOtherSide/DosQObject.h"
#include "private/qmetaobjectbuilder_p.h"
#include "private/qmetaobject_p.h"
#include "private/qobject_p.h"
#include <QtCore/QAbstractListModel>

namespace {

QList<QByteArray> createParameterNames(const DOS::SignalDefinition &signal)
{
    QList<QByteArray> result;
    size_t size = signal.parameterTypes.size();
    result.reserve(size);
    for (size_t i = 0; i < size; ++i)
        result << QString("arg%1").arg(i).toUtf8();
    return result;
}

template<class T>
QByteArray createSignature(const T &functionDefinition)
{
    QString signature("%1(%2)");
    QString arguments;

    const auto &parameters = functionDefinition.parameterTypes;

    for (size_t i = 0; i < parameters.size(); ++i) {
        if (i != 0)
            arguments += ",";
        arguments += QMetaType::typeName(parameters[i]);
    }

    return signature.arg(functionDefinition.name, arguments).toUtf8();
}

template<class Key, class Value>
Value valueOrDefault(std::unordered_map<Key, Value> const &map, const Key &k, Value value)
{
    auto it = map.find(k);
    return it != std::end(map) ? it->second : std::move(value);
}

QMetaObject *createDynamicQObjectMetaObject()
{
    QMetaObjectBuilder builder;
    builder.setClassName("DosQObject");
    builder.setSuperClass(&QObject::staticMetaObject);
    return builder.toMetaObject();
}

QMetaObject *createDynamicQAbstractItemModelMetaObject()
{
    QMetaObjectBuilder builder;
    builder.setClassName("DosQAbstractItemModel");
    builder.setSuperClass(&QAbstractItemModel::staticMetaObject);
    return builder.toMetaObject();
}

}

namespace DOS {

BaseDosQMetaObject::BaseDosQMetaObject(QMetaObject *metaObject)
    : m_metaObject(metaObject)
{}

const QMetaObject *BaseDosQMetaObject::metaObject() const
{
    return m_metaObject;
}

QMetaMethod BaseDosQMetaObject::signal(const QString &signalName) const
{
    return QMetaMethod();
}

QMetaMethod BaseDosQMetaObject::readSlot(const char *propertyName) const
{
    return QMetaMethod();
}

QMetaMethod BaseDosQMetaObject::writeSlot(const char *propertyName) const
{
    return QMetaMethod();
}

const DosIQMetaObject *BaseDosQMetaObject::superClassDosMetaObject() const
{
    return nullptr;
}

DosQObjectMetaObject::DosQObjectMetaObject()
    : BaseDosQMetaObject(::createDynamicQObjectMetaObject())
{}

DosQAbstractItemModelMetaObject::DosQAbstractItemModelMetaObject()
    : BaseDosQMetaObject(::createDynamicQAbstractItemModelMetaObject())
{}

DosQMetaObject::DosQMetaObject(DosIQMetaObjectPtr superClassMetaObject,
                               const QString &className,
                               const SignalDefinitions &signalDefinitions,
                               const SlotDefinitions &slotDefinitions,
                               const PropertyDefinitions &propertyDefinitions)
    : BaseDosQMetaObject(nullptr)
    , m_superClassDosMetaObject(std::move(superClassMetaObject))
    , m_signalIndexByName(QHash<QString, int>())
    , m_propertySlots(QHash<QString, QPair<int, int>>())
{
    // We do the metaobject initialization here because
    // we must wait for both maps to be initialized before filling them
    m_metaObject.reset(createMetaObject(className, signalDefinitions, slotDefinitions, propertyDefinitions));
}

QMetaObject *DosQMetaObject::createMetaObject(const QString &className,
                                              const SignalDefinitions &signalDefinitions,
                                              const SlotDefinitions &slotDefinitions,
                                              const PropertyDefinitions &propertyDefinitions)
{
    QMetaObjectBuilder builder;
    builder.setClassName(className.toUtf8());
    builder.setSuperClass(m_superClassDosMetaObject->metaObject());

    for (const SignalDefinition &signal : signalDefinitions) {
        QMetaMethodBuilder signalBuilder = builder.addSignal(::createSignature(signal));
        signalBuilder.setReturnType(QMetaType::typeName(QMetaType::Void));
        signalBuilder.setAccess(QMetaMethod::Public);
        signalBuilder.setParameterNames(createParameterNames(signal));
        m_signalIndexByName[signal.name] = signalBuilder.index();
    }

    QHash<QString, int> methodIndexByName;
    for (const SlotDefinition &slot : slotDefinitions) {
        QMetaMethodBuilder methodBuilder = builder.addSlot(::createSignature(slot));
        methodBuilder.setReturnType(QMetaType::typeName(slot.returnType));
        methodBuilder.setAttributes(QMetaMethod::Scriptable);
        methodIndexByName[slot.name] = methodBuilder.index();
    }

    for (const PropertyDefinition &property : propertyDefinitions) {
        const int notifier = m_signalIndexByName.value(property.notifySignal, -1);
        const QByteArray name = property.name.toUtf8();
        const QByteArray typeName = QMetaObject::normalizedType(QMetaType::typeName(property.type));
        QMetaPropertyBuilder propertyBuilder = builder.addProperty(name, typeName, notifier);
        if (notifier == -1)
            propertyBuilder.setConstant(true);
        m_propertySlots[property.name] = qMakePair(methodIndexByName.value(property.readSlot, -1),
                                                   methodIndexByName.value(property.writeSlot, -1));
    }

    return builder.toMetaObject();
}

QMetaMethod DosQMetaObject::signal(const QString &signalName) const
{
    const int index = m_signalIndexByName.value(signalName, -1);
    if (index != -1)
        return metaObject()->method(metaObject()->methodOffset() + index);
    if (auto superMetaObject = superClassDosMetaObject())
        return superMetaObject->signal(signalName);
    return QMetaMethod();
}

QMetaMethod DosQMetaObject::readSlot(const char *propertyName) const
{
    const auto index = m_propertySlots.value(QString::fromUtf8(propertyName), qMakePair(-1, -1)).first;
    if (index != -1)
        return metaObject()->method(metaObject()->methodOffset() + index);
    if (auto superMetaObject = superClassDosMetaObject())
        return superMetaObject->readSlot(propertyName);
    return QMetaMethod();
}

QMetaMethod DosQMetaObject::writeSlot(const char *propertyName) const
{
    const auto index = m_propertySlots.value(QString::fromUtf8(propertyName), qMakePair(-1, -1)).second;
    if (index != -1)
        return metaObject()->method(metaObject()->methodOffset() + index);
    if (auto superMetaObject = superClassDosMetaObject())
        return superMetaObject->writeSlot(propertyName);
    return QMetaMethod();
}

const DosIQMetaObject *DosQMetaObject::superClassDosMetaObject() const
{
    return m_superClassDosMetaObject.get();
}

} // namespace DOS
