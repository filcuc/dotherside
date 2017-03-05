#include "DOtherSide/DosQDeclarative.h"
#include "DOtherSide/DosQObjectWrapper.h"
#include "DOtherSide/DosQAbstractItemModelWrapper.h"

namespace DOS {

bool isQAbstractItemModel(const QMetaObject *metaObject)
{
    const QMetaObject *current = metaObject;
    while (current) {
        if (&QAbstractItemModel::staticMetaObject == current)
            return true;
        current = current->superClass();
    }
    return false;
}

int dosQmlRegisterType(QmlRegisterType args)
{
    static int i = 0;
    static int j = 0;
    if (isQAbstractItemModel(args.staticMetaObject->metaObject()))
        return DQAIMW::DosQmlRegisterHelper<35>::Register(j++, std::move(args));
    else
        return DQOW::DosQmlRegisterHelper<35>::Register(i++, std::move(args));
}

int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    static int i = 0;
    static int j = 0;
    if (isQAbstractItemModel(args.staticMetaObject->metaObject()))
        return DQAIMW::DosQmlRegisterSingletonHelper<35>::Register(j++, std::move(args));
    else
        return DQOW::DosQmlRegisterSingletonHelper<35>::Register(i++, std::move(args));
}

}
