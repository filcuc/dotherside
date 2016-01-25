#pragma once

#include "DOtherSide/DOtherSideTypes.h"

#include <QtCore/QObject>

namespace DOS {
    int dosQmlRegisterType(const char* uri, int major, int minor,
                           const char* qmlName,
                           const QMetaObject& staticMetaObject,
                           CreateDObject createDObject,
                           DeleteDObject deleteDObject);
}
