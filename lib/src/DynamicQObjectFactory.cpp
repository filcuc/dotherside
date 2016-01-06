#include "DOtherSide/DynamicQObjectFactory.h"
#include "DOtherSide/DynamicQObject.h"
#include "private/qmetaobjectbuilder_p.h"
#include "private/qmetaobject_p.h"
#include "private/qobject_p.h"

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
}

namespace DOS
{

DynamicQObjectFactoryData::DynamicQObjectFactoryData(SignalDefinitions signalDefinitions,
                                                     SlotDefinitions slotDefinitions,
                                                     PropertyDefinitions propertyDefinitions)
    : m_metaObject(nullptr)
{
    QMetaObjectBuilder builder;
    builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    builder.setClassName("DynamicQObject");
    builder.setSuperClass(&QObject::staticMetaObject);

    m_signalIndexByName.reserve(signalDefinitions.size());

    for (const SignalDefinition& signal : signalDefinitions)
    {
        QMetaMethodBuilder signalBuilder = builder.addSignal(::createSignature(signal));
        signalBuilder.setReturnType(QMetaType::typeName(QMetaType::Void));
        signalBuilder.setAccess(QMetaMethod::Public);
        m_signalIndexByName[signal.name.toUtf8()] = signalBuilder.index();
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
        const int notifier = m_signalIndexByName.value(property.notifySignal.toUtf8(), -1);
        const QByteArray name = property.name.toUtf8();
        const QByteArray typeName = QMetaObject::normalizedType(QMetaType::typeName(property.type));
        QMetaPropertyBuilder propertyBuilder = builder.addProperty(name, typeName, notifier);
        if (notifier == -1)
            propertyBuilder.setConstant(true);
        m_propertySlots[propertyBuilder.name()] = { methodIndexByName.value(property.readSlot, -1)
                , methodIndexByName.value(property.writeSlot, -1)};
    }

    m_metaObject.reset(builder.toMetaObject());
}

} // namespace DOS
