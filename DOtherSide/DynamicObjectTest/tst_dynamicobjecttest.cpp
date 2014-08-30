#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "Mockprinter.h"
#include "DynamicQObject.h"

class DynamicObjectTest : public QObject
{
    Q_OBJECT

public:
    DynamicObjectTest();

private Q_SLOTS:
    void dynamicSignalToRealSlotConnectTest();
    void realSignalToDynamicSlotConnectTest();
};

DynamicObjectTest::DynamicObjectTest()
{
}

void DynamicObjectTest::dynamicSignalToRealSlotConnectTest()
{
    DynamicQObject dynamicQObject;
    int index;
    dynamicQObject.registerSignal("message", {QMetaType::QVariant}, index);

    MockPrinter printer;
    QObject::connect(&dynamicQObject, SIGNAL(message(QVariant)), &printer, SLOT(print(QVariant)));

    dynamicQObject.emitSignal("message", {"Hello"});
}

void DynamicObjectTest::realSignalToDynamicSlotConnectTest()
{
    DynamicQObject dynamicQObject;
    int slotIndex;
    dynamicQObject.registerSlot("print", QMetaType::Void, {QMetaType::QVariant}, slotIndex);
    MockPrinter printer;
    QObject::connect(&printer, SIGNAL(printed(QVariant)), &dynamicQObject, SLOT(print(QVariant)));
    printer.print("Hello");
}

QTEST_MAIN(DynamicObjectTest)

#include "tst_dynamicobjecttest.moc"
