#ifndef DOTHERSIDETYPES_H
#define DOTHERSIDETYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

// Raw data types
typedef void *QVariantVoidPtr;
typedef void *QModelIndexVoidPtr;
typedef void *QAbstractListModelVoidPtr;
typedef void *QQmlApplicationEngineVoidPtr;
typedef void *QQuickViewVoidPtr;
typedef void *QQmlContextVoidPtr;
typedef void *QHashIntQByteArrayVoidPtr;

// Raw function types
typedef void(*Function)(void *);
typedef void(*DObjectCallback)(void *, void *, int, void **);
typedef void(*RowCountCallback)(void *model, const void *index, int *result);
typedef void(*ColumnCountCallback)(void *model, const void *index, int *result);
typedef void(*DataCallback)(void *model, const void *index, int role, QVariantVoidPtr result);
typedef void(*SetDataCallback) (void *model, const void *index, const void *value, int role, bool *result);
typedef void(*RoleNamesCallback)(void *model, QHashIntQByteArrayVoidPtr result);
typedef void(*FlagsCallback) (void *model, const void *index, int *result);
typedef void(*HeaderDataCallback) (void *model, int section, int orientation, int role, QVariantVoidPtr result);
typedef void(*CreateDObject)(int, void **, void **);
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
