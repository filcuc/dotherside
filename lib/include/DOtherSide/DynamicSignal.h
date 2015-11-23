#pragma once

// std
#include <memory>
// Qt
#include <QtCore/QMetaType>
#include <QtCore/QString>
#include <QtCore/QMetaType>
#include <QtCore/QList>

class DynamicSignal final
{
public:
    DynamicSignal();
    DynamicSignal(const QString& name, const QList<QMetaType::Type>& arguments);
    DynamicSignal(const DynamicSignal& signal);
    DynamicSignal& operator=(const DynamicSignal& signal);
    ~DynamicSignal();

    bool isValid() const;

    QString name() const;
    QByteArray signature() const;

    bool validate(const QVariantList& arguments);

private:
    void _initSignature();

    struct SignalData;
    std::unique_ptr<SignalData> d;
};
