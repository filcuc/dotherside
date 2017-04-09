#include "DOtherSide/Core/Core.h"

#include <QCoreApplication>

char *convert_to_cstring(const QByteArray &array)
{
    return qstrdup(array.data());
}

char *convert_to_cstring(const QString &source)
{
    return convert_to_cstring(source.toUtf8());
}

char *dos_qcoreapplication_application_dir_path()
{
    return convert_to_cstring(QCoreApplication::applicationDirPath());
} 
