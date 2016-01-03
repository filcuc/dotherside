#include "DOtherSide/DynamicQObject.h"
#include "DOtherSide/DynamicQObjectFactory.h"
#include <QtCore/QMetaMethod>
#include <QtCore/QDebug>

namespace DOS
{

DynamicQObject::DynamicQObject(OnMetaObject onMetaObject, OnSlotExecuted onSlotExecuted)
    : m_onMetaObject(std::move(onMetaObject))
    , m_onSlotExecuted(std::move(onSlotExecuted))
{
}

bool DynamicQObject::emitSignal(const QString &name, const std::vector<QVariant> &args)
{
    const int index = factory()->signalSlotIndex(name);
    const QMetaMethod method = metaObject()->method(index);
    if (!method.isValid())
        return false;
    Q_ASSERT(name.toUtf8() == method.name());

    std::vector<void*> arguments(args.size() + 1, nullptr);
    arguments.front() = nullptr;
    auto func = [](const QVariant& arg) -> void* { return (void*)(&arg); };
    std::transform(args.begin(), args.end(), arguments.begin() + 1, func);
    QMetaObject::activate(this, index, arguments.data());
    return true;
}

const QMetaObject *DynamicQObject::metaObject() const
{
    return factory()->metaObject();
}

int DynamicQObject::qt_metacall(QMetaObject::Call callType, int index, void** args)
{
    switch (callType)
    {
    case QMetaObject::InvokeMetaMethod:
        return executeSlot(index, args) ? 1 : -1;
    case QMetaObject::ReadProperty:
        return readProperty(index, args) ? 1 : -1;
    case QMetaObject::WriteProperty:
        return writeProperty(index, args) ? 1 : -1;
    default:
        return QObject::qt_metacall(callType, index, args);
    }

    return -1;
}

bool DynamicQObject::executeSlot(int index, void **args)
{
    const QMetaMethod method = metaObject()->method(index);
    if (!method.isValid())
        return false;

    const bool hasReturnType = method.returnType() != QMetaType::Void;

    std::vector<QVariant> arguments;
    arguments.reserve(method.parameterCount());
    for (int i = 0, j = hasReturnType ? 1 : 0; i < method.parameterCount(); ++i, ++j) {
        QVariant argument(method.parameterType(i), args[j]);
        arguments.emplace_back(std::move(argument));
    }

    QVariant result = m_onSlotExecuted(method.name(), arguments); // Execute method

    if (hasReturnType && result.isValid()) {
        QMetaType::construct(method.returnType(), args[0], result.constData());
    }

    return true;
}

bool DynamicQObject::readProperty(int index, void **args)
{
    const QMetaProperty property = metaObject()->property(index);
    if (!property.isValid() || !property.isReadable())
        return false;
    return executeSlot(factory()->readSlotIndex(property.name()), args);
}

bool DynamicQObject::writeProperty(int index, void **args)
{
    const QMetaProperty property = metaObject()->property(index);
    if (!property.isValid() || !property.isWritable())
        return false;
    return executeSlot(factory()->writeSlotIndex(property.name()), args);
}

std::shared_ptr<const DynamicQObjectFactoryData> DynamicQObject::factory() const
{
    static std::shared_ptr<const DynamicQObjectFactoryData> result = m_onMetaObject()->data();
    return result;
}

} // namespace DOS
