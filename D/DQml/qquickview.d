import dothersideinterface;
import qqmlcontext;
import chararray;
import std.string;

class QQuickView
{ 
  this()
  {
    dos_qquickview_create(data);
  }
  
  ~this()
  {
    dos_qquickview_delete(data);
  }
  
  void show()
  {
    dos_qquickview_show(data);
  }
  
  QQmlContext rootContext()
  {
    void* contextData;
    dos_qquickview_rootContext(data, contextData);
    return new QQmlContext(contextData);
  }
  
  string source()
  {
    auto array = new CharArray();
    scope(exit) destroy(array);
    dos_qquickview_source(data, array.dataRef(), array.sizeRef());
    return array.toString();
  }
  
  void setSource(string filename)
  {
    immutable(char)* filenameAsCString = filename.toStringz();
    dos_qquickview_set_source(data, filenameAsCString);
  }

  private void* data;
}
