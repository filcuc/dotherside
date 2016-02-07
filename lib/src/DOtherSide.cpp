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
#include "DOtherSide/DosQMetaObject.h"
#include "DOtherSide/DosQObject.h"
#include "DOtherSide/DosQObjectImpl.h"
#include "DOtherSide/DosQAbstractListModel.h"
#include "DOtherSide/DosQObjectWrapper.h"

using namespace DOS;


void convert_to_cstring(const QString &source, char **destination)
{
    QByteArray array = source.toUtf8();
    *destination = qstrdup(array.data());
}

void dos_qcoreapplication_application_dir_path(char **result)
{
    convert_to_cstring(QCoreApplication::applicationDirPath(), result);
}

void dos_qguiapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char *argv[] = {empty};
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
    static char *argv[] = {empty};
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

void dos_qqmlapplicationengine_create(void **vptr)
{
    *vptr = new QQmlApplicationEngine();
}

void dos_qqmlapplicationengine_load(void *vptr, const char *filename)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    engine->load(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qqmlapplicationengine_load_url(void *vptr, void *url)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    auto qurl = static_cast<QUrl *>(url);
    engine->load(*qurl);
}

void dos_qqmlapplicationengine_load_data(void *vptr, const char *data)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    engine->loadData(data);
}

void dos_qqmlapplicationengine_add_import_path(void *vptr, const char *path)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    engine->addImportPath(QString(path));
}

void dos_qqmlapplicationengine_context(void *vptr, void **context)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    engine->rootContext();
    *context = engine->rootContext();
}

void dos_qqmlapplicationengine_delete(void *vptr)
{
    auto engine = static_cast<QQmlApplicationEngine *>(vptr);
    delete engine;
}

void dos_qquickview_create(void **vptr)
{
    *vptr = new QQuickView();
}

void dos_qquickview_show(void *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->show();
}

void dos_qquickview_delete(void *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    delete view;
}

void dos_qquickview_source(void *vptr, char **result)
{
    auto view = static_cast<QQuickView *>(vptr);
    QUrl url = view->source();
    convert_to_cstring(url.toString(), result);
}

void dos_qquickview_set_source(void *vptr, const char *filename)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qquickview_set_source_url(void *vptr, void *url)
{
    auto view = static_cast<QQuickView *>(vptr);
    auto _url = static_cast<QUrl *>(url);
    view->setSource(*_url);
}

void dos_qquickview_set_resize_mode(void *vptr, int resizeMode)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->setResizeMode((QQuickView::ResizeMode) resizeMode);
}

void dos_qquickview_rootContext(void *vptr, void **context)
{
    auto view = static_cast<QQuickView *>(vptr);
    *context = view->rootContext();
}

void dos_chararray_delete(char *ptr)
{
    if (ptr) delete[] ptr;
}

void dos_qqmlcontext_baseUrl(void *vptr, char **result)
{
    auto context = static_cast<QQmlContext *>(vptr);
    QUrl url = context->baseUrl();
    convert_to_cstring(url.toString(), result);
}

void dos_qqmlcontext_setcontextproperty(void *vptr, const char *name, void *value)
{
    auto context = static_cast<QQmlContext *>(vptr);
    auto variant = static_cast<QVariant *>(value);
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

void dos_qvariant_create_string(void **vptr, const char *value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_qvariant(void **vptr, void *other)
{
    auto newQVariant = new QVariant();
    auto otherQVariant = static_cast<QVariant *>(other);
    *newQVariant = *otherQVariant;
    *vptr = newQVariant;
}

void dos_qvariant_create_qobject(void **vptr, void *value)
{
    auto qobject = static_cast<QObject *>(value);
    auto variant = new QVariant();
    variant->setValue<QObject *>(qobject);
    *vptr = variant;
}

void dos_qvariant_create_float(void **vptr, float value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_create_double(void **vptr, double value)
{
    *vptr = new QVariant(value);
}

void dos_qvariant_isnull(void *vptr, bool *isNull)
{
    auto variant = static_cast<QVariant *>(vptr);
    *isNull = variant->isNull();
}

void dos_qvariant_delete(void *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    delete variant;
}

void dos_qvariant_assign(void *vptr, void *other)
{
    auto leftQVariant = static_cast<QVariant *>(vptr);
    auto rightQVariant = static_cast<QVariant *>(other);
    *leftQVariant = *rightQVariant;
}

void dos_qvariant_toInt(void *vptr, int *value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *value = variant->toInt();
}

void dos_qvariant_toBool(void *vptr, bool *value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *value = variant->toBool();
}

void dos_qvariant_toFloat(void *vptr, float *value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *value = variant->toFloat();
}

void dos_qvariant_toDouble(void *vptr, double *value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *value = variant->toDouble();
}

void dos_qvariant_toString(void *vptr, char **ptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    convert_to_cstring(variant->toString(), ptr);
}

void dos_qvariant_toQObject(void *vptr, void **value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *value = variant->value<QObject *>();
}

void dos_qvariant_setInt(void *vptr, int value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setBool(void *vptr, bool value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setFloat(void *vptr, float value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setDouble(void *vptr, double value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setString(void *vptr, const char *value)
{
    auto variant = static_cast<QVariant *>(vptr);
    *variant = value;
}

void dos_qvariant_setQObject(void *vptr, void *value)
{
    auto variant = static_cast<QVariant *>(vptr);
    auto qobject = static_cast<QObject *>(value);
    variant->setValue<QObject *>(qobject);
}

void dos_qobject_qmetaobject(void **vptr)
{
    *vptr = new DosIQMetaObjectHolder(std::make_shared<DosQObjectMetaObject>());
}

void dos_qobject_create(void **vptr, void *dObjectPointer, void *metaObject,
                        DObjectCallback dObjectCallback)
{
    auto metaObjectHolder = static_cast<DosIQMetaObjectHolder *>(metaObject);
    auto dosQObject = new DosQObject(metaObjectHolder->data(),
                                     OnSlotExecutedHandler(dObjectPointer, dObjectCallback));
    QQmlEngine::setObjectOwnership(dosQObject, QQmlEngine::CppOwnership);
    *vptr = static_cast<QObject*>(dosQObject);
}

void dos_qobject_delete(void *vptr)
{
    auto qobject = static_cast<QObject *>(vptr);
    qobject->disconnect();
    delete qobject;
}

void dos_qobject_signal_emit(void *vptr, const char *name, int parametersCount, void **parameters)
{
    auto qobject = static_cast<QObject *>(vptr);
    auto dynamicQObject = dynamic_cast<DosIQObjectImpl *>(qobject);

    auto transformation = [](void *vptr)->QVariant{return *(static_cast<QVariant *>(vptr));};
    const std::vector<QVariant> variants = toVector(parameters, parametersCount, transformation);
    dynamicQObject->emitSignal(QString::fromStdString(name), variants);
}

void dos_qobject_signal_connect(void *senderVPtr,
                                const char *signal,
                                void *receiverVPtr,
                                const char *method,
                                int type,
                                bool *result)
{
    auto sender = static_cast<QObject *>(senderVPtr);
    auto receiver = static_cast<QObject *>(receiverVPtr);
    *result = QObject::connect(sender, signal, receiver, method, (Qt::ConnectionType) type);
}

void dos_qobject_signal_disconnect(void *senderVPtr,
                                   const char *signal,
                                   void *receiverVPtr,
                                   const char *method,
                                   bool *result)
{
    auto sender = static_cast<QObject *>(senderVPtr);
    auto receiver = static_cast<QObject *>(receiverVPtr);
    *result = QObject::disconnect(sender, signal, receiver, method);
}

void dos_qobject_objectName(void *vptr, char **result)
{
    auto object = static_cast<QObject *>(vptr);
    convert_to_cstring(object->objectName(), result);
}

void dos_qobject_setObjectName(void *vptr, const char* name)
{
    auto object = static_cast<QObject *>(vptr);
    object->setObjectName(QString::fromUtf8(name));
}

void dos_qmodelindex_create(void **vptr)
{
    auto index = new QModelIndex();
    *vptr = index;
}

void dos_qmodelindex_delete(void *vptr)
{
    auto index = static_cast<QModelIndex *>(vptr);
    delete index;
}

void dos_qmodelindex_row(void *vptr, int *row)
{
    auto index = static_cast<QModelIndex *>(vptr);
    *row = index->row();
}

void dos_qmodelindex_column(void *vptr, int *column)
{
    auto index = static_cast<QModelIndex *>(vptr);
    *column = index->column();
}

void dos_qmodelindex_isValid(void *vptr, bool *isValid)
{
    auto index = static_cast<QModelIndex *>(vptr);
    *isValid = index->isValid();
}

void dos_qmodelindex_data(void *vptr, int role, void *data)
{
    auto index = static_cast<QModelIndex *>(vptr);
    auto result = static_cast<QVariant *>(data);
    *result = index->data(role);
}

void dos_qmodelindex_parent(void *vptr, void *parent)
{
    auto index = static_cast<QModelIndex *>(vptr);
    auto parentIndex = static_cast<QModelIndex *>(parent);
    *parentIndex = index->parent();
}

void dos_qmodelindex_child(void *vptr, int row, int column, void *child)
{
    auto index = static_cast<QModelIndex *>(vptr);
    auto childIndex = static_cast<QModelIndex *>(child);
    *childIndex = index->child(row, column);
}

void dos_qmodelindex_sibling(void *vptr, int row, int column, void *sibling)
{
    auto index = static_cast<QModelIndex *>(vptr);
    auto siblingIndex = static_cast<QModelIndex *>(sibling);
    *siblingIndex = index->sibling(row, column);
}

void dos_qhash_int_qbytearray_create(QHashIntQByteArrayVoidPtr *vptr)
{
    *vptr = new QHash<int, QByteArray>();
}

void dos_qhash_int_qbytearray_delete(QHashIntQByteArrayVoidPtr vptr)
{
    auto qHash = static_cast<QHash<int, QByteArray>*>(vptr);
    delete qHash;
}

void dos_qhash_int_qbytearray_insert(QHashIntQByteArrayVoidPtr vptr, int key, const char *value)
{
    auto qHash = static_cast<QHash<int, QByteArray>*>(vptr);
    qHash->insert(key, QByteArray(value));
}

void dos_qhash_int_qbytearray_value(QHashIntQByteArrayVoidPtr vptr, int key, char **result)
{
    auto qHash = static_cast<QHash<int, QByteArray>*>(vptr);
    QByteArray value = qHash->value(key);
    *result = qstrdup(value.data());
}

void dos_qresource_register(const char *filename)
{
    QResource::registerResource(QString::fromUtf8(filename));
}

void dos_qurl_create(void **vptr, const char *url, int parsingMode)
{
    *vptr = new QUrl(QString::fromUtf8(url), (QUrl::ParsingMode) parsingMode);
}

void dos_qurl_delete(void *vptr)
{
    auto url = static_cast<QUrl *>(vptr);
    delete url;
}

void dos_qurl_to_string(void *vptr, char **result)
{
    auto url = static_cast<QUrl *>(vptr);
    convert_to_cstring(url->toString(), result);
}

void dos_qmetaobject_create(void **vptr,
                            void *superClassVPtr,
                            const char *className,
                            ::SignalDefinitions signalDefinitions,
                            ::SlotDefinitions slotDefinitions,
                            ::PropertyDefinitions propertyDefinitions)
{
    Q_ASSERT(superClassVPtr);
    auto superClassHolder = static_cast<DosIQMetaObjectHolder *>(superClassVPtr);
    Q_ASSERT(superClassHolder);
    auto data = superClassHolder->data();
    Q_ASSERT(data);

    auto metaObject = std::make_shared<DosQMetaObject>(data,
                                                       QString::fromUtf8(className),
                                                       toVector(signalDefinitions),
                                                       toVector(slotDefinitions),
                                                       toVector(propertyDefinitions));
    *vptr = new DosIQMetaObjectHolder(std::move(metaObject));
}

void dos_qmetaobject_delete(void *vptr)
{
    auto factory = static_cast<DosIQMetaObjectHolder *>(vptr);
    delete factory;
}

void dos_qabstractlistmodel_qmetaobject(void **vptr)
{
    *vptr = new DosIQMetaObjectHolder(std::make_shared<DosQAbstractListModelMetaObject>());
}

void dos_qabstractlistmodel_create(void **vptr,
                                   void *dObjectPointer,
                                   void *metaObjectPointer,
                                   DObjectCallback dObjectCallback,
                                   RowCountCallback rowCountCallback,
                                   ColumnCountCallback columnCountCallback,
                                   DataCallback dataCallback,
                                   SetDataCallback setDataCallback,
                                   RoleNamesCallback roleNamesCallaback,
                                   FlagsCallback flagsCallback,
                                   HeaderDataCallback headerDataCallback)
{
    auto metaObjectHolder = static_cast<DosIQMetaObjectHolder *>(metaObjectPointer);
    auto model = new DosQAbstractListModel(dObjectPointer,
                                           metaObjectHolder->data(),
                                           OnSlotExecutedHandler(dObjectPointer, dObjectCallback),
                                           rowCountCallback,
                                           columnCountCallback,
                                           dataCallback,
                                           setDataCallback,
                                           roleNamesCallaback,
                                           flagsCallback,
                                           headerDataCallback);
    QQmlEngine::setObjectOwnership(model, QQmlEngine::CppOwnership);
    *vptr = static_cast<QObject*>(model);
}

void dos_qabstractlistmodel_delete(void *vptr)
{
    auto model = static_cast<DosQAbstractListModel *>(vptr);
    delete model;
}

void dos_qabstractlistmodel_beginInsertRows(void *vptr, QModelIndexVoidPtr parentIndex, int first, int last)
{
    auto model = static_cast<DosQAbstractListModel *>(vptr);
    auto index = static_cast<QModelIndex *>(parentIndex);
    model->publicBeginInsertRows(*index, first, last);
}

void dos_qabstractlistmodel_endInsertRows(void *vptr)
{
    auto model = static_cast<DosQAbstractListModel *>(vptr);
    model->publicEndInsertRows();
}

void dos_qabstractlistmodel_beginRemoveRows(void *vptr, QModelIndexVoidPtr parentIndex, int first, int last)
{
    auto model = static_cast<DosQAbstractListModel *>(vptr);
    auto index = static_cast<QModelIndex *>(parentIndex);
    model->publicBeginRemoveRows(*index, first, last);
}

void dos_qabstractlistmodel_endRemoveRows(void *vptr)
{
    auto model = static_cast<DosQAbstractListModel *>(vptr);
    model->publicEndRemoveRows();
}

void dos_qabstractlistmodel_beginResetModel(void *vptr)
{
    auto model = static_cast<DosQAbstractListModel *>(vptr);
    model->publicBeginResetModel();
}

void dos_qabstractlistmodel_endResetModel(void *vptr)
{
    auto model = static_cast<DosQAbstractListModel *>(vptr);
    model->publicEndResetModel();
}

void dos_qabstractlistmodel_dataChanged(void *vptr,
                                        QModelIndexVoidPtr topLeftIndex,
                                        QModelIndexVoidPtr bottomRightIndex,
                                        int *rolesArrayPtr,
                                        int rolesArrayLength)
{
    auto model = static_cast<DosQAbstractListModel *>(vptr);
    auto topLeft = static_cast<QModelIndex *>(topLeftIndex);
    auto bottomRight = static_cast<QModelIndex *>(bottomRightIndex);
    auto roles = QVector<int>::fromStdVector(std::vector<int>(rolesArrayPtr, rolesArrayPtr + rolesArrayLength));
    model->publicDataChanged(*topLeft, *bottomRight, roles);
}

void dos_qdeclarative_qmlregistertype(::QmlRegisterType cArgs, int* result)
{
    auto holder = static_cast<DosIQMetaObjectHolder*>(cArgs.staticMetaObject);

    DOS::QmlRegisterType args;
    args.major = cArgs.major;
    args.minor = cArgs.minor;
    args.uri = cArgs.uri;
    args.qml = cArgs.qml;
    args.staticMetaObject = holder->data()->metaObject();
    args.createDObject = cArgs.createDObject;
    args.deleteDObject = cArgs.deleteDObject;

    *result = dosQmlRegisterType(std::move(args));
}
