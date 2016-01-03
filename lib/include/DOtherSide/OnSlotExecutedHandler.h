#pragma once

// std
#include <vector>
// Qt
#include <QVariant>
// DOtherSide
#include "DOtherSide/DOtherSideTypesCpp.h"
#include "DOtherSide/IDynamicQObject.h"

namespace DOS
{

class OnMetaObjectHandler
{
public:
    OnMetaObjectHandler(void* dObjectPointer, MetaObjectCallback dMetaObjectCallback);

    DynamicQObjectFactory* operator()();

private:
    void* m_dObjectPointer;
    MetaObjectCallback m_dMetaObjectCallback;
};

class OnSlotExecutedHandler
{
public:
    OnSlotExecutedHandler(void* dObjectPointer, DObjectCallback dObjectCallback);

    QVariant operator()(const QString& name, const std::vector<QVariant>& args);

private:
    void* m_dObjectPointer;
    DObjectCallback m_dObjectCallback;
};

} // namespace DOS
