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
        ::PropertyDefinition propertyDefinitionArray[1];

        ::PropertyDefinitions propertyDefinitions;
        propertyDefinitions.count = 0;
        propertyDefinitions.definitions = nullptr;

        return VoidPointer(dos_qmetaobject_create(superClassMetaObject, "MockQObject", &signalDefinitions, &slotDefinitions, &propertyDefinitions),
                           &dos_qmetaobject_delete);
    }
}

MockQAbstractListModel::MockQAbstractListModel()
    : m_vptr(dos_qabstractlistmodel_create(this, metaObject(), &onSlotCalled, &onRowCountCalled,
                                           &onColumnCountCalled, &onDataCalled, &onSetDataCalled,
                                           &onRoleNamesCalled, &onFlagsCalled, &onHeaderDataCalled), &dos_qobject_delete)
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

void MockQAbstractListModel::onRowCountCalled(DosQAbstractListModel *model, const DosQModelIndex *index, int *result)
{

}

void MockQAbstractListModel::onColumnCountCalled(DosQAbstractListModel *model, const DosQModelIndex *index, int *result)
{

}

void MockQAbstractListModel::onDataCalled(DosQAbstractListModel *model, const DosQModelIndex *index, int role, DosQVariant *result)
{

}

void MockQAbstractListModel::onSetDataCalled(DosQAbstractListModel *model, const DosQModelIndex *index, const DosQVariant *value, int role, bool *result)
{

}

void MockQAbstractListModel::onRoleNamesCalled(DosQAbstractListModel *model, DosQHashIntQByteArray *result)
{

}

void MockQAbstractListModel::onFlagsCalled(DosQAbstractListModel *model, const DosQModelIndex *index, int *result)
{

}

void MockQAbstractListModel::onHeaderDataCalled(DosQAbstractListModel *model, int section, int orientation, int role, DosQVariant *result)
{

}
