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
                           RoleNamesCallback roleNamesCallback);

    /// Return the model's row count
    virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;

    /// Return the QVariant at the given index
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

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
    RoleNamesCallback m_roleNamesCallback;
};

BaseQAbstractListModel::BaseQAbstractListModel(void* modelObject,
        RowCountCallback rowCountCallback,
        DataCallback dataCallback,
        RoleNamesCallback roleNamesCallback)
    : m_modelObject(modelObject)
    , m_rowCountCallback(rowCountCallback)
    , m_dataCallback(dataCallback)
    , m_roleNamesCallback(roleNamesCallback)
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
