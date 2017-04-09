#ifndef DOTHERSIDE_QUICK_H
#define DOTHERSIDE_QUICK_H

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

#ifdef __cplusplus
}
#endif

#endif
