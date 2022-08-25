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

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QMetaMethod>

#include <mutex>
#include <memory>
#include <unordered_map>

#include "DOtherSideTypes.h"

namespace DOS {

class LambdaInvoker final : public QObject
{
public:
    LambdaInvoker(DosQObjectConnectLambdaCallback callback,
                  void* callbackData,
                  QMetaObject* metaObject,
                  int slotIndex);

    LambdaInvoker(DosQObjectConnectLambdaCallback callback,
                  void* callbackData,
                  QObject* context,
                  QMetaObject* metaObject,
                  int slotIndex);

    ~LambdaInvoker();

    const char* invokeSlotSignature() const;

    const QMetaObject* metaObject() const final;

    int qt_metacall(QMetaObject::Call call, int index, void **args) final;

private:
    void invoke(void** args);
    void invoke(std::vector<QVariant> const& args);

    QMetaObject* const m_metaObject = nullptr;
    const QMetaMethod m_method;
    DosQObjectConnectLambdaCallback m_callback = nullptr;
    void* m_callbackData = nullptr;
    bool m_checkContext = false;
    QPointer<QObject> m_context = nullptr;
};

class LambdaInvokerRegistry
{
public:
    static LambdaInvokerRegistry& instance();

    ~LambdaInvokerRegistry();

    std::unique_ptr<QMetaObject::Connection> add(::DosQObject *sender, const char *signal,
                                                 DosQObjectConnectLambdaCallback callback,
                                                 void *callbackData,
                                                 DosQtConnectionType connection_type);

    std::unique_ptr<QMetaObject::Connection> add(::DosQObject *sender, const char *signal, ::DosQObject *context,
                                                 DosQObjectConnectLambdaCallback callback,
                                                 void *callbackData,
                                                 DosQtConnectionType connection_type);

    void remove(QMetaObject::Connection* connection);

private:
    std::mutex mutex;
    std::unordered_map<QMetaObject::Connection*, LambdaInvoker*> lambdas;
};

}
