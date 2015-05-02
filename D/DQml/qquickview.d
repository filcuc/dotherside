import dothersideinterface;
import qqmlcontext;
import std.string;

class QQuickView
{ 
    this()
    {
        dos_qquickview_create(this.vptr);
    }
  
    ~this()
    {
        dos_qquickview_delete(this.vptr);
    }

    public void* voidPointer()
    {
        return this.vptr;
    }
  
    public void show()
    {
        dos_qquickview_show(this.vptr);
    }
  
    public QQmlContext rootContext()
    {
        void* contextData;
        dos_qquickview_rootContext(this.vptr, contextData);
        return new QQmlContext(contextData);
    }
  
    public string source()
    {
        char* array;
        dos_qquickview_source(this.vptr, array);
        string result = fromStringz(array).dup;
        dos_chararray_delete(array);
        return result;
    }
  
    public void setSource(string filename)
    {
        immutable(char)* filenameAsCString = filename.toStringz();
        dos_qquickview_set_source(this.vptr, filenameAsCString);
    }

    private void* vptr;
}
