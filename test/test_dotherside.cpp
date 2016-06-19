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
#include <DOtherSide/DOtherSide.h>
#include <DOtherSide/DosQObject.h>
#include <DOtherSide/DosQMetaObject.h>
#include <DOtherSide/DosQObject.h>
#include <DOtherSide/DosQAbstractListModel.h>

#include "MockQObject.h"
#include "MockQAbstractListModel.h"

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
        testObject.reset(new MockQAbstractListModel());
        engine.reset(new QQmlApplicationEngine());
        engine->rootContext()->setContextProperty("testObject", QVariant::fromValue<QObject*>(static_cast<QObject*>(testObject->data())));
        engine->load(QUrl("qrc:///testQAbstractItemModel.qml"));
    }

    void cleanup()
    {
        engine.reset();
        testObject.reset();
    }

    void testRowCount() {
        QObject* testCase = engine->rootObjects().first();
        QVERIFY(testCase);
        QVariant result;
        QVERIFY(QMetaObject::invokeMethod(testCase, "testRowCount", Q_RETURN_ARG(QVariant, result)));
        QVERIFY(result.type() == QVariant::Bool);
        QVERIFY(result.toBool());
    }

    void testColumnCount() {
        QObject* testCase = engine->rootObjects().first();
        QVERIFY(testCase);
        QVariant result;
        QVERIFY(QMetaObject::invokeMethod(testCase, "testColumnCount", Q_RETURN_ARG(QVariant, result)));
        QVERIFY(result.type() == QVariant::Bool);
        QVERIFY(result.toBool());
    }

    void testData() {
        QObject* testCase = engine->rootObjects().first();
        QVERIFY(testCase);
        QVariant result;
        QVERIFY(QMetaObject::invokeMethod(testCase, "testData", Q_RETURN_ARG(QVariant, result)));
        QVERIFY(result.type() == QVariant::Bool);
        QVERIFY(result.toBool());
    }


private:
    QString value;
    unique_ptr<MockQAbstractListModel> testObject;
    unique_ptr<QQmlApplicationEngine> engine;
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
