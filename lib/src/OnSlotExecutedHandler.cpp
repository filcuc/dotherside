#include "DOtherSide/OnSlotExecutedHandler.h"

namespace DOS
{

OnSlotExecutedHandler::OnSlotExecutedHandler(void *dObjectPointer,
                                             DObjectCallback dObjectCallback)
    : m_dObjectPointer(dObjectPointer)
    , m_dObjectCallback(dObjectCallback)
{}

QVariant OnSlotExecutedHandler::operator()(const QString &name, const std::vector<QVariant> &args)
{
    QVariant result;

    if (!m_dObjectCallback || !m_dObjectPointer)
        return result;

    // prepare slot name
    QVariant slotName(name);

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

OnMetaObjectHandler::OnMetaObjectHandler(void *dObjectPointer, MetaObjectCallback dMetaObjectCallback)
    : m_dObjectPointer(dObjectPointer)
    , m_dMetaObjectCallback(dMetaObjectCallback)
{}

DosIQMetaObjectHolder* OnMetaObjectHandler::operator()()
{
    DosIQMetaObjectHolder* result = nullptr;
    m_dMetaObjectCallback(m_dObjectPointer, reinterpret_cast<void**>(&result));
    return result;
}

} // namespace DOS
