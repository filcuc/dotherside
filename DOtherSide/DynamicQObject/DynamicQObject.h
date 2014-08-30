#pragma once

class QMetaObject;

#include <QScopedPointer>
#include <QObject>

#include "DynamicSignal.h"
#include "DynamicSlot.h"


class DynamicQObject : public QObject
{
    typedef void (*Callback)(void*, void*, int, void **);

public:
    DynamicQObject(QObject* parent = 0);
    virtual ~DynamicQObject();


    void setDObjectCallback(Callback callback) { m_dObjectCallback = callback; }
    void setDObjectPointer(void* dObjectPointer)  { m_dObjectPointer = dObjectPointer; }

    bool registerSignal(const QString& name, const QList<QMetaType::Type>& argumentsTypes, int& signalIndex);
    bool emitSignal(const QString& name, const QList<QVariant>& argumentsValues);

    bool registerSlot(const QString& name,
                      const QMetaType::Type returnType,
                      const QList<QMetaType::Type>& argumentsTypes,
                      int& slotIndex);
    bool executeSlot(const QString& name, const QList<QVariant>& argumentsValues);

    virtual const QMetaObject *metaObject() const;
    int qt_metacall(QMetaObject::Call, int, void **);

private:
    QHash<QString, DynamicSignal> m_signalsByName;
    QHash<QByteArray, DynamicSignal> m_signalsBySignature;
    QHash<QString, DynamicSlot> m_slotsByName;
    QHash<QByteArray, DynamicSlot> m_slotsBySignature;
    QScopedPointer<QMetaObject> m_metaObject;
    void* m_dObjectPointer;
    Callback m_dObjectCallback;
};
