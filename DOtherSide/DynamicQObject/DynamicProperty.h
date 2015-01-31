#pragma once

#include <QtCore/QString>
#include <QtCore/QMetaType>
#include <memory>

class QString;
class PropertyData;

class DynamicProperty
{
public:
    DynamicProperty();
    DynamicProperty(const QString& name,
                    QMetaType::Type type,
                    const QString& readSlotName,
                    const QString& writeSlotName = QString(),
                    const QString& notifySignalName = QString());
    DynamicProperty(const DynamicProperty& other);
    DynamicProperty& operator=(const DynamicProperty& other);
    ~DynamicProperty();

    QString name() const;
    QMetaType::Type type() const;

    bool isValid() const {
        return d != nullptr;
    }

    bool isReadable() const;
    bool isWriteable() const;
    bool hasNotifySignal() const;

    QString readSlot() const;
    QString writeSlot() const;
    QString notifySignal() const;

private:
    std::unique_ptr<PropertyData> d;
};
