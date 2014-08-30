#include "DOtherSide.h"

#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>
#include <QtCore/QDir>
#include <QtCore/QDebug>

#include "DynamicQObject.h"

void convert_to_cstring(const QString& source, CharPtr& destination, int& length)
{
    QByteArray array = source.toUtf8();
    destination = qstrdup(array.data());
    length = qstrlen(array.data());
}

void dos_guiapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char* argv[] = {empty};
    new QGuiApplication(argc, argv);
}

void dos_guiapplication_delete()
{
    delete qApp;
}

void dos_guiapplication_exec()
{
    qApp->exec();
}

void dos_quickview_create(void** vptr)
{
    *vptr = new QQuickView();
}

void dos_quickview_show(void* vptr)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    view->show();
}

void dos_quickview_delete(void* vptr)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    delete view;
}

void dos_quickview_source(void *vptr, CharPtr& result, int& length)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    QUrl url = view->source();
    convert_to_cstring(url.toString(), result, length);
}

void dos_quickview_set_source(void* vptr, const char* filename)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    view->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_quickview_rootContext(void* vptr, void** context)
{
    QQuickView* view = reinterpret_cast<QQuickView*>(vptr);
    *context = view->rootContext();
}

void dos_chararray_create(CharPtr& ptr)
{
    ptr = 0;
}

void dos_chararray_create(CharPtr& ptr, int size)
{
    if (size > 0)
        ptr = new char[size];
    else
        ptr = 0;
}

void dos_chararray_delete(CharPtr &ptr)
{
    if (ptr) delete[] ptr;
}

void dos_qmlcontext_baseUrl(void* vptr, CharPtr& result, int& length)
{
    QQmlContext* context = reinterpret_cast<QQmlContext*>(vptr);
    QUrl url = context->baseUrl();
    convert_to_cstring(url.toString(), result, length);
}

void dos_qmlcontext_setcontextproperty(void* vptr, const char* name, void* value)
{
    QQmlContext* context = reinterpret_cast<QQmlContext*>(vptr);
    auto variant = reinterpret_cast<QVariant*>(value);
    context->setContextProperty(QString::fromUtf8(name), *variant);
}

void dos_qvariant_create(void **vptr)
{
    *vptr = new QVariant();
}

void dos_qvariant_create_int(void **vptr, int value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_bool(void **vptr, bool value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_string(void** vptr, const char* value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_qobject(void **vptr, void* value)
{
    auto qobject = reinterpret_cast<QObject*>(value);
    auto variant = new QVariant();
    variant->setValue<QObject*>(qobject);
    *vptr = variant;
}

void dos_qvariant_isnull(void* vptr, bool& isNull)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    isNull = variant->isNull();
}

void dos_qvariant_delete(void *vptr)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    delete variant;
}

void dos_qvariant_toInt(void* vptr, int& value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    value = variant->toInt();
}

void dos_qvariant_toBool(void* vptr, bool& value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    value = variant->toBool();
}

void dos_qvariant_toString(void* vptr, CharPtr& ptr, int& size)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    convert_to_cstring(variant->toString(), ptr, size);
}

void dos_qvariant_setInt(void* vptr, int value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setBool(void* vptr, bool value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setString(void* vptr, const char* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qobject_create(void** vptr, void* dObjectPointer, DObjectCallback dObjectCallback)
{
    auto dynamicQObject = new DynamicQObject();
    dynamicQObject->setDObjectPointer(dObjectPointer);
    dynamicQObject->setDObjectCallback(dObjectCallback);
    *vptr = dynamicQObject;
}

void dos_qobject_delete(void *vptr)
{
    auto dynamicQObject = reinterpret_cast<DynamicQObject*>(vptr);
    delete dynamicQObject;
}

void dos_qobject_slot_create(void* vptr, const char* name, int parametersCount, int* parametersMetaTypes, int* slotIndex)
{
    if (parametersCount <= 0)
        return;

    auto dynamicQObject = reinterpret_cast<DynamicQObject*>(vptr);

    QMetaType::Type returnType = static_cast<QMetaType::Type>(parametersMetaTypes[0]);
    QList<QMetaType::Type> argumentsTypes;
    for (int i = 1; i < parametersCount; ++i)
        argumentsTypes << static_cast<QMetaType::Type>(parametersMetaTypes[i]);

    dynamicQObject->registerSlot(QString::fromStdString(name), returnType, argumentsTypes, *slotIndex);
}

void dos_qobject_signal_create(void* vptr, const char* name, int parametersCount, int* parametersMetaTypes, int* signalIndex)
{
    if (parametersCount <= 0)
        return;

    auto dynamicQObject = reinterpret_cast<DynamicQObject*>(vptr);

    QList<QMetaType::Type> argumentsTypes;
    for (int i = 0; i < parametersCount; ++i)
        argumentsTypes << static_cast<QMetaType::Type>(parametersMetaTypes[i]);

    dynamicQObject->registerSignal(QString::fromStdString(name), argumentsTypes, *signalIndex);

    qDebug() << "C++: registered the" << name << "signal";
}

void dos_qobject_signal_emit(void* vptr, const char* name, int parametersCount, void** parameters)
{
    auto dynamicQObject = reinterpret_cast<DynamicQObject*>(vptr);
    QVariantList arguments;
    for (int i = 0; i < parametersCount; ++i)
        arguments << *(reinterpret_cast<QVariant*>(parameters[i]));
    dynamicQObject->emitSignal(QString::fromStdString(name), arguments);
}
