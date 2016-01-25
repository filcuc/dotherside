#pragma once

#include "DOtherSide/DOtherSideTypes.h"

#include <QtCore/QObject>

namespace DOS {
    class DosIQObjectImpl;
    class DosQObject;

    class DosQObjectWrapper : public QObject
    {
    public:
        static const QMetaObject staticMetaObject;

        DosQObjectWrapper(QObject *parent = nullptr);
        ~DosQObjectWrapper();

        const QMetaObject* metaObject() const override;
        int qt_metacall(QMetaObject::Call, int, void **) override;

        static CreateDObject createDObject();
        static DeleteDObject deleteDObject();
        static void setCreateDObject(CreateDObject createDObject);
        static void setDeleteDObject(DeleteDObject deleteDObject);
        static void setStaticMetaObject(const QMetaObject& metaObject);

    private:
        void* m_dObject;
        DosQObject* m_impl;
        static CreateDObject m_createDObject;
        static DeleteDObject m_deleteDObject;
    };
}
