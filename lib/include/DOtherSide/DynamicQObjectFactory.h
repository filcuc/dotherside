#pragma once

#include <memory>
#include <unordered_map>
#include <tuple>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QHash>

#include "DOtherSide/DOtherSideTypesCpp.h"

namespace DOS
{

class DynamicQObject2;

class DynamicQObjectFactory
{
    using SafeQMetaObjectPtr = std::unique_ptr<QMetaObject, void(*)(void*)>;
    using OnSlotExecuted = std::function<QVariant(const QString&, const std::vector<QVariant>&)>;

public:
    DynamicQObjectFactory(SignalDefinitions signalDefinitions,
                          SlotDefinitions slotDefinitions,
                          PropertyDefinitions propertyDefinitions);

    DynamicQObject2* create(OnSlotExecuted handler) const;
    inline const QMetaObject* metaObject() const;
    inline int signalSlotIndex(const QString& signalName) const;
    inline int readSlotIndex(const char* propertyName) const;
    inline int writeSlotIndex(const char* propertyName) const;

private:
    SafeQMetaObjectPtr m_metaObject;
    QHash<QByteArray, int> m_signalIndexByName;
    QHash<QByteArray, QPair<int,int>> m_propertySlots;
};

const QMetaObject *DynamicQObjectFactory::metaObject() const
{
    return m_metaObject.get();
}

inline int DynamicQObjectFactory::signalSlotIndex(const QString &signalName) const
{
    return m_signalIndexByName.value(signalName.toUtf8(), -1);
}

inline int DynamicQObjectFactory::readSlotIndex(const char *propertyName) const
{
    return m_propertySlots.value(propertyName, {-1,-1}).first;
}

inline int DynamicQObjectFactory::writeSlotIndex(const char *propertyName) const
{
    return m_propertySlots.value(propertyName, {-1,-1}).second;
}

} // namespace DOS
