// std
#include <tuple>
#include <iostream>
// Qt
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
// DOtherSide
#include "DOtherSide/BaseQObject.h"
#include "DOtherSide/DynamicQObject.h"

// Templates that convers a T to a string
template <typename T>
struct TypeName
{
    static const char* Get() { return typeid(T).name(); }
};
template <> struct TypeName<int> { static const char* Get() { return "int"; } };
template <> struct TypeName<QString> { static const char* Get() { return "QString"; } };
template <> struct TypeName<bool> { static const char* Get() { return "bool"; } };
template <> struct TypeName<QVariant> { static const char* Get() { return "QVariant"; } };

class TestDynamicQObject : public QObject
{
    Q_OBJECT

private slots:
    void memoryLeakTest() {
        DynamicQObject<QObject> dynamicQObject;
        BaseQObject baseQObject;
    }

    void testRegisterSignal() {
        DynamicQObject<QObject> dynamicQObject;
        int index;
        dynamicQObject.registerSignal("fooSignal", {}, index);
        QVERIFY(index != -1);

        QSignalSpy signalSpy(&dynamicQObject, SIGNAL(fooSignal()));
        dynamicQObject.emitSignal("fooSignal", {});
        QCOMPARE(signalSpy.count(), 1);
    }

    void testSlotExecution() {
        testSlotExecutionForType<int>(10);
        testSlotExecutionForType<QString>("foo");
        testSlotExecutionForType<bool>(false);
        testSlotExecutionForType<QVariant>(QVariant(40));
    }

    void testRegisterProperty() {
        DynamicQObject<QObject> dynamicQObject;
        int index = -1;
        bool result = false;
        result = dynamicQObject.registerSlot("foo", QMetaType::Int, {}, index);
        QVERIFY(index != -1);
        QVERIFY(result);
        result = dynamicQObject.registerSlot("setFoo", QMetaType::Void, {QMetaType::Int}, index);
        QVERIFY(index != -1);
        QVERIFY(result);
        result = dynamicQObject.registerSignal("fooChanged", {QMetaType::Int}, index);
        QVERIFY(index != -1);
        QVERIFY(result);
        result = dynamicQObject.registerProperty("foo", QMetaType::Int, "foo", "setFoo", "fooChanged");
        QVERIFY(result);;

        int propertyValue = -1;

        auto handler = [&propertyValue](const DynamicSlot &slot, const std::vector<QVariant> &args) -> QVariant {
            if (slot.name() == "foo")
                return propertyValue;
            else if (slot.name() == "setFoo")
                propertyValue = args.front().toInt();
            return QVariant();
        };

        dynamicQObject.setOnSlotExecutedHandler(handler);

        // Test property read
        QCOMPARE(dynamicQObject.property("foo").toInt(), -1);

        // Test property write and signal emittion
        dynamicQObject.setProperty("foo", 10);
        QCOMPARE(propertyValue, 10);
    }

private:
    template<typename ReturnType>
    void testSlotExecutionForType(ReturnType expectedReturnValue) {
        DynamicQObject<QObject> dynamicQObject;
        int index;
        auto type = static_cast<QMetaType::Type>(qMetaTypeId<ReturnType>());
        dynamicQObject.registerSlot("fooSlot", type, {type}, index);
        QVERIFY(index != -1);

        // Call the slot and check return value
        bool called = false;
        bool obtainedArgument = false;
        bool argumentMatch = false;
        auto handler = [&called, expectedReturnValue, &obtainedArgument, &argumentMatch]
                (const DynamicSlot &, const std::vector<QVariant> &args) -> QVariant
        {
            obtainedArgument = args.size() == 1;
            argumentMatch = (!args.empty() && args.front().value<ReturnType>() == expectedReturnValue);
            called = true;
            return expectedReturnValue;
        };
        dynamicQObject.setOnSlotExecutedHandler(handler);
        ReturnType result;
        QMetaObject::invokeMethod(&dynamicQObject, "fooSlot",
                                  QGenericReturnArgument(TypeName<ReturnType>::Get(), &result),
                                  QGenericArgument(TypeName<ReturnType>::Get(), &expectedReturnValue));
        QVERIFY(called);
        QVERIFY(obtainedArgument);
        QVERIFY(argumentMatch);
        QCOMPARE(result, expectedReturnValue);
    }
};

QTEST_MAIN(TestDynamicQObject)

#include "test_dynamicqobject.moc"
