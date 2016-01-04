#include "DOtherSide/DynamicQObject.h"
#include "DOtherSide/DynamicQObjectFactory.h"
#include <QtCore/QMetaMethod>
#include <QtCore/QDebug>

namespace DOS
{

DynamicQObject::DynamicQObject()
    : m_impl(nullptr)
{
}

bool DynamicQObject::emitSignal(const QString &name, const std::vector<QVariant> &args)
{
    Q_ASSERT(m_impl);
    return m_impl->emitSignal(name, args);
}

const QMetaObject *DynamicQObject::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

int DynamicQObject::qt_metacall(QMetaObject::Call callType, int index, void** args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(callType, index, args);
}

void DynamicQObject::setImpl(std::unique_ptr<IDynamicQObject> impl)
{
    m_impl = std::move(impl);
}

} // namespace DOS
