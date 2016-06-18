// std
#include <tuple>
#include <iostream>
#include <memory>
// Qt
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <QTimer>
#include <QApplication>
#include <QQuickWindow>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQmlContext>
#include <QtQuickTest/QtQuickTest>

// DOtherSide
#include "DOtherSide/DOtherSide.h"
#include "DOtherSide/DosQObject.h"
#include "DOtherSide/DosQMetaObject.h"
#include "DOtherSide/DosQObject.h"
#include "DOtherSide/DosQAbstractListModel.h"

using namespace std;
using namespace DOS;

template<typename Test>
bool ExecuteTest(int argc, char *argv[])
{
    Test test;
    return QTest::qExec(&test, argc, argv) == 0;
}

template<typename Test>
bool ExecuteGuiTest(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Test test;
    return QTest::qExec(&test, argc, argv) == 0;
}

/*
 * Test QGuiApplication
 */
class TestQGuiApplication : public QObject
{
    Q_OBJECT

private slots:
    void testExecution()
    {
        bool quit = false;
        dos_qguiapplication_create();
        QTimer timer;
        QObject::connect(&timer, &QTimer::timeout, [&quit]() {
            quit = true;
            dos_qguiapplication_quit();
        });
        timer.start(100);
        dos_qguiapplication_exec();
        QVERIFY(quit);
        dos_qguiapplication_delete();
    }
};

/*
 * Test QApplication
 */
class TestQApplication : public QObject
{
    Q_OBJECT

private slots:
    void testExecution()
    {
        bool quit = false;
        dos_qapplication_create();
        QTimer timer;
        QObject::connect(&timer, &QTimer::timeout, [&quit]() {
            quit = true;
            dos_qapplication_quit();
        });
        timer.start(100);
        dos_qapplication_exec();
        QVERIFY(quit);
        dos_qapplication_delete();
    }
};

/*
 * Test QQmlApplicationEngine
 */
class TestQQmlApplicationEngine : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        m_engine = nullptr;
    }

    void cleanupTestCase()
    {
        QVERIFY(m_engine == nullptr);
    }

    void init()
    {
        QVERIFY(m_engine == nullptr);
        m_engine = dos_qqmlapplicationengine_create();
        QVERIFY(m_engine != nullptr);
    }

    void cleanup()
    {
        dos_qqmlapplicationengine_delete(m_engine);
        m_engine = nullptr;
    }

    void testCreateAndDelete()
    {
        // Implicit by invoking init and cleanup
    }

    void testLoadUrl()
    {
        void *url = dos_qurl_create("qrc:///main.qml", QUrl::TolerantMode);
        QVERIFY(url != nullptr);
        dos_qqmlapplicationengine_load_url(m_engine, url);
        QCOMPARE(engine()->rootObjects().size(), 1);
        QCOMPARE(engine()->rootObjects().front()->objectName(), QString::fromLocal8Bit("testWindow"));
        QVERIFY(engine()->rootObjects().front()->isWindowType());
        dos_qurl_delete(url);
    }

    void testLoadData()
    {
        dos_qqmlapplicationengine_load_data(m_engine, "import QtQuick 2.3; import QtQuick.Controls 1.2; ApplicationWindow { objectName: \"testWindow\"}");
        QCOMPARE(engine()->rootObjects().size(), 1);
        QCOMPARE(engine()->rootObjects().front()->objectName(), QString::fromLocal8Bit("testWindow"));
        QVERIFY(engine()->rootObjects().front()->isWindowType());
    }

private:
    QQmlApplicationEngine *engine()
    {
        return static_cast<QQmlApplicationEngine *>(m_engine);
    }

    void *m_engine;
};

/*
 * Test QQmlContext
 */
class TestQQmlContext : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        m_engine = nullptr;
        m_context = nullptr;
    }

    void cleanupTestCase()
    {
        QVERIFY(m_engine == nullptr);
        QVERIFY(m_context == nullptr);
    }

    void init()
    {
        m_engine = dos_qqmlapplicationengine_create();
        m_context = dos_qqmlapplicationengine_context(m_engine);
        QVERIFY(m_engine != nullptr);
        QVERIFY(m_context != nullptr);
    }

    void cleanup()
    {
        m_context = nullptr;
        dos_qqmlapplicationengine_delete(m_engine);
        m_engine = nullptr;
    }

    void testCreateAndDelete()
    {
        // Implicit by invoking init and cleanup
    }

    void testSetContextProperty()
    {
        QVariant testData("Test Message");
        dos_qqmlcontext_setcontextproperty(m_context, "testData", &testData);
        engine()->loadData("import QtQuick 2.3; Text { objectName: \"label\"; text: testData } ");
        QObject *label = engine()->rootObjects().first();
        QVERIFY(label != nullptr);
        QCOMPARE(label->objectName(), QString::fromLocal8Bit("label"));
        QCOMPARE(label->property("text").toString(), testData.toString());
    }

private:
    QQmlApplicationEngine *engine()
    {
        return static_cast<QQmlApplicationEngine *>(m_engine);
    }
    QQmlContext *context()
    {
        return static_cast<QQmlContext *>(m_context);
    }

    void *m_engine;
    void *m_context;
};

extern "C" {
    typedef void DOS_CALL(*VoidDeleter)(void*);
    typedef void DOS_CALL(*CharDeleter)(char*);
}
using VoidPointer = unique_ptr<void, VoidDeleter>;
using CharPointer = unique_ptr<char, CharDeleter>;


string toStringFromQVariant(DosQVariant* variant) {
    CharPointer charArray(dos_qvariant_toString(variant), &dos_chararray_delete);
    return string(charArray.get());
}

class MockQObject
{

public:
    MockQObject()
        : m_vptr(dos_qobject_create(this, metaObject(), &onSlotCalled), &dos_qobject_delete)
    {}

    std::string objectName() const {
        CharPointer result (dos_qobject_objectName(m_vptr.get()), &dos_chararray_delete);
        return string(result.get());
    }

    void setObjectName(const string& objectName) {
        dos_qobject_setObjectName(m_vptr.get(), objectName.c_str());
    }

    ::DosQMetaObject *metaObject() {
        static VoidPointer result = initializeMetaObject();
        return result.get();
    }

    ::DosQObject *data() {
        return m_vptr.get();
    }

    std::string name() const
    {
        return m_name;
    }

    void setName(const string& name)
    {
        if (name == m_name)
            return;
        m_name = name;

    }

    void nameChanged(const string& name)
    {
        int argc = 1;
        DosQVariant* argv[1];
        argv[0] = dos_qvariant_create_string(name.c_str());
        dos_qobject_signal_emit(m_vptr.get(), "nameChanged", argc, argv);
        dos_qvariant_delete(argv[0]);
    }

private:

    static void onSlotCalled(void *selfVPtr, DosQVariant *dosSlotNameVariant, int dosSlotArgc, DosQVariant **dosSlotArgv) {
        MockQObject* self = static_cast<MockQObject*>(selfVPtr);

        string slotName = toStringFromQVariant(dosSlotNameVariant);
        if (slotName == "name") {
            VoidPointer name(dos_qvariant_create_string(self->name().c_str()), &dos_qvariant_delete);
            dos_qvariant_assign(dosSlotArgv[0], name.get());
            return;
        }

        if (slotName == "setName") {
            self->setName(toStringFromQVariant(dosSlotArgv[1]));
            return;
        }
    }

    static VoidPointer initializeMetaObject() {
        void* superClassMetaObject = dos_qobject_qmetaobject();
        // Signals
        ::SignalDefinition signalDefinitionArray[1];
        signalDefinitionArray[0].name = "nameChanged";
        signalDefinitionArray[0].parametersCount = 1;
        int nameChanged[1];
        nameChanged[0] = QMetaType::QString;
        signalDefinitionArray[0].parametersMetaTypes = nameChanged;

        ::SignalDefinitions signalDefinitions;
        signalDefinitions.count = 1;
        signalDefinitions.definitions = signalDefinitionArray;

        // Slots
        ::SlotDefinition slotDefinitionArray[2];

        slotDefinitionArray[0].name = "name";
        slotDefinitionArray[0].returnMetaType = QMetaType::QString;
        slotDefinitionArray[0].parametersCount = 0;
        slotDefinitionArray[0].parametersMetaTypes = nullptr;

        slotDefinitionArray[1].name = "setName";
        slotDefinitionArray[1].returnMetaType = QMetaType::Void;
        int setNameParameters[1];
        setNameParameters[0] = QMetaType::QString;
        slotDefinitionArray[1].parametersCount = 1;
        slotDefinitionArray[1].parametersMetaTypes = setNameParameters;

        ::SlotDefinitions slotDefinitions;
        slotDefinitions.count = 2;
        slotDefinitions.definitions = slotDefinitionArray;

        // Properties
        ::PropertyDefinition propertyDefinitionArray[1];
        propertyDefinitionArray[0].name = "name";
        propertyDefinitionArray[0].notifySignal = "nameChanged";
        propertyDefinitionArray[0].propertyMetaType = QMetaType::QString;
        propertyDefinitionArray[0].readSlot = "name";
        propertyDefinitionArray[0].writeSlot = "setName";

        ::PropertyDefinitions propertyDefinitions;
        propertyDefinitions.count = 1;
        propertyDefinitions.definitions = propertyDefinitionArray;

        return VoidPointer(dos_qmetaobject_create(superClassMetaObject, "MockQObject", &signalDefinitions, &slotDefinitions, &propertyDefinitions),
                           &dos_qmetaobject_delete);
    }

    VoidPointer m_vptr;
    std::string m_name;
};


/*
 * Test QQmlContext
 */
class TestQObject : public QObject
{
    Q_OBJECT

private slots:
    void init()
    {   
        testObject.reset(new MockQObject());
        testObject->setObjectName("testObject");
        testObject->setName("foo");

        engine.reset(new QQmlApplicationEngine());
        engine->rootContext()->setContextProperty("testObject", QVariant::fromValue<QObject*>(static_cast<QObject*>(testObject->data())));
        engine->load(QUrl("qrc:///testQObject.qml"));
    }

    void cleanup()
    {
        engine.reset();
        testObject.reset();
    }

    void testObjectName() {
        QObject* testCase = engine->rootObjects().first();
        QVERIFY(testCase);
        QVariant result;
        QVERIFY(QMetaObject::invokeMethod(testCase, "testObjectName", Q_RETURN_ARG(QVariant, result)));
        QVERIFY(result.type() == QVariant::Bool);
        QVERIFY(result.toBool());
    }

    void testPropertyReadAndWrite()
    {
        QObject* testCase = engine->rootObjects().first();
        QVERIFY(testCase);
        QVariant result;
        QVERIFY(QMetaObject::invokeMethod(testCase, "testPropertyReadAndWrite", Q_RETURN_ARG(QVariant, result)));
        QVERIFY(result.type() == QVariant::Bool);
        QVERIFY(result.toBool());
    }

    void testSignalEmittion()
    {
        QObject* testCase = engine->rootObjects().first();
        QVERIFY(testCase);
        QVariant result;
        QVERIFY(QMetaObject::invokeMethod(testCase, "testSignalEmittion", Q_RETURN_ARG(QVariant, result)));
        QVERIFY(result.type() == QVariant::Bool);
        QVERIFY(result.toBool());
    }

private:
    QString value;
    unique_ptr<MockQObject> testObject;
    unique_ptr<QQmlApplicationEngine> engine;
};

/*
 * Test QQmlContext
 */
class TestQAbstractListModel : public QObject
{
    Q_OBJECT

private slots:
    void init()
    {
        DOS::SignalDefinitions signalDefinitions {DOS::SignalDefinition {"nameChanged", {QMetaType::QString}}};
        DOS::SlotDefinitions slotDefinitions {DOS::SlotDefinition {"name", QMetaType::QString, {}},
                                              DOS::SlotDefinition {"setName", QMetaType::Void, {QMetaType::QString}}};
        DOS::PropertyDefinitions propertyDefinitions {DOS::PropertyDefinition{"name", QMetaType::QString, "name", "setName", "nameChanged"}};

        auto mo = make_shared<DOS::DosQMetaObject>(make_shared<DosQAbstractListModelMetaObject>(),
                                                        "TestClass",
                                                        signalDefinitions,
                                                        slotDefinitions,
                                                        propertyDefinitions);

        unique_ptr<DosIQMetaObjectHolder> moh(new DosIQMetaObjectHolder(mo));

        auto ose = [this, value = QString()](const QString & name, const vector<QVariant> &args) mutable -> QVariant {
            if (name == "name")
                return value;
            else if (name == "setName") {
                value = args.front().toString();
                testObject->emitSignal(testObject.get(), "nameChanged", {value});
            }
            return QVariant();
        };

        RowCountCallback rcc = nullptr;
        ColumnCountCallback ccc = nullptr;
        DataCallback dc = nullptr;
        SetDataCallback sdc = nullptr;
        RoleNamesCallback rnc = nullptr;
        FlagsCallback fc = nullptr;
        HeaderDataCallback hdc = nullptr;

        void *dPointer = nullptr;

        testObject = make_unique<DOS::DosQAbstractListModel>(dPointer, moh->data(), ose, rcc, ccc, dc, sdc, rnc, fc, hdc);
        testObject->setObjectName("testObject");
        testObject->setProperty("name", "foo");
    }

    void cleanup()
    {
        testObject.reset();
    }

    void testPropertyInheritance()
    {
        /// Test property read
        QCOMPARE(testObject->property("objectName").toString(), QString("testObject"));
        QCOMPARE(testObject->property("name").toString(), QString("foo"));
    }

    void testPropertyReadAndWrite()
    {
        QCOMPARE(testObject->property("name").toString(), QString("foo"));
        testObject->setProperty("name", QString("bar"));
        QCOMPARE(testObject->property("name").toString(), QString("bar"));
    }

    void testSlotInvokation()
    {
        QMetaObject::invokeMethod(testObject.get(), "setName", Q_ARG(QString, "bar"));
        QCOMPARE(testObject->property("name").toString(), QString("bar"));
    }

    void testSignalEmittion()
    {
        QSignalSpy signalSpy(testObject.get(), SIGNAL(nameChanged(QString)));
        QCOMPARE(signalSpy.size(), 0);
        QCOMPARE(testObject->property("name").toString(), QString("foo"));
        testObject->setProperty("name", QString("bar"));
        QCOMPARE(testObject->property("name").toString(), QString("bar"));
        QCOMPARE(signalSpy.size(), 1);
    }

private:
    QString value;
    unique_ptr<DOS::DosQAbstractListModel> testObject;
};

int main(int argc, char *argv[])
{
    using namespace DOS;

    bool success = true;
    success &= ExecuteTest<TestQGuiApplication>(argc, argv);
    success &= ExecuteTest<TestQApplication>(argc, argv);
    success &= ExecuteGuiTest<TestQQmlApplicationEngine>(argc, argv);
    success &= ExecuteGuiTest<TestQQmlContext>(argc, argv);
    success &= ExecuteGuiTest<TestQObject>(argc, argv);
    success &= ExecuteGuiTest<TestQAbstractListModel>(argc, argv);

    return success ? 0 : 1;
}

#include "test_dotherside.moc"
