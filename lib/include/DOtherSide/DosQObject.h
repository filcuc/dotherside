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

    /// Return the metaobject
    const QMetaObject* metaObject() const override;

    /// qt metacall
    int qt_metacall(QMetaObject::Call callType, int index, void**args) override;

    /// Set the implementation
    void setImpl(std::unique_ptr<IDosQObject> impl);

private:
    std::unique_ptr<IDosQObject> m_impl;
};

} // namespace DOS
