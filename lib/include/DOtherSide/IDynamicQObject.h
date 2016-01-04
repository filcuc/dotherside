#pragma once

class QMetaObject;

namespace DOS
{

class IDynamicQObject
{
public:
    /// Destructor
    virtual ~IDynamicQObject() = default;

    /// Emit the signal with the given name and arguments
    virtual bool emitSignal(const QString& name, const std::vector<QVariant>& argumentsValues) = 0;

    /// Implementation of QObject::metaObject
    virtual const QMetaObject* metaObject() const = 0;

    /// Implementation of QObject::qt_metacall
    virtual int qt_metacall(QMetaObject::Call callType, int index, void**args) = 0;
};

} // namespace DOS
