#pragma once

#include "private/qobject_p.h"

namespace DOS
{

class IDosQObject
{
public:
    /// Destructor
    virtual ~IDosQObject() = default;

    /// Emit the signal with the given name and arguments
    virtual bool emitSignal(const QString& name, const std::vector<QVariant>& argumentsValues) = 0;

    /// Return the metaObject
    virtual const QMetaObject* metaObject() const = 0;

    /// The qt_metacall implementation
    virtual int qt_metacall(QMetaObject::Call, int, void**) = 0;
};

} // namespace dos
