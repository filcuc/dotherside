#pragma once

#include "DOtherSide/DOtherSideTypes.h"

#include <QtCore/QObject>

namespace DOS {
    int dosQmlRegisterType(QmlRegisterType args);
    int dosQmlRegisterSingletonType(QmlRegisterType args);
}
