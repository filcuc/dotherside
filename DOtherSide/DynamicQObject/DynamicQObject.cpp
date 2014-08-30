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

    QMetaObjectBuilder builder(m_metaObject.data());
    QMetaMethodBuilder methodBuilder = builder.addSlot(slot.signature());
    methodBuilder.setReturnType(QMetaType::typeName(returnType));
    methodBuilder.setAttributes(QMetaMethod::Scriptable);
    m_metaObject.reset(builder.toMetaObject());

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

    QMetaObjectBuilder builder(m_metaObject.data());
    QMetaMethodBuilder methodBuilder = builder.addSignal(signal.signature());
    methodBuilder.setReturnType(QMetaType::typeName(QMetaType::Void));
    methodBuilder.setAccess(QMetaMethod::Public);
    m_metaObject.reset(builder.toMetaObject());

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

        if (!method.isValid()) return -1;

        DynamicSlot slot = m_slotsBySignature[method.methodSignature()];

        qDebug() << "Slot" << slot.name();

        if (!slot.isValid()) return -1;

        int slotIndex = m_metaObject->indexOfSlot(QMetaObject::normalizedSignature(slot.signature()));

        int numParametersPlusReturn = method.parameterCount() + 1;

        /*
         * TODO: ALLOCATE ON THE STACK AN ARRAY OF VOID* EACH ONE IS
         * A POINTER TO A QVARIANT INITIALIZED WITH THE VALUE RECEIVED IN THIS METACALL.
         * THEN FORWARD IT TO D.
         * D THEN CAN SIMPLY CREATE SOME QVARIANT FOR THE VOID POINTERS AND USE
         * THE API FOR QVARIANTS.
         * THIS SOLUTION ALLOW ALSO THE D TO SET THE RETURN VALUE TO THE FIRST QVARIANT
         * AND THEN WE CAN SAFELY COPY ITS VALUE THE FIRST ARGS HERE.
         *
         * CHANGE ALSO THE CALLBACK OF D. INFACT WE DON'T NEED ANYMORE THE METATYPES.
         * BECAUSE THIS INFORMATION CAN BE DISCOVERED FROM THE QVARIANT API
         */

        std::vector<QVariant> argumentsAsVariants(numParametersPlusReturn);
        std::vector<void*> argumentsAsVoidPointers(numParametersPlusReturn);

        for (int i = 0; i < numParametersPlusReturn; ++i) {
            int parameterType = i == 0 ? method.returnType() : method.parameterType(i - 1);
            qDebug() << "C++: parameter metatype " << parameterType;
            QVariant variant(parameterType, args[i]);
            qDebug() << "C++ parameter value as variant " << variant.toString();
            argumentsAsVariants[i] = variant;
            argumentsAsVoidPointers[i] = &argumentsAsVariants[i];
        }

        // Forward  values and types to D
        if (m_dObjectCallback && m_dObjectPointer)
            m_dObjectCallback(m_dObjectPointer, slotIndex, numParametersPlusReturn, &argumentsAsVoidPointers[0]);

        const void* temp = argumentsAsVariants.front().constData();
        QVariant temp2(method.returnType(), temp);

        qDebug() << "C++: " << temp << temp2.toString();

        QMetaType metatype(method.returnType());
        metatype.construct(args[0], temp);

        return 1;
    }

    return -1;
}



