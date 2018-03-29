#pragma once

// std
#include <vector>
// Qt
#include <QtCore/QVariant>
// DOtherSide
#include "DOtherSide/DOtherSideTypesCpp.h"

namespace DOS {

class OnSlotExecutedHandler
{
public:
    OnSlotExecutedHandler(void *dObjectPointer, DObjectCallback dObjectCallback);

    QVariant operator()(const QString &name, const std::vector<QVariant> &args);

private:
    void *m_dObjectPointer;
    DObjectCallback m_dObjectCallback;
};

} // namespace DOS
