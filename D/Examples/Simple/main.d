import std.stdio;
import std.string;
import std.traits;
import std.conv;
import std.functional;
import core.memory;
import dqml;
import myqobject;

void main()
{
  try
  {
    auto app = new QGuiApplication;
    scope(exit) destroy(app);

    auto myQObject = new MyQObject();
    scope(exit) destroy(myQObject);

    auto qmlApplicationEngine = new QQmlApplicationEngine;
    scope(exit) destroy(qmlApplicationEngine);
    qmlApplicationEngine.context().setContextProperty("myQObject", new QVariant(myQObject));
    qmlApplicationEngine.load("main.qml");

    app.exec();
  }
  catch 
  {}
}
