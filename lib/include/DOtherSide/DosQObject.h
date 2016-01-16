#pragma once

// Qt
#include <QObject>
#include <functional>
// DOtherSide
#include "DOtherSideTypesCpp.h"
#include "DOtherSide/IDosQObject.h"

namespace DOS
{

/// This class model a QObject
class DosQObject : public QObject, public IDosQObject
{
public:
    /// Constructor
    DosQObject(OnMetaObject onMetaObject,
               OnSlotExecuted onSlotExecuted);

    /// Emit a signal
    bool emitSignal(const QString& name, const std::vector<QVariant>& arguments) override;

    /// Return the metaObject
    const QMetaObject* metaObject() const override;

    /// The qt_metacall
    int qt_metacall(QMetaObject::Call, int, void **) override;

private:
    IDosQObject* m_impl;
};

} // namespace DOS
