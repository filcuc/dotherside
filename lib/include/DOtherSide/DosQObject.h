#pragma once

// Qt
#include <QObject>
#include <functional>
// DOtherSide
#include "DOtherSideTypesCpp.h"
#include "DOtherSide/DosIQObjectImpl.h"

namespace DOS {

/// This class model a QObject
class DosQObject : public QObject, public DosIQObjectImpl
{
public:
    /// Constructor
    DosQObject(DosIQMetaObjectPtr metaObject,
               OnSlotExecuted onSlotExecuted);

    /// Emit a signal
    bool emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &arguments) override;

    /// Return the metaObject
    const QMetaObject *metaObject() const override;

    /// The qt_metacall
    int qt_metacall(QMetaObject::Call, int, void **) override;

private:
    std::unique_ptr<DosIQObjectImpl> m_impl;
};

} // namespace DOS
