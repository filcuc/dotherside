#include "BaseQAbstractListModel.h"

BaseQAbstractListModel::BaseQAbstractListModel(void* modelObject,
					       RowCountCallback rowCountCallback)
  : m_modelObject(modelObject)
  , m_rowCountCallback(rowCountCallback)
{
}

int BaseQAbstractListModel::rowCount(const QModelIndex& index) const 
{
  return m_rowCountCallback(m_modelObject);
}

QVariant BaseQAbstractListModel::data(const QModelIndex& index, int role) const
{
  return QVariant();
}

void* BaseQAbstractListModel::modelObject()
{
  return m_modelObject;
}
