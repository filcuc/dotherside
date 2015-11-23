#pragma once

// std
#include <memory>
#include <functional>
// Qt
#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QMetaType>
#include "private/qmetaobjectbuilder_p.h"

class QString;

class DynamicSlot final
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
    QMetaType::Type returnType() const;
    QList<QMetaType::Type> argumentsTypes() const;
    QMetaType::Type argumentTypeAt(int i) const;

private:
    void _initSignature();

    struct SlotData;
    std::unique_ptr<SlotData> d;
};
