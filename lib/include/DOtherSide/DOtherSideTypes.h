/**
 * @file DOtherSideTypes.h
 * @brief The DOtherSide types
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

/// \brief A pointer to a QVariant
typedef void DosQVariant;

/// \brief A pointer to a QModelIndex
typedef void DosQModelIndex;

/// \brief A pointer to a QAbstractListModel
typedef void DosQAbstractListModel;

/// \brief A pointer to a QQmlApplicationEngine
typedef void DosQQmlApplicationEngine;

/// \brief A pointer to a QQuickView
typedef void DosQQuickView;

/// \brief A pointer to a QQmlContext
typedef void DosQQmlContext;

/// \brief A pointer to a QHash<int,QByteArray>
typedef void DosQHashIntQByteArray;

/// \brief A pointer to a QUrl
typedef void DosQUrl;

/// \brief A pointer to a QMetaObject
typedef void DosQMetaObject;

/// \brief A pointer to a QObject
typedef void DosQObject;

/**
 * \brief Called when a slot should be executed
 * \param self The pointer to the QObject in the binded language
 * \param slotName The slotName as DosQVariant. It should not be deleted
 * \param argc The number of arguments
 * \param argv An array of DosQVariant pointers. They should not be deleted
 */
typedef void (DOS_CALL *DObjectCallback)(void *self, DosQVariant *slotName, int argc, DosQVariant **argv);

/**
 * \brief Called when the QAbstractListModel::rowCount method must be executed
 * \param self The pointer to the QAbstractListModel in the binded language
 * \param index The parent DosQModelIndex. It should not be deleted
 * \param result The rowCount result. This must be deferenced and filled from the binded language. It should not be deleted
 */
typedef void (DOS_CALL *RowCountCallback)(void *self, const DosQModelIndex *parent, int *result);

/**
 * \brief Called when the QAbstractListModel::columnCount method must be executed
 * \param self The pointer to the QAbstractListModel in the binded language
 * \param index The parent DosQModelIndex. It should not be deleted
 * \param result The rowCount result. This must be deferenced and filled from the binded language. It should not be deleted
 */
typedef void (DOS_CALL *ColumnCountCallback)(void *self, const DosQModelIndex *parent, int *result);

/**
 * \brief Called when the QAbstractListModel::data method must be executed
 * \param self The pointer to the QAbstractListModel in the binded language
 * \param index The DosQModelIndex to which we request the data. It should not be deleted
 * \param result The DosQVariant result. This must be deferenced and filled from the binded language.
 * It should not be deleted. See dos_qvariant_assign or other DosQVariant setters
 */
typedef void (DOS_CALL *DataCallback)(void *self, const DosQModelIndex *index, int role, DosQVariant *result);

/**
 * \brief Called when the QAbstractListModel::setData method must be executed
 */
typedef void (DOS_CALL *SetDataCallback)(void *self, const DosQModelIndex *index, const DosQVariant *value, int role, bool *result);

/**
 * \brief Called when the QAbstractListModel::roleNames method must be executed
 */
typedef void (DOS_CALL *RoleNamesCallback)(void *self, DosQHashIntQByteArray *result);

/**
 * \brief Called when the QAbstractListModel::flags method must be called
 */
typedef void (DOS_CALL *FlagsCallback)(void *self, const DosQModelIndex *index, int *result);

/**
 * \brief Called when the QAbstractListModel::headerData method must be called
 */
typedef void (DOS_CALL *HeaderDataCallback)(void *self, int section, int orientation, int role, DosQVariant *result);

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
