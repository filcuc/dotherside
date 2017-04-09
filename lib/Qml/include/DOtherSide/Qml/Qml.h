#ifndef DOTHERSIDE_QML_H
#define DOTHERSIDE_QML_H

#ifdef WIN32
#define DOS_API   __declspec( dllexport )
#define DOS_CALL __cdecl
#else
#define DOS_API
#define DOS_CALL
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef void DosQQmlApplicationEngine;
typedef void DosQQmlContext;
typedef void DosQUrl;
typedef void DosQVariant;

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

#ifdef __cplusplus
}
#endif

#endif
