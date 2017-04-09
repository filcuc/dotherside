#ifndef DOTHERSIDE_CORE_H
#define DOTHERSIDE_CORE_H

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

/// \brief Return the QCore::applicationDirPath
/// \return The QCore::applicationDirPath as a UTF-8 string
/// \note The returned string should be deleted by the calling code by using
/// the dos_chararray_delete() function
DOS_API char *DOS_CALL dos_qcoreapplication_application_dir_path();

#ifdef __cplusplus
}
#endif

#endif
