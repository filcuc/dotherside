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
  class QMetaObjectFactory
  {
  public:
    QMetaObjectFactory(SignalDefinitions signalDefinitions,
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

  const QMetaObject *QMetaObjectFactory::metaObject() const
  {
    return m_metaObject;
  }

  inline int QMetaObjectFactory::signalSlotIndex(const QString &signalName) const
  {
    return m_signalIndexByName.value(signalName.toUtf8(), -1);
  }

  inline int QMetaObjectFactory::readSlotIndex(const char *propertyName) const
  {
    return m_propertySlots.value(propertyName, {-1,-1}).first;
  }

  inline int QMetaObjectFactory::writeSlotIndex(const char *propertyName) const
  {
    return m_propertySlots.value(propertyName, {-1,-1}).second;
  }
} // namespace DOS
