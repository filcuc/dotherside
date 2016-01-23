#pragma once

// std
#include <vector>
// Qt
#include <QMutex>
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
    using ParentMetaCall = std::function<int(QMetaObject::Call, int, void **)>;

    /// Constructor
    DosQObjectImpl(QObject* parent,
                   ParentMetaCall parentMetaCall,
                   std::shared_ptr<const IDosQMetaObject> metaObject,
                   OnSlotExecuted onSlotExecuted);


    /// @see IDosQObject::emitSignal
    bool emitSignal(const QString& name, const std::vector<QVariant>& arguments) override;

    /// @see IDosQObject::metaObject()
    const QMetaObject* metaObject() const override;

    /// @see IDosQObject::qt_metacall
    int qt_metacall(QMetaObject::Call, int, void **) override;

private:
    bool executeSlot(const QMetaMethod& method, void** args);
    bool executeSlot(int index, void** args);
    bool readProperty(int index, void** args);
    bool writeProperty(int index, void** args);

    QObject* m_parent;
    const ParentMetaCall m_parentMetaCall;
    const OnSlotExecuted m_onSlotExecuted;
    mutable std::shared_ptr<const IDosQMetaObject> m_metaObject;
};

} // namespace DOS
