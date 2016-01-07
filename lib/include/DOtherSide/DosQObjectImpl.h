#pragma once

// std
#include <vector>
// Qt
#include <QtCore/QString>
#include <QtCore/QVariant>
// DOtherSide
#include "DOtherSide/DosQObject.h"
#include "DOtherSide/DOtherSideTypesCpp.h"

namespace DOS
{

class DynamicQObjectImpl : public IDosQObject
{
public:
    DynamicQObjectImpl(QObject* parent,
                       OnMetaObject onMetaObject,
                       OnSlotExecuted onSlotExecuted);

    bool emitSignal(const QString& name, const std::vector<QVariant>& arguments) override;
    const QMetaObject* metaObject() const override;
    int qt_metacall(QMetaObject::Call callType, int index, void**args) override;

private:
    std::shared_ptr<const DOS::IDosQMetaObject> dosMetaObject() const;
    bool executeSlot(const QMetaMethod& method, void** args);
    bool executeSlot(int index, void** args);
    bool readProperty(int index, void** args);
    bool writeProperty(int index, void** args);

    QObject* m_parent;
    const OnMetaObject m_onMetaObject;
    const OnSlotExecuted m_onSlotExecuted;
};

} // namespace DOS
