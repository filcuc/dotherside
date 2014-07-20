import std.stdio;
import std.string;
import std.traits;
import std.conv;
import core.memory;
import std.functional;
import dotherside;
import dobject;
import dslot;

class MyObject : DObject 
{
  this()
  {
    //foo = registerSlot("foo", &_foo);
    bar = registerSlot("bar", &_bar);
  }
  
  DSlot!(void delegate(int)) foo;
  void _foo(int fooValue)
  {
    writeln("D: Called foo slot with argument ", fooValue , "!!");
  }
  
  DSlot!(int delegate(int)) bar;
  int _bar(int barValue)
  {
    writeln("D: Called bar slot with argument " , barValue, "!!");
    return 666;
  }
}

void main()
{
  try
  {
    auto app = new GuiApplication;
    scope(exit) clear(app);
    auto view = new QuickView;
    scope(exit) clear(view);
    
    auto myObject = new MyObject();
    
    auto context = view.rootContext();
    context.setContextProperty("myObject", new QVariant(myObject));
    
    view.setSource("Test.qml");
    view.show();
    app.exec();
  }
  catch 
  {}
}
