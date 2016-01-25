#include "DOtherSide/DosQObjectWrapper.h"
#include "DOtherSide/DosIQObjectImpl.h"
#include "DOtherSide/DosQObject.h"
#include <QDebug>

namespace DOS {

const QMetaObject DosQObjectWrapper::staticMetaObject = QObject::staticMetaObject;
CreateDObject DosQObjectWrapper::m_createDObject;
DeleteDObject DosQObjectWrapper::m_deleteDObject;

DosQObjectWrapper::DosQObjectWrapper(QObject *parent)
    : QObject(parent)
    , m_dObject(nullptr)
    , m_impl(nullptr)
{
    void* impl = nullptr;
    m_createDObject(&m_dObject, &impl);
    m_impl = static_cast<DosQObject*>(impl);
    Q_ASSERT(m_dObject);
    Q_ASSERT(m_impl);
}

DosQObjectWrapper::~DosQObjectWrapper()
{
    m_deleteDObject(m_dObject);
    m_dObject = nullptr;
    m_impl = nullptr;
}

const QMetaObject *DosQObjectWrapper::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

int DosQObjectWrapper::qt_metacall(QMetaObject::Call call, int index, void **args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(call, index, args);
}

CreateDObject DosQObjectWrapper::createDObject() { return m_createDObject; }

DeleteDObject DosQObjectWrapper::deleteDObject() { return m_deleteDObject; }

void DosQObjectWrapper::setCreateDObject(CreateDObject createDObject) { m_createDObject = createDObject; }

void DosQObjectWrapper::setDeleteDObject(DeleteDObject deleteDObject) { m_deleteDObject = deleteDObject; }

void DosQObjectWrapper::setStaticMetaObject(const QMetaObject &metaObject)
{
    *(const_cast<QMetaObject*>(&staticMetaObject)) = metaObject;
}

}
