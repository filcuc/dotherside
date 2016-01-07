#pragma once

// std
#include <memory>
#include <unordered_map>
#include <tuple>
// Qt
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QHash>
// DOtherSide
#include "DOtherSide/DOtherSideTypesCpp.h"

namespace DOS
{

/// This the QMetaObject wrapper
class IDosQMetaObject
{
public:
    virtual ~IDosQMetaObject() = default;
    virtual const QMetaObject* metaObject() const = 0;
    virtual int signalSlotIndex(const QString& signalName) const = 0;
    virtual int readSlotIndex(const char* propertyName) const = 0;
    virtual int writeSlotIndex(const char* propertyName) const = 0;
};

/// Base class for any IDosQMetaObject
class BaseDosQMetaObject : public IDosQMetaObject
{
public:
    BaseDosQMetaObject(QMetaObject* metaObject)
        : m_metaObject(metaObject)
    {}
    const QMetaObject *metaObject() const override { return m_metaObject; }
    int signalSlotIndex(const QString &signalName) const override { return -1; }
    int readSlotIndex(const char *propertyName) const override { return -1; }
    int writeSlotIndex(const char *propertyName) const override { return -1; }

private:
    SafeQMetaObjectPtr m_metaObject;
};

/// This is the DosQMetaObject for a QObject
class DosQObjectMetaObject : public BaseDosQMetaObject
{
public:
    DosQObjectMetaObject();
};

/// This is the DosQMetaObject for a QAbstractListModel
class DosQAbstractListModelMetaObject : public BaseDosQMetaObject
{
public:
    DosQAbstractListModelMetaObject();
};

/// This the generic version used by subclasses of QObject or QAbstractListModels
class DosQMetaObject : public BaseDosQMetaObject
{
public:
    DosQMetaObject(const IDosQMetaObject& superClassMetaObject,
                   const QString& className,
                   const SignalDefinitions &signalDefinitions,
                   const SlotDefinitions &slotDefinitions,
                   const PropertyDefinitions &propertyDefinitions);

    int signalSlotIndex(const QString& signalName) const override;
    int readSlotIndex(const char* propertyName) const override;
    int writeSlotIndex(const char* propertyName) const override;

private:
    QMetaObject *createMetaObject(const IDosQMetaObject &superClassMetaObject,
                                  const QString& className,
                                  const SignalDefinitions &signalDefinitions,
                                  const SlotDefinitions &slotDefinitions,
                                  const PropertyDefinitions &propertyDefinitions);

    QHash<QByteArray, int> m_signalIndexByName;
    QHash<QByteArray, QPair<int,int>> m_propertySlots;
};

/// This class simply holds a ptr to a IDosQMetaObject
class DosIQMetaObjectHolder
{
public:
    DosIQMetaObjectHolder(std::shared_ptr<IDosQMetaObject> ptr)
        : m_data(std::move(ptr))
    {}

    const std::shared_ptr<const IDosQMetaObject>& data() const { return m_data; }

private:
    std::shared_ptr<const IDosQMetaObject> m_data;
};

} // namespace DOS
