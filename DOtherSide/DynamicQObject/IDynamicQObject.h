#ifndef IDYNAMICQOBJECT_H
#define IDYNAMICQOBJECT_H

class IDynamicQObject
{
public:
    typedef void (*Callback)(void*, void*, int, void**);

    /// Destructor
    virtual ~IDynamicQObject() = default;

    /// Sets the function to be called from C++ to D or Nimrod
    virtual void setDObjectCallback(Callback callback) = 0;

    /// Sets the D or Nimrod object that owns this DynamicQObject
    virtual void setDObjectPointer(void* dObjectPointer) = 0;

    /// Register a new signal
    virtual bool registerSignal(const QString& name,
                                const QList<QMetaType::Type>& argumentsTypes,
                                int& signalIndex) = 0;

    /// Register a new slot
    virtual bool registerSlot(const QString& name,
                              const QMetaType::Type returnType,
                              const QList<QMetaType::Type>& argumentsTypes,
                              int& slotIndex) = 0;

    /// Register a new property
    virtual bool registerProperty(const QString& name,
                                  QMetaType::Type type,
                                  const QString& readSlotName,
                                  const QString& writeSlotName = "",
                                  const QString& notifySignalName = "") = 0;

    /// Emit the signal with the given name and arguments
    virtual bool emitSignal(const QString& name, const QList<QVariant>& argumentsValues) = 0;
};

#endif