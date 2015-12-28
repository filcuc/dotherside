#pragma once

#include <QObject>
#include <functional>

#include "DOtherSide/IDynamicQObject.h"

namespace DOS
{

class DynamicQObjectFactory;

class DynamicQObject : public QObject, public IDynamicQObject
{
public:
    using OnSlotExecuted = std::function<QVariant(const QString&, const std::vector<QVariant>&)>;

    DynamicQObject(const DynamicQObjectFactory* factory,
                    OnSlotExecuted handler);

    bool emitSignal(const QString& name, const std::vector<QVariant>& arguments) override;
    const QMetaObject* metaObject() const override;
    int qt_metacall(QMetaObject::Call callType, int index, void**args) override;

private:
    bool executeSlot(int index, void** args);
    bool readProperty(int index, void** args);
    bool writeProperty(int index, void** args);

    const DynamicQObjectFactory* const m_factory;
    const OnSlotExecuted m_handler;
};

} // namespace DOS
