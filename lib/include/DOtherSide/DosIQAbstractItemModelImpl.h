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

    /// @see QAbstractItemModel::rowCount
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const = 0;

    /// @see QAbstractItemModel::columnCount
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const = 0;

    /// @see QAbstractItemModel::data
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;

    /// @see QAbstractItemModel::setData
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) = 0;

    /// @see QAbstractItemModel::flags
    virtual Qt::ItemFlags flags(const QModelIndex &index) const = 0;

    /// @see QAbstractItemModel::headerData
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const = 0;

    /// @see QAbstractItemModel::roleNames
    virtual QHash<int, QByteArray> roleNames() const = 0;

    /// @see QAbstractItemModel::beginInsertRows
    virtual void publicBeginInsertRows(const QModelIndex &index, int first, int last) = 0;

    /// @see QAbstractItemModel::endInsertRows
    virtual void publicEndInsertRows() = 0;

    /// @see QAbstractItemModel::beginRemoveRows
    virtual void publicBeginRemoveRows(const QModelIndex &index, int first, int last) = 0;

    /// @see QAbstractItemModel::endRemoveRows
    virtual void publicEndRemoveRows() = 0;

    /// @see QAbstractItemModel::beginResetModel
    virtual void publicBeginResetModel() = 0;

    /// @see QAbstractItemModel::endResetModel
    virtual void publicEndResetModel() = 0;

    /// @see QAbstractItemModel::dataChanged
    virtual void publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()) = 0;

};
} // namespace dos
