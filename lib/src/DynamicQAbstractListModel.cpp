#include "DOtherSide/DynamicQAbstractListModel.h"

namespace DOS
{

DynamicQAbstractListModel::DynamicQAbstractListModel(void *modelObject, RowCountCallback rowCountCallback, ColumnCountCallback columnCountCallback, DataCallback dataCallback, SetDataCallback setDataCallback, RoleNamesCallback roleNamesCallback, FlagsCallback flagsCallback, HeaderDataCallback headerDataCallback)
    : m_impl(nullptr)
    , m_modelObject(modelObject)
    , m_rowCountCallback(rowCountCallback)
    , m_columnCountCallback(columnCountCallback)
    , m_dataCallback(dataCallback)
    , m_setDataCallback(setDataCallback)
    , m_roleNamesCallback(roleNamesCallback)
    , m_flagsCallback(flagsCallback)
    , m_headerDataCallback(headerDataCallback)
{
}

bool DynamicQAbstractListModel::emitSignal(const QString &name, const std::vector<QVariant> &argumentsValues)
{
    return m_impl->emitSignal(name, argumentsValues);
}

const QMetaObject *DynamicQAbstractListModel::metaObject() const
{
    return m_impl->metaObject();
}

int DynamicQAbstractListModel::qt_metacall(QMetaObject::Call callType, int index, void **args)
{
    return m_impl->qt_metacall(callType, index, args);
}

int DynamicQAbstractListModel::rowCount(const QModelIndex &parent) const
{
    auto parentIndex = new QModelIndex();
    *parentIndex = parent;
    int result;
    m_rowCountCallback(m_modelObject, parentIndex, &result);
    return result;
}

int DynamicQAbstractListModel::columnCount(const QModelIndex &parent) const
{
    auto parentIndex = new QModelIndex();
    *parentIndex = parent;
    int result;
    m_columnCountCallback(m_modelObject, parentIndex, &result);
    return result;
}

QVariant DynamicQAbstractListModel::data(const QModelIndex &index, int role) const
{
    auto newIndex = new QModelIndex();
    *newIndex = index;
    QVariant result;
    m_dataCallback(m_modelObject, newIndex, role, &result);
    return result;
}

bool DynamicQAbstractListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto newIndex = new QModelIndex(index);
    *newIndex = index;
    auto newValue = new QVariant();
    *newValue = value;
    bool result = false;
    m_setDataCallback(m_modelObject, newIndex, newValue, role, &result);
    return result;
}

Qt::ItemFlags DynamicQAbstractListModel::flags(const QModelIndex &index) const
{
    auto newIndex = new QModelIndex(index);
    *newIndex = index;
    int result;
    m_flagsCallback(m_modelObject, newIndex, &result);
    return Qt::ItemFlags(result);
}

QVariant DynamicQAbstractListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    m_headerDataCallback(m_modelObject, section, orientation, role, &result);
    return result;
}

void *DynamicQAbstractListModel::modelObject()
{
    return m_modelObject;
}

QHash<int, QByteArray> DynamicQAbstractListModel::roleNames() const
{
    QHash<int, QByteArray> result;
    m_roleNamesCallback(m_modelObject, &result);
    return result;
}

void DynamicQAbstractListModel::publicBeginInsertRows(const QModelIndex &index, int first, int last)
{
    beginInsertRows(index, first, last);
}

void DynamicQAbstractListModel::publicEndInsertRows()
{
    return endInsertRows();
}

void DynamicQAbstractListModel::publicBeginRemoveRows(const QModelIndex &index, int first, int last)
{
    beginRemoveRows(index, first, last);
}

void DynamicQAbstractListModel::publicEndRemoveRows()
{
    return endRemoveRows();
}

void DynamicQAbstractListModel::publicBeginResetModel()
{
    beginResetModel();
}

void DynamicQAbstractListModel::publicEndResetModel()
{
    endResetModel();
}

void DynamicQAbstractListModel::publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    emit dataChanged(topLeft, bottomRight, roles);
}

void DynamicQAbstractListModel::setImpl(std::unique_ptr<IDynamicQObject> impl)
{
    m_impl = std::move(impl);
}

}
