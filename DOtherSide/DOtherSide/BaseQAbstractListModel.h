#pragma once

#include "DOtherSideTypes.h"
#include <QAbstractListModel>

/// This class act as a base class for D and Nim QAbstractListModel
class BaseQAbstractListModel : public QAbstractListModel
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
