#include "DOtherSide/Core/Core.h"

#include <QVariant>

char *convert_to_cstring(const QByteArray &array)
{
    return qstrdup(array.data());
}

char *convert_to_cstring(const QString &source)
{
    return convert_to_cstring(source.toUtf8());
}

void dos_qvariantarray_delete(DosQVariantArray *ptr)
{
    if (!ptr || !ptr->data)
        return;
    // Delete each variant
    for (int i = 0; i < ptr->size; ++i)
        dos_qvariant_delete(ptr->data[i]);
    // Delete the array
    delete[] ptr->data;
    ptr->data = nullptr;
    ptr->size = 0;
    // Delete the wrapped struct
    delete ptr;
}

::DosQVariant *dos_qvariant_create()
{
    return new QVariant();
}

::DosQVariant *dos_qvariant_create_int(int value)
{
    return new QVariant(value);
}

::DosQVariant *dos_qvariant_create_bool(bool value)
{
    return new QVariant(value);
}

::DosQVariant *dos_qvariant_create_string(const char *value)
{
    return new QVariant(value);
}

::DosQVariant *dos_qvariant_create_qvariant(const ::DosQVariant *other)
{
    auto otherQVariant = static_cast<const QVariant *>(other);
    auto result = new QVariant();
    *result = *otherQVariant;
    return result;
}

::DosQVariant *dos_qvariant_create_qobject(::DosQObject *value)
{
    auto qobject = static_cast<QObject *>(value);
    auto result = new QVariant();
    result->setValue<QObject *>(qobject);
    return result;
}

::DosQVariant *dos_qvariant_create_float(float value)
{
    return new QVariant(value);
}

::DosQVariant *dos_qvariant_create_double(double value)
{
    return new QVariant(value);
}

::DosQVariant *dos_qvariant_create_array(int size, ::DosQVariant **array)
{
    QList<QVariant> data;
    data.reserve(size);
    for (int i = 0; i < size; ++i)
        data << *(static_cast<QVariant *>(array[i]));
    return new QVariant(data);
}

bool dos_qvariant_isnull(const DosQVariant *vptr)
{
    auto variant = static_cast<const QVariant *>(vptr);
    return variant->isNull();
}

void dos_qvariant_delete(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    delete variant;
}

void dos_qvariant_assign(::DosQVariant *vptr, const DosQVariant *other)
{
    auto leftQVariant = static_cast<QVariant *>(vptr);
    auto rightQVariant = static_cast<const QVariant *>(other);
    *leftQVariant = *rightQVariant;
}

int dos_qvariant_toInt(const ::DosQVariant *vptr)
{
    auto variant = static_cast<const QVariant *>(vptr);
    return variant->toInt();
}

bool dos_qvariant_toBool(const ::DosQVariant *vptr)
{
    auto variant = static_cast<const QVariant *>(vptr);
    return variant->toBool();
}

float dos_qvariant_toFloat(const DosQVariant *vptr)
{
    auto variant = static_cast<const QVariant *>(vptr);
    return variant->toFloat();
}

double dos_qvariant_toDouble(const DosQVariant *vptr)
{
    auto variant = static_cast<const QVariant *>(vptr);
    return variant->toDouble();
}

char *dos_qvariant_toString(const DosQVariant *vptr)
{
    auto variant = static_cast<const QVariant *>(vptr);
    return convert_to_cstring(variant->toString());
}

DosQVariantArray *dos_qvariant_toArray(const DosQVariant *vptr)
{
    auto variant = static_cast<const QVariant *>(vptr);
    QVariantList data = variant->toList();
    auto result = new DosQVariantArray();
    result->size = data.size();
    result->data = new DosQVariant*[result->size];
    for (int i = 0; i < result->size; ++i)
        result->data[i] = new QVariant(data[i]);
    return result;
}

::DosQObject *dos_qvariant_toQObject(const DosQVariant *vptr)
{
    auto variant = static_cast<const QVariant *>(vptr);
    return variant->value<QObject *>();
}

void dos_qvariant_setInt(::DosQVariant *vptr, int value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setBool(::DosQVariant *vptr, bool value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setFloat(::DosQVariant *vptr, float value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setDouble(::DosQVariant *vptr, double value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setString(::DosQVariant *vptr, const char *value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setQObject(::DosQVariant *vptr, ::DosQObject *value)
{
    auto variant = static_cast<QVariant *>(vptr);
    auto qobject = static_cast<QObject *>(value);
    variant->setValue<QObject *>(qobject);
}

void dos_qvariant_setArray(::DosQVariant *vptr, int size, ::DosQVariant **array)
{
    auto variant = static_cast<QVariant *>(vptr);
    QVariantList data;
    data.reserve(size);
    for (int i = 0; i < size; ++i)
        data << *(static_cast<QVariant *>(array[i]));
    variant->setValue(data);
}
