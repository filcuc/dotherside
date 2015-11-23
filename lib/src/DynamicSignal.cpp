#include "DOtherSide/DynamicSignal.h"

struct DynamicSignal::SignalData
{
    QString name;
    QList<QMetaType::Type> argumentsTypes;
    QByteArray signature;
};

DynamicSignal::DynamicSignal()
    : d(nullptr)
{}

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

DynamicSignal::~DynamicSignal() = default;

bool DynamicSignal::isValid() const
{
    return d != nullptr;
}

QString DynamicSignal::name() const
{
    return isValid() ? d->name : QString();
}

QByteArray DynamicSignal::signature() const
{
    return isValid() ? d->signature : QByteArray();
}

bool DynamicSignal::validate(const QVariantList& arguments)
{
	// TODO: here we should test if the given arguments
	// match this signal signature
	// This is important because a class could have multiple
	// signals with the same name but different arguments
	Q_UNUSED(arguments);
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
