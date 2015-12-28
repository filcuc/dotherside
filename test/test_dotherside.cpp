// std
#include <tuple>
#include <iostream>
// Qt
#include <QDebug>
#include <QTest>
#include <QSignalSpy>
#include <QTimer>
#include <QApplication>
#include <QQuickWindow>

// DOtherSide
#include "DOtherSide/DOtherSide.h"
#include "DOtherSide/DynamicQObject.h"
#include "DOtherSide/DynamicQObjectFactory.h"

template<typename Test>
bool ExecuteTest(int argc, char* argv[]) {
    Test test;
    return QTest::qExec(&test, argc, argv) == 0;
}

template<typename Test>
bool ExecuteGuiTest(int argc, char* argv[]) {
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
    void testExecution() {
        bool quit = false;
        dos_qguiapplication_create();
        QTimer::singleShot(100, [&quit](){ quit = true; dos_qguiapplication_quit(); });
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
    void testExecution() {
        bool quit = false;
        dos_qapplication_create();
        QTimer::singleShot(100, [&quit](){ quit = true; dos_qapplication_quit(); });
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
    void initTestCase() {
        m_engine = nullptr;
    }

    void cleanupTestCase() {
        QVERIFY(m_engine == nullptr);
    }

    void init() {
        QVERIFY(m_engine == nullptr);
        dos_qqmlapplicationengine_create(&m_engine);
        QVERIFY(m_engine != nullptr);
    }

    void cleanup() {
        dos_qqmlapplicationengine_delete(m_engine);
        m_engine = nullptr;
    }

    void testCreateAndDelete() {

    }

    void testLoadUrl() {
        void* url = nullptr;
        dos_qurl_create(&url, "qrc:///main.qml", QUrl::TolerantMode);
        QVERIFY(url != nullptr);
        dos_qqmlapplicationengine_load_url(m_engine, url);
        dos_qurl_delete(url);
    }

    void testRootObjects() {
        void** rootObjects = nullptr;
        int length = 0;
        void* url = nullptr;
        dos_qurl_create(&url, "qrc:///main.qml", QUrl::TolerantMode);
        dos_qqmlapplicationengine_load_url(m_engine, url);
        dos_qurl_delete(url);
        dos_qqmlapplicationengine_rootObjects(m_engine, &rootObjects, &length);
        QCOMPARE(length, 1);
        QObject* window = reinterpret_cast<QObject*>(rootObjects[0]);
        QVERIFY(window->isWindowType());
        dos_qobjectptr_array_delete(rootObjects);
    }

private:
    void* m_engine;
};

/*
 * Test QQmlContext
 */
class TestQQmlContext : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase() {
        m_engine = nullptr;
        m_context = nullptr;
    }

    void cleanupTestCase() {
        QVERIFY(m_engine == nullptr);
        QVERIFY(m_context == nullptr);
    }

    void init() {
        dos_qqmlapplicationengine_create(&m_engine);
        dos_qqmlapplicationengine_context(m_engine, &m_context);
        QVERIFY(m_engine != nullptr);
        QVERIFY(m_context != nullptr);
    }

    void cleanup() {
        m_context = nullptr;
        dos_qqmlapplicationengine_delete(m_engine);
        m_engine = nullptr;
    }

private:
    void* m_engine;
    void* m_context;
};

/*
 * Test DynamicQObject
 */
class TestDynamicQObject : public QObject
{
    Q_OBJECT

private slots:
    void benchmarkDynamicQObject2Performance() {

        QBENCHMARK {
            DOS::DynamicQObjectFactory factory {{DOS::SignalDefinition{"fooChanged", {QMetaType::Int}}},
                                                {DOS::SlotDefinition{"foo", QMetaType::Int, {}}, DOS::SlotDefinition{"setFoo", QMetaType::Void, {QMetaType::Int}}},
                                                {DOS::PropertyDefinition{"foo",  QMetaType::Int, "foo", "setFoo", "fooChanged"}}};
            for (int i = 0; i < 1000; ++i) {
                std::unique_ptr<DOS::DynamicQObject> dynamicQObject(factory.create([](const QString&, const std::vector<QVariant>&)-> QVariant{}));
            }
        }
    }

    void testDynamicQObject2() {
        DOS::DynamicQObjectFactory factory {{DOS::SignalDefinition{"fooChanged", {QMetaType::Int}}},
                                            {DOS::SlotDefinition{"foo", QMetaType::Int, {}}, DOS::SlotDefinition{"setFoo", QMetaType::Void, {QMetaType::Int}}},
                                            {DOS::PropertyDefinition{"foo",  QMetaType::Int, "foo", "setFoo", "fooChanged"}}};
        std::unique_ptr<DOS::DynamicQObject> dynamicQObject(factory.create([](const QString&, const std::vector<QVariant>&)-> QVariant{}));
        QVERIFY(dynamicQObject != nullptr);

        QSignalSpy signalSpy(dynamicQObject.get(), SIGNAL(fooChanged(int)));
        dynamicQObject->emitSignal("fooChanged", {10});
        QCOMPARE(signalSpy.count(), 1);
    }
};


int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(Resources);
    bool success = true;
    success &= ExecuteTest<TestQGuiApplication>(argc, argv);
    success &= ExecuteTest<TestQApplication>(argc, argv);
    success &= ExecuteGuiTest<TestQQmlApplicationEngine>(argc, argv);
    success &= ExecuteTest<TestDynamicQObject>(argc, argv);
    return success ? 0 : 1;
}

#include "test_dotherside.moc"
