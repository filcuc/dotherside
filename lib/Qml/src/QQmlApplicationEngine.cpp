#include "DOtherSide/Qml/Qml.h"

#include <QCoreApplication>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlContext>

char *convert_to_cstring(const QByteArray &array)
{
    return qstrdup(array.data());
}

char *convert_to_cstring(const QString &source)
{
    return convert_to_cstring(source.toUtf8());
}

::DosQQmlApplicationEngine *dos_qqmlapplicationengine_create()
{
    return new QQmlApplicationEngine();
}

void dos_qqmlapplicationengine_load(::DosQQmlApplicationEngine *vptr, const char *filename)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    engine->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qqmlapplicationengine_load_url(::DosQQmlApplicationEngine *vptr, ::DosQUrl *url)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    auto qurl = static_cast<QUrl *>(url);
    engine->load(*qurl);
}

void dos_qqmlapplicationengine_load_data(::DosQQmlApplicationEngine *vptr, const char *data)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    engine->loadData(data);
}

void dos_qqmlapplicationengine_add_import_path(::DosQQmlApplicationEngine *vptr, const char *path)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    engine->addImportPath(QString(path));
}

::DosQQmlContext *dos_qqmlapplicationengine_context(::DosQQmlApplicationEngine *vptr)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    engine->rootContext();
    return engine->rootContext();
}

void dos_qqmlapplicationengine_delete(::DosQQmlApplicationEngine *vptr)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    delete engine;
}

char *dos_qqmlcontext_baseUrl(const ::DosQQmlContext *vptr)
{
    auto context = static_cast<const QQmlContext *>(vptr);
    QUrl url = context->baseUrl();
    return convert_to_cstring(url.toString());
}

void dos_qqmlcontext_setcontextproperty(::DosQQmlContext *vptr, const char *name, ::DosQVariant *value)
{
    auto context = static_cast<QQmlContext *>(vptr);
    auto variant = static_cast<QVariant *>(value);
    context->setContextProperty(QString::fromUtf8(name), *variant);
}
