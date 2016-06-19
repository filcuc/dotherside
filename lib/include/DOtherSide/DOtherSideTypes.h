#ifndef DOTHERSIDETYPES_H
#define DOTHERSIDETYPES_H

#ifdef WIN32
#define DOS_CALL __cdecl
#else
#define DOS_CALL
#endif


#ifdef __cplusplus
extern "C"
{
#endif

// Raw data types
typedef void DosQVariant;
typedef void DosQModelIndex;
typedef void DosQAbstractListModel;
typedef void DosQQmlApplicationEngine;
typedef void DosQQuickView;
typedef void DosQQmlContext;
typedef void DosQHashIntQByteArray;
typedef void DosQUrl;
typedef void DosQMetaObject;
typedef void DosQObject;

// Raw function types
typedef void (DOS_CALL *Function)(void *);

/// Called when a slot should be executed
/// @param self The pointer to the QObject in the binded language
/// @param slotName The slotName as DosQVariant. It should not be deleted
/// @param argc The number of arguments
/// @param argv An array of DosQVariant pointers. They should not be deleted
typedef void (DOS_CALL *DObjectCallback)(void *self, DosQVariant *slotName, int argc, DosQVariant **argv);

typedef void (DOS_CALL *RowCountCallback)     (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void (DOS_CALL *ColumnCountCallback)  (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void (DOS_CALL *DataCallback)         (DosQAbstractListModel *model, const DosQModelIndex *index, int role, DosQVariant *result);
typedef void (DOS_CALL *SetDataCallback)      (DosQAbstractListModel *model, const DosQModelIndex *index, const DosQVariant *value, int role, bool *result);
typedef void (DOS_CALL *RoleNamesCallback)    (DosQAbstractListModel *model, DosQHashIntQByteArray *result);
typedef void (DOS_CALL *FlagsCallback)        (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void (DOS_CALL *HeaderDataCallback)   (DosQAbstractListModel *model, int section, int orientation, int role, DosQVariant *result);
typedef void (DOS_CALL *CreateDObject)(int, void *, void **, void **);
typedef void (DOS_CALL *DeleteDObject)(int, void *);

struct QmlRegisterType {
    int major;
    int minor;
    const char *uri;
    const char *qml;
    void *staticMetaObject;
    CreateDObject createDObject;
    DeleteDObject deleteDObject;
};

struct SignalDefinition {
    const char *name;
    int parametersCount;
    int *parametersMetaTypes;
};

struct SignalDefinitions {
    int count;
    SignalDefinition *definitions;
};

struct SlotDefinition {
    const char *name;
    int returnMetaType;
    int parametersCount;
    int *parametersMetaTypes;
};

struct SlotDefinitions {
    int count;
    SlotDefinition *definitions;
};

struct PropertyDefinition {
    const char *name;
    int propertyMetaType;
    const char *readSlot;
    const char *writeSlot;
    const char *notifySignal;
};

struct PropertyDefinitions {
    int count;
    PropertyDefinition *definitions;
};

#ifdef __cplusplus
}
#endif

#endif
