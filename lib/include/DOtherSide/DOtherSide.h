#ifndef DOTHERSIDE_H
#define DOTHERSIDE_H

#ifdef WIN32
#define DOS_API   __declspec( dllexport )
#define DOS_CALL __cdecl
#else
#define DOS_API
#define DOS_CALL
#endif

#include <DOtherSide/DOtherSideTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

// QCoreApplication
DOS_API char *DOS_CALL dos_qcoreapplication_application_dir_path();

// QGuiApplication
DOS_API void DOS_CALL dos_qguiapplication_create();
DOS_API void DOS_CALL dos_qguiapplication_exec();
DOS_API void DOS_CALL dos_qguiapplication_quit();
DOS_API void DOS_CALL dos_qguiapplication_delete();

// QApplication
DOS_API void DOS_CALL dos_qapplication_create();
DOS_API void DOS_CALL dos_qapplication_exec();
DOS_API void DOS_CALL dos_qapplication_quit();
DOS_API void DOS_CALL dos_qapplication_delete();

// QQmlApplicationEngine
DOS_API DosQQmlApplicationEngine *DOS_CALL dos_qqmlapplicationengine_create();
DOS_API void  DOS_CALL dos_qqmlapplicationengine_load(DosQQmlApplicationEngine *vptr, const char *filename);
DOS_API void  DOS_CALL dos_qqmlapplicationengine_load_url(DosQQmlApplicationEngine *vptr, DosQUrl *url);
DOS_API void  DOS_CALL dos_qqmlapplicationengine_load_data(DosQQmlApplicationEngine *vptr, const char *data);
DOS_API void  DOS_CALL dos_qqmlapplicationengine_add_import_path(DosQQmlApplicationEngine *vptr, const char *path);
DOS_API DosQQmlContext *DOS_CALL dos_qqmlapplicationengine_context(DosQQmlApplicationEngine *vptr);
DOS_API void  DOS_CALL dos_qqmlapplicationengine_delete(DosQQmlApplicationEngine *vptr);

// QQuickView
DOS_API DosQQuickView *DOS_CALL dos_qquickview_create();
DOS_API void   DOS_CALL dos_qquickview_show(DosQQuickView *vptr);
DOS_API char *DOS_CALL dos_qquickview_source(DosQQuickView *vptr);
DOS_API void   DOS_CALL dos_qquickview_set_source_url(DosQQuickView *vptr, DosQUrl *url);
DOS_API void   DOS_CALL dos_qquickview_set_source(DosQQuickView *vptr, const char *filename);
DOS_API void   DOS_CALL dos_qquickview_set_resize_mode(DosQQuickView *vptr, int resizeMode);
DOS_API void   DOS_CALL dos_qquickview_delete(DosQQuickView *vptr);
DOS_API DosQQmlContext *DOS_CALL dos_qquickview_rootContext(DosQQuickView *vptr);

// QQmlContext
DOS_API char *DOS_CALL dos_qqmlcontext_baseUrl(DosQQmlContext *vptr);

/// Sets a property inside the context
/// @param vptr The DosQQmlContext
/// @param name The property name. The string is owned by the caller thus it will not be deleted by the library
/// @param value The property value. The DosQVariant is owned by the caller thus it will not be deleted by the library
DOS_API void   DOS_CALL dos_qqmlcontext_setcontextproperty(DosQQmlContext *vptr, const char *name, DosQVariant *value);

// CharArray
/// Delete a string
/// @param ptr The string
DOS_API void DOS_CALL dos_chararray_delete(char *ptr);

// QVariant
DOS_API DosQVariant *DOS_CALL dos_qvariant_create();
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_int(int value);
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_bool(bool value);
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_string(const char *value);
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_qobject(DosQObject *value);
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_qvariant(DosQVariant *value);
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_float(float value);
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_double(double value);
DOS_API void   DOS_CALL dos_qvariant_setInt    (DosQVariant *vptr, int value);
DOS_API void   DOS_CALL dos_qvariant_setBool   (DosQVariant *vptr, bool value);
DOS_API void   DOS_CALL dos_qvariant_setFloat  (DosQVariant *vptr, float value);
DOS_API void   DOS_CALL dos_qvariant_setDouble (DosQVariant *vptr, double value);
DOS_API void   DOS_CALL dos_qvariant_setString (DosQVariant *vptr, const char *value);
DOS_API void   DOS_CALL dos_qvariant_setQObject(DosQVariant *vptr, DosQObject *value);
DOS_API bool   DOS_CALL dos_qvariant_isnull    (const DosQVariant *vptr);
DOS_API void   DOS_CALL dos_qvariant_delete    (DosQVariant *vptr);
DOS_API void   DOS_CALL dos_qvariant_assign    (DosQVariant *vptr, const DosQVariant *other);
DOS_API int    DOS_CALL dos_qvariant_toInt     (const DosQVariant *vptr);
DOS_API bool   DOS_CALL dos_qvariant_toBool    (const DosQVariant *vptr);
DOS_API char  *DOS_CALL dos_qvariant_toString  (const DosQVariant *vptr);
DOS_API float  DOS_CALL dos_qvariant_toFloat   (const DosQVariant *vptr);
DOS_API double DOS_CALL dos_qvariant_toDouble  (const DosQVariant *vptr);
DOS_API DosQObject *DOS_CALL dos_qvariant_toQObject(const DosQVariant *vptr);

// QMetaObject
DOS_API DosQMetaObject *DOS_CALL dos_qmetaobject_create(DosQMetaObject *superClassMetaObject,
                                                        const char *className,
                                                        const SignalDefinitions *signalDefinitions,
                                                        const SlotDefinitions *slotDefinitions,
                                                        const PropertyDefinitions *propertyDefinitions);
DOS_API void DOS_CALL dos_qmetaobject_delete(DosQMetaObject *vptr);

// QAbstractListModel
DOS_API DosQMetaObject *DOS_CALL dos_qabstractlistmodel_qmetaobject();
DOS_API DosQAbstractListModel *DOS_CALL dos_qabstractlistmodel_create(void *callbackObject,
                                                                      DosQMetaObject *metaObject,
                                                                      DObjectCallback dObjectCallback,
                                                                      RowCountCallback rowCountCallback,
                                                                      ColumnCountCallback columnCountCallback,
                                                                      DataCallback dataCallback,
                                                                      SetDataCallback setDataCallback,
                                                                      RoleNamesCallback roleNamesCallback,
                                                                      FlagsCallback flagsCallback,
                                                                      HeaderDataCallback headerDataCallback);
DOS_API void DOS_CALL dos_qabstractlistmodel_beginInsertRows(DosQAbstractListModel *vptr, DosQModelIndex *parent, int first, int last);
DOS_API void DOS_CALL dos_qabstractlistmodel_endInsertRows  (DosQAbstractListModel *vptr);
DOS_API void DOS_CALL dos_qabstractlistmodel_beginRemoveRows(DosQAbstractListModel *vptr, DosQModelIndex *parent, int first, int last);
DOS_API void DOS_CALL dos_qabstractlistmodel_endRemoveRows  (DosQAbstractListModel *vptr);
DOS_API void DOS_CALL dos_qabstractlistmodel_beginResetModel(DosQAbstractListModel *vptr);
DOS_API void DOS_CALL dos_qabstractlistmodel_endResetModel  (DosQAbstractListModel *vptr);

/// Emit the dataChanged signal
/// @param vptr The DosQAbstractListModel pointer
/// @param topLeft The topLeft DosQModelIndex. The index is owned by the caller thus it will not be deleted
/// @param bottomRight The bottomright DosQModelIndex. The index is owned by the caller thus it will not be deleted
/// @param rolesPtr The roles array. The pointer is owned by the caller and thus it will not be deleted
/// @param rolesLength The roles array length
DOS_API void DOS_CALL dos_qabstractlistmodel_dataChanged(DosQAbstractListModel *vptr,
                                                         const DosQModelIndex *topLeft,
                                                         const DosQModelIndex *bottomRight,
                                                         int *rolesPtr, int rolesLength);

// QObject
DOS_API DosQMetaObject *DOS_CALL dos_qobject_qmetaobject();
DOS_API DosQObject *DOS_CALL dos_qobject_create(void *dObjectPointer,
                                                DosQMetaObject *metaObject,
                                                DObjectCallback dObjectCallback);
DOS_API void DOS_CALL dos_qobject_signal_emit(DosQObject *vptr,
                                              const char *name,
                                              int parametersCount,
                                              void **parameters);
DOS_API bool DOS_CALL dos_qobject_signal_connect(DosQObject *senderVPtr,
                                                 const char *signal,
                                                 DosQObject *receiverVPtr,
                                                 const char *method,
                                                 int type);
DOS_API bool DOS_CALL dos_qobject_signal_disconnect(DosQObject *senderVPtr,
                                                    const char *signal,
                                                    DosQObject *receiverVPtr,
                                                    const char *method);
/// Return the DosQObject objectName
/// @param vptr The DosQObject pointer
/// @return A string in UTF8 format. The ownership is transferred to the caller thus
/// it's his responsability to free the string
DOS_API char *DOS_CALL dos_qobject_objectName(DosQObject *vptr);

/// Sets the DosQObject objectName
/// @param vptr the DosQObject pointer
/// @param name a pointer to a UTF8 string. The string is owned by the caller thus
/// it will not be deleted.
DOS_API void   DOS_CALL dos_qobject_setObjectName(DosQObject *vptr, const char *name);

/// Delete the DosQObject
/// @param vptr the DosQObject pointer
DOS_API void   DOS_CALL dos_qobject_delete(DosQObject *vptr);

// QModelIndex
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_create();
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_create_qmodelindex(DosQModelIndex *index);
DOS_API void DOS_CALL dos_qmodelindex_delete (DosQModelIndex *vptr);
DOS_API int  DOS_CALL dos_qmodelindex_row    (const DosQModelIndex *vptr);
DOS_API int  DOS_CALL dos_qmodelindex_column (const DosQModelIndex *vptr);
DOS_API bool DOS_CALL dos_qmodelindex_isValid(const DosQModelIndex *vptr);
DOS_API DosQVariant *DOS_CALL dos_qmodelindex_data (DosQModelIndex *vptr, int role);
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_parent (const DosQModelIndex *vptr);
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_child  (const DosQModelIndex *vptr, int row, int column);
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_sibling(const DosQModelIndex *vptr, int row, int column);
DOS_API void DOS_CALL dos_qmodelindex_assign (DosQModelIndex *l, const DosQModelIndex *r);

// QHash<int, QByteArray>
DOS_API DosQHashIntQByteArray *DOS_CALL dos_qhash_int_qbytearray_create();
DOS_API void   DOS_CALL dos_qhash_int_qbytearray_delete(DosQHashIntQByteArray *vptr);
DOS_API void   DOS_CALL dos_qhash_int_qbytearray_insert(DosQHashIntQByteArray *vptr, int key, const char *value);
DOS_API char *DOS_CALL dos_qhash_int_qbytearray_value (DosQHashIntQByteArray *vptr, int key);

// QResource
DOS_API void DOS_CALL dos_qresource_register(const char *filename);

// QUrl
DOS_API DosQUrl *DOS_CALL dos_qurl_create(const char *url, int parsingMode);
DOS_API void   DOS_CALL dos_qurl_delete(DosQUrl *vptr);
DOS_API char *DOS_CALL dos_qurl_to_string(DosQUrl *vptr);

// QDeclarative
DOS_API int DOS_CALL dos_qdeclarative_qmlregistertype(const QmlRegisterType *qmlRegisterType);
DOS_API int DOS_CALL dos_qdeclarative_qmlregistersingletontype(const QmlRegisterType *qmlRegisterType);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
