#ifndef DOTHERSIDETYPES_H
#define DOTHERSIDETYPES_H

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
typedef void(*Function)(void *);
typedef void(*DObjectCallback)(void *, void *, int, void **);
typedef void(*RowCountCallback)     (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void(*ColumnCountCallback)  (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void(*DataCallback)         (DosQAbstractListModel *model, const DosQModelIndex *index, int role, DosQVariant *result);
typedef void(*SetDataCallback)      (DosQAbstractListModel *model, const DosQModelIndex *index, const DosQVariant *value, int role, bool *result);
typedef void(*RoleNamesCallback)    (DosQAbstractListModel *model, DosQHashIntQByteArray *result);
typedef void(*FlagsCallback)        (DosQAbstractListModel *model, const DosQModelIndex *index, int *result);
typedef void(*HeaderDataCallback)   (DosQAbstractListModel *model, int section, int orientation, int role, DosQVariant *result);
typedef void(*CreateDObject)(int, void *, void **, void **);
typedef void(*DeleteDObject)(int, void *);

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
