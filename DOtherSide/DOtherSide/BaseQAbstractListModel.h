#pragma once

#include <QAbstractListModel>

/// This class act as a base class for D and Nim QAbstractListModel
class BaseQAbstractListModel : public QAbstractListModel
{
  typedef int (*RowCountCallback) (void*);
  
 public:
  /// Constructor
  BaseQAbstractListModel(void* modelObject, RowCountCallback rowCountCallback);

  /// Return the model's row count
  virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;

  /// Return the QVariant at the given index 
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

  /// Return the dModelPointer
  void* modelObject();
  
 private:
  void* m_modelObject;
  RowCountCallback m_rowCountCallback;
};
