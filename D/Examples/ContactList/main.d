import std.stdio;
import std.string;
import std.traits;
import std.conv;
import std.functional;
import core.memory;
import dqml;
import contactlist;
import contact;

void main()
{
  try
  {
    auto app = new QGuiApplication;
    scope(exit) destroy(app);

    auto contactList = new ContactList();
    scope(exit) destroy(contactList);
    contactList.addContact("John", "Doo");
    contactList.addContact("Peter", "Roger");

    auto qmlApplicationEngine = new QQmlApplicationEngine;
    scope(exit) destroy(qmlApplicationEngine);
    qmlApplicationEngine.context().setContextProperty("contactList", new QVariant(contactList));
    qmlApplicationEngine.load("main.qml");

    app.exec();
  }
  catch 
  {}
}
