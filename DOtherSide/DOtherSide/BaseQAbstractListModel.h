#pragma once

#include <QAbstractListModel>

/// This class act as a base class for D and Nim QAbstractListModel
class BaseQAbstractListModel : public QAbstractListModel
{
public:
  /// Constructor
  BaseQAbstractListModel();

  /// Return the model's row count
  virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;

  /// Return the QVariant at the given index 
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

};
