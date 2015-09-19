#include <QTest>
#include <QSignalSpy>
#include "../src/DynamicQObject.h"

class TestDynamicQObject : public QObject
{
    Q_OBJECT

private slots:
    void memoryLeakTest() {
        DynamicQObject<QObject> dynamicQObject;
    }

    void testRegisterSignal() {
        DynamicQObject<QObject> dynamicQObject;
        int index;
        dynamicQObject.registerSignal("fooSignal", {}, index);
        QCOMPARE(index != -1, true);

        QSignalSpy signalSpy(&dynamicQObject, SIGNAL(fooSignal()));
        dynamicQObject.emitSignal("fooSignal", {});
        QCOMPARE(signalSpy.count(), 1);
    }

    void testRegisterSlot() {
        DynamicQObject<QObject> dynamicQObject;
        int index;
        dynamicQObject.registerSlot("fooSlot", QMetaType::Void, {}, index);
        QCOMPARE(index != -1, true);
    }

    void testRegisterProperty() {
        DynamicQObject<QObject> dynamicQObject;
        int index = -1;
        bool result = false;
        result = dynamicQObject.registerSlot("foo", QMetaType::Int, {}, index);
        QCOMPARE(index != -1, true);
        QCOMPARE(result, true);
        result = dynamicQObject.registerSlot("setFoo", QMetaType::Void, {QMetaType::Int}, index);
        QCOMPARE(index != -1, true);
        QCOMPARE(result, true);
        result = dynamicQObject.registerSignal("fooChanged", {QMetaType::Int}, index);
        QCOMPARE(index != -1, true);
        QCOMPARE(result, true);
        result = dynamicQObject.registerProperty("foo", QMetaType::Int, "foo", "setFoo", "fooChanged");
        QCOMPARE(result, true);
    }
};

QTEST_MAIN(TestDynamicQObject)

#include "test_dynamicqobject.moc"
