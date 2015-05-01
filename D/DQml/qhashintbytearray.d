import dothersideinterface;
import qvariant;
import std.string;

class QHashIntByteArray
{
    this()
    {
        dos_qhash_int_qbytearray_create(this.vptr);
    }

    this(void* vptr)
    {
        this.vptr = vptr;
    }

    ~this()
    {
        dos_qhash_int_qbytearray_delete(this.vptr);
    }

    public void* voidPointer()
    {
        return vptr;
    }

    public void insert(int key, string value)
    {
        dos_qhash_int_qbytearray_insert(this.vptr, key, value.toStringz());
    }

    public string value(int key)
    {
        char* array;
        dos_qhash_int_qbytearray_value(this.vptr, key, array);
        string result = fromStringz(array).dup;
        dos_chararray_delete(array);
        return result;
    }

    private void* vptr;
}
