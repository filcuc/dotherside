#pragma once

// Qt
#include <QAbstractListModel>
// DOtherSide
#include "DOtherSide/DOtherSideTypes.h"
#include "DOtherSide/DynamicQObject.h"


/// This class act as a base class for D and Nim QAbstractListModel
class BaseQAbstractListModel final : public DynamicQObject<QAbstractListModel>
{
public:
    /// Constructor
    BaseQAbstractListModel(void* modelObject,
                           RowCountCallback rowCountCallback,
                           ColumnCountCallback columnCountCallback,
                           DataCallback dataCallback,
                           SetDataCallback setDataCallback,
                           RoleNamesCallback roleNamesCallback,
                           FlagsCallback flagsCallback,
                           HeaderDataCallback headerDataCallback);

    /// Return the model's row count
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    
    /// Return the model's column count
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    
    /// Return the QVariant at the given index
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /// Sets the QVariant value at the given index and role
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    
    /// Return the item flags for the given index
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    
    /// Return the data for the given role and section in the header with the specified orientation
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
    /// Return the dModelPointer
    void* modelObject();

    /// Return the roleNames
    QHash<int, QByteArray> roleNames() const override;

    /// Expose beginInsertRows
    void publicBeginInsertRows(const QModelIndex& index, int first, int last);

    /// Expose endInsertRows
    void publicEndInsertRows();

    /// Expose beginRemoveRows
    void publicBeginRemoveRows(const QModelIndex& index, int first, int last);

    /// Expose endInsertRows
    void publicEndRemoveRows();

    /// Expose beginResetModel
    void publicBeginResetModel();

    /// Expose endResetModel
    void publicEndResetModel();

    /// Expose dataChanged
    void publicDataChanged(const QModelIndex& topLeft,
                           const QModelIndex& bottomRight,
                           const QVector<int>& roles = QVector<int>());

private:
    void* m_modelObject;
    RowCountCallback m_rowCountCallback;
    ColumnCountCallback m_columnCountCallback;
    DataCallback m_dataCallback;
    SetDataCallback m_setDataCallback;
    RoleNamesCallback m_roleNamesCallback;
    FlagsCallback m_flagsCallback;
    HeaderDataCallback m_headerDataCallback;
};

BaseQAbstractListModel::BaseQAbstractListModel(void* modelObject,
                                               RowCountCallback rowCountCallback,
                                               ColumnCountCallback columnCountCallback,
                                               DataCallback dataCallback,
                                               SetDataCallback setDataCallback,
                                               RoleNamesCallback roleNamesCallback,
                                               FlagsCallback flagsCallback,
                                               HeaderDataCallback headerDataCallback)
    : m_modelObject(modelObject)
    , m_rowCountCallback(rowCountCallback)
    , m_columnCountCallback(columnCountCallback)
    , m_dataCallback(dataCallback)
    , m_setDataCallback(setDataCallback)
    , m_roleNamesCallback(roleNamesCallback)
    , m_flagsCallback(flagsCallback)
    , m_headerDataCallback(headerDataCallback)
{
}

int BaseQAbstractListModel::rowCount(const QModelIndex& parent) const
{
    auto parentIndex = new QModelIndex();
    *parentIndex = parent;
    int result;
    m_rowCountCallback(m_modelObject, parentIndex, &result);
    return result;
}

int BaseQAbstractListModel::columnCount(const QModelIndex& parent) const
{
    auto parentIndex = new QModelIndex();
    *parentIndex = parent;
    int result;
    m_columnCountCallback(m_modelObject, parentIndex, &result);
    return result;
}

QVariant BaseQAbstractListModel::data(const QModelIndex& index, int role) const
{
    auto newIndex = new QModelIndex();
    *newIndex = index;
    QVariant result;
    m_dataCallback(m_modelObject, newIndex, role, &result);
    return result;
}

bool BaseQAbstractListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    auto newIndex = new QModelIndex(index);
    *newIndex = index;
    auto newValue = new QVariant();
    *newValue = value;
    bool result = false;
    m_setDataCallback(m_modelObject, newIndex, newValue, role, &result);
    return result;
}

Qt::ItemFlags BaseQAbstractListModel::flags(const QModelIndex& index) const
{
    auto newIndex = new QModelIndex(index);
    *newIndex = index;
    int result;
    m_flagsCallback(m_modelObject, newIndex, &result);
    return Qt::ItemFlags(result);
}

QVariant BaseQAbstractListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    m_headerDataCallback(m_modelObject, section, orientation, role, &result);
    return result;
}

void* BaseQAbstractListModel::modelObject()
{
    return m_modelObject;
}

QHash<int, QByteArray> BaseQAbstractListModel::roleNames() const
{
    QHash<int, QByteArray> result;
    m_roleNamesCallback(m_modelObject, &result);
    return result;
}

void BaseQAbstractListModel::publicBeginInsertRows(const QModelIndex& index, int first, int last)
{
    beginInsertRows(index, first, last);
}

void BaseQAbstractListModel::publicEndInsertRows()
{
    return endInsertRows();
}

void BaseQAbstractListModel::publicBeginRemoveRows(const QModelIndex& index, int first, int last)
{
    beginRemoveRows(index, first, last);
}

void BaseQAbstractListModel::publicEndRemoveRows()
{
    return endRemoveRows();
}

void BaseQAbstractListModel::publicBeginResetModel()
{
    beginResetModel();
}

void BaseQAbstractListModel::publicEndResetModel()
{
    endResetModel();
}

void BaseQAbstractListModel::publicDataChanged(const QModelIndex& topLeft,
                                               const QModelIndex& bottomRight,
                                               const QVector<int>& roles)
{
    emit dataChanged(topLeft, bottomRight, roles);
}

