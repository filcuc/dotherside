#pragma once

#include <QObject>
#include <functional>

#include "DOtherSideTypesCpp.h"
#include "DOtherSide/IDynamicQObject.h"

namespace DOS
{

class DynamicQObjectFactoryData;

class DynamicQObject : public QObject, public IDynamicQObject
{
public:
    DynamicQObject(OnMetaObject onMetaObject, OnSlotExecuted onSlotExecuted);

    bool emitSignal(const QString& name, const std::vector<QVariant>& arguments) override;
    const QMetaObject* metaObject() const override;
    int qt_metacall(QMetaObject::Call callType, int index, void**args) override;

private:
    std::shared_ptr<const DynamicQObjectFactoryData> factory() const;

    bool executeSlot(int index, void** args);
    bool readProperty(int index, void** args);
    bool writeProperty(int index, void** args);

    const OnMetaObject m_onMetaObject;
    const OnSlotExecuted m_onSlotExecuted;
};

} // namespace DOS
