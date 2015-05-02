import dqml;
import model;

void main()
{
    try
    {
        auto app = new QGuiApplication();
        scope(exit) destroy(app);

        auto model = new ListModel();
        scope(exit) destroy(model);

        auto variant = new QVariant();
        variant.setValue(model);

        auto engine = new QQmlApplicationEngine();
        scope(exit) destroy(engine);

        engine.rootContext().setContextProperty("myListModel", variant);
        engine.load("main.qml");
        app.exec();
    }
    catch
    {}
}
