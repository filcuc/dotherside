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

#include "DOtherSide/DosQDeclarative.h"
#include "DOtherSide/DosQObjectWrapper.h"
#include "DOtherSide/DosQAbstractItemModelWrapper.h"

namespace DOS {

template<class T>
bool isItemModel(const QMetaObject *metaObject)
{
    const QMetaObject *current = metaObject;
    while (current) {
        if (&T::staticMetaObject == current)
            return true;
        current = current->superClass();
    }
    return false;
}

int dosQmlRegisterType(QmlRegisterType args)
{
    static int i = 0;
    static int j = 0;
    if (isItemModel<QAbstractListModel>(args.staticMetaObject->metaObject()))
        return DQAIMW::DosQmlRegisterHelper<QAbstractListModel, 35>::Register(j++, std::move(args));
    else if (isItemModel<QAbstractTableModel>(args.staticMetaObject->metaObject()))
        return DQAIMW::DosQmlRegisterHelper<QAbstractTableModel, 35>::Register(j++, std::move(args));
    else if (isItemModel<QAbstractItemModel>(args.staticMetaObject->metaObject()))
        return DQAIMW::DosQmlRegisterHelper<QAbstractItemModel, 35>::Register(j++, std::move(args));
    else
        return DQOW::DosQmlRegisterHelper<35>::Register(i++, std::move(args));
}

int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    static int i = 0;
    static int j = 0;
    if (isItemModel<QAbstractListModel>(args.staticMetaObject->metaObject()))
        return DQAIMW::DosQmlRegisterSingletonHelper<QAbstractListModel, 35>::Register(j++, std::move(args));
    else if (isItemModel<QAbstractTableModel>(args.staticMetaObject->metaObject()))
        return DQAIMW::DosQmlRegisterSingletonHelper<QAbstractTableModel, 35>::Register(j++, std::move(args));
    else if (isItemModel<QAbstractItemModel>(args.staticMetaObject->metaObject()))
        return DQAIMW::DosQmlRegisterSingletonHelper<QAbstractItemModel, 35>::Register(j++, std::move(args));
    else
        return DQOW::DosQmlRegisterSingletonHelper<35>::Register(i++, std::move(args));
}

}
