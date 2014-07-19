#include "Mockprinter.h"
#include <QtCore/QVariant>
#include <QtCore/QDebug>

MockPrinter::MockPrinter(QObject *parent) :
    QObject(parent)
{
}


void MockPrinter::print(const QVariant& message)
{
    emit printed(message);
}
