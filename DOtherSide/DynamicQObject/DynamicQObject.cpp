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
    builder.setSuperClass(&QObject::staticMetaObject);
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

    // Collect the current methods and signals
    QList<QMetaMethod> signalsList;
    QList<QMetaMethod> methodsList;

    for (int i = m_metaObject->methodOffset(); i < m_metaObject->methodCount(); ++i)
    {
        auto method = m_metaObject->method(i);
        if (method.methodType() == QMetaMethod::Signal)
            signalsList.append(method);
        else
            methodsList.append(method);
    }

    QMetaObjectBuilder newMetaObjectBuilder;
    newMetaObjectBuilder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    newMetaObjectBuilder.setClassName("DynamicObject");
    newMetaObjectBuilder.setSuperClass(&QObject::staticMetaObject);

    foreach(auto method, signalsList)
        newMetaObjectBuilder.addMethod(method);

    foreach (auto method, methodsList)
        newMetaObjectBuilder.addMethod(method);

    QMetaMethodBuilder methodBuilder = newMetaObjectBuilder.addSlot(slot.signature());
    methodBuilder.setReturnType(QMetaType::typeName(returnType));
    methodBuilder.setAttributes(QMetaMethod::Scriptable);
    m_metaObject.reset(newMetaObjectBuilder.toMetaObject());

    slotIndex = m_metaObject->indexOfSlot(QMetaObject::normalizedSignature(slot.signature()));

    return slotIndex != -1;
}

bool DynamicQObject::registerSignal(const QString& name, const QList<QMetaType::Type>& arguments, int& signalIndex)
{
    DynamicSignal signal(name, arguments);

    if (m_signalsBySignature.contains(signal.signature()))
        return false;

    m_signalsByName.insertMulti(signal.name(), signal);
    m_signalsBySignature[signal.signature()] = signal;

    // Collect the current methods and signals
    QList<QMetaMethod> signalsList;
    QList<QMetaMethod> methodsList;

    for (int i = m_metaObject->methodOffset(); i < m_metaObject->methodCount(); ++i)
    {
        auto method = m_metaObject->method(i);
        if (method.methodType() == QMetaMethod::Signal)
            signalsList.append(method);
        else
            methodsList.append(method);
    }

    QMetaObjectBuilder newMetaObjectBuilder;
    newMetaObjectBuilder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
    newMetaObjectBuilder.setClassName("DynamicObject");
    newMetaObjectBuilder.setSuperClass(&QObject::staticMetaObject);

    foreach(auto method, signalsList)
        newMetaObjectBuilder.addMethod(method);

    QMetaMethodBuilder methodBuilder = newMetaObjectBuilder.addSignal(signal.signature());
    methodBuilder.setReturnType(QMetaType::typeName(QMetaType::Void));
    methodBuilder.setAccess(QMetaMethod::Public);

    foreach (auto method, methodsList)
        newMetaObjectBuilder.addMethod(method);

    m_metaObject.reset(newMetaObjectBuilder.toMetaObject());

    signalIndex = m_metaObject->indexOfSignal(QMetaObject::normalizedSignature(signal.signature()));

    return signalIndex != -1;
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

        if (!method.isValid())
            return -1;

        DynamicSlot slot = m_slotsBySignature[method.methodSignature()];

        if (!slot.isValid())
            return -1;

        int numParametersPlusReturn = method.parameterCount() + 1;

        // Pack the slot name
        QVariant slotName(slot.name());

        // Pack the arguments to QVariants
        std::vector<QVariant> argumentsAsVariants(numParametersPlusReturn);
        std::vector<void*> argumentsAsVoidPointers(numParametersPlusReturn);

        for (int i = 0; i < numParametersPlusReturn; ++i) {
            int parameterType = i == 0 ? method.returnType() : method.parameterType(i - 1);
            argumentsAsVariants[i] =  parameterType != QMetaType::Void ? QVariant(parameterType, args[i]) : QVariant();
            argumentsAsVoidPointers[i] = &argumentsAsVariants[i];
        }

        // Forward  values and types to D
        if (m_dObjectCallback && m_dObjectPointer)
            m_dObjectCallback(m_dObjectPointer, &slotName, numParametersPlusReturn, &argumentsAsVoidPointers[0]);

        // Update the return value
        if (method.returnType() != QMetaType::Void)
        {
            const void* returnValue = argumentsAsVariants.front().constData();
            QMetaType metatype(method.returnType());
            metatype.construct(args[0], returnValue);
        }

        return 1;
    }

    return -1;
}



