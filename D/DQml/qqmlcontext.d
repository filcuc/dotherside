import dothersideinterface;
import qvariant;
import std.string;

class QQmlContext
{
    public this(void* data)
    {
        this.data = data;
    }

    public void* rawData()
    {
        return data;
    }

    public string baseUrl()
    {
        char* array;
        dos_qqmlcontext_baseUrl(data, array);
        string result = fromStringz(array).dup;
        dos_chararray_delete(array);
        return result;
    }
  
    public void setContextProperty(string name, QVariant value)
    {
        dos_qqmlcontext_setcontextproperty(data, name.ptr, value.rawData());
    }

    private void* data;
}
