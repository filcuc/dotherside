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

#include <QtCore/QMetaMethod>

namespace DOS {

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))

inline QMetaType parameterMetaType(const QMetaMethod& method, int index)
{
    return method.parameterMetaType(index);
}

inline QMetaType returnMetaType(const QMetaMethod& method)
{
    return method.returnMetaType();
}

inline bool isString(const QVariant& v)
{
    return v.typeId() == QMetaType::QString;
}

inline bool isBool(const QVariant& v)
{
    return v.typeId() == QMetaType::Bool;
}

inline bool haveSameType(const QVariant& lhs, const QVariant& rhs)
{
    return lhs.typeId() == rhs.typeId();
}

inline const char* metaTypeName(QMetaType::Type type)
{
    return QMetaType(type).name();
}

#else

inline int parameterMetaType(const QMetaMethod& method, int index)
{
    return method.parameterType(index);
}

inline int returnMetaType(const QMetaMethod& method)
{
    return method.returnType();
}

inline bool isString(const QVariant& v)
{
    return v.type() == QVariant::String;
}

inline bool isBool(const QVariant& v)
{
    return v.type() == QVariant::Bool;
}

inline bool haveSameType(const QVariant& lhs, const QVariant& rhs)
{
    return lhs.type() == rhs.type();
}

inline const char* metaTypeName(QMetaType::Type type)
{
    return QMetaType::typeName(type);
}

#endif

}
