#include "DOtherSide/DosQAbstractItemModel.h"
#include "DOtherSide/DosQObjectImpl.h"

namespace {
DOS::DosQObjectImpl::ParentMetaCall createParentMetaCall(QAbstractItemModel *parent)
{
    return [parent](QMetaObject::Call callType, int index, void **args)->int {
        return parent->QAbstractItemModel::qt_metacall(callType, index, args);
    };
}
}

namespace DOS {

DosQAbstractItemModel::DosQAbstractItemModel(void *modelObject,
                                             DosIQMetaObjectPtr metaObject,
                                             OnSlotExecuted onSlotExecuted,
                                             RowCountCallback rowCountCallback,
                                             ColumnCountCallback columnCountCallback,
                                             DataCallback dataCallback,
                                             SetDataCallback setDataCallback,
                                             RoleNamesCallback roleNamesCallback,
                                             FlagsCallback flagsCallback,
                                             HeaderDataCallback headerDataCallback,
                                             IndexCallback indexCallback,
                                             ParentCallback parentCallback)
    : m_impl(new DosQObjectImpl(this, ::createParentMetaCall(this), std::move(metaObject), std::move(onSlotExecuted)))
    , m_modelObject(std::move(modelObject))
    , m_rowCountCallback(std::move(rowCountCallback))
    , m_columnCountCallback(std::move(columnCountCallback))
    , m_dataCallback(std::move(dataCallback))
    , m_setDataCallback(std::move(setDataCallback))
    , m_roleNamesCallback(std::move(roleNamesCallback))
    , m_flagsCallback(std::move(flagsCallback))
    , m_headerDataCallback(std::move(headerDataCallback))
    , m_indexCallback(std::move(indexCallback))
    , m_parentCallback(std::move(parentCallback))
{}

bool DosQAbstractItemModel::emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &argumentsValues)
{
    Q_ASSERT(m_impl);
    return m_impl->emitSignal(emitter, name, argumentsValues);
}

const QMetaObject *DosQAbstractItemModel::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

int DosQAbstractItemModel::qt_metacall(QMetaObject::Call call, int index, void **args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(call, index, args);
}

int DosQAbstractItemModel::rowCount(const QModelIndex &parent) const
{
    int result;
    m_rowCountCallback(m_modelObject, &parent, &result);
    return result;
}

int DosQAbstractItemModel::columnCount(const QModelIndex &parent) const
{
    int result;
    m_columnCountCallback(m_modelObject, &parent, &result);
    return result;
}

QVariant DosQAbstractItemModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    m_dataCallback(m_modelObject, &index, role, &result);
    return result;
}

bool DosQAbstractItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    m_setDataCallback(m_modelObject, &index, &value, role, &result);
    return result;
}

Qt::ItemFlags DosQAbstractItemModel::flags(const QModelIndex &index) const
{
    int result;
    m_flagsCallback(m_modelObject, &index, &result);
    return Qt::ItemFlags(result);
}

QVariant DosQAbstractItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    m_headerDataCallback(m_modelObject, section, orientation, role, &result);
    return result;
}

QModelIndex DosQAbstractItemModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex result;
    m_indexCallback(m_modelObject, row, column, &parent, &result);
    return result;
}

QModelIndex DosQAbstractItemModel::parent(const QModelIndex &child) const
{
    QModelIndex result;
    m_parentCallback(m_modelObject, &child, &result);
    return result;
}

void *DosQAbstractItemModel::modelObject()
{
    return m_modelObject;
}

QHash<int, QByteArray> DosQAbstractItemModel::roleNames() const
{
    QHash<int, QByteArray> result;
    m_roleNamesCallback(m_modelObject, &result);
    return result;
}

void DOS::DosQAbstractItemModel::publicBeginInsertColumns(const QModelIndex &index, int first, int last)
{
    beginInsertColumns(index, first, last);
}

void DOS::DosQAbstractItemModel::publicEndInsertColumns()
{
    endInsertColumns();
}

void DOS::DosQAbstractItemModel::publicBeginRemoveColumns(const QModelIndex &index, int first, int last)
{
    beginRemoveColumns(index, first, last);
}

void DOS::DosQAbstractItemModel::publicEndRemoveColumns()
{
    endRemoveColumns();
}

void DOS::DosQAbstractItemModel::publicBeginInsertRows(const QModelIndex &index, int first, int last)
{
    beginInsertRows(index, first, last);
}

void DOS::DosQAbstractItemModel::publicEndInsertRows()
{
    endInsertRows();
}

void DOS::DosQAbstractItemModel::publicBeginRemoveRows(const QModelIndex &index, int first, int last)
{
    beginRemoveRows(index, first, last);
}

void DOS::DosQAbstractItemModel::publicEndRemoveRows()
{
    endRemoveRows();
}

void DOS::DosQAbstractItemModel::publicBeginResetModel()
{
    beginResetModel();
}

void DOS::DosQAbstractItemModel::publicEndResetModel()
{
    endResetModel();
}

void DOS::DosQAbstractItemModel::publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    emit dataChanged(topLeft, bottomRight, roles);
}

QModelIndex DOS::DosQAbstractItemModel::publicCreateIndex(int row, int column, void *data) const
{
    return createIndex(row, column, data);
}

} // namespace DOS
