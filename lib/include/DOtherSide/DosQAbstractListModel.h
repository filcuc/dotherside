#pragma once

// Qt
#include <QAbstractListModel>
// DOtherSide
#include "DOtherSide/DOtherSideTypes.h"
#include "DOtherSide/DosQObject.h"

namespace DOS
{

class DosQAbstractListModel : public QAbstractListModel, public IDosQObject
{
public:
    /// Constructor
    DosQAbstractListModel(void* modelObject,
                          std::shared_ptr<const IDosQMetaObject> metaObject,
                          OnSlotExecuted onSlotExecuted,
                          RowCountCallback rowCountCallback,
                          ColumnCountCallback columnCountCallback,
                          DataCallback dataCallback,
                          SetDataCallback setDataCallback,
                          RoleNamesCallback roleNamesCallback,
                          FlagsCallback flagsCallback,
                          HeaderDataCallback headerDataCallback);

    /// @see IDynamicQObject::emitSignal
    bool emitSignal(const QString &name, const std::vector<QVariant> &argumentsValues) override;

    /// @see QAbstractListModel::metaObject()
    const QMetaObject *metaObject() const override;

    /// @see QAbstractListModel::qt_metacall
    int qt_metacall(QMetaObject::Call, int, void **) override;

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
    IDosQObject* m_impl;
    void* m_modelObject;
    RowCountCallback m_rowCountCallback;
    ColumnCountCallback m_columnCountCallback;
    DataCallback m_dataCallback;
    SetDataCallback m_setDataCallback;
    RoleNamesCallback m_roleNamesCallback;
    FlagsCallback m_flagsCallback;
    HeaderDataCallback m_headerDataCallback;
};

} // namespace DOS
