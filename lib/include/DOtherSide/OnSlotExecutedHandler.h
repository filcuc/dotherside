#pragma once

// std
#include <vector>
// Qt
#include <QVariant>
// DOtherSide
#include "DOtherSide/IDynamicQObject.h"

class DynamicSlot;

class OnSlotExecutedHandler
{
public:
    using Callback = void (*)(void*, void*, int, void**);

    OnSlotExecutedHandler(void* dObjectPointer, Callback dObjectCallback);

    QVariant operator()(const QString& name, const std::vector<QVariant>& args);
private:
    void* m_dObjectPointer;
    Callback m_dObjectCallback;
};
