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

    int signalIndex;
    dynamicQObject.registerSignal("nameChanged", {QMetaType::QString}, signalIndex);

    int slotIndex;
    dynamicQObject.registerSlot("bar", QMetaType::Int, {QMetaType::Int}, slotIndex);
    dynamicQObject.registerSlot("foo", QMetaType::Void, {}, slotIndex);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dynamicQObject", QVariant::fromValue<QObject*>(&dynamicQObject));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    QVariantList list;
    list << "Prova";
    dynamicQObject.emitSignal("nameChanged", list);

    return app.exec();
}
