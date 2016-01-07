#include "DOtherSide/DosQObject.h"
#include "DOtherSide/DosQMetaObject.h"
#include <QtCore/QMetaMethod>
#include <QtCore/QDebug>

namespace DOS
{

DosQObject::DosQObject()
    : m_impl(nullptr)
{
}

bool DosQObject::emitSignal(const QString &name, const std::vector<QVariant> &args)
{
    Q_ASSERT(m_impl);
    return m_impl->emitSignal(name, args);
}

const QMetaObject *DosQObject::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

int DosQObject::qt_metacall(QMetaObject::Call callType, int index, void** args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(callType, index, args);
}

void DosQObject::setImpl(std::unique_ptr<IDosQObject> impl)
{
    m_impl = std::move(impl);
}

} // namespace DOS
