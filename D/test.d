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
  
  DSlot!(void delegate()) foo;
  void _foo()
  {
    writeln("Called foo slot!!");
  }
  
  DSlot!(int delegate()) bar;
  int _bar()
  {
    writeln("Called bar slot!!");
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
