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
class DosQObjectImpl : public QAbstractDynamicMetaObject, public IDosQObject
{
public:
    using ParentMetaCall = std::function<int(QMetaObject::Call, int, void **)>;

    /// Constructor
    DosQObjectImpl(QObject* parent,
                   ParentMetaCall parentMetaCall,
                   OnMetaObject onMetaObject,
                   OnSlotExecuted onSlotExecuted);


    /// @see IDosObject::emitSignal
    bool emitSignal(const QString& name, const std::vector<QVariant>& arguments) override;

    /// @see QAbstractDynamicMetaObject::metaCall
    int metaCall(QMetaObject::Call callType, int index, void **args) override;

private:
    std::shared_ptr<const DOS::IDosQMetaObject> dosMetaObject() const;
    bool executeSlot(const QMetaMethod& method, void** args);
    bool executeSlot(int index, void** args);
    bool readProperty(int index, void** args);
    bool writeProperty(int index, void** args);

    QObject* m_parent;
    const ParentMetaCall m_parentMetaCall;
    const OnMetaObject m_onMetaObject;
    const OnSlotExecuted m_onSlotExecuted;
};

} // namespace DOS
