#pragma once

#include "DOtherSide/DosQAbstractListModel.h"
#include "DOtherSide/DosQMetaObject.h"

namespace DOS {
template <int, int>
class DosQAbstractListModelWrapper : public QAbstractListModel, public DosIQAbstractListModelImpl
{
public:
    static const QMetaObject staticMetaObject;

    /// Constructor
    DosQAbstractListModelWrapper(QObject *parent = nullptr);

    /// Destructor
    ~DosQAbstractListModelWrapper();

    /// @see DosIQObjectImpl::metaObject
    const QMetaObject *metaObject() const override;

    /// @see DosIQObjectImpl::qt_metacall
    int qt_metacall(QMetaObject::Call, int, void **) override;

    /// @see DosIQObjectImpl::emitSignal
    bool emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &argumentsValues);

    /// Return the qml registration type
    static const QmlRegisterType &qmlRegisterType();

    /// Sets the qml registration type
    static void setQmlRegisterType(QmlRegisterType data);

    /// Sets the static metaobject
    static void setStaticMetaObject(const QMetaObject &metaObject);

    /// Sets the qmlRegisterType id
    static void setId(int id);

    /// @see QAbstractListModel::rowCount
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// @see QAbstractListModel::columnCount
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /// @see QAbstractListModel::data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// @see QAbstractListModel::setData
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /// @see QAbstractListModel::flags
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /// @see QAbstractListModel::headerData
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /// @see QAbstractListModel::roleNames
    QHash<int, QByteArray> roleNames() const override;

    /// @see DosIQAbstractListModelImpl::publicBeginInsertRows
    void publicBeginInsertRows(const QModelIndex &index, int first, int last) override;

    /// @see DosIQAbstractListModelImpl::publicEndInsertRows
    void publicEndInsertRows() override;

    /// @see DosIQAbstractListModelImpl::publicBeginRemoveRows
    void publicBeginRemoveRows(const QModelIndex &index, int first, int last) override;

    /// @see DosIQAbstractListModelImpl::publicEndRemoveRows
    void publicEndRemoveRows() override;

    /// @see DosIQAbstractListModelImpl::publicBeginResetModel
    void publicBeginResetModel() override;

    /// @see DosIQAbstractListModelImpl::publicEndResetModel
    void publicEndResetModel() override;

    /// @see DosIQAbstractListModelImpl::publicDataChanged
    void publicDataChanged(const QModelIndex &topLeft,
                           const QModelIndex &bottomRight,
                           const QVector<int> &roles = QVector<int>()) override;

private:
    void *m_dObject;
    DosQAbstractListModel *m_impl;
    static int m_id;
    static QmlRegisterType m_data;
};

template<int N, int M>
const QMetaObject DosQAbstractListModelWrapper<N, M>::staticMetaObject = QAbstractListModel::staticMetaObject;

template<int N, int M>
QmlRegisterType DosQAbstractListModelWrapper<N, M>::m_data;

template<int N, int M>
int DosQAbstractListModelWrapper<N, M>::m_id = -1;

template<int N, int M>
DosQAbstractListModelWrapper<N, M>::DosQAbstractListModelWrapper(QObject *parent)
    : QAbstractListModel(parent)
    , m_dObject(nullptr)
    , m_impl(nullptr)
{
    void *impl = nullptr;
    m_data.createDObject(m_id, static_cast<QObject *>(this), &m_dObject, &impl);
    beginResetModel();
    m_impl = dynamic_cast<DosQAbstractListModel *>(static_cast<QObject *>(impl));
    QObject::connect(m_impl, &DosQAbstractListModel::rowsAboutToBeInserted, this, &DosQAbstractListModelWrapper::beginInsertRows);
    QObject::connect(m_impl, &DosQAbstractListModel::rowsInserted, this, &DosQAbstractListModelWrapper::endInsertRows);
    QObject::connect(m_impl, &DosQAbstractListModel::rowsAboutToBeRemoved, this, &DosQAbstractListModelWrapper::beginRemoveRows);
    QObject::connect(m_impl, &DosQAbstractListModel::rowsRemoved, this, &DosQAbstractListModelWrapper::endRemoveRows);
    QObject::connect(m_impl, &DosQAbstractListModel::rowsAboutToBeMoved, this, &DosQAbstractListModelWrapper::beginMoveRows);
    QObject::connect(m_impl, &DosQAbstractListModel::rowsMoved, this, &DosQAbstractListModelWrapper::endMoveRows);
    QObject::connect(m_impl, &DosQAbstractListModel::columnsAboutToBeInserted, this, &DosQAbstractListModelWrapper::beginInsertColumns);
    QObject::connect(m_impl, &DosQAbstractListModel::columnsInserted, this, &DosQAbstractListModelWrapper::endInsertColumns);
    QObject::connect(m_impl, &DosQAbstractListModel::columnsAboutToBeRemoved, this, &DosQAbstractListModelWrapper::beginRemoveColumns);
    QObject::connect(m_impl, &DosQAbstractListModel::columnsRemoved, this, &DosQAbstractListModelWrapper::endRemoveColumns);
    QObject::connect(m_impl, &DosQAbstractListModel::columnsAboutToBeMoved, this, &DosQAbstractListModelWrapper::beginMoveColumns);
    QObject::connect(m_impl, &DosQAbstractListModel::columnsMoved, this, &DosQAbstractListModelWrapper::endMoveColumns);
    QObject::connect(m_impl, &DosQAbstractListModel::modelAboutToBeReset, this, &DosQAbstractListModelWrapper::beginResetModel);
    QObject::connect(m_impl, &DosQAbstractListModel::modelReset, this, &DosQAbstractListModelWrapper::endResetModel);
    QObject::connect(m_impl, &DosQAbstractListModel::dataChanged, this, &DosQAbstractListModelWrapper::dataChanged);
    QObject::connect(m_impl, &DosQAbstractListModel::layoutAboutToBeChanged, this, &DosQAbstractListModelWrapper::layoutAboutToBeChanged);
    QObject::connect(m_impl, &DosQAbstractListModel::layoutChanged, this, &DosQAbstractListModelWrapper::layoutChanged);
    endResetModel();
    Q_ASSERT(m_dObject);
    Q_ASSERT(m_impl);
}

template<int N, int M>
DosQAbstractListModelWrapper<N, M>::~DosQAbstractListModelWrapper()
{
    m_data.deleteDObject(m_id, m_dObject);
    m_dObject = nullptr;
    delete m_impl;
    m_impl = nullptr;
}

template<int N, int M>
const QMetaObject *DosQAbstractListModelWrapper<N, M>::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

template<int N, int M>
int DosQAbstractListModelWrapper<N, M>::qt_metacall(QMetaObject::Call call, int index, void **args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(call, index, args);
}

template<int N, int M>
bool DosQAbstractListModelWrapper<N, M>::emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &argumentsValues)
{
    Q_ASSERT(m_impl);
    return m_impl->emitSignal(this, name, argumentsValues);
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::setQmlRegisterType(QmlRegisterType data)
{
    m_data = std::move(data);
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::setStaticMetaObject(const QMetaObject &metaObject)
{
    *(const_cast<QMetaObject *>(&staticMetaObject)) = metaObject;
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::setId(int id)
{
    m_id = id;
}

template<int N, int M>
int DosQAbstractListModelWrapper<N, M>::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(m_impl);
    return m_impl->rowCount(parent);
}

template<int N, int M>
int DosQAbstractListModelWrapper<N, M>::columnCount(const QModelIndex &parent) const
{
    Q_ASSERT(m_impl);
    return m_impl->columnCount(parent);
}

template<int N, int M>
QVariant DosQAbstractListModelWrapper<N, M>::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(m_impl);
    return m_impl->data(index, role);
}

template<int N, int M>
bool DosQAbstractListModelWrapper<N, M>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_ASSERT(m_impl);
    return m_impl->setData(index, value, role);
}

template<int N, int M>
Qt::ItemFlags DosQAbstractListModelWrapper<N, M>::flags(const QModelIndex &index) const
{
    Q_ASSERT(m_impl);
    return m_impl->flags(index);
}

template<int N, int M>
QVariant DosQAbstractListModelWrapper<N, M>::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_ASSERT(m_impl);
    return m_impl->headerData(section, orientation, role);
}

template<int N, int M>
QHash<int, QByteArray> DosQAbstractListModelWrapper<N, M>::roleNames() const
{
    Q_ASSERT(m_impl);
    return m_impl->roleNames();
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::publicBeginInsertRows(const QModelIndex &index, int first, int last)
{
    m_impl->publicBeginInsertRows(index, first, last);
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::publicEndInsertRows()
{
    m_impl->publicEndInsertRows();
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::publicBeginRemoveRows(const QModelIndex &index, int first, int last)
{
    m_impl->publicBeginRemoveRows(index, first, last);
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::publicEndRemoveRows()
{
    m_impl->publicEndRemoveRows();
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::publicBeginResetModel()
{
    m_impl->publicBeginResetModel();
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::publicEndResetModel()
{
    m_impl->publicEndResetModel();
}

template<int N, int M>
void DosQAbstractListModelWrapper<N, M>::publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    m_impl->publicDataChanged(topLeft, bottomRight, roles);
}

template<int N, int M>
const QmlRegisterType &DosQAbstractListModelWrapper<N, M>::qmlRegisterType()
{
    return m_data;
}

namespace DQALMW {

template<int N>
using RegisterTypeQObject = DosQAbstractListModelWrapper<N, 0>;

template<int N>
int dosQmlRegisterType(QmlRegisterType args)
{
    RegisterTypeQObject<N>::setQmlRegisterType(std::move(args));
    const QmlRegisterType &type = RegisterTypeQObject<N>::qmlRegisterType();
    RegisterTypeQObject<N>::setStaticMetaObject(*(type.staticMetaObject->metaObject()));
    int result = qmlRegisterType<RegisterTypeQObject<N>>(type.uri.c_str(), type.major, type.minor, type.qml.c_str());
    RegisterTypeQObject<N>::setId(result);
    return result;
}

template<int N>
struct DosQmlRegisterHelper {
    static int Register(int i, QmlRegisterType args)
    {
        if (i > N)
            return -1;
        else if (i == N)
            return dosQmlRegisterType<N>(std::move(args));
        else
            return DosQmlRegisterHelper < N - 1 >::Register(i, std::move(args));
    }
};

template<>
struct DosQmlRegisterHelper<0> {
    static int Register(int i, QmlRegisterType args)
    {
        return i == 0 ? dosQmlRegisterType<0>(std::move(args)) : -1;
    }
};

int dosQmlRegisterType(QmlRegisterType args)
{
    static int i = 0;
    return DosQmlRegisterHelper<35>::Register(i++, std::move(args));
}

template<int N>
using RegisterSingletonTypeQObject = DosQAbstractListModelWrapper<N, 1>;

template<int N>
QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    return new RegisterSingletonTypeQObject<N>();
}

template<int N>
int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    using Func = QObject * (*)(QQmlEngine *, QJSEngine *);
    Func f = singletontype_provider<N>;

    RegisterSingletonTypeQObject<N>::setQmlRegisterType(std::move(args));
    const QmlRegisterType &type = RegisterSingletonTypeQObject<N>::qmlRegisterType();
    RegisterSingletonTypeQObject<N>::setStaticMetaObject(*(type.staticMetaObject->metaObject()));
    int result = qmlRegisterSingletonType<RegisterSingletonTypeQObject<N>>(type.uri.c_str(), type.major, type.minor, type.qml.c_str(), f);
    RegisterSingletonTypeQObject<N>::setId(result);
    return result;
}

template<int N>
struct DosQmlRegisterSingletonHelper {
    static int Register(int i, QmlRegisterType args)
    {
        if (i > N)
            return -1;
        else if (i == N)
            return dosQmlRegisterSingletonType<N>(std::move(args));
        else
            return DosQmlRegisterSingletonHelper < N - 1 >::Register(i, std::move(args));
    }
};

template<>
struct DosQmlRegisterSingletonHelper<0> {
    static int Register(int i, QmlRegisterType args)
    {
        return i == 0 ? dosQmlRegisterSingletonType<0>(std::move(args)) : -1;
    }
};

int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    static int i = 0;
    return DosQmlRegisterSingletonHelper<35>::Register(i++, std::move(args));
}

}
}
