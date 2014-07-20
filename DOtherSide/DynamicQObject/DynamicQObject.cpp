#include "DynamicQObject.h"
#include <QDebug>
#include <memory>
#include <array>
#include "private/qmetaobjectbuilder_p.h"

DynamicQObject::DynamicQObject(QObject* parent)
    : m_dObjectPointer(nullptr)
    , m_dObjectCallback(nullptr)
{
    QMetaObjectBuilder builder;
    builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    builder.setClassName("DynamicQObject");
    builder.setSuperClass(QObject::metaObject());
    m_metaObject.reset(builder.toMetaObject());
}

DynamicQObject::~DynamicQObject()
{
}

bool DynamicQObject::registerSlot(const QString& name,
                                  const QMetaType::Type returnType,
                                  const QList<QMetaType::Type>& argumentsTypes,
                                  int& slotIndex)
{   
    DynamicSlot slot (name, returnType, argumentsTypes);

    if (m_slotsBySignature.contains(slot.signature()))
        return false;

    m_slotsByName.insertMulti(slot.name(), slot);
    m_slotsBySignature[slot.signature()] = slot;

    QMetaObjectBuilder builder(m_metaObject.data());
    QMetaMethodBuilder methodBuilder = builder.addSlot(slot.signature());
    methodBuilder.setReturnType(QMetaType::typeName(returnType));
    methodBuilder.setAttributes(QMetaMethod::Scriptable);
    m_metaObject.reset(builder.toMetaObject());

    slotIndex = m_metaObject->indexOfSlot(QMetaObject::normalizedSignature(slot.signature()));

    return slotIndex != -1;
}

bool DynamicQObject::executeSlot(const QString& name, const QList<QVariant>& argumentsValues)
{
    DynamicSlot slot;

    for (DynamicSlot currentSlot : m_slotsByName.values(name))
    {
        if (currentSlot.validate(argumentsValues))
        {
            slot = currentSlot;
            break;
        }
    }

    if (!slot.isValid())
        return false;

    int index = m_metaObject->indexOfSlot(QMetaObject::normalizedSignature(slot.signature()));
    if (index < 0)
        return false;

    auto method = m_metaObject->method(index);

    method.invoke(this, Q_ARG(QVariant, argumentsValues[0]));

    return true;
}

bool DynamicQObject::registerSignal(const QString& name, const QList<QMetaType::Type>& arguments)
{
    DynamicSignal signal(name, arguments);

    if (m_signalsBySignature.contains(signal.signature()))
        return false;

    m_signalsByName.insertMulti(signal.name(), signal);
    m_signalsBySignature[signal.signature()] = signal;

    QMetaObjectBuilder builder(m_metaObject.data());
    builder.addSignal(signal.signature());
    m_metaObject.reset(builder.toMetaObject());

    return true;
}

bool DynamicQObject::emitSignal(const QString& name, const QList<QVariant>& args)
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

    QVector<void*> arguments(argsCopy.size() + 1 ,0);
    arguments[0] = 0;
    for (int i = 0; i < argsCopy.size(); ++i)
        arguments[i + 1] = &argsCopy[i];

    QMetaObject::activate(this, index, arguments.data());

    return true;
}

const QMetaObject* DynamicQObject::metaObject() const
{
    return m_metaObject.data();
}

int DynamicQObject::qt_metacall(QMetaObject::Call callType, int index, void**  args)
{
    if (callType == QMetaObject::InvokeMetaMethod)
    {
        QMetaMethod method = m_metaObject->method(index);

        if (!method.isValid()) return -1;

        DynamicSlot slot = m_slotsBySignature[method.methodSignature()];

        if (!slot.isValid()) return -1;

        int slotIndex = m_metaObject->indexOfSlot(QMetaObject::normalizedSignature(slot.signature()));

        int size = method.parameterCount() + 1; // Add return type

        // Create the parameter types vector and allocate it on the stack
        std::vector<int> parameterTypes;
        parameterTypes.push_back(method.returnType());

        for (int i = 0; i < size; ++i)
            parameterTypes.push_back(method.parameterType(i));

        qDebug() << "C++: " << __func__ << parameterTypes[0];

        // Forward  values and types to D
        if (m_dObjectCallback && m_dObjectPointer)
            m_dObjectCallback(m_dObjectPointer, slotIndex, size, &parameterTypes[0], size, &args);

        return 1;
    }

    return -1;
}



