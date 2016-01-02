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
DOS_API void dos_qcoreapplication_application_dir_path(char** result);

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
DOS_API void dos_qqmlapplicationengine_create(void** vptr);
DOS_API void dos_qqmlapplicationengine_load(void* vptr, const char* filename);
DOS_API void dos_qqmlapplicationengine_load_url(void* vptr, void* url);
DOS_API void dos_qqmlapplicationengine_load_data(void* vptr, const char* data);
DOS_API void dos_qqmlapplicationengine_add_import_path(void* vptr, const char* path);
DOS_API void dos_qqmlapplicationengine_context(void* vptr, void** context);
DOS_API void dos_qqmlapplicationengine_rootObjects(void* vptr, void*** array, int* array_length);
DOS_API void dos_qqmlapplicationengine_delete(void* vptr);

// QQuickView
DOS_API void dos_qquickview_create(void** vptr);
DOS_API void dos_qquickview_show(void* vptr);
DOS_API void dos_qquickview_source(void* vptr, char** result);
DOS_API void dos_qquickview_set_source_url(void* vptr, void* url);
DOS_API void dos_qquickview_set_source(void* vptr, const char* filename);
DOS_API void dos_qquickview_set_resize_mode(void* vptr, int resizeMode);
DOS_API void dos_qquickview_delete(void* vptr);
DOS_API void dos_qquickview_rootContext(void* vptr, void** result);

// QQmlContext
DOS_API void dos_qqmlcontext_baseUrl(void* vptr, char** result);
DOS_API void dos_qqmlcontext_setcontextproperty(void* vptr, const char* name, void* value);

// CharArray
DOS_API void dos_chararray_delete(char* ptr);

// QObjectPtrArray
DOS_API void dos_qobjectptr_array_delete(void** ptr);

// QVariant
DOS_API void dos_qvariant_create(void** vptr);
DOS_API void dos_qvariant_create_int(void** vptr, int value);
DOS_API void dos_qvariant_create_bool(void** vptr, bool value);
DOS_API void dos_qvariant_create_string(void** vptr, const char* value);
DOS_API void dos_qvariant_create_qobject(void** vptr, void* value);
DOS_API void dos_qvariant_create_qvariant(void** vptr, void* value);
DOS_API void dos_qvariant_create_float(void** vptr, float value);
DOS_API void dos_qvariant_create_double(void** vptr, double value);
DOS_API void dos_qvariant_create_qabstractlistmodel(void** vptr, void* value);
DOS_API void dos_qvariant_toInt(void* vptr, int* result);
DOS_API void dos_qvariant_setInt(void* vptr, int value);
DOS_API void dos_qvariant_toBool(void* vptr, bool* result);
DOS_API void dos_qvariant_setBool(void* vptr, bool value);
DOS_API void dos_qvariant_toFloat(void* vptr, float* result);
DOS_API void dos_qvariant_setFloat(void* vptr, float value);
DOS_API void dos_qvariant_toDouble(void* vptr, double* result);
DOS_API void dos_qvariant_setDouble(void* vptr, double value);
DOS_API void dos_qvariant_toString(void* vptr, char** result);
DOS_API void dos_qvariant_setString(void* vptr, const char* value);
DOS_API void dos_qvariant_toQObject(void* vptr, void** value);
DOS_API void dos_qvariant_setQObject(void* vptr, void* value);
DOS_API void dos_qvariant_setQAbstractListModel(void* vptr, void* value);
DOS_API void dos_qvariant_isnull(void* vptr, bool* result);
DOS_API void dos_qvariant_delete(void* vptr);
DOS_API void dos_qvariant_assign(void* vptr, void* other);

// QObjectFactory
DOS_API void dos_qmetaobjectfactory_create(void** vptr,
                                       SignalDefinitions signalDefinitions,
                                       SlotDefinitions slotDefinitions,
                                       PropertyDefinitions propertyDefinitions);
DOS_API void dos_qmetaobjectfactory_delete(void* vptr);

// QObject
DOS_API void dos_qobject_signal_emit(void* vptr,
                                     const char* name,
                                     int parametersCount,
                                     void** parameters);
DOS_API void dos_qobject_signal_connect(void* senderVPtr,
                                        const char* signal,
                                        void* receiverVPtr,
                                        const char* method,
                                        int type,
                                        bool* result);
DOS_API void dos_qobject_signal_disconnect(void* senderVPtr,
                                           const char* signal,
                                           void* receiverVPtr,
                                           const char* method,
                                           bool* result);
DOS_API void dos_qobject_objectName(void* vptr, char** result);
DOS_API void dos_qobject_findChild(void* vptr, const char* name, int options, void** child);
DOS_API void dos_qobject_delete(void* vptr);

// QModelIndex
DOS_API void dos_qmodelindex_create(void** vptr);
DOS_API void dos_qmodelindex_delete(void* vptr);
DOS_API void dos_qmodelindex_row(void* vptr, int* row);
DOS_API void dos_qmodelindex_column(void* vptr, int* column);
DOS_API void dos_qmodelindex_isValid(void* vptr, bool* isValid);
DOS_API void dos_qmodelindex_data(void* vptr, int role, void* data);
DOS_API void dos_qmodelindex_parent(void* vptr, void* parent);
DOS_API void dos_qmodelindex_child(void* vptr, int row, int column, void* child);
DOS_API void dos_qmodelindex_sibling(void* vptr, int row, int column, void* sibling);

// QHash<int, QByteArray>
DOS_API void dos_qhash_int_qbytearray_create(QHashIntQByteArrayVoidPtr* vptr);
DOS_API void dos_qhash_int_qbytearray_delete(QHashIntQByteArrayVoidPtr vptr);
DOS_API void dos_qhash_int_qbytearray_insert(QHashIntQByteArrayVoidPtr vptr, int key, const char* value);
DOS_API void dos_qhash_int_qbytearray_value(QHashIntQByteArrayVoidPtr vptr, int key, char** result);

// QResource
DOS_API void dos_qresource_register(const char* filename);

// QUrl
DOS_API void dos_qurl_create(void** vptr, const char* url, int parsingMode);
DOS_API void dos_qurl_delete(void* vptr);
DOS_API void dos_qurl_to_string(void* vptr, char** result);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
