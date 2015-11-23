#pragma once

// std
#include <memory>
#include <array>
// Qt
#include <QtCore/QObject>
#include <QtCore/QScopedPointer>
#include <QtCore/QDebug>
#include "private/qmetaobjectbuilder_p.h"
// DOtherSide
#include "DOtherSide/DynamicSignal.h"
#include "DOtherSide/DynamicSlot.h"
#include "DOtherSide/DynamicProperty.h"
#include "DOtherSide/IDynamicQObject.h"

/// This class implements a QObject to which signals, slots and properties can be added dynamically
template <class T>
class DynamicQObject : public T, public IDynamicQObject
{
    using SafeQMetaObjectPtr = std::unique_ptr<QMetaObject, void(*)(void*)>;
    using OnSlotExecutedHandler = std::function<QVariant(const DynamicSlot&, const std::vector<QVariant>&)>;

public:
    /// Constructor
    DynamicQObject();

    /// Destructor
    virtual ~DynamicQObject();

    /// Sets the on slot executed handler
    void setOnSlotExecutedHandler(const OnSlotExecutedHandler& handler);

    /// Register a new signal
    bool registerSignal(const QString& name,
                        const QList<QMetaType::Type>& argumentsTypes,
                        int& signalIndex) override;

    /// Register a new slot
    bool registerSlot(const QString& name,
                      const QMetaType::Type returnType,
                      const QList<QMetaType::Type>& argumentsTypes,
                      int& slotIndex) override;

    /// Register a new property
    bool registerProperty(const QString& name,
                          QMetaType::Type type,
                          const QString& readSlotName,
                          const QString& writeSlotName = "",
                          const QString& notifySignalName = "") override;

    /// Emit the signal with the given name and arguments
    bool emitSignal(const QString& name, const QList<QVariant>& argumentsValues) override;

    /// Return the QMetaObject for this DynamicQObject
    const QMetaObject* metaObject() const override;

    /// The qt metacall. Called from Qt when a signals, slot or property is invoked
    int qt_metacall(QMetaObject::Call, int, void**) override;

private:
    bool executeSlot(const DynamicSlot& slot, void**  args);

    bool readProperty(const DynamicProperty& property, void** args);

    bool writeProperty(const DynamicProperty& property, void** args);

    /// Function for recreating the metaobject starting from another one.
    /// The creation is customizable by injecting custom code after signals and slots have
    /// been added
    static QMetaObject* recreateMetaObjectBuilder(QMetaObject* currentMetaObject,
                                                  const std::function<void(QMetaObjectBuilder&)>& afterSignalAdded,
                                                  const std::function<void(QMetaObjectBuilder&)>& afterSlotAdded,
                                                  const std::function<void(QMetaObjectBuilder&)>& afterPropertyAdded);

    SafeQMetaObjectPtr m_metaObject;
    QHash<QString, DynamicSignal> m_signalsByName;
    QHash<QByteArray, DynamicSignal> m_signalsBySignature;
    QHash<QString, DynamicSlot> m_slotsByName;
    QHash<QByteArray, DynamicSlot> m_slotsBySignature;
    QHash<QByteArray, DynamicProperty> m_propertiesByName;
    OnSlotExecutedHandler m_onSlotExecutedHandler;
};

template <typename T>
DynamicQObject<T>::DynamicQObject()
    : T()
    , m_metaObject(nullptr, ::free)
{
    QMetaObjectBuilder builder;
    builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    builder.setClassName("DynamicQObject");
    builder.setSuperClass(&T::staticMetaObject);
    m_metaObject.reset(builder.toMetaObject());
}

template <typename T>
void DynamicQObject<T>::setOnSlotExecutedHandler(const typename DynamicQObject::OnSlotExecutedHandler &handler)
{
    m_onSlotExecutedHandler = handler;
}

template <typename T>
DynamicQObject<T>::~DynamicQObject() = default;

template <typename T>
bool DynamicQObject<T>::registerSlot(const QString& name,
                                     const QMetaType::Type returnType,
                                     const QList<QMetaType::Type>& argumentsTypes,
                                     int& slotIndex)
{
    DynamicSlot slot(name, returnType, argumentsTypes);

    if (m_slotsBySignature.contains(slot.signature()))
        return false;

    m_slotsByName.insertMulti(slot.name(), slot);
    m_slotsBySignature[slot.signature()] = slot;

    auto afterSignalAdded = [](QMetaObjectBuilder&) {};
    auto afterPropertyAdded = afterSignalAdded;

    auto afterSlotAdded = [&slot, returnType](QMetaObjectBuilder & metaObjectBuilder) {
        QMetaMethodBuilder methodBuilder = metaObjectBuilder.addSlot(slot.signature());
        methodBuilder.setReturnType(QMetaType::typeName(returnType));
        methodBuilder.setAttributes(QMetaMethod::Scriptable);
    };

    auto newMetaObject = recreateMetaObjectBuilder(m_metaObject.get(),
                                                   afterSignalAdded,
                                                   afterSlotAdded,
                                                   afterPropertyAdded);

    m_metaObject.reset(newMetaObject);

    slotIndex = m_metaObject->indexOfSlot(QMetaObject::normalizedSignature(slot.signature()));

    return slotIndex != -1;
}

template <typename T>
bool DynamicQObject<T>::registerSignal(const QString& name, const QList<QMetaType::Type>& arguments, int& signalIndex)
{
    DynamicSignal signal(name, arguments);

    if (m_signalsBySignature.contains(signal.signature()))
        return false;

    m_signalsByName.insertMulti(signal.name(), signal);
    m_signalsBySignature[signal.signature()] = signal;

    auto afterSignalAdded = [&signal](QMetaObjectBuilder & metaObjectBuilder) {
        QMetaMethodBuilder methodBuilder = metaObjectBuilder.addSignal(signal.signature());
        methodBuilder.setReturnType(QMetaType::typeName(QMetaType::Void));
        methodBuilder.setAccess(QMetaMethod::Public);
    };

    auto afterSlotAdded = [](QMetaObjectBuilder&) {};
    auto afterPropertyAdded = afterSlotAdded;

    auto newMetaObject = recreateMetaObjectBuilder(m_metaObject.get(),
                                                   afterSignalAdded,
                                                   afterSlotAdded,
                                                   afterPropertyAdded);

    m_metaObject.reset(newMetaObject);

    signalIndex = m_metaObject->indexOfSignal(QMetaObject::normalizedSignature(signal.signature()));

    return signalIndex != -1;
}

template <typename T>
bool DynamicQObject<T>::registerProperty(const QString& name,
                                         QMetaType::Type type,
                                         const QString& readSlotName,
                                         const QString& writeSlotName,
                                         const QString& notifySignalName)
{
    DynamicProperty property(name, type, readSlotName, writeSlotName, notifySignalName);

    DynamicSignal notifySignal;

    if (!notifySignalName.isEmpty())
    {
        notifySignal = m_signalsByName.value(notifySignalName, DynamicSignal());
        if (!notifySignal.isValid())
            return false;
    }

    m_propertiesByName.insert(name.toUtf8(), property);

    auto afterSignalAdded = [](QMetaObjectBuilder & metaObjectBuilder) { Q_UNUSED(metaObjectBuilder); };
    auto afterSlotAdded = [](QMetaObjectBuilder & metaObjectBuilder) { Q_UNUSED(metaObjectBuilder); };
    auto afterPropertyAdded = [name, type, notifySignal](QMetaObjectBuilder & metaObjectBuilder)
    {
        int signalIndex = -1;
        if (notifySignal.isValid())
        {
            for (int i = 0; i < metaObjectBuilder.methodCount(); ++i)
            {
                QMetaMethodBuilder methodBuilder = metaObjectBuilder.method(i);
                if (methodBuilder.methodType() == QMetaMethod::Signal)
                {
                    if (methodBuilder.signature() == QMetaObject::normalizedSignature(notifySignal.signature()))
                    {
                        signalIndex = i;
                        break;
                    }
                }
            }

        }

        auto typeName = QMetaType::typeName(type);
        auto builder = metaObjectBuilder.addProperty(name.toUtf8(),
                                                     QMetaObject::normalizedType(typeName),
                                                     signalIndex);
        if (signalIndex == -1)
            builder.setConstant(true);
    };

    auto newMetaObject = recreateMetaObjectBuilder(m_metaObject.get()
                                                   , afterSignalAdded
                                                   , afterSlotAdded
                                                   , afterPropertyAdded);
    m_metaObject.reset(newMetaObject);
    return true;
}

template <typename T>
bool DynamicQObject<T>::emitSignal(const QString& name, const QList<QVariant>& args)
{
    DynamicSignal signal;

    for (DynamicSignal currentSignal : m_signalsByName.values(name))
    {
        if (currentSignal.validate(args))
        {
            signal = currentSignal;
            break;
        }
    }

    if (!signal.isValid())
        return false;

    int index = m_metaObject->indexOfSignal(QMetaObject::normalizedSignature(signal.signature()));
    if (index < 0)
        return false;

    QVariantList argsCopy = args;

    QVector<void*> arguments(argsCopy.size() + 1 , 0);
    arguments[0] = 0;
    for (int i = 0; i < argsCopy.size(); ++i)
        arguments[i + 1] = &argsCopy[i];

    QMetaObject::activate(this, index, arguments.data());

    return true;
}

template <typename T>
const QMetaObject* DynamicQObject<T>::metaObject() const
{
    return m_metaObject.get();
}

template <typename T>
bool DynamicQObject<T>::executeSlot(const DynamicSlot& slot, void**  args)
{
    if (!slot.isValid())
        return false;

    std::vector<QVariant> arguments;
    arguments.reserve(slot.argumentsTypes().size());
    for (int i = 0; i < slot.argumentsTypes().count(); ++i)
        arguments.emplace_back(QVariant(slot.argumentTypeAt(i), args[i + 1]));

    QVariant result = m_onSlotExecutedHandler(slot, arguments);

    if (slot.returnType() != QMetaType::Void && result.isValid())
    {
        QMetaType metatype(slot.returnType());
        metatype.construct(args[0], result.constData());
    }

    return true;
}

template <typename T>
bool DynamicQObject<T>::readProperty(const DynamicProperty& property, void** args)
{
    if (!property.isValid())
        return false;

    if (!property.isReadable())
        return false;

    DynamicSlot readSlot = m_slotsByName.value(property.readSlot(), DynamicSlot());

    if (!readSlot.isValid())
        return false;

    if (readSlot.argumentsTypes().count() > 0)
        return false;

    if (readSlot.returnType() != property.type())
        return false;

    return executeSlot(readSlot, args);
}

template <typename T>
bool DynamicQObject<T>::writeProperty(const DynamicProperty& property, void** args)
{
    if (!property.isValid())
        return false;

    if (!property.isWriteable())
        return false;

    DynamicSlot writeSlot = m_slotsByName.value(property.writeSlot(), DynamicSlot());

    if (!writeSlot.isValid())
        return false;

    if (writeSlot.argumentsTypes().count() != 1)
        return false;

    if (writeSlot.returnType() != QMetaType::Void)
        return false;

    void* sortedArgs[2];                    // The write property is peculiar because it has
    sortedArgs[0] = args[2];                // the actual value in pos 0 and result in 2
    sortedArgs[1] = args[0];                // We reorder it for having the result in 0 and
    executeSlot(writeSlot, sortedArgs);     // first arg in 1

    return true;
}

template <typename T>
int DynamicQObject<T>::qt_metacall(QMetaObject::Call callType, int index, void**  args)
{
    switch (callType)
    {
    case QMetaObject::InvokeMetaMethod: {
        QMetaMethod method = m_metaObject->method(index);

        if (!method.isValid())
            return -1;

        DynamicSlot slot = m_slotsBySignature[method.methodSignature()];
        return executeSlot(slot, args) ? 1 : -1;
    }

    case QMetaObject::ReadProperty: {
        QMetaProperty metaProperty = m_metaObject->property(index);

        if (!metaProperty.isValid())
            return -1;

        DynamicProperty dynamicProperty = m_propertiesByName.value(metaProperty.name(), DynamicProperty());
        return readProperty(dynamicProperty, args) ? 1 : -1;
    }

    case QMetaObject::WriteProperty: {
        QMetaProperty metaProperty = m_metaObject->property(index);

        if (!metaProperty.isValid())
            return -1;

        DynamicProperty dynamicProperty = m_propertiesByName.value(metaProperty.name(), DynamicProperty());
        return writeProperty(dynamicProperty, args) ? 1 : -1;
    }

    default:
        return T::qt_metacall(callType, index, args);
    }

    return -1;
}

template <typename T>
QMetaObject* DynamicQObject<T>::recreateMetaObjectBuilder(QMetaObject* currentMetaObject,
                                                          const std::function<void(QMetaObjectBuilder&)>& afterSignalAdded,
                                                          const std::function<void(QMetaObjectBuilder&)>& afterSlotAdded,
                                                          const std::function<void(QMetaObjectBuilder&)>& afterPropertyAdded)
{
    // Collect the current methods and signals
    QList<QMetaMethod> signalsList;
    QList<QMetaMethod> methodsList;
    QList<QMetaProperty> propertiesList;

    for (int i = currentMetaObject->methodOffset(); i < currentMetaObject->methodCount(); ++i)
    {
        QMetaMethod method = currentMetaObject->method(i);
        if (method.methodType() == QMetaMethod::Signal)
            signalsList.append(method);
        else
            methodsList.append(method);
    }

    for (int i = currentMetaObject->propertyOffset(); i < currentMetaObject->propertyCount(); ++i)
    {
        QMetaProperty property = currentMetaObject->property(i);
        propertiesList.append(property);
    }

    QMetaObjectBuilder metaObjectBuilder;
    metaObjectBuilder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    metaObjectBuilder.setClassName(currentMetaObject->className());
    metaObjectBuilder.setSuperClass(currentMetaObject->superClass());

    for (auto& method : signalsList)
        metaObjectBuilder.addMethod(method);

    // Call custom code to be executed after signal have been added
    afterSignalAdded(metaObjectBuilder);

    for (auto& method : methodsList)
        metaObjectBuilder.addMethod(method);

    // Call custom code to be executed after slots have been added
    afterSlotAdded(metaObjectBuilder);

    for (auto& property : propertiesList)
        metaObjectBuilder.addProperty(property);

    afterPropertyAdded(metaObjectBuilder);

    return metaObjectBuilder.toMetaObject();
}
