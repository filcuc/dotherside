#pragma once

#include <QObject>
#include <functional>

#include "DOtherSideTypesCpp.h"
#include "DOtherSide/IDynamicQObject.h"

namespace DOS
{

/// This class model a QObject
class DynamicQObject : public QObject, public IDynamicQObject
{
public:
    /// Constructor
    DynamicQObject();

    /// Emit a signal
    bool emitSignal(const QString& name, const std::vector<QVariant>& arguments) override;

    /// Return the metaobject
    const QMetaObject* metaObject() const override;

    /// qt metacall
    int qt_metacall(QMetaObject::Call callType, int index, void**args) override;

    /// Set the implementation
    void setImpl(std::unique_ptr<IDynamicQObject> impl);

private:
    std::unique_ptr<IDynamicQObject> m_impl;
};

} // namespace DOS
