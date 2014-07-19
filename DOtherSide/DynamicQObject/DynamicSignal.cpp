#include "DynamicSignal.h"
#include "DynamicQObject.h"

struct SignalData
{
    QString name;
    QByteArray signature;
    QList<QMetaType::Type> arguments;
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
    d->arguments = arguments;
    _initSignature();
}

DynamicSignal::DynamicSignal(const DynamicSignal& signal)
    : d(nullptr)
{
    if (signal.isValid())
    {
        d.reset(new SignalData());
        *d = *signal.d;
    }
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
    if (!isValid())
        return false;
    return validate(d->arguments, arguments);
}

bool DynamicSignal::validate(const QList<QMetaType::Type>& argumentsTypes, const QVariantList& argumentsValues)
{
    if (argumentsTypes.size() != argumentsValues.size())
        return false;

    for (int i = 0; i < argumentsTypes.size(); ++i)
    {
        QMetaType::Type expected = argumentsTypes[i];
        if (expected == QMetaType::QVariant)
            continue;
        QMetaType::Type actual = static_cast<QMetaType::Type>(argumentsValues[i].type());
        if (expected != actual)
            return false;
    }

    return true;
}

void DynamicSignal::_initSignature()
{
    QString signature("%1(%2)");
    QString arguments;
    for (int i = 0; i < d->arguments.size(); ++i)
    {
        if (i != 0)
            arguments += ',';
        arguments += QMetaType::typeName(d->arguments[i]);
    }

    d->signature = signature.arg(d->name, arguments).toUtf8();
}

