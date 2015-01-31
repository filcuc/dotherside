#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMetaMethod>
#include <DynamicQObject.h>
#include <QDebug>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    DynamicQObject dynamicQObject;

    int signalIndex;
    dynamicQObject.registerSignal("nameChanged", {QMetaType::QString}, signalIndex);

    int slotIndex;
    dynamicQObject.registerSlot("foo", QMetaType::Void, {}, slotIndex);
    dynamicQObject.registerSlot("bar", QMetaType::Int, {QMetaType::Int}, slotIndex);
    dynamicQObject.registerSlot("getName", QMetaType::QString, {}, slotIndex);
    dynamicQObject.registerSlot("setName", QMetaType::Void, {QMetaType::QString}, slotIndex);

    dynamicQObject.registerProperty("name", QMetaType::QString, "getName", "setName", "nameChanged");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dynamicQObject", QVariant::fromValue<QObject*>(&dynamicQObject));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QVariantList list;
    list << "NewName";
    dynamicQObject.emitSignal("nameChanged", list);

    return app.exec();
}
