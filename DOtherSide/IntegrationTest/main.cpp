#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMetaMethod>
#include <DynamicQObject.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DynamicQObject dynamicQObject;
    int slotIndex;
    dynamicQObject.registerSlot("foo", QMetaType::Void, {}, slotIndex);
    dynamicQObject.registerSlot("bar", QMetaType::Int, {QMetaType::Int}, slotIndex);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dynamicQObject", QVariant::fromValue<QObject*>(&dynamicQObject));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
