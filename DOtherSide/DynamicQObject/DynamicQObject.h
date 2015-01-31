#pragma once

#include <QObject>
#include <QScopedPointer>

#include "DynamicSignal.h"
#include "DynamicSlot.h"
#include "DynamicProperty.h"

class QMetaObjectBuilder;

/// This class implements a QObject to which signals, slots and properties can be added dynamically
class DynamicQObject : public QObject
{
    typedef void (*Callback)(void*, void*, int, void**);

public:
    /// Constructor
    DynamicQObject();

    /// Destructor
    virtual ~DynamicQObject();

    /// Sets the function to be called from C++ to D or Nimrod
    void setDObjectCallback(Callback callback) {
        m_dObjectCallback = callback;
    }

    /// Sets the D or Nimrod object that owns this DynamicQObject
    void setDObjectPointer(void* dObjectPointer)  {
        m_dObjectPointer = dObjectPointer;
    }

    /// Register a new signal
    bool registerSignal(const QString& name,
                        const QList<QMetaType::Type>& argumentsTypes,
                        int& signalIndex);

    /// Register a new slot
    bool registerSlot(const QString& name,
                      const QMetaType::Type returnType,
                      const QList<QMetaType::Type>& argumentsTypes,
                      int& slotIndex);

    /// Register a new property
    bool registerProperty(const QString& name,
                          QMetaType::Type type,
                          const QString& readSlotName,
                          const QString& writeSlotName = "",
                          const QString& notifySignalName = "");

    /// Emit the signal with the given name and arguments
    bool emitSignal(const QString& name, const QList<QVariant>& argumentsValues);

    /// Return the QMetaObject for this DynamicQObject
    virtual const QMetaObject* metaObject() const;

    /// The qt metacall. Called from Qt when a signals, slot or property is invoked
    int qt_metacall(QMetaObject::Call, int, void**);

private:
    bool executeSlot(const DynamicSlot& slot, void**  args);

    QVariant executeSlot(const DynamicSlot& slot, const QList<QVariant>& args = QList<QVariant>());

    bool readProperty(const DynamicProperty& property, void** args);

    bool writeProperty(const DynamicProperty& property, void** args);

    /// Function for recreating the metaobject starting from another one.
    /// The creation is customizable by injecting custom code after signals and slots have
    /// been added
    static QMetaObject* recreateMetaObjectBuilder(QMetaObject* currentMetaObject,
            const std::function<void(QMetaObjectBuilder&)>& afterSignalAdded,
            const std::function<void(QMetaObjectBuilder&)>& afterSlotAdded,
            const std::function<void(QMetaObjectBuilder&)>& afterPropertyAdded);

    QHash<QString, DynamicSignal> m_signalsByName;
    QHash<QByteArray, DynamicSignal> m_signalsBySignature;
    QHash<QString, DynamicSlot> m_slotsByName;
    QHash<QByteArray, DynamicSlot> m_slotsBySignature;
    QHash<QByteArray, DynamicProperty> m_propertiesByName;
    QScopedPointer<QMetaObject> m_metaObject;
    void* m_dObjectPointer;
    Callback m_dObjectCallback;
};
