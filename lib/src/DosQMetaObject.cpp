#include "DOtherSide/DosQMetaObject.h"
#include "DOtherSide/DosQObject.h"
#include "private/qmetaobjectbuilder_p.h"
#include "private/qmetaobject_p.h"
#include "private/qobject_p.h"
#include <QtCore/QAbstractListModel>

namespace
{

template<class T>
QByteArray createSignature(const T& functionDefinition)
{
    QString signature("%1(%2)");
    QString arguments;

    const auto& parameters = functionDefinition.parameterTypes;

    for (size_t i = 0; i < parameters.size(); ++i) {
        if (i != 0)
            arguments += ",";
        arguments += QMetaType::typeName(parameters[i]);
    }

    return signature.arg(functionDefinition.name, arguments).toUtf8();
}

template<class Key, class Value>
Value valueOrDefault(std::unordered_map<Key,Value> const& map, const Key& k, Value value)
{
    auto it = map.find(k);
    return it != std::end(map) ? it->second : std::move(value);
}

QMetaObject* createDynamicQObjectMetaObject()
{
    QMetaObjectBuilder builder;
    builder.setClassName("DosQObject");
    builder.setSuperClass(&QObject::staticMetaObject);
    return builder.toMetaObject();
}

QMetaObject* createDynamicQAbstractListModelMetaObject()
{
    QMetaObjectBuilder builder;
    builder.setClassName("DosQAbstractListModel");
    builder.setSuperClass(&QAbstractListModel::staticMetaObject);
    return builder.toMetaObject();
}

}

namespace DOS
{

DosQObjectMetaObject::DosQObjectMetaObject()
    : BaseDosQMetaObject(::createDynamicQObjectMetaObject())
{}

DosQAbstractListModelMetaObject::DosQAbstractListModelMetaObject()
    : BaseDosQMetaObject(::createDynamicQAbstractListModelMetaObject())
{}

DosQMetaObject::DosQMetaObject(std::shared_ptr<const IDosQMetaObject> superClassMetaObject,
                               const QString &className,
                               const SignalDefinitions& signalDefinitions,
                               const SlotDefinitions& slotDefinitions,
                               const PropertyDefinitions& propertyDefinitions)
    : m_superClassDosMetaObject(std::move(superClassMetaObject))
    , m_metaObject(createMetaObject(className, signalDefinitions, slotDefinitions, propertyDefinitions))
{
}

QMetaObject *DosQMetaObject::createMetaObject(const QString &className,
                                              const SignalDefinitions& signalDefinitions,
                                              const SlotDefinitions& slotDefinitions,
                                              const PropertyDefinitions& propertyDefinitions)
{
    QMetaObjectBuilder builder;
    builder.setClassName(className.toUtf8());
    builder.setSuperClass(m_superClassDosMetaObject->metaObject());

    for (const SignalDefinition& signal : signalDefinitions)
    {
        QMetaMethodBuilder signalBuilder = builder.addSignal(::createSignature(signal));
        signalBuilder.setReturnType(QMetaType::typeName(QMetaType::Void));
        signalBuilder.setAccess(QMetaMethod::Public);
        m_signalIndexByName[signal.name] = signalBuilder.index();
    }

    QHash<QString, int> methodIndexByName;
    for (const SlotDefinition& slot : slotDefinitions)
    {
        QMetaMethodBuilder methodBuilder = builder.addSlot(::createSignature(slot));
        methodBuilder.setReturnType(QMetaType::typeName(slot.returnType));
        methodBuilder.setAttributes(QMetaMethod::Scriptable);
        methodIndexByName[slot.name] = methodBuilder.index();
    }

    for (const PropertyDefinition& property : propertyDefinitions)
    {
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
    const auto index = m_propertySlots.value(QString::fromUtf8(propertyName), qMakePair(-1,-1)).first;
    if (index != -1)
        return metaObject()->method(metaObject()->methodOffset() + index);
    if (auto superMetaObject = superClassDosMetaObject())
        return superMetaObject->readSlot(propertyName);
    return QMetaMethod();
}

QMetaMethod DosQMetaObject::writeSlot(const char *propertyName) const
{
    const auto index = m_propertySlots.value(QString::fromUtf8(propertyName), qMakePair(-1,-1)).second;
    if (index != -1)
        return metaObject()->method(metaObject()->methodOffset() + index);
    if (auto superMetaObject = superClassDosMetaObject())
        return superMetaObject->writeSlot(propertyName);
    return QMetaMethod();
}

const QMetaObject *DosQMetaObject::metaObject() const
{
    return m_metaObject;
}

const IDosQMetaObject *DosQMetaObject::superClassDosMetaObject() const
{
    return m_superClassDosMetaObject.get();
}

} // namespace DOS
