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
#else
#include <stdbool.h>
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
typedef void (DOS_CALL *DObjectCallback)(void *, void *, int, void **);
typedef void (DOS_CALL *RowCountCallback)     (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void (DOS_CALL *ColumnCountCallback)  (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void (DOS_CALL *DataCallback)         (DosQAbstractListModel *model, const DosQModelIndex *index, int role, DosQVariant *result);
typedef void (DOS_CALL *SetDataCallback)      (DosQAbstractListModel *model, const DosQModelIndex *index, const DosQVariant *value, int role, bool *result);
typedef void (DOS_CALL *RoleNamesCallback)    (DosQAbstractListModel *model, DosQHashIntQByteArray *result);
typedef void (DOS_CALL *FlagsCallback)        (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void (DOS_CALL *HeaderDataCallback)   (DosQAbstractListModel *model, int section, int orientation, int role, DosQVariant *result);
typedef void (DOS_CALL *CreateDObject)(int, void *, void **, void **);
typedef void (DOS_CALL *DeleteDObject)(int, void *);

typedef struct {
    int major;
    int minor;
    const char *uri;
    const char *qml;
    void *staticMetaObject;
    CreateDObject createDObject;
    DeleteDObject deleteDObject;
} QmlRegisterType;

typedef struct {
    const char *name;
    int parametersCount;
    int *parametersMetaTypes;
} SignalDefinition;

typedef struct {
    int count;
    SignalDefinition *definitions;
} SignalDefinitions;

typedef struct {
    const char *name;
    int returnMetaType;
    int parametersCount;
    int *parametersMetaTypes;
} SlotDefinition;

typedef struct {
    int count;
    SlotDefinition *definitions;
} SlotDefinitions;

typedef struct {
    const char *name;
    int propertyMetaType;
    const char *readSlot;
    const char *writeSlot;
    const char *notifySignal;
} PropertyDefinition;

typedef struct {
    int count;
    PropertyDefinition *definitions;
} PropertyDefinitions;

#ifdef __cplusplus
}
#endif

#endif
