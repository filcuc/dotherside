import std.string;
import std.stdio;
import std.conv;
import std.traits;
import std.functional;
import std.typecons;
import core.vararg;
import dothersideinterface;
import dobject;

class GuiApplication
{ 
  this()
  {
    dos_guiapplication_create();
  }
  
  ~this()
  {
    dos_guiapplication_delete();
  }
  
  void exec()
  {
    dos_guiapplication_exec();
  }
}

class QuickView
{ 
  void* data;
  
  this()
  {
    dos_quickview_create(data);
  }
  
  ~this()
  {
    dos_quickview_delete(data);
  }
  
  void show()
  {
    dos_quickview_show(data);
  }
  
  QQmlContext rootContext()
  {
    auto context = new QQmlContext();
    dos_quickview_rootContext(data, context.data);
    return context;
  }
  
  string source()
  {
    auto array = new CharArray();
    dos_quickview_source(data, array.dataRef(), array.sizeRef());
    return to!(string)(array.data());
  }
  
  void setSource(string filename)
  {
    immutable(char)* filenameAsCString = filename.toStringz();
    dos_quickview_set_source(data, filenameAsCString);
  }
}

class QQmlContext
{
  void* data;
  
  string baseUrl()
  {
    auto array = new CharArray();
    dos_qmlcontext_baseUrl(data, array.dataRef(), array.sizeRef());
    return to!(string)(array.data());
  }
  
  void setContextProperty(string name, QVariant value)
  {
    dos_qmlcontext_setcontextproperty(data, name.ptr, value.data);
  }
}

class QVariant
{
  private void* data;
  
  this()
  {
    dos_qvariant_create(this.data);
  }
  
  this(int value)
  {
    dos_qvariant_create_int(this.data, value);
  }
  
  this(bool value)
  {
    dos_qvariant_create_bool(this.data, value);
  }
  
  this(string value)
  {
    dos_qvariant_create_string(this.data, value.toStringz());
  }
  
  this(DObject value)
  {
    dos_qvariant_create_qobject(this.data, value.data);
  }
  
  bool isNull()
  {
    bool result;
    dos_qvariant_isnull(this.data, result);
    return result;
  }
  
  bool toBool()
  {
    bool result;
    dos_qvariant_toBool(this.data, result);
    return result;
  }
  
  int toInt()
  {
    int result;
    dos_qvariant_toInt(this.data, result);
    return result;
  }
  
  override string toString()
  {
    auto array = new CharArray();
    dos_qvariant_toString(this.data, array.dataRef(), array.sizeRef());
    return to!(string)(array.data());
  }
  
  ~this()
  {
    dos_qvariant_delete(this.data);
  }
}

class CharArray
{
  char* _data;
  int _size;
  
  this()
  {
    _size = 0;
    dos_chararray_create(_data, _size);
  }
  
  this(int size)
  {
    _size = size;
    dos_chararray_create(_data, _size);
  }
  
  this(char* data, int size)
  {
    _data = data;
    _size = size;
  }
  
  ~this()
  {
    dos_chararray_delete(_data);
  }
  
  char* data()
  {
    return _data;
  }
  
  int size()
  {
    return _size;
  }
  
  ref char* dataRef()
  {
    return _data;
  }
  
  ref int sizeRef()
  {
    return _size;
  }
}

/*
class QSlot
{
  alias Callback = void function();
  
  void* data;
  Callback callback;
  
  extern (C) static void staticCallback(void* dobject)
  {
    QSlot slot = cast(QSlot) dobject;
    Callback callback = slot.getCallback();
    callback();
  }

  this()
  {
    dos_qslot_create(this.data);
  }

  ~this()
  {
    dos_qslot_delete(this.data);
  }
  
  Callback getCallback()
  {
    return this.callback;
  }
  
  void setCallback(Callback callback)
  {
    this.callback = callback;
    dos_qslot_setcallback(this.data, cast (void*) this, &staticCallback);
  }
}

class QSlot2(T)
{
  void* data;
  int numberOfArguments;
  T* callback;
  alias ReturnType!T SlotReturnType;
  alias ParameterTypeTuple!T SlotArgumentsType;
  
  extern (C) static void staticCallback(void* dobject, int numArgs, ...)
  {
    auto arguments = Tuple!SlotArgumentsType();
    
    va_list ap;
    version (X86_64)
      va_start(ap, __va_argsave);
    else version (X86)
      va_start(ap, numArgs);
    
    foreach (i, argument; arguments) {
        writefln("%s: %s", i, arguments);
        va_arg(ap, arguments[i]);
    }
    va_end(ap);
    
    QSlot2 slot = cast(QSlot2) dobject;
    T* callback = slot.getCallback();
    callback(arguments.expand);
  }
  
  this(T* t)
  {
    this.numberOfArguments = arity!t;
    this.callback = t;
    dos_qslot_create(this.data);
    dos_qslot_setcallback2(this.data, cast (void*) this, &staticCallback);
  }
  
  ~this()
  {
    dos_qslot_delete(this.data);
  }
  
  T* getCallback()
  {
    return this.callback;
  }
 
  int getNumberOfArguments()
  {
    return this.numberOfArguments;
  }
}
*/