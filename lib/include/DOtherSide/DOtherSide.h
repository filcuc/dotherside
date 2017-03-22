/**
 * \file DOtherSide.h
 * \brief The DOtherSide API file
 * \author Filippo Cucchetto
 *
 * This file contains all the functions from creating or manipulating the QML
 * environement
 */

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

/// \defgroup QGuiApplication QGuiApplication
/// \brief Functions related to the QGuiApplication class
/// @{

/// \brief Return the QCore::applicationDirPath
/// \return The QCore::applicationDirPath as a UTF-8 string
/// \note The returned string should be deleted by the calling code by using
/// the dos_chararray_delete() function
DOS_API char *DOS_CALL dos_qcoreapplication_application_dir_path();

/// \brief Create a QGuiApplication
/// \note The created QGuiApplication should be freed by calling dos_qguiapplication_delete()
DOS_API void DOS_CALL dos_qguiapplication_create();

/// \brief Calls the QGuiApplication::exec() function of the current QGuiApplication
/// \note A QGuiApplication should have been already created through dos_qguiapplication_create()
DOS_API void DOS_CALL dos_qguiapplication_exec();

/// \brief Calls the QGuiApplication::quit() function of the current QGuiApplication
/// \note A QGuiApplication should have been already created through dos_qguiapplication_create()
DOS_API void DOS_CALL dos_qguiapplication_quit();

/// \brief Free the memory of the current QGuiApplication
/// \note A QGuiApplication should have been already created through dos_qguiapplication_create()
DOS_API void DOS_CALL dos_qguiapplication_delete();

/// @}

/// \defgroup QApplication QApplication
/// \brief Functions related to the QApplication class
/// @{

/// \brief Create a QApplication
/// \note The created QApplication should be freed by calling dos_qapplication_delete()
DOS_API void DOS_CALL dos_qapplication_create();

/// \brief Calls the QApplication::exec() function of the current QGuiApplication
/// \note A QApplication should have been already created through dos_qapplication_create()
DOS_API void DOS_CALL dos_qapplication_exec();

/// \brief Calls the QApplication::quit() function of the current QGuiApplication
/// \note A QApplication should have been already created through dos_qapplication_create()
DOS_API void DOS_CALL dos_qapplication_quit();

/// \brief Free the memory of the current QApplication
/// \note A QApplication should have been already created through dos_qapplication_create()
DOS_API void DOS_CALL dos_qapplication_delete();

/// @}

/// \defgroup QQmlApplicationEngine QQmlApplicationEngine
/// \brief Functions related to the QQmlApplicationEngine class
/// @{

/// \brief Create a new QQmlApplicationEngine
/// \return A new QQmlApplicationEngine
/// \note The returned QQmlApplicationEngine should be freed by using dos_qqmlapplicationengine_delete(DosQQmlApplicationEngine*)
DOS_API DosQQmlApplicationEngine *DOS_CALL dos_qqmlapplicationengine_create();

/// \brief Calls the QQmlApplicationEngine::load function
/// \param vptr The QQmlApplicationEngine
/// \param filename The file to load. The file is relative to the directory that contains the application executable
DOS_API void DOS_CALL dos_qqmlapplicationengine_load(DosQQmlApplicationEngine *vptr, const char *filename);

/// \brief Calls the QQmlApplicationEngine::load function
/// \param vptr The QQmlApplicationEngine
/// \param url The QUrl of the file to load
DOS_API void DOS_CALL dos_qqmlapplicationengine_load_url(DosQQmlApplicationEngine *vptr, DosQUrl *url);

/// \brief Calls the QQmlApplicationEngine::loadData function
/// \param vptr The QQmlApplicationEngine
/// \param data The UTF-8 string of the QML to load
DOS_API void DOS_CALL dos_qqmlapplicationengine_load_data(DosQQmlApplicationEngine *vptr, const char *data);

/// \brief Calls the QQmlApplicationEngine::addImportPath function
/// \param vptr The QQmlApplicationEngine
/// \param path The path to be added to the list of import paths
DOS_API void DOS_CALL dos_qqmlapplicationengine_add_import_path(DosQQmlApplicationEngine *vptr, const char *path);

/// \brief Calls the QQmlApplicationEngine::context
/// \param vptr The QQmlApplicationEngine
/// \return A pointer to a QQmlContext. This should not be stored nor made available to the binded language if
/// you can't guarantee that this QQmlContext should not live more that its Engine. This context is owned by
/// the engine and so it should die with the engine.
DOS_API DosQQmlContext *DOS_CALL dos_qqmlapplicationengine_context(DosQQmlApplicationEngine *vptr);

/// \brief Free the memory allocated for the given QQmlApplicationEngine
/// \param vptr The QQmlApplicationEngine
DOS_API void DOS_CALL dos_qqmlapplicationengine_delete(DosQQmlApplicationEngine *vptr);

/// @}


/// \defgroup QQuickView QQuickView
/// \brief Functions related to the QQuickView class
/// @{

/// \brief Create a new QQuickView
/// \return A new QQuickView
/// \note The returned QQuickView should be freed by using dos_qquickview_delete(DosQQuickview*)
DOS_API DosQQuickView *DOS_CALL dos_qquickview_create();

/// \brief Calls the QQuickView::show() function
/// \param vptr The QQuickView
DOS_API void  DOS_CALL dos_qquickview_show(DosQQuickView *vptr);

/// \brief Calls the QQuickView::source() function
/// \param vptr The QQuickView
/// \return The QQuickView source as an UTF-8 string
/// \note The returned string should be freed by using the dos_chararray_delete() function
DOS_API char *DOS_CALL dos_qquickview_source(const DosQQuickView *vptr);

/// \brief Calls the QQuickView::setSource() function
/// \param vptr The QQuickView
/// \param url The source QUrl
DOS_API void DOS_CALL dos_qquickview_set_source_url(DosQQuickView *vptr, DosQUrl *url);

/// \brief Calls the QQuickView::setSource() function
/// \param vptr The QQuickView
/// \param filename The source path as an UTF-8 string. The path is relative to the directory
///  that contains the application executable
DOS_API void DOS_CALL dos_qquickview_set_source(DosQQuickView *vptr, const char *filename);

/// \brief Calls the QQuickView::setResizeMode() function
/// \param vptr The QQuickView
/// \param resizeMode The resize mode
DOS_API void DOS_CALL dos_qquickview_set_resize_mode(DosQQuickView *vptr, int resizeMode);

/// \brief Free the memory allocated for the given QQuickView
/// \param vptr The QQuickView
DOS_API void DOS_CALL dos_qquickview_delete(DosQQuickView *vptr);

/// \brief Return the QQuickView::rootContext() as a QQuickContext
/// \param vptr The QQuickView
DOS_API DosQQmlContext *DOS_CALL dos_qquickview_rootContext(DosQQuickView *vptr);

/// @}

/// \defgroup QQmlContext QQmlContext
/// \brief Functions related to the QQmlContext class
/// @{

/// \brief Calls the QQmlContext::baseUrl function
/// \return The QQmlContext url as an UTF-8 string
/// \note The returned string should be freed using with the dos_chararray_delete() function
DOS_API char *DOS_CALL dos_qqmlcontext_baseUrl(const DosQQmlContext *vptr);

/// \brief Sets a property inside the context
/// \param vptr The DosQQmlContext
/// \param name The property name. The string is owned by the caller thus it will not be deleted by the library
/// \param value The property value. The DosQVariant is owned by the caller thus it will not be deleted by the library
DOS_API void DOS_CALL dos_qqmlcontext_setcontextproperty(DosQQmlContext *vptr, const char *name, DosQVariant *value);

/// @}

/// \defgroup String String
/// \brief Functions related to strings
/// @{

/// \brief Free the memory allocated for the given UTF-8 string
/// \param ptr The UTF-8 string to be freed
DOS_API void DOS_CALL dos_chararray_delete(char *ptr);

/// @}


/// \defgroup QVariant QVariant
/// \brief Functions related to the QVariant class
/// @{

/// Delete a DosQVariantArray
DOS_API void DOS_CALL dos_qvariantarray_delete(DosQVariantArray *ptr);

/// \brief Create a new QVariant (null)
/// \return The a new QVariant
/// \note The returned QVariant should be freed using dos_qvariant_delete()
DOS_API DosQVariant *DOS_CALL dos_qvariant_create();

/// \brief Create a new QVariant holding an int value
/// \return The a new QVariant
/// \param value The int value
/// \note The returned QVariant should be freed using dos_qvariant_delete()
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_int(int value);

/// \brief Create a new QVariant holding a bool value
/// \return The a new QVariant
/// \param value The bool value
/// \note The returned QVariant should be freed using dos_qvariant_delete()
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_bool(bool value);

/// \brief Create a new QVariant holding a string value
/// \return The a new QVariant
/// \param value The string value
/// \note The returned QVariant should be freed using dos_qvariant_delete()
/// \note The given string is copied inside the QVariant and will not be deleted
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_string(const char *value);

/// \brief Create a new QVariant holding a QObject value
/// \return The a new QVariant
/// \param value The QObject value
/// \note The returned QVariant should be freed using dos_qvariant_delete()
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_qobject(DosQObject *value);

/// \brief Create a new QVariant with the same value of the one given as argument
/// \return The a new QVariant
/// \param value The QVariant to which copy its value
/// \note The returned QVariant should be freed using dos_qvariant_delete()
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_qvariant(const DosQVariant *value);

/// \brief Create a new QVariant holding a float value
/// \return The a new QVariant
/// \param value The float value
/// \note The returned QVariant should be freed using dos_qvariant_delete()
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_float(float value);

/// \brief Create a new QVariant holding a double value
/// \return The a new QVariant
/// \param value The double value
/// \note The returned QVariant should be freed using dos_qvariant_delete()
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_double(double value);

/// \brief Create a new QVariant holding a QVariantList
/// \return A new QVariant
/// \param size The size of the QVariant array
/// \param array The array of QVariant that will be inserted in the inner QVariantList
/// \note The \p array is owned by the caller thus it will not be deleted
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_array(int size, DosQVariant** array);

/// \brief Calls the QVariant::setValue<int>() function
/// \param vptr The QVariant
/// \param value The int value
DOS_API void DOS_CALL dos_qvariant_setInt(DosQVariant *vptr, int value);

/// \brief Calls the QVariant::setValue<bool>() function
/// \param vptr The QVariant
/// \param value The bool value
DOS_API void DOS_CALL dos_qvariant_setBool(DosQVariant *vptr, bool value);

/// \brief Calls the QVariant::setValue<float>() function
/// \param vptr The QVariant
/// \param value The float value
DOS_API void DOS_CALL dos_qvariant_setFloat(DosQVariant *vptr, float value);

/// \brief Calls the QVariant::setValue<double>() function
/// \param vptr The QVariant
/// \param value The double value
DOS_API void DOS_CALL dos_qvariant_setDouble(DosQVariant *vptr, double value);

/// \brief Calls the QVariant::setValue<QString>() function
/// \param vptr The QVariant
/// \param value The string value
/// \note The string argument is copied inside the QVariant and it will not be deleted
DOS_API void DOS_CALL dos_qvariant_setString(DosQVariant *vptr, const char *value);

/// \brief Calls the QVariant::setValue<QObject*>() function
/// \param vptr The QVariant
/// \param value The string value
/// \note The string argument is copied inside the QVariant and it will not be deleted
DOS_API void DOS_CALL dos_qvariant_setQObject(DosQVariant *vptr, DosQObject *value);

/// \brief Calls the QVariant::setValue<QVariantList>() function
/// \param vptr The QVariant
/// \param size The size of the \p array
/// \param array The array of QVariant use for setting the inner QVariantList
DOS_API void DOS_CALL dos_qvariant_setArray(DosQVariant *vptr, int size, DosQVariant** array);

/// \brief Calls the QVariant::isNull function
/// \return True if the QVariant is null, false otherwise
/// \param vptr The QVariant
DOS_API bool DOS_CALL dos_qvariant_isnull(const DosQVariant *vptr);

/// \brief Free the memory allocated for the given QVariant
/// \param vptr The QVariant
DOS_API void DOS_CALL dos_qvariant_delete(DosQVariant *vptr);

/// \brief Calls the QVariant::operator=(const QVariant&) function
/// \param vptr The QVariant (left side)
/// \param other The QVariant (right side)
DOS_API void DOS_CALL dos_qvariant_assign(DosQVariant *vptr, const DosQVariant *other);

/// \brief Calls the QVariant::value<int>() function
/// \param vptr The QVariant
/// \return The int value
DOS_API int DOS_CALL dos_qvariant_toInt(const DosQVariant *vptr);

/// \brief Calls the QVariant::value<bool>() function
/// \param vptr The QVariant
/// \return The bool value
DOS_API bool DOS_CALL dos_qvariant_toBool(const DosQVariant *vptr);

/// \brief Calls the QVariant::value<QString>() function
/// \param vptr The QVariant
/// \return The string value
/// \note The returned string should be freed by using dos_chararray_delete()
DOS_API char *DOS_CALL dos_qvariant_toString(const DosQVariant *vptr);

/// \brief Calls the QVariant::value<float>() function
/// \param vptr The QVariant
/// \return The float value
DOS_API float DOS_CALL dos_qvariant_toFloat (const DosQVariant *vptr);

/// \brief Calls the QVariant::value<double>() function
/// \param vptr The QVariant
/// \return The double value
DOS_API double DOS_CALL dos_qvariant_toDouble(const DosQVariant *vptr);

/// \brief Calls the QVariant::value<QVariantList>() function
/// \param vptr The QVariant
/// \return The QVariantList value as an array
DOS_API DosQVariantArray* DOS_CALL dos_qvariant_toArray(const DosQVariant *vptr);

/// \brief Calls the QVariant::value<QObject*>() function
/// \param vptr The QVariant
/// \return The QObject* value
/// \note Storing the returned QObject* is higly dengerous and depends on how you managed the memory
/// of QObjects in the binded language
DOS_API DosQObject *DOS_CALL dos_qvariant_toQObject(const DosQVariant *vptr);

/// @}


/// \defgroup QMetaObject QMetaObject
/// \brief Functions related to the QMetaObject class
/// @{

/// \brief Create a new QMetaObject
/// \param superClassMetaObject The superclass metaobject
/// \param className The class name
/// \param signalDefinitions The SignalDefinitions
/// \param slotDefinitions The SlotDefinitions struct
/// \param propertyDefinitions The PropertyDefinitions struct
/// \note The returned QMetaObject should be freed using dos_qmetaobject_delete().
/// \attention The QMetaObject should live more than the QObject it refears to.
/// Depending on the implementation usually the QMetaObject should be modeled as static variable
/// So with a lifetime equals to the entire application
DOS_API DosQMetaObject *DOS_CALL dos_qmetaobject_create(DosQMetaObject *superClassMetaObject,
                                                        const char *className,
                                                        const SignalDefinitions *signalDefinitions,
                                                        const SlotDefinitions *slotDefinitions,
                                                        const PropertyDefinitions *propertyDefinitions);

/// \brief Free the memory allocated for the given QMetaObject
/// \param vptr The QMetaObject
DOS_API void DOS_CALL dos_qmetaobject_delete(DosQMetaObject *vptr);

/// @}

/// \defgroup QAbstractListModel QAbstractItemModel
/// \brief Functions related to the QAbstractListModel class
/// @{

/// \brief Return QMetaObject associated to the QAbstractListModel class
/// \return The QMetaObject of the QAbstractListModel class
/// \note The returned QMetaObject should be freed using dos_qmetaobject_delete().
DOS_API DosQMetaObject *DOS_CALL dos_qabstractlistmmodel_qmetaobject();

/// \brief Create a new QAbstractListModel
/// \param callbackObject The pointer of QAbstractListModel in the binded language
/// \param metaObject The QMetaObject for this QAbstractListModel
/// \param dObjectCallback The callback for handling the properties read/write and slots execution
/// \param rowCountCallback The callback for handling the QAbstractItemModel::rowCount() execution
/// \param columnCountCallback The callback for handling the QAbstractItemModel::columnCount() execution
/// \param dataCallback The callback for handling the QAbstractItemModel::data() execution
/// \param setDataCallback The callback for handling the QAbstractItemModel::setData() execution
/// \param roleNamesCallback The callback for handling the QAbstractItemModel::roleNames() execution
/// \param flagsCallback The callback for handling the QAbstractItemModel::flags() execution
/// \param headerDataCallback The callback for handling the QAbstractItemModel::headerData() execution
/// \param indexCallback The callback for handling the QAbstractItemModel::index() execution
/// \param parentCallback The callback for handling the QAbstractItemModel::parent() execution
DOS_API DosQAbstractListModel *DOS_CALL dos_qabstractlistmodel_create(void *callbackObject,
                                                                      DosQMetaObject *metaObject,
                                                                      DObjectCallback dObjectCallback,
                                                                      RowCountCallback rowCountCallback,
                                                                      ColumnCountCallback columnCountCallback,
                                                                      DataCallback dataCallback,
                                                                      SetDataCallback setDataCallback,
                                                                      RoleNamesCallback roleNamesCallback,
                                                                      FlagsCallback flagsCallback,
                                                                      HeaderDataCallback headerDataCallback,
                                                                      IndexCallback indexCallback,
                                                                      ParentCallback parentCallback);
/// @}

/// \defgroup QAbstractTableModel QAbstractTableModel
/// \brief Functions related to the QAbstractTableModel class
/// @{

/// \brief Return QMetaObject associated to the QAbstractTableModel class
/// \return The QMetaObject of the QAbstractTableModel class
/// \note The returned QMetaObject should be freed using dos_qmetaobject_delete().
DOS_API DosQMetaObject *DOS_CALL dos_qabstracttablemmodel_qmetaobject();

/// \brief Create a new QAbstractTableModel
/// \param callbackObject The pointer of QAbstractTableModel in the binded language
/// \param metaObject The QMetaObject for this QAbstractTableModel
/// \param dObjectCallback The callback for handling the properties read/write and slots execution
/// \param rowCountCallback The callback for handling the QAbstractItemModel::rowCount() execution
/// \param columnCountCallback The callback for handling the QAbstractItemModel::columnCount() execution
/// \param dataCallback The callback for handling the QAbstractItemModel::data() execution
/// \param setDataCallback The callback for handling the QAbstractItemModel::setData() execution
/// \param roleNamesCallback The callback for handling the QAbstractItemModel::roleNames() execution
/// \param flagsCallback The callback for handling the QAbstractItemModel::flags() execution
/// \param headerDataCallback The callback for handling the QAbstractItemModel::headerData() execution
/// \param indexCallback The callback for handling the QAbstractItemModel::index() execution
/// \param parentCallback The callback for handling the QAbstractItemModel::parent() execution
DOS_API DosQAbstractListModel *DOS_CALL dos_qabstracttablemodel_create(void *callbackObject,
                                                                      DosQMetaObject *metaObject,
                                                                      DObjectCallback dObjectCallback,
                                                                      RowCountCallback rowCountCallback,
                                                                      ColumnCountCallback columnCountCallback,
                                                                      DataCallback dataCallback,
                                                                      SetDataCallback setDataCallback,
                                                                      RoleNamesCallback roleNamesCallback,
                                                                      FlagsCallback flagsCallback,
                                                                      HeaderDataCallback headerDataCallback,
                                                                      IndexCallback indexCallback,
                                                                      ParentCallback parentCallback);
/// @}

/// \defgroup QAbstractItemModel QAbstractItemModel
/// \brief Functions related to the QAbstractItemModel class
/// @{

/// \brief Return QMetaObject associated to the QAbstractItemModel class
/// \return The QMetaObject of the QAbstractItemModel class
/// \note The returned QMetaObject should be freed using dos_qmetaobject_delete().
DOS_API DosQMetaObject *DOS_CALL dos_qabstractitemmodel_qmetaobject();


/// \brief Create a new QAbstractItemModel
/// \param callbackObject The pointer of QAbstractItemModel in the binded language
/// \param metaObject The QMetaObject for this QAbstractItemModel
/// \param dObjectCallback The callback for handling the properties read/write and slots execution
/// \param rowCountCallback The callback for handling the QAbstractItemModel::rowCount() execution
/// \param columnCountCallback The callback for handling the QAbstractItemModel::columnCount() execution
/// \param dataCallback The callback for handling the QAbstractItemModel::data() execution
/// \param setDataCallback The callback for handling the QAbstractItemModel::setData() execution
/// \param roleNamesCallback The callback for handling the QAbstractItemModel::roleNames() execution
/// \param flagsCallback The callback for handling the QAbstractItemModel::flags() execution
/// \param headerDataCallback The callback for handling the QAbstractItemModel::headerData() execution
/// \param indexCallback The callback for handling the QAbstractItemModel::index() execution
/// \param parentCallback The callback for handling the QAbstractItemModel::parent() execution
DOS_API DosQAbstractItemModel *DOS_CALL dos_qabstractitemmodel_create(void *callbackObject,
                                                                      DosQMetaObject *metaObject,
                                                                      DObjectCallback dObjectCallback,
                                                                      RowCountCallback rowCountCallback,
                                                                      ColumnCountCallback columnCountCallback,
                                                                      DataCallback dataCallback,
                                                                      SetDataCallback setDataCallback,
                                                                      RoleNamesCallback roleNamesCallback,
                                                                      FlagsCallback flagsCallback,
                                                                      HeaderDataCallback headerDataCallback,
                                                                      IndexCallback indexCallback,
                                                                      ParentCallback parentCallback);

/// \brief Calls the QAbstractItemModel::beginInsertRows() function
/// \param vptr The QAbstractItemModel
/// \param parent The parent QModelIndex
/// \param first The first row in the range
/// \param last The last row in the range
/// \note The \p parent QModelIndex is owned by the caller thus it will not be deleted
DOS_API void DOS_CALL dos_qabstractitemmodel_beginInsertRows(DosQAbstractItemModel *vptr, DosQModelIndex *parent, int first, int last);

/// \brief Calls the QAbstractItemModel::endInsertRows() function
/// \param vptr The QAbstractItemModel
DOS_API void DOS_CALL dos_qabstractitemmodel_endInsertRows(DosQAbstractItemModel *vptr);

/// \brief Calls the QAbstractItemModel::beginRemovetRows() function
/// \param vptr The QAbstractItemModel
/// \param parent The parent QModelIndex
/// \param first The first column in the range
/// \param last The last column in the range
/// \note The \p parent QModelIndex is owned by the caller thus it will not be deleted
DOS_API void DOS_CALL dos_qabstractitemmodel_beginRemoveRows(DosQAbstractItemModel *vptr, DosQModelIndex *parent, int first, int last);

/// \brief Calls the QAbstractItemModel::endRemoveRows() function
/// \param vptr The QAbstractItemModel
DOS_API void DOS_CALL dos_qabstractitemmodel_endRemoveRows(DosQAbstractItemModel *vptr);

/// \brief Calls the QAbstractItemModel::beginInsertColumns() function
/// \param vptr The QAbstractItemModel
/// \param parent The parent QModelIndex
/// \param first The first column in the range
/// \param last The last column in the range
/// \note The \p parent QModelIndex is owned by the caller thus it will not be deleted
DOS_API void DOS_CALL dos_qabstractitemmodel_beginInsertColumns(DosQAbstractItemModel *vptr, DosQModelIndex *parent, int first, int last);

/// \brief Calls the QAbstractItemModel::endInsertColumns() function
/// \param vptr The QAbstractItemModel
DOS_API void DOS_CALL dos_qabstractitemmodel_endInsertColumns(DosQAbstractItemModel *vptr);

/// \brief Calls the QAbstractItemModel::beginRemovetColumns() function
/// \param vptr The QAbstractItemModel
/// \param parent The parent QModelIndex
/// \param first The first column in the range
/// \param last The last column in the range
/// \note The \p parent QModelIndex is owned by the caller thus it will not be deleted
DOS_API void DOS_CALL dos_qabstractitemmodel_beginRemoveColumns(DosQAbstractItemModel *vptr, DosQModelIndex *parent, int first, int last);

/// \brief Calls the QAbstractItemModel::endRemoveColumns() function
/// \param vptr The QAbstractItemModel
DOS_API void DOS_CALL dos_qabstractitemmodel_endRemoveColumns(DosQAbstractItemModel *vptr);

/// \brief Calls the QAbstractItemModel::beginResetModel() function
/// \param vptr The QAbstractItemModel
DOS_API void DOS_CALL dos_qabstractitemmodel_beginResetModel(DosQAbstractItemModel *vptr);

/// \brief Calls the QAbstractItemModel::endResetModel() function
/// \param vptr The QAbstractItemModel
DOS_API void DOS_CALL dos_qabstractitemmodel_endResetModel(DosQAbstractItemModel *vptr);

/// \brief Emit the dataChanged signal
/// \param vptr The DosQAbstractItemModel pointer
/// \param topLeft The topLeft DosQModelIndex
/// \param bottomRight The bottomright DosQModelIndex
/// \param rolesPtr The roles array
/// \param rolesLength The roles array length
/// \note The \p topLeft, \p bottomRight and \p rolesPtr arguments are owned by the caller thus they will not be deleted
DOS_API void DOS_CALL dos_qabstractitemmodel_dataChanged(DosQAbstractItemModel *vptr,
                                                         const DosQModelIndex *topLeft,
                                                         const DosQModelIndex *bottomRight,
                                                         int *rolesPtr, int rolesLength);

/// \brief Calls the createIndex function
DOS_API DosQModelIndex* DOS_CALL dos_qabstractitemmodel_createIndex(DosQAbstractItemModel *vptr,
                                                                    int row, int column, void *data = 0);
/// @}


/// \defgroup QObject QObject
/// \brief Functions related to the QObject class
/// @{

/// \brief Return QMetaObject associated to the QObject class
/// \return The QMetaObject of the QObject class
/// \note The returned QObject should be freed using dos_qmetaobject_delete().
DOS_API DosQMetaObject *DOS_CALL dos_qobject_qmetaobject();

/// \brief Create a new QObject
/// \param dObjectPointer The pointer of the QObject in the binded language
/// \param metaObject The QMetaObject associated to the given QObject
/// \param dObjectCallback The callback called from QML whenever a slot or property
/// should be in read, write or invoked
/// \return A new QObject
/// \note The returned QObject should be freed by calling dos_qobject_delete()
/// \note The \p dObjectPointer is usefull for forwarding a property read/slot to the correct
/// object in the binded language in the callback
DOS_API DosQObject *DOS_CALL dos_qobject_create(void *dObjectPointer,
                                                DosQMetaObject *metaObject,
                                                DObjectCallback dObjectCallback);

/// \brief Emit a signal definited in a QObject
/// \param vptr The QObject
/// \param name The signal name
/// \param parametersCount The number of parameters in the \p parameters array
/// \param parameters An array of DosQVariant with the values of signal arguments
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

/// \brief Return the DosQObject objectName
/// \param vptr The DosQObject pointer
/// \return A string in UTF8 format
/// \note The returned string should be freed using the dos_chararray_delete() function
DOS_API char *DOS_CALL dos_qobject_objectName(const DosQObject *vptr);

/// \brief Calls the QObject::setObjectName() function
/// \param vptr The QObject
/// \param name A pointer to an UTF-8 string
/// \note The \p name string is owned by the caller thus it will not be deleted
DOS_API void DOS_CALL dos_qobject_setObjectName(DosQObject *vptr, const char *name);

/// \brief Free the memory allocated for the QObject
/// \param vptr The QObject
DOS_API void DOS_CALL dos_qobject_delete(DosQObject *vptr);

/// @}


/// \defgroup QModelIndex QModelIndex
/// \brief Functions related to the QModelIndex class
/// @{

/// \brief Create a new QModelIndex()
/// \note The returned QModelIndex should be freed by calling the dos_qmodelindex_delete() function
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_create();

/// \brief Create a new QModelIndex() copy constructed with given index
/// \note The returned QModelIndex should be freed by calling the dos_qmodelindex_delete() function
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_create_qmodelindex(DosQModelIndex *index);

/// \brief Free the memory allocated for the QModelIndex
/// \param vptr The QModelIndex
DOS_API void DOS_CALL dos_qmodelindex_delete (DosQModelIndex *vptr);

/// \brief Calls the QModelIndex::row() function
/// \param vptr The QModelIndex
/// \return The QModelIndex row
DOS_API int  DOS_CALL dos_qmodelindex_row    (const DosQModelIndex *vptr);

/// \brief Calls the QModelIndex::column() function
/// \param vptr The QModelIndex
/// \return The QModelIndex column
DOS_API int  DOS_CALL dos_qmodelindex_column (const DosQModelIndex *vptr);

/// \brief Calls the QModelIndex::isvalid() function
/// \param vptr The QModelIndex
/// \return True if the QModelIndex is valid, false otherwise
DOS_API bool DOS_CALL dos_qmodelindex_isValid(const DosQModelIndex *vptr);

/// \brief Calls the QModelIndex::data() function
/// \param vptr The QModelIndex
/// \param role The model role to which we want the data
/// \return The QVariant associated at the given role
/// \note The returned QVariant should be freed by calling the dos_qvariant_delete() function
DOS_API DosQVariant *DOS_CALL dos_qmodelindex_data (const DosQModelIndex *vptr, int role);

/// \brief Calls the QModelIndex::parent() function
/// \param vptr The QModelIndex
/// \return The model parent QModelIndex
/// \note The returned QModelIndex should be freed by calling the dos_qmodelindex_delete() function
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_parent (const DosQModelIndex *vptr);

/// \brief Calls the QModelIndex::child() function
/// \param vptr The QModelIndex
/// \param row The child row
/// \param column The child column
/// \return The model child QModelIndex at the given \p row and \p column
/// \note The returned QModelIndex should be freed by calling the dos_qmodelindex_delete() function
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_child  (const DosQModelIndex *vptr, int row, int column);

/// \brief Calls the QModelIndex::sibling() function
/// \param vptr The QModelIndex
/// \param row The sibling row
/// \param column The sibling column
/// \return The model sibling QModelIndex at the given \p row and \p column
/// \note The returned QModelIndex should be freed by calling the dos_qmodelindex_delete() function
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_sibling(const DosQModelIndex *vptr, int row, int column);

/// \brief Calls the QModelIndex::operator=(const QModelIndex&) function
/// \param l The left side QModelIndex
/// \param r The right side QModelIndex
DOS_API void DOS_CALL dos_qmodelindex_assign (DosQModelIndex *l, const DosQModelIndex *r);

/// @}

/// \defgroup QHash QHash
/// \brief Functions related to the QHash class
/// @{

/// \brief Create a new QHash<int, QByteArray>
/// \return A new QHash<int, QByteArray>
/// \note The retuned QHash<int, QByteArray> should be freed using
/// the dos_qhash_int_qbytearray_delete(DosQHashIntQByteArray *) function
DOS_API DosQHashIntQByteArray *DOS_CALL dos_qhash_int_qbytearray_create();

/// \brief Free the memory allocated for the QHash<int, QByteArray>
/// \param vptr The QHash<int, QByteArray>
DOS_API void  DOS_CALL dos_qhash_int_qbytearray_delete(DosQHashIntQByteArray *vptr);

/// \brief Calls the QHash<int, QByteArray>::insert() function
/// \param vptr The QHash<int, QByteArray>
/// \param key The key
/// \param value The UTF-8 string
/// \note The \p value string is owned by the caller thus it will not be freed
DOS_API void  DOS_CALL dos_qhash_int_qbytearray_insert(DosQHashIntQByteArray *vptr, int key, const char *value);

/// \brief Calls the QHash<int, QByteArray>::value() function
/// \param vptr The QHash<int, QByteArray>
/// \param key The key to which retrive the value
/// \return The UTF-8 string associated to the given value
/// \note The returned string should be freed by calling the dos_chararray_delete() function
DOS_API char *DOS_CALL dos_qhash_int_qbytearray_value(const DosQHashIntQByteArray *vptr, int key);

/// @}

/// \defgroup QResource QResource
/// \brief Functions related to the QResource class
/// @{

/// Register the given .rcc (compiled) file in the resource system
DOS_API void DOS_CALL dos_qresource_register(const char *filename);

/// @}

/// \defgroup QUrl QUrl
/// \brief Functions related to the QUrl class
/// @{

/// \brief Create a new QUrl
/// \param url The UTF-8 string that represents an url
/// \param parsingMode The parsing mode
/// \note The retuned QUrl should be freed using the dos_qurl_delete() function
DOS_API DosQUrl *DOS_CALL dos_qurl_create(const char *url, int parsingMode);

/// \brief Free the memory allocated for the QUrl
/// \param vptr The QUrl to be freed
DOS_API void  DOS_CALL dos_qurl_delete(DosQUrl *vptr);

/// \brief Calls the QUrl::toString() function
/// \param vptr The QUrl
/// \return The url as an UTF-8 string
/// \note The returned string should be freed using the dos_chararray_delete() function
DOS_API char *DOS_CALL dos_qurl_to_string(const DosQUrl *vptr);

/// \brief Class the QUrl::isValid() function
/// \param vptr The QUrl
/// \return True if the QUrl is valid, false otherwise
DOS_API bool dos_qurl_isValid(const DosQUrl *vptr);

/// @}

/// \defgroup QDeclarative QDeclarative
/// \brief Functions related to the QDeclarative module
/// @{

/// \brief Register a type in order to be instantiable from QML
/// \return An integer value that represents the registration ID in the
/// qml environment
/// \note The \p qmlRegisterType is owned by the caller thus it will not be freed
DOS_API int DOS_CALL dos_qdeclarative_qmlregistertype(const QmlRegisterType *qmlRegisterType);

/// \brief Register a singleton type in order to be accessible from QML
/// \return An integer value that represents the registration ID in the
/// \note The \p qmlRegisterType is owned by the caller thus it will not be freed
DOS_API int DOS_CALL dos_qdeclarative_qmlregistersingletontype(const QmlRegisterType *qmlRegisterType);

/// @}

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
