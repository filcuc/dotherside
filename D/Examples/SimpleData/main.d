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

        auto qVar1 = new QVariant(10);
        scope(exit) destroy(qVar1);
        
        auto qVar2 = new QVariant("Hello World");
        scope(exit) destroy(qVar1);
        
        auto qVar3 = new QVariant(false);
        scope(exit) destroy(qVar1);
        
        auto qVar4 = new QVariant(3.5f);
        scope(exit) destroy(qVar1);
        
        engine.rootContext().setContextProperty("qVar1", qVar1);
        engine.rootContext().setContextProperty("qVar2", qVar2);
        engine.rootContext().setContextProperty("qVar3", qVar3);
        engine.rootContext().setContextProperty("qVar4", qVar4);
        engine.load("main.qml");

        app.exec();
    }
    catch
    {}
}
