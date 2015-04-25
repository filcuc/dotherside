import std.stdio;
import dqml;

void main()
{
    try
    {
        auto app = new QGuiApplication();
        scope(exit) destroy(app);

        auto engine = new QQmlApplicationEngine();
        scope(exit) destroy(engine);
        engine.load("main.qml");

        app.exec();
    }
    catch
    {}
}
