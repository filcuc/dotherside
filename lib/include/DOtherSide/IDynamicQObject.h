#pragma once

namespace DOS
{

class IDynamicQObject
{
public:
    /// Destructor
    virtual ~IDynamicQObject() = default;

    /// Emit the signal with the given name and arguments
    virtual bool emitSignal(const QString& name, const std::vector<QVariant>& argumentsValues) = 0;
};

} // namespace DOS
