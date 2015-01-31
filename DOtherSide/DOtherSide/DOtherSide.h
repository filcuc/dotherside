#ifndef DOTHERSIDE_H
#define DOTHERSIDE_H

#include "DOtherSideTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef char* CharPtr;
typedef void(*Function)(void*);
typedef void(*DObjectCallback)(void*, void*, int, void**);

// QGuiApplication
void dos_qguiapplication_create();
void dos_qguiapplication_exec();
void dos_qguiapplication_quit();
void dos_qguiapplication_delete();

// QApplication
void dos_qapplication_create();
void dos_qapplication_exec();
void dos_qapplication_quit();
void dos_qapplication_delete();

// QQmlApplicationEngine
void dos_qqmlapplicationengine_create(void** vptr);
void dos_qqmlapplicationengine_load(void* vptr, const char* filename);
void dos_qqmlapplicationengine_context(void* vptr, void** context);
void dos_qqmlapplicationengine_delete(void* vptr);

// QQuickView
void dos_qquickview_create(void** vptr);
void dos_qquickview_show(void* vptr);
void dos_qquickview_source(void* vptr, char** result, int* length);
void dos_qquickview_set_source(void* vptr, const char* filename);
void dos_qquickview_delete(void* vptr);
void dos_qquickview_rootContext(void* vptr, void** context);

// QQmlContext
void dos_qqmlcontext_baseUrl(void* vptr, char** result, int* length);
void dos_qqmlcontext_setcontextproperty(void* vptr, const char* name, void* value);

// CharArray
void dos_chararray_create(char** ptr, int size);
void dos_chararray_delete(char* ptr);

// QVariant
void dos_qvariant_create(void **vptr);
void dos_qvariant_create_int(void **vptr, int value);
void dos_qvariant_create_bool(void **vptr, bool value);
void dos_qvariant_create_string(void **vptr, const char* value);
void dos_qvariant_create_qobject(void **vptr, void* value);
void dos_qvariant_create_qvariant(void **vptr, void* value);
void dos_qvariant_create_float(void **vptr, float value);
void dos_qvariant_create_double(void **vptr, double value);
void dos_qvariant_create_qabstractlistmodel(void **vptr, void* value);
void dos_qvariant_toInt(void* vptr, int* value);
void dos_qvariant_setInt(void* vptr, int value);
void dos_qvariant_toBool(void* vptr, bool* value);
void dos_qvariant_setBool(void* vptr, bool value);
void dos_qvariant_toFloat(void* vptr, float* value);
void dos_qvariant_setFloat(void* vptr, float value);
void dos_qvariant_toDouble(void* vptr, double* value);
void dos_qvariant_setDouble(void* vptr, double value);
void dos_qvariant_toString(void* vptr, char** ptr, int* size);
void dos_qvariant_setString(void* vptr, const char* value);
void dos_qvariant_setQObject(void* vptr, void* value);
void dos_qvariant_setQAbstractListModel(void* vptr, void* value);
void dos_qvariant_isnull(void *vptr, bool* isNull);
void dos_qvariant_delete(void *vptr);
void dos_qvariant_assign(void* vptr, void* other);

// QObject
void dos_qobject_create(void** vptr,
                        void* dObjectPointer,
                        DObjectCallback dObjectCallback);

void dos_qobject_slot_create(void* vptr,
                             const char* name,
                             int parametersCount,
                             int* parametersMetaTypes,
                             int* slotIndex);

void dos_qobject_signal_create(void* vptr,
                               const char* name,
                               int parametersCount,
                               int* parametersMetaTypes,
                               int* signalIndex);

void dos_qobject_signal_emit(void* vptr,
                             const char* name,
                             int parametersCount,
                             void** parameters);

void dos_qobject_property_create(void* vptr,
                                 const char* name,
                                 int propertyMetaType,
                                 const char* readSlot,
                                 const char* writeSlot,
                                 const char* notifySignal);
void dos_qobject_delete(void *vptr);

// QModelIndex
void dos_qmodelindex_create(void** vptr);
void dos_qmodelindex_delete(void* vptr);
void dos_qmodelindex_row(void* vptr, int* row);
void dos_qmodelindex_column(void* vptr, int* column);
void dos_qmodelindex_isValid(void* vptr, bool* isValid);
void dos_qmodelindex_data(void* vptr, int role, void* data);
void dos_qmodelindex_parent(void* vptr, void* parent);
void dos_qmodelindex_child(void* vptr, int row, int column, void* child);
void dos_qmodelindex_sibling(void* vptr, int row, int column, void* sibling);

// QHash<int, QByteArray>
void dos_qhash_int_qbytearray_create(QHashIntQByteArrayVoidPtr* vptr);
void dos_qhash_int_qbytearray_delete(QHashIntQByteArrayVoidPtr vptr);
void dos_qhash_int_qbytearray_insert(QHashIntQByteArrayVoidPtr vptr, int key, const char* value);
void dos_qhash_int_qbytearray_value(QHashIntQByteArrayVoidPtr vptr, int key, char** result);

// QAbstractListModel
void dos_qabstractlistmodel_create(void** vptr,
                                   void* callbackObject,
                                   RowCountCallback rowCountCallback,
                                   DataCallback dataCallback);
void dos_qabstractlistmodel_delete(void* vptr);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
