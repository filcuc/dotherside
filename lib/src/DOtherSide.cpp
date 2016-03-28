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
#include "DOtherSide/DosQDeclarative.h"

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

::DosQQuickView *dos_qquickview_create()
{
    return new QQuickView();
}

void dos_qquickview_show(::DosQQuickView *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->show();
}

void dos_qquickview_delete(::DosQQuickView *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    delete view;
}

char *dos_qquickview_source(::DosQQuickView *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    QUrl url = view->source();
    return convert_to_cstring(url.toString());
}

void dos_qquickview_set_source(::DosQQuickView *vptr, const char *filename)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + QString(filename)));
}

void dos_qquickview_set_source_url(::DosQQuickView *vptr, ::DosQUrl *url)
{
    auto view = static_cast<QQuickView *>(vptr);
    auto _url = static_cast<QUrl *>(url);
    view->setSource(*_url);
}

void dos_qquickview_set_resize_mode(::DosQQuickView *vptr, int resizeMode)
{
    auto view = static_cast<QQuickView *>(vptr);
    view->setResizeMode((QQuickView::ResizeMode) resizeMode);
}

::DosQQmlContext *dos_qquickview_rootContext(::DosQQuickView *vptr)
{
    auto view = static_cast<QQuickView *>(vptr);
    return view->rootContext();
}

void dos_chararray_delete(char *ptr)
{
    if (ptr) delete[] ptr;
}

char *dos_qqmlcontext_baseUrl(::DosQQmlContext *vptr)
{
    auto context = static_cast<QQmlContext *>(vptr);
    QUrl url = context->baseUrl();
    return convert_to_cstring(url.toString());
}

void dos_qqmlcontext_setcontextproperty(::DosQQmlContext *vptr, const char *name, ::DosQVariant *value)
{
    auto context = static_cast<QQmlContext *>(vptr);
    auto variant = static_cast<QVariant *>(value);
    context->setContextProperty(QString::fromUtf8(name), *variant);
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

::DosQVariant *dos_qvariant_create_qvariant(::DosQVariant *other)
{
    auto otherQVariant = static_cast<QVariant *>(other);
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

bool dos_qvariant_isnull(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    return variant->isNull();
}

void dos_qvariant_delete(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    delete variant;
}

void dos_qvariant_assign(::DosQVariant *vptr, ::DosQVariant *other)
{
    auto leftQVariant = static_cast<QVariant *>(vptr);
    auto rightQVariant = static_cast<QVariant *>(other);
    *leftQVariant = *rightQVariant;
}

int dos_qvariant_toInt(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    return variant->toInt();
}

bool dos_qvariant_toBool(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    return variant->toBool();
}

float dos_qvariant_toFloat(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    return variant->toFloat();
}

double dos_qvariant_toDouble(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    return variant->toDouble();
}

char *dos_qvariant_toString(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
    return convert_to_cstring(variant->toString());
}

::DosQObject *dos_qvariant_toQObject(::DosQVariant *vptr)
{
    auto variant = static_cast<QVariant *>(vptr);
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

::DosQMetaObject *dos_qobject_qmetaobject()
{
    return new DOS::DosIQMetaObjectHolder(std::make_shared<DOS::DosQObjectMetaObject>());
}

::DosQObject *dos_qobject_create(void *dObjectPointer, ::DosQMetaObject *metaObject, ::DObjectCallback dObjectCallback)
{
    auto metaObjectHolder = static_cast<DOS::DosIQMetaObjectHolder *>(metaObject);
    auto dosQObject = new DOS::DosQObject(metaObjectHolder->data(),
                                     DOS::OnSlotExecutedHandler(dObjectPointer, dObjectCallback));
    QQmlEngine::setObjectOwnership(dosQObject, QQmlEngine::CppOwnership);
    return static_cast<QObject *>(dosQObject);
}

void dos_qobject_delete(::DosQObject *vptr)
{
    auto qobject = static_cast<QObject *>(vptr);
    qobject->disconnect();
    delete qobject;
}

void dos_qobject_signal_emit(::DosQObject *vptr, const char *name, int parametersCount, void **parameters)
{
    auto qobject = static_cast<QObject *>(vptr);
    auto dynamicQObject = dynamic_cast<DOS::DosIQObjectImpl *>(qobject);

    auto transformation = [](void *vptr)->QVariant{return *(static_cast<QVariant *>(vptr));};
    const std::vector<QVariant> variants = DOS::toVector(parameters, parametersCount, transformation);
    dynamicQObject->emitSignal(qobject, QString::fromStdString(name), variants);
}

void dos_qobject_signal_connect(::DosQObject *senderVPtr,
                                const char *signal,
                                ::DosQObject *receiverVPtr,
                                const char *method,
                                int type,
                                bool *result)
{
    auto sender = static_cast<QObject *>(senderVPtr);
    auto receiver = static_cast<QObject *>(receiverVPtr);
    *result = QObject::connect(sender, signal, receiver, method, (Qt::ConnectionType) type);
}

void dos_qobject_signal_disconnect(::DosQObject *senderVPtr,
                                   const char *signal,
                                   ::DosQObject *receiverVPtr,
                                   const char *method,
                                   bool *result)
{
    auto sender = static_cast<QObject *>(senderVPtr);
    auto receiver = static_cast<QObject *>(receiverVPtr);
    *result = QObject::disconnect(sender, signal, receiver, method);
}

char *dos_qobject_objectName(::DosQObject *vptr)
{
    auto object = static_cast<QObject *>(vptr);
    return convert_to_cstring(object->objectName());
}

void dos_qobject_setObjectName(::DosQObject *vptr, const char *name)
{
    auto object = static_cast<QObject *>(vptr);
    object->setObjectName(QString::fromUtf8(name));
}

::DosQModelIndex *dos_qmodelindex_create()
{
    return new QModelIndex();
}

::DosQModelIndex *dos_qmodelindex_create_qmodelindex(::DosQModelIndex *other_vptr)
{
    auto other = static_cast<QModelIndex *>(other_vptr);
    return new QModelIndex(*other);
}

void dos_qmodelindex_delete(::DosQModelIndex *vptr)
{
    auto index = static_cast<QModelIndex *>(vptr);
    delete index;
}

int dos_qmodelindex_row(::DosQModelIndex *vptr)
{
    auto index = static_cast<QModelIndex *>(vptr);
    return index->row();
}

int dos_qmodelindex_column(::DosQModelIndex *vptr)
{
    auto index = static_cast<QModelIndex *>(vptr);
    return index->column();
}

bool dos_qmodelindex_isValid(::DosQModelIndex *vptr)
{
    auto index = static_cast<QModelIndex *>(vptr);
    return index->isValid();
}

::DosQVariant *dos_qmodelindex_data(::DosQModelIndex *vptr, int role)
{
    auto index = static_cast<QModelIndex *>(vptr);
    auto result = new QVariant(index->data(role));
    return static_cast<QVariant *>(result);
}

::DosQModelIndex *dos_qmodelindex_parent(::DosQModelIndex *vptr)
{
    auto index = static_cast<QModelIndex *>(vptr);
    auto result = new QModelIndex(index->parent());
    return static_cast<QModelIndex *>(result);
}

::DosQModelIndex *dos_qmodelindex_child(::DosQModelIndex *vptr, int row, int column)
{
    auto index = static_cast<QModelIndex *>(vptr);
    auto result = new QModelIndex(index->child(row, column));
    return static_cast<QModelIndex *>(result);
}

::DosQModelIndex *dos_qmodelindex_sibling(::DosQModelIndex *vptr, int row, int column)
{
    auto index = static_cast<QModelIndex *>(vptr);
    auto result = new QModelIndex(index->sibling(row, column));
    return static_cast<QModelIndex *>(result);
}

void dos_qmodelindex_assign(::DosQModelIndex *l, ::DosQModelIndex *r)
{
    auto li = static_cast<QModelIndex *>(l);
    auto ri = static_cast<QModelIndex *>(r);
    *li = *ri;
}

::DosQHashIntQByteArray *dos_qhash_int_qbytearray_create()
{
    return new QHash<int, QByteArray>();
}

void dos_qhash_int_qbytearray_delete(::DosQHashIntQByteArray* vptr)
{
    auto qHash = static_cast<QHash<int, QByteArray>*>(vptr);
    delete qHash;
}

void dos_qhash_int_qbytearray_insert(::DosQHashIntQByteArray* vptr, int key, const char *value)
{
    auto qHash = static_cast<QHash<int, QByteArray>*>(vptr);
    qHash->insert(key, QByteArray(value));
}

char *dos_qhash_int_qbytearray_value(::DosQHashIntQByteArray* vptr, int key)
{
    auto qHash = static_cast<QHash<int, QByteArray>*>(vptr);
    return convert_to_cstring(qHash->value(key));
}

void dos_qresource_register(const char *filename)
{
    QResource::registerResource(QString::fromUtf8(filename));
}

::DosQUrl *dos_qurl_create(const char *url, int parsingMode)
{
    return new QUrl(QString::fromUtf8(url), (QUrl::ParsingMode) parsingMode);
}

void dos_qurl_delete(::DosQUrl *vptr)
{
    auto url = static_cast<QUrl *>(vptr);
    delete url;
}

char *dos_qurl_to_string(::DosQUrl *vptr)
{
    auto url = static_cast<QUrl *>(vptr);
    return convert_to_cstring(url->toString());
}

::DosQMetaObject* dos_qmetaobject_create(::DosQMetaObject *superClassVPtr,
                                         const char *className,
                                         const ::SignalDefinitions *signalDefinitions,
                                         const ::SlotDefinitions *slotDefinitions,
                                         const ::PropertyDefinitions *propertyDefinitions)
{
    Q_ASSERT(superClassVPtr);
    auto superClassHolder = static_cast<DOS::DosIQMetaObjectHolder *>(superClassVPtr);
    Q_ASSERT(superClassHolder);
    auto data = superClassHolder->data();
    Q_ASSERT(data);

    auto metaObject = std::make_shared<DOS::DosQMetaObject>(data,
                                                            QString::fromUtf8(className),
                                                            DOS::toVector(*signalDefinitions),
                                                            DOS::toVector(*slotDefinitions),
                                                            DOS::toVector(*propertyDefinitions));
    return new DOS::DosIQMetaObjectHolder(std::move(metaObject));
}

void dos_qmetaobject_delete(::DosQMetaObject *vptr)
{
    auto factory = static_cast<DOS::DosIQMetaObjectHolder *>(vptr);
    delete factory;
}

::DosQMetaObject *dos_qabstractlistmodel_qmetaobject()
{
    return new DOS::DosIQMetaObjectHolder(std::make_shared<DOS::DosQAbstractListModelMetaObject>());
}

::DosQAbstractListModel *dos_qabstractlistmodel_create(void *dObjectPointer,
                                                       ::DosQMetaObject *metaObjectPointer,
                                                       ::DObjectCallback dObjectCallback,
                                                       ::RowCountCallback rowCountCallback,
                                                       ::ColumnCountCallback columnCountCallback,
                                                       ::DataCallback dataCallback,
                                                       ::SetDataCallback setDataCallback,
                                                       ::RoleNamesCallback roleNamesCallaback,
                                                       ::FlagsCallback flagsCallback,
                                                       ::HeaderDataCallback headerDataCallback)
{
    auto metaObjectHolder = static_cast<DOS::DosIQMetaObjectHolder *>(metaObjectPointer);
    auto model = new DOS::DosQAbstractListModel(dObjectPointer,
                                                metaObjectHolder->data(),
                                                DOS::OnSlotExecutedHandler(dObjectPointer, dObjectCallback),
                                                rowCountCallback,
                                                columnCountCallback,
                                                dataCallback,
                                                setDataCallback,
                                                roleNamesCallaback,
                                                flagsCallback,
                                                headerDataCallback);
    QQmlEngine::setObjectOwnership(model, QQmlEngine::CppOwnership);
    return static_cast<QObject *>(model);
}

void dos_qabstractlistmodel_beginInsertRows(::DosQAbstractListModel *vptr, ::DosQModelIndex *parentIndex, int first, int last)
{
    auto object = static_cast<QObject *>(vptr);
    auto model = dynamic_cast<DOS::DosIQAbstractListModelImpl *>(object);
    auto index = static_cast<QModelIndex *>(parentIndex);
    model->publicBeginInsertRows(*index, first, last);
}

void dos_qabstractlistmodel_endInsertRows(::DosQAbstractListModel *vptr)
{
    auto object = static_cast<QObject *>(vptr);
    auto model = dynamic_cast<DOS::DosIQAbstractListModelImpl *>(object);
    model->publicEndInsertRows();
}

void dos_qabstractlistmodel_beginRemoveRows(::DosQAbstractListModel *vptr, ::DosQModelIndex *parentIndex, int first, int last)
{
    auto object = static_cast<QObject *>(vptr);
    auto model = dynamic_cast<DOS::DosIQAbstractListModelImpl *>(object);
    auto index = static_cast<QModelIndex *>(parentIndex);
    model->publicBeginRemoveRows(*index, first, last);
}

void dos_qabstractlistmodel_endRemoveRows(::DosQAbstractListModel *vptr)
{
    auto object = static_cast<QObject *>(vptr);
    auto model = dynamic_cast<DOS::DosIQAbstractListModelImpl *>(object);
    model->publicEndRemoveRows();
}

void dos_qabstractlistmodel_beginResetModel(::DosQAbstractListModel *vptr)
{
    auto object = static_cast<QObject *>(vptr);
    auto model = dynamic_cast<DOS::DosIQAbstractListModelImpl *>(object);
    model->publicBeginResetModel();
}

void dos_qabstractlistmodel_endResetModel(::DosQAbstractListModel *vptr)
{
    auto object = static_cast<QObject *>(vptr);
    auto model = dynamic_cast<DOS::DosIQAbstractListModelImpl *>(object);
    model->publicEndResetModel();
}

void dos_qabstractlistmodel_dataChanged(::DosQAbstractListModel *vptr,
                                        ::DosQModelIndex *topLeftIndex,
                                        ::DosQModelIndex *bottomRightIndex,
                                        int *rolesArrayPtr,
                                        int rolesArrayLength)
{
    auto object = static_cast<QObject *>(vptr);
    auto model = dynamic_cast<DOS::DosIQAbstractListModelImpl *>(object);
    auto topLeft = static_cast<QModelIndex *>(topLeftIndex);
    auto bottomRight = static_cast<QModelIndex *>(bottomRightIndex);
    auto roles = QVector<int>::fromStdVector(std::vector<int>(rolesArrayPtr, rolesArrayPtr + rolesArrayLength));
    model->publicDataChanged(*topLeft, *bottomRight, roles);
}

int dos_qdeclarative_qmlregistertype(const ::QmlRegisterType *cArgs)
{
    auto holder = static_cast<DOS::DosIQMetaObjectHolder *>(cArgs->staticMetaObject);

    DOS::QmlRegisterType args;
    args.major = cArgs->major;
    args.minor = cArgs->minor;
    args.uri = cArgs->uri;
    args.qml = cArgs->qml;
    args.staticMetaObject = holder->data();
    args.createDObject = cArgs->createDObject;
    args.deleteDObject = cArgs->deleteDObject;

    return DOS::dosQmlRegisterType(std::move(args));
}

int dos_qdeclarative_qmlregistersingletontype(const ::QmlRegisterType *cArgs)
{
    auto holder = static_cast<DOS::DosIQMetaObjectHolder *>(cArgs->staticMetaObject);

    DOS::QmlRegisterType args;
    args.major = cArgs->major;
    args.minor = cArgs->minor;
    args.uri = cArgs->uri;
    args.qml = cArgs->qml;
    args.staticMetaObject = holder->data();
    args.createDObject = cArgs->createDObject;
    args.deleteDObject = cArgs->deleteDObject;

    return DOS::dosQmlRegisterSingletonType(std::move(args));
}
