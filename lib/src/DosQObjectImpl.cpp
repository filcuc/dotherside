#include "DOtherSide/DosQObjectImpl.h"
#include "DOtherSide/DosQMetaObject.h"
#include <QtCore/QMetaObject>
#include <QtCore/QMetaMethod>
#include <QtCore/QDebug>

namespace DOS {

DosQObjectImpl::DosQObjectImpl(QObject *parent,
                               ParentMetaCall parentMetaCall,
                               std::shared_ptr<const DosIQMetaObject> metaObject,
                               OnSlotExecuted onSlotExecuted)
    : m_parent(std::move(parent))
    , m_parentMetaCall(std::move(parentMetaCall))
    , m_onSlotExecuted(std::move(onSlotExecuted))
    , m_metaObject(std::move(metaObject))
{
}

bool DosQObjectImpl::emitSignal(const QString &name, const std::vector<QVariant> &args)
{
    const QMetaMethod method = m_metaObject->signal(name);
    if (!method.isValid())
        return false;

    Q_ASSERT(name.toUtf8() == method.name());

    std::vector<void *> arguments(args.size() + 1, nullptr);
    arguments.front() = nullptr;
    auto func = [](const QVariant & arg) -> void * { return (void *)(&arg); };
    std::transform(args.begin(), args.end(), arguments.begin() + 1, func);
    QMetaObject::activate(m_parent, method.methodIndex(), arguments.data());
    return true;
}

const QMetaObject *DosQObjectImpl::metaObject() const
{
    return m_metaObject->metaObject();
}

int DosQObjectImpl::qt_metacall(QMetaObject::Call callType, int index, void **args)
{
    index = m_parentMetaCall(callType, index, args);
    if (index < 0)
        return index;

    switch (callType) {
    case QMetaObject::InvokeMetaMethod:
        executeSlot(index, args);
        break;
    case QMetaObject::ReadProperty:
        readProperty(index, args);
        break;
    case QMetaObject::WriteProperty:
        writeProperty(index, args);
        break;
    }

    return -1;
}

bool DosQObjectImpl::executeSlot(int index, void **args)
{
    const QMetaObject *const mo = this->metaObject();
    const QMetaMethod method = mo->method(mo->methodOffset() + index);
    if (!method.isValid()) {
        qDebug() << "C++: executeSlot: invalid method";
        return false;
    }
    executeSlot(method, args);
}

bool DosQObjectImpl::executeSlot(const QMetaMethod &method, void **args, int argumentsOffset)
{
    Q_ASSERT(method.isValid());

    const bool hasReturnType = method.returnType() != QMetaType::Void;

    std::vector<QVariant> arguments;
    arguments.reserve(method.parameterCount());
    for (int i = 0, j = argumentsOffset; i < method.parameterCount(); ++i, ++j) {
        QVariant argument(method.parameterType(i), args[j]);
        arguments.emplace_back(std::move(argument));
    }

    const QVariant result = m_onSlotExecuted(method.name(), arguments); // Execute method

    if (hasReturnType && result.isValid()) {
        QMetaType::construct(method.returnType(), args[0], result.constData());
    }

    return true;
}

bool DosQObjectImpl::readProperty(int index, void **args)
{
    const QMetaObject *const mo = metaObject();
    const QMetaProperty property = mo->property(mo->propertyOffset() + index);
    if (!property.isValid() || !property.isReadable())
        return false;
    const QMetaMethod method = m_metaObject->readSlot(property.name());
    if (!method.isValid()) {
        qDebug() << "C++: readProperty: invalid read method for property " << property.name();
        return false;
    }
    return executeSlot(method, args);
}

bool DosQObjectImpl::writeProperty(int index, void **args)
{
    const QMetaObject *const mo = metaObject();
    const QMetaProperty property = mo->property(mo->propertyOffset() + index);
    if (!property.isValid() || !property.isWritable())
        return false;
    const QMetaMethod method = m_metaObject->writeSlot(property.name());
    if (!method.isValid()) {
        qDebug() << "C++: writeProperty: invalid write method for property " << property.name();
        return false;
    }
    return executeSlot(method, args, 0);
}

}
