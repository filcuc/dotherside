#pragma once

// Qt
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QHash>
#include <QtCore/QByteArray>
#include <QtCore/QVector>
// DOtherSide
#include "DOtherSide/DosIQObjectImpl.h"

namespace DOS {

class DosIQAbstractItemModelImpl : public DosIQObjectImpl
{
public:
    /// Destructor
    virtual ~DosIQAbstractItemModelImpl() = default;

    /// @see QAbstractListModel::rowCount
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const = 0;

    /// @see QAbstractListModel::columnCount
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const = 0;

    /// @see QAbstractListModel::data
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;

    /// @see QAbstractListModel::setData
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) = 0;

    /// @see QAbstractListModel::flags
    virtual Qt::ItemFlags flags(const QModelIndex &index) const = 0;

    /// @see QAbstractListModel::headerData
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const = 0;

    /// @see QAbstractListModel::roleNames
    virtual QHash<int, QByteArray> roleNames() const = 0;

    /// @see QAbstractListModel::beginInsertRows
    virtual void publicBeginInsertRows(const QModelIndex &index, int first, int last) = 0;

    /// @see QAbstractListModel::endInsertRows
    virtual void publicEndInsertRows() = 0;

    /// @see QAbstractListModel::beginRemoveRows
    virtual void publicBeginRemoveRows(const QModelIndex &index, int first, int last) = 0;

    /// @see QAbstractListModel::endRemoveRows
    virtual void publicEndRemoveRows() = 0;

    /// @see QAbstractListModel::beginInsertColumns
    virtual void publicBeginInsertColumns(const QModelIndex &index, int first, int last) = 0;

    /// @see QAbstractListModel::endInsertColumns
    virtual void publicEndInsertColumns() = 0;

    /// @see QAbstractListModel::beginRemoveColumns
    virtual void publicBeginRemoveColumns(const QModelIndex &index, int first, int last) = 0;

    /// @see QAbstractListModel::endRemoveColumns
    virtual void publicEndRemoveColumns() = 0;

    /// @see QAbstractListModel::beginResetModel
    virtual void publicBeginResetModel() = 0;

    /// @see QAbstractListModel::endResetModel
    virtual void publicEndResetModel() = 0;

    /// @see QAbstractListModel::dataChanged
    virtual void publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()) = 0;

    /// @see QAbstractListModel::createIndex
    virtual QModelIndex publicCreateIndex(int row, int column, void* data = 0) const = 0;
};
} // namespace dos
