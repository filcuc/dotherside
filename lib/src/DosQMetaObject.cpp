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

    for (int type : functionDefinition.parameterTypes) {
        if (type != functionDefinition.parameterTypes.front())
            arguments += QLatin1Char(',');
        arguments += QMetaType::typeName(type);
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
    builder.setClassName("DynamicQObject");
    builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    builder.setSuperClass(&QObject::staticMetaObject);
    return builder.toMetaObject();
}

QMetaObject* createDynamicQAbstractListModelMetaObject()
{
    QMetaObjectBuilder builder;
    builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    builder.setClassName("DynamicQAbstractListModel");
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

DosQMetaObject::DosQMetaObject(const IDosQMetaObject &superClassMetaObject,
                               const QString &className,
                               const SignalDefinitions& signalDefinitions,
                               const SlotDefinitions& slotDefinitions,
                               const PropertyDefinitions& propertyDefinitions)
    : m_metaObject(nullptr)
{
    m_metaObject.reset(createMetaObject(superClassMetaObject, className, signalDefinitions, slotDefinitions, propertyDefinitions));
}

QMetaObject *DosQMetaObject::createMetaObject(const IDosQMetaObject &superClassMetaObject,
                                              const QString &className,
                                              const SignalDefinitions& signalDefinitions,
                                              const SlotDefinitions& slotDefinitions,
                                              const PropertyDefinitions& propertyDefinitions)
{
    QMetaObjectBuilder builder;
    builder.setClassName(className.toUtf8());
    builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    builder.setSuperClass(superClassMetaObject.metaObject());

    for (const SignalDefinition& signal : signalDefinitions)
    {
        QMetaMethodBuilder signalBuilder = builder.addSignal(::createSignature(signal));
        signalBuilder.setReturnType(QMetaType::typeName(QMetaType::Void));
        signalBuilder.setAccess(QMetaMethod::Public);
        m_signalIndexByName[signal.name.toStdString()] = signalBuilder.index();
    }

    std::unordered_map<std::string, int> methodIndexByName;
    for (const SlotDefinition& slot : slotDefinitions)
    {
        QMetaMethodBuilder methodBuilder = builder.addSlot(::createSignature(slot));
        methodBuilder.setReturnType(QMetaType::typeName(slot.returnType));
        methodBuilder.setAttributes(QMetaMethod::Scriptable);
        methodIndexByName[slot.name.toStdString()] = methodBuilder.index();
    }

    for (const PropertyDefinition& property : propertyDefinitions)
    {
        const int notifier = ::valueOrDefault(m_signalIndexByName, property.notifySignal.toStdString(), -1);
        const QByteArray name = property.name.toUtf8();
        const QByteArray typeName = QMetaObject::normalizedType(QMetaType::typeName(property.type));
        QMetaPropertyBuilder propertyBuilder = builder.addProperty(name, typeName, notifier);
        if (notifier == -1)
            propertyBuilder.setConstant(true);
        m_propertySlots[propertyBuilder.name().toStdString()] = std::make_pair(::valueOrDefault(methodIndexByName, property.readSlot.toStdString(), -1),
                                                                               ::valueOrDefault(methodIndexByName, property.writeSlot.toStdString(), -1));
    }

    return builder.toMetaObject();
}

int DosQMetaObject::signalSlotIndex(const QString &signalName) const
{
    return metaObject()->methodOffset() + ::valueOrDefault(m_signalIndexByName, signalName.toStdString(), -1);
}

int DosQMetaObject::readSlotIndex(const char *propertyName) const
{
    return metaObject()->methodOffset() + ::valueOrDefault(m_propertySlots, std::string(propertyName), std::make_pair(-1,-1)).first;
}

int DosQMetaObject::writeSlotIndex(const char *propertyName) const
{
    return metaObject()->methodOffset() + valueOrDefault(m_propertySlots, std::string(propertyName), std::make_pair(-1,-1)).second;
}

const QMetaObject *DosQMetaObject::metaObject() const
{
    return m_metaObject;
}

} // namespace DOS
