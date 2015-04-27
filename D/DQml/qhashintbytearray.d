import dothersideinterface;
import qvariant;
import std.string;

class QHashIntByteArray
{
    this()
    {
        dos_qhash_int_qbytearray_create(data);
    }

    ~this()
    {
        dos_qhash_int_qbytearray_delete(data);
    }

    public void insert(int key, string value)
    {
        dos_qhash_int_qbytearray_insert(key, value.toStringz());
    }

    public string value(int key)
    {
        char* array;
        dos_qhash_int_qbytearray_value(key, array);
        string result = fromStringz(array).dup;
        dos_chararray_delete(array);
        return result;
    }

    public void* rawData()
    {
        return data;
    }
    
    private void* data;
}
