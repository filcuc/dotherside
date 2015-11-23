#include "DOtherSide/DynamicSlot.h"

struct DynamicSlot::SlotData
{
    QString name;
    QMetaType::Type returnType;
    QList<QMetaType::Type> argumentsTypes;
    QByteArray signature;
};

DynamicSlot::DynamicSlot()
    : d(nullptr)
{}

DynamicSlot::DynamicSlot(const QString& name,
                         QMetaType::Type returnType,
                         const QList<QMetaType::Type>& argumentsTypes)
    : d(new SlotData())
{
    d->name = name;
    d->returnType = returnType;
    d->argumentsTypes = argumentsTypes;
    _initSignature();
}

DynamicSlot::DynamicSlot(const DynamicSlot& slot)
{
    if (slot.isValid())
    {
        d.reset(new SlotData());
        *d = *slot.d;
    }
    else
        d.reset(nullptr);
}

DynamicSlot& DynamicSlot::operator=(const DynamicSlot& slot)
{
    if (slot.isValid())
    {
        d.reset(new SlotData());
        *d = *slot.d;
    }
    else
        d.reset(nullptr);

    return *this;
}

DynamicSlot::~DynamicSlot()
{
}

QString DynamicSlot::name() const
{
    return isValid() ? d->name : QString();
}

bool DynamicSlot::isValid() const
{
    return d != nullptr;
}

QByteArray DynamicSlot::signature() const
{
    return isValid() ? d->signature : QByteArray();
}

QMetaType::Type DynamicSlot::returnType() const
{
    return isValid() ? d->returnType : QMetaType::UnknownType;
}

QList<QMetaType::Type> DynamicSlot::argumentsTypes() const
{
    return isValid() ? d->argumentsTypes : QList<QMetaType::Type>();
}

QMetaType::Type DynamicSlot::argumentTypeAt(int i) const
{
    return isValid() ? d->argumentsTypes.at(i) : QMetaType::UnknownType;
}

void DynamicSlot::_initSignature()
{
    QString signature("%1(%2)");
    QString arguments = "";
    for (int i = 0; i < d->argumentsTypes.size(); ++i)
    {
        if (i != 0)
            arguments += ',';
        arguments += QMetaType::typeName(d->argumentsTypes[i]);
    }

    d->signature = signature.arg(d->name, arguments).toUtf8();
}
