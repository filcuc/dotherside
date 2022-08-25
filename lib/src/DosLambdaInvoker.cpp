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

#include "DOtherSide/DosLambdaInvoker.h"
#include "DOtherSide/DosQtCompatUtils.h"

#include <memory>

#include <QtCore/private/qmetaobjectbuilder_p.h>
#include <QtCore/QThread>
#include <QtCore/QDebug>


namespace {

DOS::LambdaInvoker* MakeInvoker(DosQObjectConnectLambdaCallback callback, void *callbackData, QObject *context, const QString &signalSignature)
{
    auto begin = signalSignature.indexOf("(");
    if (begin < 0)
        return nullptr;

    auto end = signalSignature.lastIndexOf(")");
    if (end < 0 || begin >= end)
        return nullptr;

    const QString signalTypes = signalSignature.mid(begin + 1, end - begin - 1).trimmed();
    const std::string slotSignatureString = QString("invoke(%1)").arg(signalTypes).toStdString();
    const char* const slotSignature = slotSignatureString.c_str();

    QMetaObjectBuilder builder;
    builder.setClassName("LambdaInvoker");
    builder.setSuperClass(&QObject::staticMetaObject);
    auto slot = builder.addSlot(slotSignature);
    slot.setReturnType(DOS::metaTypeName(QMetaType::Void));
    slot.setAttributes(QMetaMethod::Scriptable);

    const auto metaObject = builder.toMetaObject();
    return new DOS::LambdaInvoker(callback, callbackData, context, metaObject, metaObject->indexOfSlot(slotSignature));
}

}

DOS::LambdaInvoker::LambdaInvoker(DosQObjectConnectLambdaCallback callback, void *callbackData, QObject *context, QMetaObject* metaObject, int slotIndex)
    : m_metaObject(metaObject)
    , m_method(metaObject->method(slotIndex))
    , m_callback(callback)
    , m_callbackData(callbackData)
    , m_checkContext(context)
    , m_context(context)
{
}

DOS::LambdaInvoker::LambdaInvoker(DosQObjectConnectLambdaCallback callback, void* callbackData, QMetaObject* metaObject, int slotIndex)
    : DOS::LambdaInvoker(callback, callbackData, nullptr, metaObject, slotIndex)
{

}

DOS::LambdaInvoker::~LambdaInvoker()
{
    free(m_metaObject);
}

const char *DOS::LambdaInvoker::invokeSlotSignature() const
{
    return m_method.methodSignature().prepend("1");
}

const QMetaObject *DOS::LambdaInvoker::metaObject() const {
    return m_metaObject;
}

int DOS::LambdaInvoker::qt_metacall(QMetaObject::Call call, int index, void **args)
{
    if (call == QMetaObject::InvokeMetaMethod)
        if (m_method.methodIndex() == index)
            invoke(args);
    return -1;
}

void DOS::LambdaInvoker::invoke(void **args) {
    std::vector<QVariant> arguments(m_method.parameterCount());
    for (int i = 0, j = 1; i < m_method.parameterCount(); ++i, ++j)
        arguments[i] = QVariant(DOS::parameterMetaType(m_method, i), args[j]);

    invoke(arguments);
}

void DOS::LambdaInvoker::invoke(const std::vector<QVariant> &args) {
    std::vector<void *> argsPointers(args.size());
    for (size_t i = 0; i < args.size(); ++i)
        argsPointers[i] = ((void *)(&args[i]));

    if (m_checkContext && !m_context)
        return;

    if (m_callback)
        m_callback(m_callbackData, static_cast<int>(argsPointers.size()), argsPointers.data());
}

DOS::LambdaInvokerRegistry &DOS::LambdaInvokerRegistry::instance()
{
    static DOS::LambdaInvokerRegistry instance;
    return instance;
}

DOS::LambdaInvokerRegistry::~LambdaInvokerRegistry()
{
    for (auto const& pair : lambdas)
        pair.second->deleteLater();
}

std::unique_ptr<QMetaObject::Connection> DOS::LambdaInvokerRegistry::add(DosQObject *sender, const char *signal,
                                                        DosQObjectConnectLambdaCallback callback, void *callbackData,
                                                        DosQtConnectionType connection_type)
{
    std::unique_lock<std::mutex> lock(mutex);
    auto invoker = ::MakeInvoker(callback, callbackData, nullptr, signal);
    auto result = QObject::connect(static_cast<QObject*>(sender), signal, invoker, invoker->invokeSlotSignature(), static_cast<Qt::ConnectionType>(connection_type));
    return std::unique_ptr<QMetaObject::Connection>(new QMetaObject::Connection(result));
}

std::unique_ptr<QMetaObject::Connection> DOS::LambdaInvokerRegistry::add(DosQObject *sender, const char *signal, DosQObject *context,
                                                        DosQObjectConnectLambdaCallback callback, void *callbackData,
                                                        DosQtConnectionType connection_type)
{
    std::unique_lock<std::mutex> lock(mutex);
    auto invoker = ::MakeInvoker(callback, callbackData, static_cast<QObject*>(context), signal);
    auto result = QObject::connect(static_cast<QObject*>(sender), signal, invoker, invoker->invokeSlotSignature(), static_cast<Qt::ConnectionType>(connection_type));
    return std::unique_ptr<QMetaObject::Connection>(new QMetaObject::Connection(result));
}

void DOS::LambdaInvokerRegistry::remove(QMetaObject::Connection *connection)
{
    std::unique_lock<std::mutex> lock(mutex);
    auto it = lambdas.find(connection);
    if (it != lambdas.end())
    {
        it->second->deleteLater();
        lambdas.erase(it);
    }
}
