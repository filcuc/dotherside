#include "DOtherSide/OnSlotExecutedHandler.h"
#include "DOtherSide/DynamicSlot.h"

OnSlotExecutedHandler::OnSlotExecutedHandler(void *dObjectPointer,
                                             IDynamicQObject::Callback dObjectCallback)
    : m_dObjectPointer(dObjectPointer)
    , m_dObjectCallback(dObjectCallback)
{}

QVariant OnSlotExecutedHandler::operator()(const DynamicSlot& slot, const std::vector<QVariant> &args)
{
    QVariant result;

    if (!m_dObjectCallback || !m_dObjectPointer)
        return result;

    // prepare slot name
    QVariant slotName(slot.name());

    // prepare void* for the QVariants
    std::vector<void*> argumentsAsVoidPointers;
    argumentsAsVoidPointers.reserve(args.size() + 1);
    argumentsAsVoidPointers.emplace_back(&result);
    for (size_t i = 0; i < args.size(); ++i)
        argumentsAsVoidPointers.emplace_back((void*)(&args[i]));

    // send them to the binding handler
    m_dObjectCallback(m_dObjectPointer, &slotName, argumentsAsVoidPointers.size(), &argumentsAsVoidPointers[0]);

    return result;
}
