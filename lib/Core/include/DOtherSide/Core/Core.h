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

typedef void DosQObject;
typedef void DosQVariant;

/// \brief Store an array of QVariant
/// \note This struct should be freed by calling dos_qvariantarray_delete(DosQVariantArray *ptr). This in turn
/// cleans up the internal array
struct DosQVariantArray {
    /// The number of elements
    int size;
    /// The array
    DosQVariant **data;
};

#ifndef __cplusplus
typedef struct DosQVariantArray DosQVariantArray;
#endif

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
DOS_API DosQVariant *DOS_CALL dos_qvariant_create_array(int size, DosQVariant **array);

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
DOS_API void DOS_CALL dos_qvariant_setArray(DosQVariant *vptr, int size, DosQVariant **array);

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
DOS_API DosQVariantArray *DOS_CALL dos_qvariant_toArray(const DosQVariant *vptr);

/// \brief Calls the QVariant::value<QObject*>() function
/// \param vptr The QVariant
/// \return The QObject* value
/// \note Storing the returned QObject* is higly dengerous and depends on how you managed the memory
/// of QObjects in the binded language
DOS_API DosQObject *DOS_CALL dos_qvariant_toQObject(const DosQVariant *vptr);

/// @}

#ifdef __cplusplus
}
#endif

#endif
