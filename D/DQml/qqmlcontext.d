import dothersideinterface;
import qvariant;
import std.string;

class QQmlContext
{
    this(void* vptr)
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
        dos_qqmlcontext_baseUrl(this.vptr, array);
        string result = fromStringz(array).dup;
        dos_chararray_delete(array);
        return result;
    }
  
    public void setContextProperty(string name, QVariant value)
    {
        dos_qqmlcontext_setcontextproperty(this.vptr, name.ptr, value.voidPointer());
    }

    private void* vptr;
}
