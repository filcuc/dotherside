#include "BaseQAbstractListModel.h"

BaseQAbstractListModel::BaseQAbstractListModel(void* modelObject,
					       RowCountCallback rowCountCallback)
  : m_modelObject(modelObject)
  , m_rowCountCallback(rowCountCallback)
{
}

int BaseQAbstractListModel::rowCount(const QModelIndex& index) const 
{
  auto newIndex = new QModelIndex();
  *newIndex = index;
  return m_rowCountCallback(m_modelObject, newIndex);
}

QVariant BaseQAbstractListModel::data(const QModelIndex& index, int role) const
{
  return QVariant();
}

void* BaseQAbstractListModel::modelObject()
{
  return m_modelObject;
}
