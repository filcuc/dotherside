#ifndef DOTHERSIDE_WIDGETS_H
#define DOTHERSIDE_WIDGETS_H

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

#ifdef __cplusplus
}
#endif

#endif
