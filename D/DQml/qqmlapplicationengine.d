import dothersideinterface;
import qqmlcontext;
import std.string;

class QQmlApplicationEngine
{
    public this()
    {
        dos_qqmlapplicationengine_create(data);
    }
  
    public ~this()
    {
        dos_qqmlapplicationengine_delete(data);
    }

    public QQmlContext rootContext()
    {
        void* contextData;
        dos_qqmlapplicationengine_context(data, contextData);
        return new QQmlContext(contextData);
    }
  
    public void load(string filename)
    {
        dos_qqmlapplicationengine_load(data, filename.toStringz());
    }
  
    private void* data;
}
