#include "DOtherSide/DosQObjectImpl.h"
#include "DOtherSide/DosQMetaObject.h"
#include <QtCore/QMetaObject>
#include <QtCore/QMetaMethod>

namespace DOS
{

DynamicQObjectImpl::DynamicQObjectImpl(QObject* parent,
                                       OnMetaObject onMetaObject,
                                       OnSlotExecuted onSlotExecuted)
    : m_parent(std::move(parent))
    , m_onMetaObject(std::move(onMetaObject))
    , m_onSlotExecuted(std::move(onSlotExecuted))
{
}

bool DynamicQObjectImpl::emitSignal(const QString &name, const std::vector<QVariant> &args)
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
    QMetaObject::activate(m_parent, index, arguments.data());
    return true;
}

const QMetaObject *DynamicQObjectImpl::metaObject() const
{
    return factory()->metaObject();
}

int DynamicQObjectImpl::qt_metacall(QMetaObject::Call callType, int index, void **args)
{
    using Fuction = int (QObject::*)(QMetaObject::Call, int, void**);

    switch (callType)
    {
    case QMetaObject::InvokeMetaMethod:
        return executeSlot(index, args) ? 1 : -1;
    case QMetaObject::ReadProperty:
        return readProperty(index, args) ? 1 : -1;
    case QMetaObject::WriteProperty:
        return writeProperty(index, args) ? 1 : -1;
    default:
        return m_parent->QObject::qt_metacall(callType, index, args);
    }

    return -1;
}

std::shared_ptr<const IDosQMetaObject> DynamicQObjectImpl::factory() const
{
    static std::shared_ptr<const IDosQMetaObject> result = m_onMetaObject()->data();
    return result;
}

bool DynamicQObjectImpl::executeSlot(int index, void **args)
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

bool DynamicQObjectImpl::readProperty(int index, void **args)
{
    const QMetaProperty property = metaObject()->property(index);
    if (!property.isValid() || !property.isReadable())
        return false;
    return executeSlot(factory()->readSlotIndex(property.name()), args);
}

bool DynamicQObjectImpl::writeProperty(int index, void **args)
{
    const QMetaProperty property = metaObject()->property(index);
    if (!property.isValid() || !property.isWritable())
        return false;
    return executeSlot(factory()->writeSlotIndex(property.name()), args);
}

}
