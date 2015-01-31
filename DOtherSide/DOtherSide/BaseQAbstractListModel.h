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
                         DataCallback dataCallback);

  /// Return the model's row count
  virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;

  /// Return the QVariant at the given index 
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

  /// Return the dModelPointer
  void* modelObject();
  
  /// Return the roleNames
  virtual QHash<int, QByteArray> roleNames() const override;
  
 private:
  void* m_modelObject;
  RowCountCallback m_rowCountCallback;
  DataCallback m_dataCallback;
};
