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
};

} // namespace DOS
