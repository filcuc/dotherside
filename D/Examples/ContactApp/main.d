import dqml;
import applicationlogic;

void main()
{
    try
    {
        auto app = new QApplication();
        scope(exit) destroy(app);

        auto logic = new ApplicationLogic(app);
        scope(exit) destroy(logic);

        auto variant = new QVariant();
        variant.setValue(logic);

        auto engine = new QQmlApplicationEngine();
        scope(exit) destroy(engine);

        engine.rootContext().setContextProperty("logic", variant);
        engine.load("main.qml");
        app.exec();
    }
    catch
    {}
}
