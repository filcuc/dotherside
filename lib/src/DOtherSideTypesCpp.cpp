#include "DOtherSide/DOtherSideTypesCpp.h"

namespace DOS
{

SignalDefinitions toVector(const ::SignalDefinitions& cType)
{
    return toVector<SignalDefinition>(cType.definitions, cType.count);
}

SlotDefinitions toVector(const ::SlotDefinitions& cType)
{
    return toVector<SlotDefinition>(cType.definitions, cType.count);
}

PropertyDefinitions toVector(const ::PropertyDefinitions& cType)
{
    return toVector<PropertyDefinition>(cType.definitions, cType.count);
}

} // namespace DOS
