#include "DOtherSide/DosQDeclarative.h"
#include "DOtherSide/DosQObjectWrapper.h"

namespace DOS {

int dosQmlRegisterType(QmlRegisterType args)
{
    static int i = 0;
    return DosQmlRegisterHelper<35>::Register(i++, std::move(args));
}

int dosQmlRegisterSingletonType(QmlRegisterType args)
{
    static int i = 0;
    return DosQmlRegisterSingletonHelper<35>::Register(i++, std::move(args));
}

}
