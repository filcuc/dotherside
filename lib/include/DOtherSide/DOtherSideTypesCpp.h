#pragma once

// std
#include <memory>
// Qt
#include <QtGlobal>
#include <QtCore/QString>
#include <QtCore/QMetaType>
// DOtherSide
#include "DOtherSide/DOtherSideTypes.h"
#include "DOtherSide/Utils.h"

namespace DOS {

struct ParameterDefinition {
    ParameterDefinition(const ::ParameterDefinition &definition)
        : name(QString::fromUtf8(definition.name))
        , metaType(static_cast<QMetaType::Type>(definition.metaType))
    {}

    QString name;
    QMetaType::Type metaType;
};

struct SignalDefinition {
    SignalDefinition(QString n,
                     std::vector<ParameterDefinition> v)
        : name(std::move(n))
        , returnType(QMetaType::Void)
        , parameters(std::move(v))
    {}

    SignalDefinition(::SignalDefinition cType)
        : name(QString::fromUtf8(cType.name))
        , returnType(QMetaType::Void)
    {
        parameters.reserve(cType.parametersCount);
        for (int i = 0; i < cType.parametersCount; ++i)
            parameters.emplace_back(cType.parameters[i]);
    }

    QString name;
    QMetaType::Type returnType;
    std::vector<ParameterDefinition> parameters;
};

struct SlotDefinition {
    SlotDefinition(QString n,
                   QMetaType::Type t,
                   std::vector<ParameterDefinition> v)
        : name(std::move(n))
        , returnType(std::move(t))
        , parameters(std::move(v))
    {}

    SlotDefinition(::SlotDefinition cType)
        : name(QString::fromUtf8(cType.name))
        , returnType(QMetaType::Type(cType.returnMetaType))
    {
        parameters.reserve(cType.parametersCount);
        for (int i = 0; i < cType.parametersCount; ++i)
            parameters.emplace_back(cType.parameters[i]);
    }

    QString name;
    QMetaType::Type returnType;
    std::vector<ParameterDefinition> parameters;
};

struct PropertyDefinition {
    PropertyDefinition(QString n,
                       QMetaType::Type t,
                       QString r,
                       QString w,
                       QString s)
        : name(std::move(n))
        , type(std::move(t))
        , readSlot(std::move(r))
        , writeSlot(std::move(w))
        , notifySignal(std::move(s))
    {}

    PropertyDefinition(::PropertyDefinition cType)
        : name(cType.name)
        , type(static_cast<QMetaType::Type>(cType.propertyMetaType))
        , readSlot(QString::fromUtf8(cType.readSlot))
        , writeSlot(QString::fromUtf8(cType.writeSlot))
        , notifySignal(QString::fromUtf8(cType.notifySignal))
    {}

    QString name;
    QMetaType::Type type;
    QString readSlot;
    QString writeSlot;
    QString notifySignal;
};

using SignalDefinitions = std::vector<SignalDefinition>;
using SlotDefinitions = std::vector<SlotDefinition>;
using PropertyDefinitions = std::vector<PropertyDefinition>;

SignalDefinitions toVector(const ::SignalDefinitions &cType);
SlotDefinitions toVector(const ::SlotDefinitions &cType);
PropertyDefinitions toVector(const ::PropertyDefinitions &cType);

class DosIQMetaObjectHolder;
class DosIQMetaObject;
using DosIQMetaObjectPtr = std::shared_ptr<const DosIQMetaObject>;
class DosQMetaObject;


using OnMetaObject = std::function<DosIQMetaObjectHolder*()>;
using OnSlotExecuted = std::function<QVariant(const QString &, const std::vector<QVariant>&)>;

class SafeQMetaObjectPtr
{
public:
    SafeQMetaObjectPtr(QMetaObject *ptr)
        : m_d(ptr, ::free)
    {}

    SafeQMetaObjectPtr(SafeQMetaObjectPtr &&) = delete;
    SafeQMetaObjectPtr(const SafeQMetaObjectPtr &) = delete;
    SafeQMetaObjectPtr &operator=(const SafeQMetaObjectPtr &) = delete;

    operator bool() const Q_DECL_NOEXCEPT
    {
        return m_d != nullptr;
    }
    operator const QMetaObject *() const Q_DECL_NOEXCEPT
    {
        return m_d.get();
    }
    const QMetaObject *operator->() const Q_DECL_NOEXCEPT
    {
        return m_d.get();
    }
    void reset(QMetaObject *other) Q_DECL_NOEXCEPT { m_d.reset(other); }

private:
    std::unique_ptr<QMetaObject, void(*)(void *)> m_d;
};


struct QmlRegisterType {
    int major;
    int minor;
    std::string uri;
    std::string qml;
    DosIQMetaObjectPtr staticMetaObject;
    CreateDObject createDObject;
    DeleteDObject deleteDObject;
};


} // namespace DOS
