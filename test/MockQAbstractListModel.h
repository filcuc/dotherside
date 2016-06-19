#pragma once

#include <Global.h>

class MockQAbstractListModel
{
public:
    MockQAbstractListModel();

    DosQMetaObject *metaObject();
    DosQObject *data();

private:
    static void onSlotCalled(void *selfVPtr, DosQVariant *dosSlotNameVariant, int dosSlotArgc, DosQVariant **dosSlotArgv);
    static void onRowCountCalled(DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
    static void onColumnCountCalled(DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
    static void onDataCalled(DosQAbstractListModel *model, const DosQModelIndex *index, int role, DosQVariant *result);
    static void onSetDataCalled(DosQAbstractListModel *model, const DosQModelIndex *index, const DosQVariant *value, int role, bool *result);
    static void onRoleNamesCalled(DosQAbstractListModel *model, DosQHashIntQByteArray *result);
    static void onFlagsCalled(DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
    static void onHeaderDataCalled(DosQAbstractListModel *model, int section, int orientation, int role, DosQVariant *result);

    VoidPointer m_vptr;
};
