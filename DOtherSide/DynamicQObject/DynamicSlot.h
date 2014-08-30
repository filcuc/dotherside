#pragma once

#include <memory>
#include <functional>

#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QVariant>

class SlotData;
class QString;

class DynamicSlot
{
public:
    DynamicSlot();
    DynamicSlot(const QString& name,
                QMetaType::Type returnType,
                const QList<QMetaType::Type>& argumentsTypes);
    DynamicSlot(const DynamicSlot& slot);
    DynamicSlot& operator=(const DynamicSlot& slot);
    ~DynamicSlot();

    QString name() const;
    bool isValid() const;
    QByteArray signature() const;
    bool validate(const QVariantList& argumentsValues);

private:
    void _initSignature();

    std::unique_ptr<SlotData> d;
};
