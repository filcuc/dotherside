#include "MockQAbstractListModel.h"

using namespace std;

namespace
{
    std::string toStringFromQVariant(DosQVariant* variant) {
        CharPointer charArray(dos_qvariant_toString(variant), &dos_chararray_delete);
        return std::string(charArray.get());
    }

    VoidPointer initializeMetaObject()
    {
        void* superClassMetaObject = dos_qabstractlistmodel_qmetaobject();

        // Signals
        ::SignalDefinitions signalDefinitions;
        signalDefinitions.count = 0;
        signalDefinitions.definitions = nullptr;

        // Slots
        ::SlotDefinitions slotDefinitions;
        slotDefinitions.count = 0;
        slotDefinitions.definitions = nullptr;

        // Properties
        ::PropertyDefinitions propertyDefinitions;
        propertyDefinitions.count = 0;
        propertyDefinitions.definitions = nullptr;

        return VoidPointer(dos_qmetaobject_create(superClassMetaObject, "MockQAbstractListModel", &signalDefinitions, &slotDefinitions, &propertyDefinitions),
                           &dos_qmetaobject_delete);
    }
}

MockQAbstractListModel::MockQAbstractListModel()
    : m_vptr(dos_qabstractlistmodel_create(this, metaObject(), &onSlotCalled, &onRowCountCalled,
                                           &onColumnCountCalled, &onDataCalled, &onSetDataCalled,
                                           &onRoleNamesCalled, &onFlagsCalled, &onHeaderDataCalled), &dos_qobject_delete)
    , m_names({"John", "Mary", "Andy", "Anna"})
{

}

DosQMetaObject *MockQAbstractListModel::metaObject()
{
    static VoidPointer result = initializeMetaObject();
    return result.get();
}

DosQObject *MockQAbstractListModel::data()
{
    return m_vptr.get();
}

void MockQAbstractListModel::onSlotCalled(void *selfVPtr, DosQVariant *dosSlotNameVariant, int dosSlotArgc, DosQVariant **dosSlotArgv)
{
    auto self = static_cast<MockQAbstractListModel*>(selfVPtr);
    string slotName = toStringFromQVariant(dosSlotNameVariant);
}

void MockQAbstractListModel::onRowCountCalled(void *selfVPtr, const DosQModelIndex *index, int *result)
{
    auto self = static_cast<MockQAbstractListModel*>(selfVPtr);
    *result = self->m_names.size();
}

void MockQAbstractListModel::onColumnCountCalled(void *selfVPtr, const DosQModelIndex *index, int *result)
{
    auto self = static_cast<MockQAbstractListModel*>(selfVPtr);
    *result = 1;
}

void MockQAbstractListModel::onDataCalled(void *selfVPtr, const DosQModelIndex *index, int role, DosQVariant *result)
{
    auto self = static_cast<MockQAbstractListModel*>(selfVPtr);

    if (!dos_qmodelindex_isValid(index))
        return;

    const int row = dos_qmodelindex_row(index);
    const int column = dos_qmodelindex_column(index);

    if (row < 0 || row >= self->m_names.size() || column != 0)
        return;

    dos_qvariant_setString(result, self->m_names[row].c_str());
}

void MockQAbstractListModel::onSetDataCalled(void *selfVPtr, const DosQModelIndex *index, const DosQVariant *value, int role, bool *result)
{

}

void MockQAbstractListModel::onRoleNamesCalled(void *selfVPtr, DosQHashIntQByteArray *result)
{

}

void MockQAbstractListModel::onFlagsCalled(void *selfVPtr, const DosQModelIndex *index, int *result)
{

}

void MockQAbstractListModel::onHeaderDataCalled(void *selfVPtr, int section, int orientation, int role, DosQVariant *result)
{

}
