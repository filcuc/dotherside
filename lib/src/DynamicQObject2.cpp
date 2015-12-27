#include "DOtherSide/DynamicQObject2.h"
#include "DOtherSide/DynamicQObjectFactory.h"
#include <QtCore/QMetaMethod>
#include <QtCore/QDebug>

namespace DOS
{

DynamicQObject2::DynamicQObject2(const DynamicQObjectFactory *factory,
                                 OnSlotExecuted handler)
    : m_factory(factory)
    , m_handler(std::move(handler))
{}

void DynamicQObject2::emitSignal(const QString &name, const std::vector<QVariant> &args)
{
    const int index = metaObject()->methodOffset() + m_factory->signalSlotIndex(name);
    const QMetaMethod method = metaObject()->method(index);
    if (!method.isValid()) {
        qDebug() << "Cannot emit signal from invalid method";
        return;
    }
    Q_ASSERT(name.toUtf8() == method.name());

    std::vector<void*> arguments(args.size() + 1, nullptr);
    arguments.front() = nullptr;
    auto func = [](const QVariant& arg) -> void* { return (void*)(&arg); };
    std::transform(args.begin(), args.end(), arguments.begin() + 1, func);
    QMetaObject::activate(this, method.methodIndex(), arguments.data());
}

const QMetaObject *DynamicQObject2::metaObject() const
{
    return m_factory->metaObject();
}

int DynamicQObject2::qt_metacall(QMetaObject::Call callType, int index, void** args)
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

bool DynamicQObject2::executeSlot(int index, void **args)
{
    const QMetaMethod method = metaObject()->method(index);
    if (!method.isValid()) {
        qDebug() << "Cannot execute invalid method";
        return false;
    }

    std::vector<QVariant> arguments;
    arguments.reserve(method.parameterCount());
    for (int i = 0; i < method.parameterCount(); ++i) {
        QVariant argument(method.parameterType(i), args[i + 1]);
        arguments.emplace_back(std::move(argument));
    }

    QVariant result = m_handler(method.name(), arguments); // Execute method

    if (method.returnType() != QMetaType::Void && result.isValid()) {
        QMetaType::construct(method.returnType(), args[0], result.constData());
    }

    return true;
}

bool DynamicQObject2::readProperty(int index, void **args)
{
    const QMetaProperty property = metaObject()->property(index);
    if (!property.isValid() || !property.isReadable()) {
        qDebug() << "Cannot read invalid or unreadable property ";
        return false;
    }
    return executeSlot(m_factory->readSlotIndex(property.name()), args);
}

bool DynamicQObject2::writeProperty(int index, void **args)
{
    const QMetaProperty property = metaObject()->property(index);
    if (!property.isValid() || !property.isWritable()) {
        qDebug() << "Cannot write invalid or unwritable property ";
        return false;
    }
    return executeSlot(m_factory->writeSlotIndex(property.name()), args);
}

} // namespace DOS
