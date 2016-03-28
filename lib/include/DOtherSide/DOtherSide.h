#ifndef DOTHERSIDE_H
#define DOTHERSIDE_H

#ifdef WIN32
#define DOS_API   __declspec( dllexport )
#else
#define DOS_API
#endif

#include <DOtherSide/DOtherSideTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

// QCoreApplication
DOS_API char *dos_qcoreapplication_application_dir_path();

// QGuiApplication
DOS_API void dos_qguiapplication_create();
DOS_API void dos_qguiapplication_exec();
DOS_API void dos_qguiapplication_quit();
DOS_API void dos_qguiapplication_delete();

// QApplication
DOS_API void dos_qapplication_create();
DOS_API void dos_qapplication_exec();
DOS_API void dos_qapplication_quit();
DOS_API void dos_qapplication_delete();

// QQmlApplicationEngine
DOS_API DosQQmlApplicationEngine *dos_qqmlapplicationengine_create();
DOS_API void  dos_qqmlapplicationengine_load(DosQQmlApplicationEngine *vptr, const char *filename);
DOS_API void  dos_qqmlapplicationengine_load_url(DosQQmlApplicationEngine *vptr, DosQUrl *url);
DOS_API void  dos_qqmlapplicationengine_load_data(DosQQmlApplicationEngine *vptr, const char *data);
DOS_API void  dos_qqmlapplicationengine_add_import_path(DosQQmlApplicationEngine *vptr, const char *path);
DOS_API DosQQmlContext *dos_qqmlapplicationengine_context(DosQQmlApplicationEngine *vptr);
DOS_API void  dos_qqmlapplicationengine_delete(DosQQmlApplicationEngine *vptr);

// QQuickView
DOS_API DosQQuickView *dos_qquickview_create();
DOS_API void  dos_qquickview_show(DosQQuickView *vptr);
DOS_API char *dos_qquickview_source(DosQQuickView *vptr);
DOS_API void  dos_qquickview_set_source_url(DosQQuickView *vptr, DosQUrl *url);
DOS_API void  dos_qquickview_set_source(DosQQuickView *vptr, const char *filename);
DOS_API void  dos_qquickview_set_resize_mode(DosQQuickView *vptr, int resizeMode);
DOS_API void  dos_qquickview_delete(DosQQuickView *vptr);
DOS_API DosQQmlContext *dos_qquickview_rootContext(DosQQuickView *vptr);

// QQmlContext
DOS_API char *dos_qqmlcontext_baseUrl(DosQQmlContext *vptr);
DOS_API void  dos_qqmlcontext_setcontextproperty(DosQQmlContext *vptr, const char *name, DosQVariant *value);

// CharArray
DOS_API void  dos_chararray_delete(char *ptr);

// QVariant
DOS_API DosQVariant *dos_qvariant_create();
DOS_API DosQVariant *dos_qvariant_create_int(int value);
DOS_API DosQVariant *dos_qvariant_create_bool(bool value);
DOS_API DosQVariant *dos_qvariant_create_string(const char *value);
DOS_API DosQVariant *dos_qvariant_create_qobject(DosQObject *value);
DOS_API DosQVariant *dos_qvariant_create_qvariant(DosQVariant *value);
DOS_API DosQVariant *dos_qvariant_create_float(float value);
DOS_API DosQVariant *dos_qvariant_create_double(double value);
DOS_API void   dos_qvariant_setInt    (DosQVariant *vptr, int value);
DOS_API void   dos_qvariant_setBool   (DosQVariant *vptr, bool value);
DOS_API void   dos_qvariant_setFloat  (DosQVariant *vptr, float value);
DOS_API void   dos_qvariant_setDouble (DosQVariant *vptr, double value);
DOS_API void   dos_qvariant_setString (DosQVariant *vptr, const char *value);
DOS_API void   dos_qvariant_setQObject(DosQVariant *vptr, DosQObject *value);
DOS_API bool   dos_qvariant_isnull    (DosQVariant *vptr);
DOS_API void   dos_qvariant_delete    (DosQVariant *vptr);
DOS_API void   dos_qvariant_assign    (DosQVariant *vptr, DosQVariant *other);
DOS_API int    dos_qvariant_toInt     (DosQVariant *vptr);
DOS_API bool   dos_qvariant_toBool    (DosQVariant *vptr);
DOS_API char  *dos_qvariant_toString  (DosQVariant *vptr);
DOS_API float  dos_qvariant_toFloat   (DosQVariant *vptr);
DOS_API double dos_qvariant_toDouble  (DosQVariant *vptr);
DOS_API DosQObject *dos_qvariant_toQObject(DosQVariant *vptr);

// QMetaObject
DOS_API DosQMetaObject *dos_qmetaobject_create(DosQMetaObject *superClassMetaObject,
                                               const char *className,
                                               const SignalDefinitions *signalDefinitions,
                                               const SlotDefinitions *slotDefinitions,
                                               const PropertyDefinitions *propertyDefinitions);
DOS_API void  dos_qmetaobject_delete(DosQMetaObject *vptr);

// QAbstractListModel
DOS_API DosQMetaObject *dos_qabstractlistmodel_qmetaobject();
DOS_API DosQAbstractListModel *dos_qabstractlistmodel_create(void *callbackObject,
                                                             DosQMetaObject *metaObject,
                                                             DObjectCallback dObjectCallback,
                                                             RowCountCallback rowCountCallback,
                                                             ColumnCountCallback columnCountCallback,
                                                             DataCallback dataCallback,
                                                             SetDataCallback setDataCallback,
                                                             RoleNamesCallback roleNamesCallback,
                                                             FlagsCallback flagsCallback,
                                                             HeaderDataCallback headerDataCallback);
DOS_API void dos_qabstractlistmodel_beginInsertRows(DosQAbstractListModel *vptr, DosQModelIndex *parent, int first, int last);
DOS_API void dos_qabstractlistmodel_endInsertRows  (DosQAbstractListModel *vptr);
DOS_API void dos_qabstractlistmodel_beginRemoveRows(DosQAbstractListModel *vptr, DosQModelIndex *parent, int first, int last);
DOS_API void dos_qabstractlistmodel_endRemoveRows  (DosQAbstractListModel *vptr);
DOS_API void dos_qabstractlistmodel_beginResetModel(DosQAbstractListModel *vptr);
DOS_API void dos_qabstractlistmodel_endResetModel  (DosQAbstractListModel *vptr);
DOS_API void dos_qabstractlistmodel_dataChanged    (DosQAbstractListModel *vptr, DosQModelIndex *topLeft, DosQModelIndex *bottomRight, int *rolesPtr, int rolesLength);

// QObject
DOS_API DosQMetaObject *dos_qobject_qmetaobject();
DOS_API DosQObject *dos_qobject_create(void *dObjectPointer,
                                       DosQMetaObject *metaObject,
                                       DObjectCallback dObjectCallback);
DOS_API void dos_qobject_signal_emit(DosQObject *vptr,
                                     const char *name,
                                     int parametersCount,
                                     void **parameters);
DOS_API void dos_qobject_signal_connect(DosQObject *senderVPtr,
                                        const char *signal,
                                        DosQObject *receiverVPtr,
                                        const char *method,
                                        int type,
                                        bool *result);
DOS_API void dos_qobject_signal_disconnect(DosQObject *senderVPtr,
                                           const char *signal,
                                           DosQObject *receiverVPtr,
                                           const char *method,
                                           bool *result);
DOS_API char *dos_qobject_objectName(DosQObject *vptr);
DOS_API void  dos_qobject_setObjectName(DosQObject *vptr, const char *name);
DOS_API void  dos_qobject_delete(DosQObject *vptr);

// QModelIndex
DOS_API DosQModelIndex *dos_qmodelindex_create();
DOS_API DosQModelIndex *dos_qmodelindex_create_qmodelindex(DosQModelIndex *index);
DOS_API void  dos_qmodelindex_delete (DosQModelIndex *vptr);
DOS_API int   dos_qmodelindex_row    (DosQModelIndex *vptr);
DOS_API int   dos_qmodelindex_column (DosQModelIndex *vptr);
DOS_API bool  dos_qmodelindex_isValid(DosQModelIndex *vptr);
DOS_API DosQVariant *dos_qmodelindex_data   (DosQModelIndex *vptr, int role);
DOS_API DosQModelIndex *dos_qmodelindex_parent (DosQModelIndex *vptr);
DOS_API DosQModelIndex *dos_qmodelindex_child  (DosQModelIndex *vptr, int row, int column);
DOS_API DosQModelIndex *dos_qmodelindex_sibling(DosQModelIndex *vptr, int row, int column);
DOS_API void  dos_qmodelindex_assign (DosQModelIndex *l, DosQModelIndex *r);

// QHash<int, QByteArray>
DOS_API DosQHashIntQByteArray *dos_qhash_int_qbytearray_create();
DOS_API void  dos_qhash_int_qbytearray_delete(DosQHashIntQByteArray *vptr);
DOS_API void  dos_qhash_int_qbytearray_insert(DosQHashIntQByteArray *vptr, int key, const char *value);
DOS_API char *dos_qhash_int_qbytearray_value (DosQHashIntQByteArray *vptr, int key);

// QResource
DOS_API void dos_qresource_register(const char *filename);

// QUrl
DOS_API DosQUrl *dos_qurl_create(const char *url, int parsingMode);
DOS_API void  dos_qurl_delete(DosQUrl *vptr);
DOS_API char *dos_qurl_to_string(DosQUrl *vptr);

// QDeclarative
DOS_API int dos_qdeclarative_qmlregistertype(const QmlRegisterType *qmlRegisterType);
DOS_API int dos_qdeclarative_qmlregistersingletontype(const QmlRegisterType *qmlRegisterType);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
