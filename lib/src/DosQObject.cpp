#include "DOtherSide/DosQObject.h"
#include "DOtherSide/DosQMetaObject.h"
#include "DOtherSide/DosQObjectImpl.h"
#include "DOtherSide/DosQMetaObject.h"
#include <QtCore/QMetaMethod>
#include <QtCore/QDebug>

namespace
{
    DOS::DosQObjectImpl::ParentMetaCall createParentMetaCall(QObject* parent)
    {
        return [parent](QMetaObject::Call callType, int index, void** args) -> int {
            return parent->QObject::qt_metacall(callType, index, args);
        };
    }
}

namespace DOS
{

DosQObject::DosQObject(OnMetaObject onMetaObject, OnSlotExecuted onSlotExecuted)
    : m_impl(new DosQObjectImpl(this, ::createParentMetaCall(this), std::move(onMetaObject), std::move(onSlotExecuted)))
{}

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

int DosQObject::qt_metacall(QMetaObject::Call call, int index, void** args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(call, index, args);
}

} // namespace DOS
