#ifndef DOTHERSIDE_GUI_H
#define DOTHERSIDE_GUI_H

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

#ifdef __cplusplus
}
#endif

#endif

