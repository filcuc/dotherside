#include "DOtherSide/DynamicProperty.h"

struct DynamicProperty::PropertyData final
{
    PropertyData(const QString& name,
                 QMetaType::Type type,
                 const QString& readSlotName,
                 const QString& writeSlotName,
                 const QString& notifySignalName)
        : name(name)
        , type(type)
        , readSlotName(readSlotName)
        , writeSlotName(writeSlotName)
        , notifySignalName(notifySignalName)
    {}

    PropertyData(const PropertyData& other)
        : name(other.name)
        , type(other.type)
        , readSlotName(other.readSlotName)
        , writeSlotName(other.writeSlotName)
        , notifySignalName(other.notifySignalName)
    {}

    PropertyData& operator=(const PropertyData& other)
    {
        name = other.name;
        type = other.type;
        readSlotName = other.readSlotName;
        writeSlotName = other.writeSlotName;
        notifySignalName = other.notifySignalName;
        return *this;
    }

    QString name;
    QMetaType::Type type;
    QString readSlotName;
    QString writeSlotName;
    QString notifySignalName;
};

DynamicProperty::DynamicProperty()
    : d(nullptr)
{}

DynamicProperty::DynamicProperty(const QString& name, QMetaType::Type type, const QString& readSlotName, const QString& writeSlotName, const QString& notifySignalName)
    : d(new PropertyData(name, type, readSlotName, writeSlotName, notifySignalName))
{
}

DynamicProperty::DynamicProperty(const DynamicProperty& other)
    : d(nullptr)
{
    if (other.d)
        d.reset(new PropertyData(*other.d));
}

DynamicProperty& DynamicProperty::operator=(const DynamicProperty& other)
{
    if (!other.d && d)
        d.reset();
    else if (other.d && !d)
        d.reset(new PropertyData(*other.d));
    else if (other.d && d)
        *d = *other.d;

    return *this;
}

DynamicProperty::~DynamicProperty()
{}

QString DynamicProperty::name() const
{
    return d->name;
}

QMetaType::Type DynamicProperty::type() const
{
    return d->type;
}

bool DynamicProperty::isReadable() const
{
    return !d->readSlotName.isEmpty();
}

bool DynamicProperty::isWriteable() const
{
    return !d->writeSlotName.isEmpty();
}

bool DynamicProperty::hasNotifySignal() const
{
    return !d->notifySignalName.isEmpty();
}

QString DynamicProperty::readSlot() const
{
    return d->readSlotName;
}

QString DynamicProperty::writeSlot() const
{
    return d->writeSlotName;
}

QString DynamicProperty::notifySignal() const
{
    return d->notifySignalName;
}
