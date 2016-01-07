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

QMetaObject* createDynamicQObjectMetaObject()
{
    QMetaObjectBuilder builder;
    builder.setClassName("DynamicQObject");
    builder.setSuperClass(&QObject::staticMetaObject);
    return builder.toMetaObject();
}

QMetaObject* createDynamicQAbstractListModelMetaObject()
{
    QMetaObjectBuilder builder;
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
    : BaseDosQMetaObject(createMetaObject(superClassMetaObject, className, signalDefinitions, slotDefinitions, propertyDefinitions))
{
}

QMetaObject *DosQMetaObject::createMetaObject(const IDosQMetaObject &superClassMetaObject,
                                              const QString &className,
                                              const SignalDefinitions& signalDefinitions,
                                              const SlotDefinitions& slotDefinitions,
                                              const PropertyDefinitions& propertyDefinitions)
{
    QMetaObjectBuilder builder;
    builder.setClassName(className.toUtf8());
    builder.setSuperClass(superClassMetaObject.metaObject());

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

    return builder.toMetaObject();
}

int DosQMetaObject::signalSlotIndex(const QString &signalName) const
{
    return metaObject()->methodOffset() + m_signalIndexByName.value(signalName.toUtf8(), -1);
}

int DosQMetaObject::readSlotIndex(const char *propertyName) const
{
    return metaObject()->methodOffset() + m_propertySlots.value(propertyName, {-1,-1}).first;
}

int DosQMetaObject::writeSlotIndex(const char *propertyName) const
{
    return metaObject()->methodOffset() + m_propertySlots.value(propertyName, {-1,-1}).second;
}

} // namespace DOS
