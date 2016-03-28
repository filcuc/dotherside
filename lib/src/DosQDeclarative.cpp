#include "DOtherSide/DosQDeclarative.h"
#include "DOtherSide/DosQObjectWrapper.h"
#include "DOtherSide/DosQAbstractListModelWrapper.h"

namespace DOS {

bool isQAbstractListModel(const QMetaObject *metaObject)
{
    const QMetaObject *current = metaObject;
    while (current) {
        if (&QAbstractListModel::staticMetaObject == current)
            return true;
        current = current->superClass();
    }
    return false;
}

int dosQmlRegisterType(QmlRegisterType args)
{
    static int i = 0;
    static int j = 0;
    if (isQAbstractListModel(args.staticMetaObject->metaObject()))
        return DQALMW::DosQmlRegisterHelper<35>::Register(j++, std::move(args));
    else
        return DQOW::DosQmlRegisterHelper<35>::Register(i++, std::move(args));
}

int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    static int i = 0;
    static int j = 0;
    if (isQAbstractListModel(args.staticMetaObject->metaObject()))
        return DQALMW::DosQmlRegisterSingletonHelper<35>::Register(j++, std::move(args));
    else
        return DQOW::DosQmlRegisterSingletonHelper<35>::Register(i++, std::move(args));
}

}
