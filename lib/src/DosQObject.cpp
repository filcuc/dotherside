#include "DOtherSide/DosQObject.h"
#include "DOtherSide/DosQMetaObject.h"
#include "DOtherSide/DosQObjectImpl.h"
#include "DOtherSide/DosQMetaObject.h"
#include <QtCore/QMetaMethod>
#include <QtCore/QDebug>

namespace DOS
{

DosQObject::DosQObject(OnMetaObject onMetaObject, OnSlotExecuted onSlotExecuted)
    : m_impl(new DosQObjectImpl(this, std::move(onMetaObject), std::move(onSlotExecuted)))
{}

bool DosQObject::emitSignal(const QString &name, const std::vector<QVariant> &args)
{
    Q_ASSERT(m_impl);
    return m_impl->emitSignal(name, args);
}

} // namespace DOS
