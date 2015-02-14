#ifndef BASEQABSTRACTLISTMODEL_H
#define BASEQABSTRACTLISTMODEL_H

#include "DOtherSideTypes.h"
#include "DynamicQObject.h"
#include <QAbstractListModel>

/// This class act as a base class for D and Nim QAbstractListModel
class BaseQAbstractListModel : public DynamicQObject<QAbstractListModel>
{
public:
    /// Constructor
    BaseQAbstractListModel(void* modelObject,
                           RowCountCallback rowCountCallback,
                           DataCallback dataCallback,
                           SetDataCallback setDataCallback,
                           RoleNamesCallback roleNamesCallback,
                           FlagsCallback flagsCallback);

    /// Return the model's row count
    virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;
    
    /// Return the QVariant at the given index
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /// Sets the QVariant value at the given index and role
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    
    /// Return the item flags for the given index
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    
    /// Return the dModelPointer
    void* modelObject();

    /// Return the roleNames
    virtual QHash<int, QByteArray> roleNames() const override;

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
    DataCallback m_dataCallback;
    SetDataCallback m_setDataCallback;
    RoleNamesCallback m_roleNamesCallback;
    FlagsCallback m_flagsCallback;
};

BaseQAbstractListModel::BaseQAbstractListModel(void* modelObject,
        RowCountCallback rowCountCallback,
        DataCallback dataCallback,
        SetDataCallback setDataCallback,
        RoleNamesCallback roleNamesCallback,
        FlagsCallback flagsCallback)
    : m_modelObject(modelObject)
    , m_rowCountCallback(rowCountCallback)
    , m_dataCallback(dataCallback)
    , m_setDataCallback(setDataCallback)
    , m_roleNamesCallback(roleNamesCallback)
    , m_flagsCallback(flagsCallback)
{
}

int BaseQAbstractListModel::rowCount(const QModelIndex& index) const
{
    auto newIndex = new QModelIndex();
    *newIndex = index;
    int result;
    m_rowCountCallback(m_modelObject, newIndex, &result);
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

#endif
