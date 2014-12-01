#include "DynamicSignal.h"
#include "DynamicQObject.h"

struct SignalData
{
    QString name;
    QList<QMetaType::Type> argumentsTypes;
    QByteArray signature;
};

DynamicSignal::DynamicSignal()
    : d(nullptr)
{
}

DynamicSignal::DynamicSignal(const QString& name, const QList<QMetaType::Type>& arguments)
    : d(new SignalData())
{
    d->name = name;
    d->signature = QByteArray();
    d->argumentsTypes = arguments;
    _initSignature();
}

DynamicSignal::DynamicSignal(const DynamicSignal& signal)
{
    if (signal.isValid())
    {
        d.reset(new SignalData());
        *d = *signal.d;
    }
    else
        d.reset(nullptr);
}

DynamicSignal& DynamicSignal::operator=(const DynamicSignal& signal)
{
    if (signal.isValid())
    {
        d.reset(new SignalData());
        *d = *signal.d;
    }
    else
        d.reset(nullptr);

    return *this;
}

DynamicSignal::~DynamicSignal()
{
}

bool DynamicSignal::isValid() const
{
    return d != nullptr;
}

QString DynamicSignal::name() const
{
    return isValid() ? d->name : QString();
}

QByteArray DynamicSignal::signature()
{
    return isValid() ? d->signature : QByteArray();
}

bool DynamicSignal::validate(const QVariantList& arguments)
{
    return true;
}

bool DynamicSignal::validate(const QList<QMetaType::Type>& argumentsTypes, const QVariantList& argumentsValues)
{
    return true;
}

void DynamicSignal::_initSignature()
{
    QString signature("%1(%2)");
    QString arguments;
    for (int i = 0; i < d->argumentsTypes.size(); ++i)
    {
        if (i != 0)
            arguments += ',';
        arguments += QMetaType::typeName(d->argumentsTypes[i]);
    }

    d->signature = signature.arg(d->name, arguments).toUtf8();
}
