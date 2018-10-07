#pragma once

// std
#include <vector>
// Qt
#include <QtCore/QMutex>
#include <QtCore/QString>
#include <QtCore/QVariant>
// DOtherSide
#include "DOtherSide/DosQObject.h"
#include "DOtherSide/DOtherSideTypesCpp.h"

namespace DOS {

/// This class implement the interface IDosQObject
/// and it's injected in DosQObject
class DosQObjectImpl : public DosIQObjectImpl
{
public:
    using ParentMetaCall = std::function<int(QMetaObject::Call, int, void **)>;

    /// Constructor
    DosQObjectImpl(ParentMetaCall parentMetaCall,
                   std::shared_ptr<const DosIQMetaObject> metaObject,
                   void *dObjectPointer,
                   DObjectCallback dObjectCallback);


    /// @see IDosQObject::emitSignal
    bool emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &arguments) override;

    /// @see IDosQObject::metaObject()
    const QMetaObject *metaObject() const override;

    /// @see IDosQObject::qt_metacall
    int qt_metacall(QMetaObject::Call, int, void **) override;

private:
    bool executeSlot(const QMetaMethod &method, void **args, int argumentsOffset = 1);
    bool executeSlot(int index, void **args);
    QVariant executeSlot(const QString &name, const std::vector<QVariant> &args);

    bool readProperty(int index, void **args);
    bool writeProperty(int index, void **args);

    const ParentMetaCall m_parentMetaCall;
    const std::shared_ptr<const DosIQMetaObject> m_metaObject;
    void* const m_dObjectPointer = nullptr;
    const DObjectCallback m_dObjectCallback;
};

} // namespace DOS
