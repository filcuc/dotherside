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
    OnSlotExecutedHandler(void* dObjectPointer, IDynamicQObject::Callback dObjectCallback);

    QVariant operator()(const DynamicSlot& slot, std::vector<QVariant> const& args);

private:
    void* m_dObjectPointer;
    IDynamicQObject::Callback m_dObjectCallback;
};
