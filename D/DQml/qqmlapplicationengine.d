import dothersideinterface;
import qqmlcontext;
import std.string;

class QQmlApplicationEngine
{
    this()
    {
        dos_qqmlapplicationengine_create(this.vptr);
    }
  
    ~this()
    {
        dos_qqmlapplicationengine_delete(this.vptr);
    }

    public void* voidPointer()
    {
        return this.vptr;
    }

    public QQmlContext rootContext()
    {
        void* contextVPtr;
        dos_qqmlapplicationengine_context(this.vptr, contextVPtr);
        return new QQmlContext(contextVPtr);
    }
  
    public void load(string filename)
    {
        dos_qqmlapplicationengine_load(this.vptr, filename.toStringz());
    }
  
    private void* vptr;
}
