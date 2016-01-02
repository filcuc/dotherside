#include "DOtherSide/DOtherSide.h"

#include <iostream>

#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QModelIndex>
#include <QtCore/QHash>
#include <QtCore/QResource>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QtWidgets/QApplication>

#include "DOtherSide/DOtherSideTypesCpp.h"
#include "DOtherSide/OnSlotExecutedHandler.h"
#include "DOtherSide/DynamicQObjectFactory.h"
#include "DOtherSide/DynamicQObject.h"


void convert_to_cstring(const QString& source, char** destination)
{
    QByteArray array = source.toUtf8();
    *destination = qstrdup(array.data());
}

void dos_qcoreapplication_application_dir_path(char** result)
{
    convert_to_cstring(QCoreApplication::applicationDirPath(), result);
}

void dos_qguiapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char* argv[] = {empty};
    new QGuiApplication(argc, argv);
}

void dos_qguiapplication_delete()
{
    delete qApp;
}

void dos_qguiapplication_exec()
{
    qApp->exec();
}

void dos_qguiapplication_quit()
{
    qApp->quit();
}

void dos_qapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char* argv[] = {empty};
    new QApplication(argc, argv);
}

void dos_qapplication_delete()
{
    delete qApp;
}

void dos_qapplication_exec()
{
    qApp->exec();
}

void dos_qapplication_quit()
{
    qApp->quit();
}

void dos_qqmlapplicationengine_create(void** vptr)
{
    *vptr = new QQmlApplicationEngine();
}

void dos_qqmlapplicationengine_load(void* vptr, const char* filename)
{
    auto engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    engine->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qqmlapplicationengine_load_url(void* vptr, void* url)
{
    auto engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    auto qurl = reinterpret_cast<QUrl*>(url);
    engine->load(*qurl);
}

void dos_qqmlapplicationengine_load_data(void *vptr, const char *data)
{
    auto engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    engine->loadData(data);
}

void dos_qqmlapplicationengine_add_import_path(void* vptr, const char* path)
{
    auto engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    engine->addImportPath(QString(path));
}

void dos_qqmlapplicationengine_context(void* vptr, void** context)
{
    auto engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    engine->rootContext();
    *context = engine->rootContext();
}

void dos_qqmlapplicationengine_rootObjects(void* vptr, void*** array, int* array_length)
{
    auto engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    QList<QObject*> list = engine->rootObjects();
    auto objects = new QObject*[list.size()];
    if (objects == nullptr) return;
    for (int i = 0; i < list.length(); i += 1) objects[i] = list.at(i);
    *array = reinterpret_cast<void**>(objects);
    *array_length = list.length();
}

void dos_qqmlapplicationengine_delete(void* vptr)
{
    auto engine = reinterpret_cast<QQmlApplicationEngine*>(vptr);
    delete engine;
}

void dos_qquickview_create(void** vptr)
{
    *vptr = new QQuickView();
}

void dos_qquickview_show(void* vptr)
{
    auto view = reinterpret_cast<QQuickView*>(vptr);
    view->show();
}

void dos_qquickview_delete(void* vptr)
{
    auto view = reinterpret_cast<QQuickView*>(vptr);
    delete view;
}

void dos_qquickview_source(void* vptr, char** result)
{
    auto view = reinterpret_cast<QQuickView*>(vptr);
    QUrl url = view->source();
    convert_to_cstring(url.toString(), result);
}

void dos_qquickview_set_source(void* vptr, const char* filename)
{
    auto view = reinterpret_cast<QQuickView*>(vptr);
    view->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qquickview_set_source_url(void* vptr, void* url)
{
    auto view = reinterpret_cast<QQuickView*>(vptr);
    auto _url = reinterpret_cast<QUrl*>(url);
    view->setSource(*_url);
}

void dos_qquickview_set_resize_mode(void* vptr, int resizeMode)
{
    auto view = reinterpret_cast<QQuickView*>(vptr);
    view->setResizeMode((QQuickView::ResizeMode) resizeMode);
}

void dos_qquickview_rootContext(void* vptr, void** context)
{
    auto view = reinterpret_cast<QQuickView*>(vptr);
    *context = view->rootContext();
}

void dos_chararray_delete(char* ptr)
{
    if (ptr) delete[] ptr;
}

void dos_qobjectptr_array_delete(void** ptr)
{
    if (ptr) delete[] ptr;
}

void dos_qqmlcontext_baseUrl(void* vptr, char** result)
{
    auto context = reinterpret_cast<QQmlContext*>(vptr);
    QUrl url = context->baseUrl();
    convert_to_cstring(url.toString(), result);
}

void dos_qqmlcontext_setcontextproperty(void* vptr, const char* name, void* value)
{
    auto context = reinterpret_cast<QQmlContext*>(vptr);
    auto variant = reinterpret_cast<QVariant*>(value);
    context->setContextProperty(QString::fromUtf8(name), *variant);
}

void dos_qvariant_create(void** vptr)
{
    *vptr = new QVariant();
}

void dos_qvariant_create_int(void** vptr, int value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_bool(void** vptr, bool value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_string(void** vptr, const char* value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_qvariant(void** vptr, void* other)
{
    auto newQVariant = new QVariant();
    auto otherQVariant = reinterpret_cast<QVariant*>(other);
    *newQVariant = *otherQVariant;
    *vptr = newQVariant;
}

void dos_qvariant_create_qobject(void** vptr, void* value)
{
    auto qobject = reinterpret_cast<QObject*>(value);
    auto variant = new QVariant();
    variant->setValue<QObject*>(qobject);
    *vptr = variant;
}

void dos_qvariant_create_float(void** vptr, float value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_double(void** vptr, double value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_qabstractlistmodel(void** vptr, void* value)
{
    auto qobject = reinterpret_cast<QObject*>(value);
    auto variant = new QVariant();
    variant->setValue<QObject*>(qobject);
    *vptr = variant;
}

void dos_qvariant_isnull(void* vptr, bool* isNull)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *isNull = variant->isNull();
}

void dos_qvariant_delete(void* vptr)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    delete variant;
}

void dos_qvariant_assign(void* vptr, void* other)
{
    auto leftQVariant = reinterpret_cast<QVariant*>(vptr);
    auto rightQVariant = reinterpret_cast<QVariant*>(other);
    *leftQVariant = *rightQVariant;
}

void dos_qvariant_toInt(void* vptr, int* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->toInt();
}

void dos_qvariant_toBool(void* vptr, bool* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->toBool();
}

void dos_qvariant_toFloat(void* vptr, float* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->toFloat();
}

void dos_qvariant_toDouble(void* vptr, double* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->toDouble();
}

void dos_qvariant_toString(void* vptr, char** ptr)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    convert_to_cstring(variant->toString(), ptr);
}

void dos_qvariant_toQObject(void* vptr, void** value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *value = variant->value<QObject*>();
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

void dos_qvariant_setFloat(void* vptr, float value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setDouble(void* vptr, double value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setString(void* vptr, const char* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    *variant = value;
}

void dos_qvariant_setQObject(void* vptr, void* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    auto qobject = reinterpret_cast<QObject*>(value);
    variant->setValue<QObject*>(qobject);
}

void dos_qvariant_setQAbstractListModel(void* vptr, void* value)
{
    auto variant = reinterpret_cast<QVariant*>(vptr);
    auto qobject = reinterpret_cast<QObject*>(value);
    variant->setValue<QObject*>(qobject);
}

void dos_qobject_delete(void* vptr)
{
    auto qobject = reinterpret_cast<QObject*>(vptr);
    qobject->disconnect();
    delete qobject;
}

void dos_qobject_signal_emit(void* vptr, const char* name, int parametersCount, void** parameters)
{
    auto qobject = reinterpret_cast<QObject*>(vptr);
    auto dynamicQObject = dynamic_cast<DOS::IDynamicQObject*>(qobject);

    auto transformation = [](void* vptr)->QVariant{return *(reinterpret_cast<QVariant*>(vptr));};
    const std::vector<QVariant> variants = DOS::toVector(parameters, parametersCount, transformation);
    dynamicQObject->emitSignal(QString::fromStdString(name), variants);
}


void dos_qobject_signal_connect(void* senderVPtr,
                                const char* signal,
                                void* receiverVPtr,
                                const char* method,
                                int type,
                                bool* result)
{
    auto sender = reinterpret_cast<QObject*>(senderVPtr);
    auto receiver = reinterpret_cast<QObject*>(receiverVPtr);
    *result = QObject::connect(sender, signal, receiver, method, (Qt::ConnectionType) type);
}

void dos_qobject_signal_disconnect(void* senderVPtr,
                                   const char* signal,
                                   void* receiverVPtr,
                                   const char* method,
                                   bool* result)
{
    auto sender = reinterpret_cast<QObject*>(senderVPtr);
    auto receiver = reinterpret_cast<QObject*>(receiverVPtr);
    *result = QObject::disconnect(sender, signal, receiver, method);
}

void dos_qobject_objectName(void* vptr, char** result)
{
    auto object = reinterpret_cast<QObject*>(vptr);
    convert_to_cstring(object->objectName(), result);
}

void dos_qobject_findChild(void* vptr, const char* name, int options, void** child)
{
    auto object = reinterpret_cast<QObject*>(vptr);
    *child = object->findChild<QObject*>(QString::fromUtf8(name), (Qt::FindChildOptions) options);
}

void dos_qmodelindex_create(void** vptr)
{
    auto index = new QModelIndex();
    *vptr = index;
}

void dos_qmodelindex_delete(void* vptr)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    delete index;
}

void dos_qmodelindex_row(void* vptr, int* row)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    *row = index->row();
}

void dos_qmodelindex_column(void* vptr, int* column)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    *column = index->column();
}

void dos_qmodelindex_isValid(void* vptr, bool* isValid)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    *isValid = index->isValid();
}

void dos_qmodelindex_data(void* vptr, int role, void* data)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    auto result = reinterpret_cast<QVariant*>(data);
    *result = index->data(role);
}

void dos_qmodelindex_parent(void* vptr, void* parent)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    auto parentIndex = reinterpret_cast<QModelIndex*>(parent);
    *parentIndex = index->parent();
}

void dos_qmodelindex_child(void* vptr, int row, int column, void* child)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    auto childIndex = reinterpret_cast<QModelIndex*>(child);
    *childIndex = index->child(row, column);
}

void dos_qmodelindex_sibling(void* vptr, int row, int column, void* sibling)
{
    auto index = reinterpret_cast<QModelIndex*>(vptr);
    auto siblingIndex = reinterpret_cast<QModelIndex*>(sibling);
    *siblingIndex = index->sibling(row, column);
}

void dos_qhash_int_qbytearray_create(QHashIntQByteArrayVoidPtr* vptr)
{
    *vptr = new QHash<int, QByteArray>();
}

void dos_qhash_int_qbytearray_delete(QHashIntQByteArrayVoidPtr vptr)
{
    auto qHash = reinterpret_cast<QHash<int, QByteArray>*>(vptr);
    delete qHash;
}

void dos_qhash_int_qbytearray_insert(QHashIntQByteArrayVoidPtr vptr, int key, const char* value)
{
    auto qHash = reinterpret_cast<QHash<int, QByteArray>*>(vptr);
    qHash->insert(key, QByteArray(value));
}

void dos_qhash_int_qbytearray_value(QHashIntQByteArrayVoidPtr vptr, int key, char** result)
{
    auto qHash = reinterpret_cast<QHash<int, QByteArray>*>(vptr);
    QByteArray value = qHash->value(key);
    *result = qstrdup(value.data());
}

void dos_qresource_register(const char* filename)
{
    QResource::registerResource(QString::fromUtf8(filename));
}

void dos_qurl_create(void** vptr, const char* url, int parsingMode)
{
    *vptr = new QUrl(QString::fromUtf8(url), (QUrl::ParsingMode) parsingMode);
}

void dos_qurl_delete(void* vptr)
{
    auto url = reinterpret_cast<QUrl*>(vptr);
    delete url;
}

void dos_qurl_to_string(void* vptr, char** result)
{
    auto url = reinterpret_cast<QUrl*>(vptr);
    convert_to_cstring(url->toString(), result);
}


void dos_qmetaobjectfactory_create(void **vptr,
                               SignalDefinitions signalDefinitions,
                               SlotDefinitions slotDefinitions,
                               PropertyDefinitions propertyDefinitions)
{
    *vptr = new DOS::DynamicQObjectFactory(DOS::toVector(signalDefinitions),
                                           DOS::toVector(slotDefinitions),
                                           DOS::toVector(propertyDefinitions));
}

void dos_qmetaobjectfactory_delete(void *vptr)
{
    auto factory = reinterpret_cast<DOS::DynamicQObjectFactory*>(vptr);
    delete factory;
}
