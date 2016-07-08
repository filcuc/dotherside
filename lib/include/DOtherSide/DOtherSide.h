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
DOS_API void  DOS_CALL dos_qquickview_set_source_url(DosQQuickView *vptr, DosQUrl *url);

/// \brief Calls the QQuickView::setSource() function
/// \param vptr The QQuickView
/// \param filename The source path as an UTF-8 string. The path is relative to the directory
///  that contains the application executable
DOS_API void  DOS_CALL dos_qquickview_set_source(DosQQuickView *vptr, const char *filename);

/// \brief Calls the QQuickView::setResizeMode() function
/// \param vptr The QQuickView
/// \param resizeMode The resize mode
DOS_API void  DOS_CALL dos_qquickview_set_resize_mode(DosQQuickView *vptr, int resizeMode);

/// \brief Free the memory allocated for the given QQuickView
/// \param vptr The QQuickView
DOS_API void  DOS_CALL dos_qquickview_delete(DosQQuickView *vptr);

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

/// \brief Calls the QVariant::setValue<int>() function
/// \param vptr The QVariant
/// \param value The int value
DOS_API void   DOS_CALL dos_qvariant_setInt    (DosQVariant *vptr, int value);

/// \brief Calls the QVariant::setValue<bool>() function
/// \param vptr The QVariant
/// \param value The bool value
DOS_API void   DOS_CALL dos_qvariant_setBool   (DosQVariant *vptr, bool value);

/// \brief Calls the QVariant::setValue<float> function
/// \param vptr The QVariant
/// \param value The float value
DOS_API void   DOS_CALL dos_qvariant_setFloat  (DosQVariant *vptr, float value);

/// \brief Calls the QVariant::setValue<double> function
/// \param vptr The QVariant
/// \param value The double value
DOS_API void   DOS_CALL dos_qvariant_setDouble (DosQVariant *vptr, double value);

/// \brief Calls the QVariant::setValue<QString> function
/// \param vptr The QVariant
/// \param value The string value
/// \note The string argument is copied inside the QVariant and it will not be deleted
DOS_API void   DOS_CALL dos_qvariant_setString (DosQVariant *vptr, const char *value);

/// \brief Calls the QVariant::setValue<QObject*> function
/// \param vptr The QVariant
/// \param value The string value
/// \note The string argument is copied inside the QVariant and it will not be deleted
DOS_API void   DOS_CALL dos_qvariant_setQObject(DosQVariant *vptr, DosQObject *value);

/// \brief Calls the QVariant::isNull function
/// \return True if the QVariant is null, false otherwise
/// \param vptr The QVariant
DOS_API bool   DOS_CALL dos_qvariant_isnull    (const DosQVariant *vptr);

/// \brief Free the memory allocated for the given QVariant
/// \param vptr The QVariant
DOS_API void   DOS_CALL dos_qvariant_delete    (DosQVariant *vptr);

/// \brief Calls the QVariant::operator=(const QVariant&) function
/// \param vptr The QVariant (left side)
/// \param other The QVariant (right side)
DOS_API void   DOS_CALL dos_qvariant_assign    (DosQVariant *vptr, const DosQVariant *other);

/// \brief Calls the QVariant::value<int>() function
/// \param vptr The QVariant
/// \return The int value
DOS_API int    DOS_CALL dos_qvariant_toInt     (const DosQVariant *vptr);

/// \brief Calls the QVariant::value<bool>() function
/// \param vptr The QVariant
/// \return The bool value
DOS_API bool   DOS_CALL dos_qvariant_toBool    (const DosQVariant *vptr);

/// \brief Calls the QVariant::value<QString>() function
/// \param vptr The QVariant
/// \return The string value
/// \note The returned string should be freed by using dos_chararray_delete()
DOS_API char  *DOS_CALL dos_qvariant_toString  (const DosQVariant *vptr);

/// \brief Calls the QVariant::value<float>() function
/// \param vptr The QVariant
/// \return The float value
DOS_API float  DOS_CALL dos_qvariant_toFloat   (const DosQVariant *vptr);

/// \brief Calls the QVariant::value<double>() function
/// \param vptr The QVariant
/// \return The double value
DOS_API double DOS_CALL dos_qvariant_toDouble  (const DosQVariant *vptr);

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
/// \param className The class name
/// \param signalDefinitions The SignalDefinitions
/// \param slotDefinitions The SlotDefinitions struct
/// \param propertyDefinitions The PropertyDefinitions struct
/// \note The returned QMetaObject should be freed using dos_qmetaobject_delete().
DOS_API DosQMetaObject *DOS_CALL dos_qmetaobject_create(DosQMetaObject *superClassMetaObject,
                                                        const char *className,
                                                        const SignalDefinitions *signalDefinitions,
                                                        const SlotDefinitions *slotDefinitions,
                                                        const PropertyDefinitions *propertyDefinitions);


/// \brief Free the memory allocated for the given QMetaObject
/// \param vptr The QMetaObject
DOS_API void DOS_CALL dos_qmetaobject_delete(DosQMetaObject *vptr);

/// @}

/// \defgroup QAbstractListModel QAbstractListModel
/// \brief Functions related to the QAbstractListModel class
/// @{

/// \brief Return QMetaObject associated to the QAbstractListModel class
/// \return The QMetaObject of the QAbstractListModel class
/// \note The returned QMetaObject should be freed using dos_qmetaobject_delete().
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



/**
 * \brief Emit the dataChanged signal
 * \param vptr The DosQAbstractListModel pointer
 * \param topLeft The topLeft DosQModelIndex. The index is owned by the caller thus it will not be deleted
 * \param bottomRight The bottomright DosQModelIndex. The index is owned by the caller thus it will not be deleted
 * \param rolesPtr The roles array. The pointer is owned by the caller and thus it will not be deleted
 * \param rolesLength The roles array length
 */
DOS_API void DOS_CALL dos_qabstractlistmodel_dataChanged(DosQAbstractListModel *vptr,
                                                         const DosQModelIndex *topLeft,
                                                         const DosQModelIndex *bottomRight,
                                                         int *rolesPtr, int rolesLength);

/// @}


/// \defgroup QObject QObject
/// \brief Functions related to the QObject class
/// @{

/// \brief Return QMetaObject associated to the QObject class
/// \return The QMetaObject of the QObject class
/// \note The returned QObject should be freed using dos_qmetaobject_delete().
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


/// \brief Return the DosQObject objectName
/// \param vptr The DosQObject pointer
/// \return A string in UTF8 format
/// \note The returned string should be freed using the dos_chararray_delete function
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

DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_create();
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_create_qmodelindex(DosQModelIndex *index);
DOS_API void DOS_CALL dos_qmodelindex_delete (DosQModelIndex *vptr);
DOS_API int  DOS_CALL dos_qmodelindex_row    (const DosQModelIndex *vptr);
DOS_API int  DOS_CALL dos_qmodelindex_column (const DosQModelIndex *vptr);
DOS_API bool DOS_CALL dos_qmodelindex_isValid(const DosQModelIndex *vptr);
DOS_API DosQVariant *DOS_CALL dos_qmodelindex_data (const DosQModelIndex *vptr, int role);
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_parent (const DosQModelIndex *vptr);
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_child  (const DosQModelIndex *vptr, int row, int column);
DOS_API DosQModelIndex *DOS_CALL dos_qmodelindex_sibling(const DosQModelIndex *vptr, int row, int column);
DOS_API void DOS_CALL dos_qmodelindex_assign (DosQModelIndex *l, const DosQModelIndex *r);

/// @}

// QHash<int, QByteArray>
DOS_API DosQHashIntQByteArray *DOS_CALL dos_qhash_int_qbytearray_create();
DOS_API void  DOS_CALL dos_qhash_int_qbytearray_delete(DosQHashIntQByteArray *vptr);
DOS_API void  DOS_CALL dos_qhash_int_qbytearray_insert(DosQHashIntQByteArray *vptr, int key, const char *value);
DOS_API char *DOS_CALL dos_qhash_int_qbytearray_value (DosQHashIntQByteArray *vptr, int key);

// QResource
DOS_API void DOS_CALL dos_qresource_register(const char *filename);

// QUrl
DOS_API DosQUrl *DOS_CALL dos_qurl_create(const char *url, int parsingMode);
DOS_API void  DOS_CALL dos_qurl_delete(DosQUrl *vptr);
DOS_API char *DOS_CALL dos_qurl_to_string(const DosQUrl *vptr);
DOS_API bool dos_qurl_isValid(const DosQUrl *vptr);

// QDeclarative
DOS_API int DOS_CALL dos_qdeclarative_qmlregistertype(const QmlRegisterType *qmlRegisterType);
DOS_API int DOS_CALL dos_qdeclarative_qmlregistersingletontype(const QmlRegisterType *qmlRegisterType);

#ifdef __cplusplus
}
#endif

#endif // DOTHERSIDE_H
