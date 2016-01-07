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

/// This class implement the interface IDosQObject
/// and it's injected in DosQObject
class DosQObjectImpl : public IDosQObject
{
public:
    /// Constructor
    DosQObjectImpl(QObject* parent,
                   OnMetaObject onMetaObject,
                   OnSlotExecuted onSlotExecuted);

    /// @see IDosObject::emitSignal
    bool emitSignal(const QString& name, const std::vector<QVariant>& arguments) override;

    /// @see IDosObject::metaObject
    const QMetaObject* metaObject() const override;

    /// @see IDosObject::qt_metacall
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
