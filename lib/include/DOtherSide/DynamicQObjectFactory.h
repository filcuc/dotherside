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

class DynamicQObjectFactoryData
{
public:
    DynamicQObjectFactoryData(SignalDefinitions signalDefinitions,
                              SlotDefinitions slotDefinitions,
                              PropertyDefinitions propertyDefinitions);

    inline const QMetaObject* metaObject() const;
    inline int signalSlotIndex(const QString& signalName) const;
    inline int readSlotIndex(const char* propertyName) const;
    inline int writeSlotIndex(const char* propertyName) const;

private:
    SafeQMetaObjectPtr m_metaObject;
    QHash<QByteArray, int> m_signalIndexByName;
    QHash<QByteArray, QPair<int,int>> m_propertySlots;
};

const QMetaObject *DynamicQObjectFactoryData::metaObject() const
{
    return m_metaObject;
}

inline int DynamicQObjectFactoryData::signalSlotIndex(const QString &signalName) const
{
    return m_metaObject->methodOffset() + m_signalIndexByName.value(signalName.toUtf8(), -1);
}

inline int DynamicQObjectFactoryData::readSlotIndex(const char *propertyName) const
{
    return m_metaObject->methodOffset() + m_propertySlots.value(propertyName, {-1,-1}).first;
}

inline int DynamicQObjectFactoryData::writeSlotIndex(const char *propertyName) const
{
    return m_metaObject->methodOffset() + m_propertySlots.value(propertyName, {-1,-1}).second;
}

class DynamicQObjectFactory
{
public:
    DynamicQObjectFactory(SignalDefinitions signalDefinitions,
                          SlotDefinitions slotDefinitions,
                          PropertyDefinitions propertyDefinitions)
        : m_data(std::make_shared<DynamicQObjectFactoryData>(signalDefinitions,
                                                             slotDefinitions,
                                                             propertyDefinitions))
    {}

    std::shared_ptr<const DynamicQObjectFactoryData> data() const { return m_data; }

private:
    std::shared_ptr<const DynamicQObjectFactoryData> m_data;
};

} // namespace DOS
