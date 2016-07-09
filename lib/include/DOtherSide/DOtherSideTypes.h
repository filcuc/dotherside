/**
 * \file DOtherSideTypes.h
 * \brief The DOtherSide types
 *
 * This file contains all the type definitions for structs and callbacks
 * used by the DOtherSide library
 */

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

/// A pointer to a QVariant
typedef void DosQVariant;

/// A pointer to a QModelIndex
typedef void DosQModelIndex;

/// A pointer to a QAbstractListModel
typedef void DosQAbstractListModel;

/// A pointer to a QQmlApplicationEngine
typedef void DosQQmlApplicationEngine;

/// pA pointer to a QQuickView
typedef void DosQQuickView;

/// A pointer to a QQmlContext
typedef void DosQQmlContext;

/// A pointer to a QHash<int,QByteArray>
typedef void DosQHashIntQByteArray;

/// A pointer to a QUrl
typedef void DosQUrl;

/// A pointer to a QMetaObject
typedef void DosQMetaObject;

/// A pointer to a QObject
typedef void DosQObject;

/// Called when a slot should be executed
/**
 * \param self The pointer to the QObject in the binded language
 * \param slotName The slotName as DosQVariant. It should not be deleted
 * \param argc The number of arguments
 * \param argv An array of DosQVariant pointers. They should not be deleted
 */
typedef void (DOS_CALL *DObjectCallback)(void *self, DosQVariant *slotName, int argc, DosQVariant **argv);

/// Called when the QAbstractListModel::rowCount method must be executed
/**
 * \param self The pointer to the QAbstractListModel in the binded language
 * \param index The parent DosQModelIndex. It should not be deleted
 * \param result The rowCount result. This must be deferenced and filled from the binded language. It should not be deleted
 */
typedef void (DOS_CALL *RowCountCallback)(void *self, const DosQModelIndex *parent, int *result);

/// Called when the QAbstractListModel::columnCount method must be executed
/**
 * \param self The pointer to the QAbstractListModel in the binded language
 * \param index The parent DosQModelIndex. It should not be deleted
 * \param result The rowCount result. This must be deferenced and filled from the binded language. It should not be deleted
 */
typedef void (DOS_CALL *ColumnCountCallback)(void *self, const DosQModelIndex *parent, int *result);

/// Called when the QAbstractListModel::data method must be executed
/**
 * \param self The pointer to the QAbstractListModel in the binded language
 * \param index The DosQModelIndex to which we request the data. It should not be deleted
 * \param result The DosQVariant result. This must be deferenced and filled from the binded language.
 * It should not be deleted. See dos_qvariant_assign or other DosQVariant setters
 */
typedef void (DOS_CALL *DataCallback)(void *self, const DosQModelIndex *index, int role, DosQVariant *result);


/// Called when the QAbstractListModel::setData method must be executed
typedef void (DOS_CALL *SetDataCallback)(void *self, const DosQModelIndex *index, const DosQVariant *value, int role, bool *result);

/// Called when the QAbstractListModel::roleNames method must be executed
typedef void (DOS_CALL *RoleNamesCallback)(void *self, DosQHashIntQByteArray *result);


/// Called when the QAbstractListModel::flags method must be called
typedef void (DOS_CALL *FlagsCallback)(void *self, const DosQModelIndex *index, int *result);


/// Called when the QAbstractListModel::headerData method must be called
typedef void (DOS_CALL *HeaderDataCallback)(void *self, int section, int orientation, int role, DosQVariant *result);

/// Callback called from QML for creating a registered type
/**
 * When a type is created through the QML engine a new QObject \i"Wrapper" is created. This becomes a proxy
 * between the "default" QObject created through dos_qobject_create() and the QML engine. This imply that implementation
 * for this callback should swap the DosQObject* stored in the binded language with the wrapper. At the end the wrapper
 * becomes the owner of the original "default" DosQObject. Furthermore if the binding language is garbage collected you
 * should disable (pin/ref) the original object and unref in the DeleteDObject() callback. Since the wrapper has been created
 * from QML is QML that expect to free the memory for it thus it shouldn't be destroyed by the QObject in the binded language.
 *
 * An example of implementation in pseudocode is: \n
 * \code{.nim}
proc createCallback(.....) =
  # Call the constructor for the given type and create a QObject in Nim
  let nimQObject = constructorMap[id]()

  # Disable GC
  GC.ref(nimQObject)

  # Retrieve the DosQObject created dos_qobject_create() inside the nimQObject
  *dosQObject = nimQObject.vptr

  # Store the pointer to the nimQObject
  *bindedQObject = cast[ptr](&nimQObject)

  # Swap the vptr inside the nimQObject with the wrapper
  nimQObject.vptr = wrapper

  # The QObject in the Nim language should not destroy its inner DosQObject
  nimQObject.owner = false

\endcode

 * \param id This is the id for which we are requesting the creation.
 * This is the same value that was returned during registration through the calls
 * to dos_qdeclarative_qmlregistertype() or dos_qdeclarative_qmlregistersingletontype()
 * \param wrapper This is the QObject wrapper that should be stored by the binded language and to which forward the
 * DOtherSide calls
 * \param dosQObject This should be deferenced and assigned with the DosQObject pointer you gained from calling the dos_qobject_create() function
 * \param bindedQObject This should be deferenced and assigned with the pointer of the QObject modeled in the binded language
 */
typedef void (DOS_CALL *CreateDObject)(int id, void *wrapper, void **dosQObject, void **bindedQObject);

/// Callback invoked from QML for deleting a registered type
/**
 * This is called when the wrapper gets deleted from QML. The implementation should unref/unpin
 * the \p bindedQObject or delete it in the case of languages without GC
 * \param id This is the type id for which we are requesting the deletion
 * \param bindedQObject This is the pointer you given in the CreateDObject callback and you can use it
 * for obtaining the QObject in your binded language. This allows you to unpin/unref it or delete it.
 */
typedef void (DOS_CALL *DeleteDObject)(int id, void * bindedQObject);

struct DosQVariantArray {
    int size;
    DosQVariant** data;
};

/// The data needed for registering a custom type in the QML environment
/**
 * This is used from dos_qdeclarative_qmlregistertype() and dos_qdeclarative_qmlregistersingletontype() calls.
 * \see dos_qdeclarative_qmlregistertype()
 * \see dos_qdeclarative_qmlregistersingletontype()
 * \note All string and objects are considered to be owned by the caller thus they'll
 * not be freed
*/
struct QmlRegisterType {
    /// The Module major version
    int major;
    /// The Module minor version
    int minor;
    /// The Module uri
    const char *uri;
    /// The type name to be used in QML files
    const char *qml;
    /// The type QMetaObject
    DosQMetaObject *staticMetaObject;
    /// The callback invoked from QML when this type should be created
    CreateDObject createDObject;
    /// The callback invoked from QML when this type should be deleted
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
