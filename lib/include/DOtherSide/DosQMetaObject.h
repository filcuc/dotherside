#pragma once

// std
#include <memory>
#include <unordered_map>
#include <tuple>
// Qt
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QMetaMethod>
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
    virtual QMetaMethod signal(const QString& signalName) const = 0;
    virtual QMetaMethod readSlot(const char* propertyName) const = 0;
    virtual QMetaMethod writeSlot(const char* propertyName) const = 0;
    virtual const IDosQMetaObject* superClassDosMetaObject() const = 0;
};

/// Base class for any IDosQMetaObject
class BaseDosQMetaObject : public IDosQMetaObject
{
public:
    BaseDosQMetaObject(const QMetaObject* metaObject)
        : m_metaObject(metaObject)
    {}
    const QMetaObject *metaObject() const override { return m_metaObject; }
    QMetaMethod signal(const QString &signalName) const override { return QMetaMethod(); }
    QMetaMethod readSlot(const char *propertyName) const override { return QMetaMethod(); }
    QMetaMethod writeSlot(const char *propertyName) const override { return QMetaMethod(); }
    const IDosQMetaObject* superClassDosMetaObject() const { return nullptr; }

private:
    const QMetaObject* m_metaObject;
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
class DosQMetaObject : public IDosQMetaObject
{
public:
    DosQMetaObject(std::shared_ptr<const IDosQMetaObject> superClassDosMetaObject,
                   const QString& className,
                   const SignalDefinitions &signalDefinitions,
                   const SlotDefinitions &slotDefinitions,
                   const PropertyDefinitions &propertyDefinitions);

    QMetaMethod signal(const QString& signalName) const override;
    QMetaMethod readSlot(const char* propertyName) const override;
    QMetaMethod writeSlot(const char* propertyName) const override;
    const QMetaObject *metaObject() const override;
    const IDosQMetaObject *superClassDosMetaObject() const override;

private:
    QMetaObject *createMetaObject(const QString& className,
                                  const SignalDefinitions &signalDefinitions,
                                  const SlotDefinitions &slotDefinitions,
                                  const PropertyDefinitions &propertyDefinitions);

    std::shared_ptr<const IDosQMetaObject> m_superClassDosMetaObject;
    QHash<QString, int> m_signalIndexByName;
    QHash<QString, QPair<int,int>> m_propertySlots;
    SafeQMetaObjectPtr m_metaObject;
};

/// This class simply holds a ptr to a IDosQMetaObject
/// It's created and passed to the binded language
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
