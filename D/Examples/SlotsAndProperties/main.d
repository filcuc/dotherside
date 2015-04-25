import std.stdio;
import dqml;
import contact;

void main()
{
    try
    {
        auto app = new QGuiApplication();
        scope(exit) destroy(app);

        auto contact = new Contact();
        scope(exit) destroy(contact);

        auto variant = new QVariant(contact);
        scope(exit) destroy(variant);

        auto engine = new QQmlApplicationEngine();
        scope(exit) destroy(engine);

        engine.rootContext().setContextProperty("contact", variant);
        engine.load("main.qml");
        app.exec();
    }
    catch
    {}
}
