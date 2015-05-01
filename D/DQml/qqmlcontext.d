import dothersideinterface;
import qvariant;
import std.string;

class QQmlContext
{
    public this(void* ptr)
    {
        this.vptr = vptr;
    }

    public void* voidPointer()
    {
        return vptr;
    }

    public string baseUrl()
    {
        char* array;
        dos_qqmlcontext_baseUrl(vptr, array);
        string result = fromStringz(array).dup;
        dos_chararray_delete(array);
        return result;
    }
  
    public void setContextProperty(string name, QVariant value)
    {
        dos_qqmlcontext_setcontextproperty(vptr, name.ptr, value.voidPointer());
    }

    private void* vptr;
}
