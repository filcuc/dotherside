#pragma once

#include <QtCore/QMetaType>
#include <memory>

class SignalData;
class DynamicQObject;

class DynamicSignal
{
public:
    DynamicSignal();
    DynamicSignal(const QString& name, const QList<QMetaType::Type>& arguments);
    DynamicSignal(const DynamicSignal& signal);
    DynamicSignal& operator=(const DynamicSignal& signal);
    ~DynamicSignal();

    bool isValid() const;

    QString name() const;
    QByteArray signature();

    bool validate(const QVariantList& arguments);
    static bool validate(const QList<QMetaType::Type>& argumentsTypes, const QVariantList& argumentsValues);

private:
    void _initSignature();

    std::unique_ptr<SignalData> d;
};
