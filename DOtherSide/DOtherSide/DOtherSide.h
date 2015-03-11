#ifndef DOTHERSIDE_H
#define DOTHERSIDE_H

#ifdef WIN32
#define DOS_API   __declspec( dllexport )
#else
#define DOS_API  
#endif

#include "DOtherSideTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef char* CharPtr;
typedef void(*Function)(void*);
typedef void(*DObjectCallback)(void*, void*, int, void**);

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
DOS_API void dos_qqmlapplicationengine_context(void* vptr, void** context);
DOS_API void dos_qqmlapplicationengine_delete(void* vptr);

// QQuickView
DOS_API void dos_qquickview_create(void** vptr);
DOS_API void dos_qquickview_show(void* vptr);
DOS_API void dos_qquickview_source(void* vptr, char** result, int* length);
DOS_API void dos_qquickview_set_source(void* vptr, const char* filename);
DOS_API void dos_qquickview_delete(void* vptr);
DOS_API void dos_qquickview_rootContext(void* vptr, void** context);
 
// QQmlContext
DOS_API void dos_qqmlcontext_baseUrl(void* vptr, char** result, int* length);
DOS_API void dos_qqmlcontext_setcontextproperty(void* vptr, const char* name, void* value);

// CharArray
DOS_API void dos_chararray_create(char** ptr, int size);
DOS_API void dos_chararray_delete(char* ptr);

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
DOS_API void dos_qvariant_toInt(void* vptr, int* value);
DOS_API void dos_qvariant_setInt(void* vptr, int value);
DOS_API void dos_qvariant_toBool(void* vptr, bool* value);
DOS_API void dos_qvariant_setBool(void* vptr, bool value);
DOS_API void dos_qvariant_toFloat(void* vptr, float* value);
DOS_API void dos_qvariant_setFloat(void* vptr, float value);
DOS_API void dos_qvariant_toDouble(void* vptr, double* value);
DOS_API void dos_qvariant_setDouble(void* vptr, double value);
DOS_API void dos_qvariant_toString(void* vptr, char** ptr, int* size);
DOS_API void dos_qvariant_setString(void* vptr, const char* value);
DOS_API void dos_qvariant_setQObject(void* vptr, void* value);
DOS_API void dos_qvariant_setQAbstractListModel(void* vptr, void* value);
DOS_API void dos_qvariant_isnull(void* vptr, bool* isNull);
DOS_API void dos_qvariant_delete(void* vptr);
DOS_API void dos_qvariant_assign(void* vptr, void* other);

// QObject
DOS_API void dos_qobject_create(void** vptr,
                                void* dObjectPointer,
                                DObjectCallback dObjectCallback);

DOS_API void dos_qobject_slot_create(void* vptr,
                                     const char* name,
                                     int parametersCount,
                                     int* parametersMetaTypes,
                                     int* slotIndex);

DOS_API void dos_qobject_signal_create(void* vptr,
                                       const char* name,
                                       int parametersCount,
                                       int* parametersMetaTypes,
                                       int* signalIndex);

DOS_API void dos_qobject_signal_emit(void* vptr,
                                     const char* name,
                                     int parametersCount,
                                     void** parameters);

DOS_API void dos_qobject_property_create(void* vptr,
                                         const char* name,
                                         int propertyMetaType,
                                         const char* readSlot,
                                         const char* writeSlot,
                                         const char* notifySignal);
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

// QAbstractListModel
DOS_API void dos_qabstractlistmodel_create(void** vptr,
                                           void* callbackObject,
                                           DObjectCallback dObjectCallback,
                                           RowCountCallback rowCountCallback,
                                           ColumnCountCallback columnCountCallback,
                                           DataCallback dataCallback,
                                           SetDataCallback setDataCallback,
                                           RoleNamesCallback roleNamesCallback,
                                           FlagsCallback flagsCallback,
                                           HeaderDataCallback headerDataCallback);
DOS_API void dos_qabstractlistmodel_beginInsertRows(void* vptr,
                                                    QModelIndexVoidPtr parentIndex,
                                                    int first,
                                                    int last);
DOS_API void dos_qabstractlistmodel_endInsertRows(void* vptr);
DOS_API void dos_qabstractlistmodel_beginRemoveRows(void* vptr,
                                                    QModelIndexVoidPtr parentIndex,
                                                    int first,
                                                    int last);
DOS_API void dos_qabstractlistmodel_endRemoveRows(void* vptr);
DOS_API void dos_qabstractlistmodel_beginResetModel(void* vptr);
DOS_API void dos_qabstractlistmodel_endResetModel(void* vptr);
DOS_API void dos_qabstractlistmodel_dataChanged(void* vptr,
                                                QModelIndexVoidPtr topLeftIndex,
                                                QModelIndexVoidPtr bottomRightIndex,
                                                int* rolesArrayPtr,
                                                int rolesArrayLength);

DOS_API void dos_qabstractlistmodel_delete(void* vptr);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
