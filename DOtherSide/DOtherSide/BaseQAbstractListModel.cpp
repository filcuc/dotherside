#include "BaseQAbstractListModel.h"

BaseQAbstractListModel::BaseQAbstractListModel()
{
}

int BaseQAbstractListModel::rowCount(const QModelIndex& index) const 
{
  return 0;
}

QVariant BaseQAbstractListModel::data(const QModelIndex& index, int role) const
{
  return QVariant();
}
