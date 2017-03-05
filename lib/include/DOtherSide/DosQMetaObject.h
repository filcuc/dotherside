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

namespace DOS {

/// This the QMetaObject wrapper
class DosIQMetaObject
{
public:
    virtual ~DosIQMetaObject() = default;
    virtual const QMetaObject *metaObject() const = 0;
    virtual QMetaMethod signal(const QString &signalName) const = 0;
    virtual QMetaMethod readSlot(const char *propertyName) const = 0;
    virtual QMetaMethod writeSlot(const char *propertyName) const = 0;
    virtual const DosIQMetaObject *superClassDosMetaObject() const = 0;
};

/// Base class for any DosIQMetaObject
class BaseDosQMetaObject : public DosIQMetaObject
{
public:
    BaseDosQMetaObject(QMetaObject *metaObject);

    const QMetaObject *metaObject() const override;
    QMetaMethod signal(const QString &signalName) const override;
    QMetaMethod readSlot(const char *propertyName) const override;
    QMetaMethod writeSlot(const char *propertyName) const override;
    const DosIQMetaObject *superClassDosMetaObject() const override;

protected:
    SafeQMetaObjectPtr m_metaObject;
};

/// This is the DosQMetaObject for a QObject
class DosQObjectMetaObject : public BaseDosQMetaObject
{
public:
    DosQObjectMetaObject();
};

/// This is the DosQMetaObject for a QAbstractItemModel
class DosQAbstractItemModelMetaObject : public BaseDosQMetaObject
{
public:
    DosQAbstractItemModelMetaObject();
};

/// This the generic version used by subclasses of QObject or QAbstractItemModels
class DosQMetaObject : public BaseDosQMetaObject
{
public:
    DosQMetaObject(DosIQMetaObjectPtr superClassDosMetaObject,
                   const QString &className,
                   const SignalDefinitions &signalDefinitions,
                   const SlotDefinitions &slotDefinitions,
                   const PropertyDefinitions &propertyDefinitions);

    QMetaMethod signal(const QString &signalName) const override;
    QMetaMethod readSlot(const char *propertyName) const override;
    QMetaMethod writeSlot(const char *propertyName) const override;
    const DosIQMetaObject *superClassDosMetaObject() const override;

private:
    QMetaObject *createMetaObject(const QString &className,
                                  const SignalDefinitions &signalDefinitions,
                                  const SlotDefinitions &slotDefinitions,
                                  const PropertyDefinitions &propertyDefinitions);

    const DosIQMetaObjectPtr m_superClassDosMetaObject;
    QHash<QString, int> m_signalIndexByName;
    QHash<QString, QPair<int, int>> m_propertySlots;
};

/// This class simply holds a ptr to a IDosQMetaObject
/// It's created and passed to the binded language
class DosIQMetaObjectHolder
{
public:
    DosIQMetaObjectHolder(DosIQMetaObjectPtr ptr)
        : m_data(std::move(ptr))
    {}

    const DosIQMetaObjectPtr &data() const
    {
        return m_data;
    }

private:
    const DosIQMetaObjectPtr m_data;
};

} // namespace DOS
