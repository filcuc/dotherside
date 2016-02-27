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
DOS_API void *dos_qqmlapplicationengine_create();
DOS_API void  dos_qqmlapplicationengine_load(void *vptr, const char *filename);
DOS_API void  dos_qqmlapplicationengine_load_url(void *vptr, void *url);
DOS_API void  dos_qqmlapplicationengine_load_data(void *vptr, const char *data);
DOS_API void  dos_qqmlapplicationengine_add_import_path(void *vptr, const char *path);
DOS_API void *dos_qqmlapplicationengine_context(void *vptr);
DOS_API void  dos_qqmlapplicationengine_delete(void *vptr);

// QQuickView
DOS_API void *dos_qquickview_create();
DOS_API void  dos_qquickview_show(void *vptr);
DOS_API char *dos_qquickview_source(void *vptr);
DOS_API void  dos_qquickview_set_source_url(void *vptr, void *url);
DOS_API void  dos_qquickview_set_source(void *vptr, const char *filename);
DOS_API void  dos_qquickview_set_resize_mode(void *vptr, int resizeMode);
DOS_API void  dos_qquickview_delete(void *vptr);
DOS_API void *dos_qquickview_rootContext(void *vptr);

// QQmlContext
DOS_API char *dos_qqmlcontext_baseUrl(void *vptr);
DOS_API void  dos_qqmlcontext_setcontextproperty(void *vptr, const char *name, void *value);

// CharArray
DOS_API void  dos_chararray_delete(char *ptr);

// QVariant
DOS_API void  *dos_qvariant_create();
DOS_API void  *dos_qvariant_create_int(int value);
DOS_API void  *dos_qvariant_create_bool(bool value);
DOS_API void  *dos_qvariant_create_string(const char *value);
DOS_API void  *dos_qvariant_create_qobject(void *value);
DOS_API void  *dos_qvariant_create_qvariant(void *value);
DOS_API void  *dos_qvariant_create_float(float value);
DOS_API void  *dos_qvariant_create_double(double value);
DOS_API void   dos_qvariant_setInt(void *vptr, int value);
DOS_API void   dos_qvariant_setBool(void *vptr, bool value);
DOS_API void   dos_qvariant_setFloat(void *vptr, float value);
DOS_API void   dos_qvariant_setDouble(void *vptr, double value);
DOS_API void   dos_qvariant_setString(void *vptr, const char *value);
DOS_API void   dos_qvariant_setQObject(void *vptr, void *value);
DOS_API bool   dos_qvariant_isnull(void *vptr);
DOS_API void   dos_qvariant_delete(void *vptr);
DOS_API void   dos_qvariant_assign(void *vptr, void *other);
DOS_API int    dos_qvariant_toInt(void *vptr);
DOS_API bool   dos_qvariant_toBool(void *vptr);
DOS_API char  *dos_qvariant_toString(void *vptr);
DOS_API float  dos_qvariant_toFloat(void *vptr);
DOS_API double dos_qvariant_toDouble(void *vptr);
DOS_API void  *dos_qvariant_toQObject(void *vptr);

// QMetaObject
DOS_API void *dos_qmetaobject_create(void *superClassMetaObject,
                                     const char *className,
                                     const SignalDefinitions *signalDefinitions,
                                     const SlotDefinitions *slotDefinitions,
                                     const PropertyDefinitions *propertyDefinitions);
DOS_API void  dos_qmetaobject_delete(void *vptr);

// QAbstractListModel
DOS_API void *dos_qabstractlistmodel_qmetaobject();
DOS_API void *dos_qabstractlistmodel_create(void *callbackObject,
                                            void *metaObject,
                                            DObjectCallback dObjectCallback,
                                            RowCountCallback rowCountCallback,
                                            ColumnCountCallback columnCountCallback,
                                            DataCallback dataCallback,
                                            SetDataCallback setDataCallback,
                                            RoleNamesCallback roleNamesCallback,
                                            FlagsCallback flagsCallback,
                                            HeaderDataCallback headerDataCallback);
DOS_API void  dos_qabstractlistmodel_beginInsertRows(void *vptr, void *parent, int first, int last);
DOS_API void  dos_qabstractlistmodel_endInsertRows(void *vptr);
DOS_API void  dos_qabstractlistmodel_beginRemoveRows(void *vptr, void *parent, int first, int last);
DOS_API void  dos_qabstractlistmodel_endRemoveRows(void *vptr);
DOS_API void  dos_qabstractlistmodel_beginResetModel(void *vptr);
DOS_API void  dos_qabstractlistmodel_endResetModel(void *vptr);
DOS_API void  dos_qabstractlistmodel_dataChanged(void *vptr, void *topLeft, void *bottomRight, int *rolesPtr, int rolesLength);

// QObject
DOS_API void *dos_qobject_qmetaobject();
DOS_API void *dos_qobject_create(void *dObjectPointer,
                                 void *metaObject,
                                 DObjectCallback dObjectCallback);
DOS_API void  dos_qobject_signal_emit(void *vptr,
                                      const char *name,
                                      int parametersCount,
                                      void **parameters);
DOS_API void  dos_qobject_signal_connect(void *senderVPtr,
                                         const char *signal,
                                         void *receiverVPtr,
                                         const char *method,
                                         int type,
                                         bool *result);
DOS_API void  dos_qobject_signal_disconnect(void *senderVPtr,
                                            const char *signal,
                                            void *receiverVPtr,
                                            const char *method,
                                            bool *result);
DOS_API char *dos_qobject_objectName(void *vptr);
DOS_API void  dos_qobject_setObjectName(void *vptr, const char *name);
DOS_API void  dos_qobject_delete(void *vptr);

// QModelIndex
DOS_API void *dos_qmodelindex_create();
DOS_API void *dos_qmodelindex_create_qmodelindex(void *index);
DOS_API void  dos_qmodelindex_delete(void *vptr);
DOS_API int   dos_qmodelindex_row(void *vptr);
DOS_API int   dos_qmodelindex_column(void *vptr);
DOS_API bool  dos_qmodelindex_isValid(void *vptr);
DOS_API void *dos_qmodelindex_data(void *vptr, int role);
DOS_API void *dos_qmodelindex_parent(void *vptr, void *parent);
DOS_API void *dos_qmodelindex_child(void *vptr, int row, int column);
DOS_API void *dos_qmodelindex_sibling(void *vptr, int row, int column);
DOS_API void  dos_qmodelindex_assign(void *l, void *r);

// QHash<int, QByteArray>
DOS_API void *dos_qhash_int_qbytearray_create();
DOS_API void  dos_qhash_int_qbytearray_delete(QHashIntQByteArrayVoidPtr vptr);
DOS_API void  dos_qhash_int_qbytearray_insert(QHashIntQByteArrayVoidPtr vptr, int key, const char *value);
DOS_API char *dos_qhash_int_qbytearray_value(QHashIntQByteArrayVoidPtr vptr, int key);

// QResource
DOS_API void dos_qresource_register(const char *filename);

// QUrl
DOS_API void *dos_qurl_create(const char *url, int parsingMode);
DOS_API void  dos_qurl_delete(void *vptr);
DOS_API char *dos_qurl_to_string(void *vptr);

// QDeclarative
DOS_API int dos_qdeclarative_qmlregistertype(const QmlRegisterType *qmlRegisterType);
DOS_API int dos_qdeclarative_qmlregistersingletontype(const QmlRegisterType *qmlRegisterType);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
