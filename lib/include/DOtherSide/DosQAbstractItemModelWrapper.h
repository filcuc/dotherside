/*
    Copyright (C) 2020 Filippo Cucchetto.
    Contact: https://github.com/filcuc/dotherside

    This file is part of the DOtherSide library.

    The DOtherSide library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the license, or (at your opinion) any later version.

    The DOtherSide library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with the DOtherSide library.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <QtQml/QQmlEngine>

#include "DOtherSide/DosQAbstractItemModel.h"
#include "DOtherSide/DosQMetaObject.h"

namespace DOS {
template <typename T, int, int>
class DosQAbstractItemModelWrapper : public T, public DosIQAbstractItemModelImpl
{
public:
    static const QMetaObject staticMetaObject;

    /// Constructor
    DosQAbstractItemModelWrapper(QObject *parent = nullptr);

    /// Destructor
    ~DosQAbstractItemModelWrapper() override;

    /// @see DosIQObjectImpl::metaObject
    const QMetaObject *metaObject() const override;

    /// @see DosIQObjectImpl::qt_metacall
    int qt_metacall(QMetaObject::Call, int, void **) override;

    /// @see DosIQObjectImpl::emitSignal
    bool emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &argumentsValues) override;

    /// Return the qml registration type
    static const QmlRegisterType &qmlRegisterType();

    /// Sets the qml registration type
    static void setQmlRegisterType(QmlRegisterType data);

    /// Sets the static metaobject
    static void setStaticMetaObject(const QMetaObject &metaObject);

    /// Sets the qmlRegisterType id
    static void setId(int id);

    /// @see QAbstractItemModel::rowCount
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// @see QAbstractItemModel::columnCount
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /// @see QAbstractItemModel::data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// @see QAbstractItemModel::setData
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /// @see QAbstractItemModel::flags
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /// @see QAbstractItemModel::headerData
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /// @see QAbstractItemModel::roleNames
    QHash<int, QByteArray> roleNames() const override;

    /// @see QAbstractItemModel::index
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    /// @see QAbstractItemModel::parent
    QModelIndex parent(const QModelIndex &child) const override;

    void publicBeginInsertRows(const QModelIndex &index, int first, int last) final;
    void publicEndInsertRows() final;
    void publicBeginRemoveRows(const QModelIndex &index, int first, int last) final;
    void publicEndRemoveRows() final;
    void publicBeginInsertColumns(const QModelIndex &index, int first, int last) final;
    void publicEndInsertColumns() final;
    void publicBeginRemoveColumns(const QModelIndex &index, int first, int last) final;
    void publicEndRemoveColumns() final;
    void publicBeginResetModel() final;
    void publicEndResetModel() final;
    void publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) final;
    QModelIndex publicCreateIndex(int row, int column, void *data) const final;
    bool hasIndex(int row, int column, const QModelIndex &parent) const final;

private:
    void *m_dObject = nullptr;
    QAbstractItemModel *m_impl = nullptr;
    DosIQAbstractItemModelImpl * m_dosImpl = nullptr;
    static int m_id;
    static QmlRegisterType m_data;
};

template<typename T, int N, int M>
const QMetaObject DosQAbstractItemModelWrapper<T, N, M>::staticMetaObject = T::staticMetaObject;

template<typename T, int N, int M>
QmlRegisterType DosQAbstractItemModelWrapper<T, N, M>::m_data;

template<typename T, int N, int M>
int DosQAbstractItemModelWrapper<T, N, M>::m_id = -1;

template<typename T, int N, int M>
DosQAbstractItemModelWrapper<T, N, M>::DosQAbstractItemModelWrapper(QObject *parent)
    : T(parent)
{
    void *impl = nullptr;
    m_data.createDObject(m_id, static_cast<QObject *>(this), &m_dObject, &impl);
    m_impl = dynamic_cast<QAbstractItemModel *>(static_cast<QObject *>(impl));
    m_dosImpl = dynamic_cast<DosIQAbstractItemModelImpl *>(static_cast<QObject *>(impl));
    QObject::connect(m_impl, &T::rowsAboutToBeInserted, this, &DosQAbstractItemModelWrapper<T, N, M>::beginInsertRows);
    QObject::connect(m_impl, &T::rowsInserted, this, &DosQAbstractItemModelWrapper<T, N, M>::endInsertRows);
    QObject::connect(m_impl, &T::rowsAboutToBeRemoved, this, &DosQAbstractItemModelWrapper<T, N, M>::beginRemoveRows);
    QObject::connect(m_impl, &T::rowsRemoved, this, &DosQAbstractItemModelWrapper<T, N, M>::endRemoveRows);
    QObject::connect(m_impl, &T::rowsAboutToBeMoved, this, &DosQAbstractItemModelWrapper<T, N, M>::beginMoveRows);
    QObject::connect(m_impl, &T::rowsMoved, this, &DosQAbstractItemModelWrapper<T, N, M>::endMoveRows);
    QObject::connect(m_impl, &T::columnsAboutToBeInserted, this, &DosQAbstractItemModelWrapper<T, N, M>::beginInsertColumns);
    QObject::connect(m_impl, &T::columnsInserted, this, &DosQAbstractItemModelWrapper<T, N, M>::endInsertColumns);
    QObject::connect(m_impl, &T::columnsAboutToBeRemoved, this, &DosQAbstractItemModelWrapper<T, N, M>::beginRemoveColumns);
    QObject::connect(m_impl, &T::columnsRemoved, this, &DosQAbstractItemModelWrapper<T, N, M>::endRemoveColumns);
    QObject::connect(m_impl, &T::columnsAboutToBeMoved, this, &DosQAbstractItemModelWrapper<T, N, M>::beginMoveColumns);
    QObject::connect(m_impl, &T::columnsMoved, this, &DosQAbstractItemModelWrapper<T, N, M>::endMoveColumns);
    QObject::connect(m_impl, &T::modelAboutToBeReset, this, &DosQAbstractItemModelWrapper<T, N, M>::beginResetModel);
    QObject::connect(m_impl, &T::modelReset, this, &DosQAbstractItemModelWrapper<T, N, M>::endResetModel);
    QObject::connect(m_impl, &T::dataChanged, this, &DosQAbstractItemModelWrapper<T, N, M>::dataChanged);
    QObject::connect(m_impl, &T::layoutAboutToBeChanged, this, &DosQAbstractItemModelWrapper<T, N, M>::layoutAboutToBeChanged);
    QObject::connect(m_impl, &T::layoutChanged, this, &DosQAbstractItemModelWrapper<T, N, M>::layoutChanged);
    Q_ASSERT(m_dObject);
    Q_ASSERT(m_impl);
}

template<typename T, int N, int M>
DosQAbstractItemModelWrapper<T, N, M>::~DosQAbstractItemModelWrapper()
{
    m_data.deleteDObject(m_id, m_dObject);
    m_dObject = nullptr;
    delete m_impl;
    m_impl = nullptr;
}

template<typename T, int N, int M>
const QMetaObject *DosQAbstractItemModelWrapper<T, N, M>::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

template<typename T, int N, int M>
int DosQAbstractItemModelWrapper<T, N, M>::qt_metacall(QMetaObject::Call call, int index, void **args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(call, index, args);
}

template<typename T, int N, int M>
bool DosQAbstractItemModelWrapper<T, N, M>::emitSignal(QObject *, const QString &name, const std::vector<QVariant> &argumentsValues)
{
    Q_ASSERT(m_impl);
    return m_dosImpl->emitSignal(this, name, argumentsValues);
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::setQmlRegisterType(QmlRegisterType data)
{
    m_data = std::move(data);
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::setStaticMetaObject(const QMetaObject &metaObject)
{
    *(const_cast<QMetaObject *>(&staticMetaObject)) = metaObject;
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::setId(int id)
{
    m_id = id;
}

template<typename T, int N, int M>
int DosQAbstractItemModelWrapper<T, N, M>::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(m_impl);
    return m_impl->rowCount(parent);
}

template<typename T, int N, int M>
int DosQAbstractItemModelWrapper<T, N, M>::columnCount(const QModelIndex &parent) const
{
    Q_ASSERT(m_impl);
    return m_impl->columnCount(parent);
}

template<typename T, int N, int M>
QVariant DosQAbstractItemModelWrapper<T, N, M>::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(m_impl);
    return m_impl->data(index, role);
}

template<typename T, int N, int M>
bool DosQAbstractItemModelWrapper<T, N, M>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_ASSERT(m_impl);
    return m_impl->setData(index, value, role);
}

template<typename T, int N, int M>
Qt::ItemFlags DosQAbstractItemModelWrapper<T, N, M>::flags(const QModelIndex &index) const
{
    Q_ASSERT(m_impl);
    return m_impl->flags(index);
}

template<typename T, int N, int M>
QVariant DosQAbstractItemModelWrapper<T, N, M>::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_ASSERT(m_impl);
    return m_impl->headerData(section, orientation, role);
}

template<typename T, int N, int M>
QHash<int, QByteArray> DosQAbstractItemModelWrapper<T, N, M>::roleNames() const
{
    Q_ASSERT(m_impl);
    return m_impl->roleNames();
}

template<typename T, int N, int M>
QModelIndex DosQAbstractItemModelWrapper<T, N, M>::index(int row, int column, const QModelIndex &parent) const
{
    Q_ASSERT(m_impl);
    return m_impl->index(row, column, parent);
}

template<typename T, int N, int M>
QModelIndex DosQAbstractItemModelWrapper<T, N, M>::parent(const QModelIndex &child) const
{
    Q_ASSERT(m_impl);
    return m_impl->parent(child);
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicBeginInsertRows(const QModelIndex &index, int first, int last)
{
    m_dosImpl->publicBeginInsertRows(index, first, last);
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicEndInsertRows()
{
    m_dosImpl->publicEndInsertRows();
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicBeginRemoveRows(const QModelIndex &index, int first, int last)
{
    m_dosImpl->publicBeginRemoveRows(index, first, last);
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicEndRemoveRows()
{
    m_dosImpl->publicEndRemoveRows();
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicBeginInsertColumns(const QModelIndex &index, int first, int last)
{
    m_dosImpl->publicBeginInsertColumns(index, first, last);
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicEndInsertColumns()
{
    m_dosImpl->publicEndInsertColumns();
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicBeginRemoveColumns(const QModelIndex &index, int first, int last)
{
    m_dosImpl->publicBeginRemoveColumns(index, first, last);
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicEndRemoveColumns()
{
    m_dosImpl->publicEndRemoveColumns();
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicBeginResetModel()
{
    m_dosImpl->publicBeginResetModel();
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicEndResetModel()
{
    m_dosImpl->publicEndResetModel();
}

template<typename T, int N, int M>
void DosQAbstractItemModelWrapper<T, N, M>::publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    m_dosImpl->publicDataChanged(topLeft, bottomRight, roles);
}

template<typename T, int N, int M>
QModelIndex DosQAbstractItemModelWrapper<T, N, M>::publicCreateIndex(int row, int column, void *data) const
{
    return m_dosImpl->publicCreateIndex(row, column, data);
}

template<typename T, int N, int M>
bool DosQAbstractItemModelWrapper<T, N, M>::hasIndex(int row, int column, const QModelIndex &parent) const
{
    return m_dosImpl->hasIndex(row, column, parent);
}

template<typename T, int N, int M>
const QmlRegisterType &DosQAbstractItemModelWrapper<T, N, M>::qmlRegisterType()
{
    return m_data;
}

namespace DQAIMW {

template<typename T, int N>
using RegisterTypeQObject = DosQAbstractItemModelWrapper<T, N, 0>;

template<typename T, int N>
int dosQmlRegisterType(QmlRegisterType args)
{
    RegisterTypeQObject<T, N>::setQmlRegisterType(std::move(args));
    const QmlRegisterType &type = RegisterTypeQObject<T, N>::qmlRegisterType();
    RegisterTypeQObject<T, N>::setStaticMetaObject(*(type.staticMetaObject->metaObject()));
    int result = qmlRegisterType<RegisterTypeQObject<T, N>>(type.uri.c_str(), type.major, type.minor, type.qml.c_str());
    RegisterTypeQObject<T, N>::setId(result);
    return result;
}

template<typename T, int N>
struct DosQmlRegisterHelper {
    static int Register(int i, QmlRegisterType args)
    {
        if (i > N)
            return -1;
        else if (i == N)
            return dosQmlRegisterType<T, N>(std::move(args));
        else
            return DosQmlRegisterHelper <T, N - 1>::Register(i, std::move(args));
    }
};

template<typename T>
struct DosQmlRegisterHelper<T, 0> {
    static int Register(int i, QmlRegisterType args)
    {
        return i == 0 ? dosQmlRegisterType<T, 0>(std::move(args)) : -1;
    }
};

template<typename T, int N>
using RegisterSingletonTypeQObject = DosQAbstractItemModelWrapper<T, N, 1>;

template<typename T, int N>
QObject *singletontype_provider(QQmlEngine *, QJSEngine *)
{
    return new RegisterSingletonTypeQObject<T, N>();
}

template<typename T, int N>
int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    using Func = QObject * (*)(QQmlEngine *, QJSEngine *);
    Func f = singletontype_provider<T, N>;

    RegisterSingletonTypeQObject<T, N>::setQmlRegisterType(std::move(args));
    const QmlRegisterType &type = RegisterSingletonTypeQObject<T, N>::qmlRegisterType();
    RegisterSingletonTypeQObject<T, N>::setStaticMetaObject(*(type.staticMetaObject->metaObject()));
    int result = qmlRegisterSingletonType<RegisterSingletonTypeQObject<T, N>>(type.uri.c_str(), type.major, type.minor, type.qml.c_str(), f);
    RegisterSingletonTypeQObject<T, N>::setId(result);
    return result;
}

template<typename T, int N>
struct DosQmlRegisterSingletonHelper {
    static int Register(int i, QmlRegisterType args)
    {
        if (i > N)
            return -1;
        else if (i == N)
            return dosQmlRegisterSingletonType<T, N>(std::move(args));
        else
            return DosQmlRegisterSingletonHelper <T, N - 1>::Register(i, std::move(args));
    }
};

template<typename T>
struct DosQmlRegisterSingletonHelper<T, 0> {
    static int Register(int i, QmlRegisterType args)
    {
        return i == 0 ? dosQmlRegisterSingletonType<T, 0>(std::move(args)) : -1;
    }
};

}
}
