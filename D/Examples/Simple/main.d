import std.stdio;
import std.string;
import std.traits;
import std.conv;
import std.functional;
import core.memory;
import dqml;

class MyObject : QObject 
{
  this()
  {
    foo = registerSlot("foo", &_foo);
    bar = registerSlot("bar", &_bar);
    nameChanged = registerSignal!(string)("nameChanged");
    tor = registerSlot("tor", &_tor);
  }
  
  public QSlot!(void delegate(int)) foo;
  private void _foo(int fooValue)
  {
    writeln("D: Called foo slot with argument ", fooValue , "!!");
  }
  
  public QSlot!(int delegate(int)) bar;
  private int _bar(int barValue)
  {
    writeln("D: Called bar slot with argument " , barValue, "!!");
    return 666;
  }

  public QSlot!(string delegate(string)) tor;
  private string _tor (string torValue)
  {
    writeln("D: Called tor slot with argument ", torValue, "!!");
    return "2343";
  }

  public QSignal!(string) nameChanged;
}

void main()
{
  try
  {
    auto app = new QGuiApplication;
    scope(exit) destroy(app);

    auto view = new QQuickView;
    scope(exit) destroy(view);
    
    auto myObject = new MyObject();
    scope(exit) destroy(myObject);
    
    auto context = view.rootContext();
    context.setContextProperty("myObject", new QVariant(myObject));
    
    view.setSource("Test.qml");
    view.show();

    myObject.nameChanged("prova");

    app.exec();
  }
  catch 
  {}
}
