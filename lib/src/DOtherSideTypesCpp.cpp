#include "DOtherSide/DOtherSideTypesCpp.h"

namespace DOS {

SignalDefinitions toVector(const ::SignalDefinitions& cType)
{
    return toVector<SignalDefinition, ::SignalDefinition>(wrap_array(cType.definitions, cType.count));
}

SlotDefinitions toVector(const ::SlotDefinitions& cType)
{
    return toVector<SlotDefinition, ::SlotDefinition>(wrap_array(cType.definitions, cType.count));
}

PropertyDefinitions toVector(const ::PropertyDefinitions& cType)
{
    return toVector<PropertyDefinition, ::PropertyDefinition>(wrap_array(cType.definitions, cType.count));
}
}
