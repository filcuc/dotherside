import dothersideinterface;
import qobject;
import std.string;

class QVariant
{
    public this()
    {
        dos_qvariant_create(this.vptr);
    }
  
    public this(int value)
    {
        dos_qvariant_create_int(this.vptr, value);
    }
  
    public this(bool value)
    {
        dos_qvariant_create_bool(this.vptr, value);
    }
  
    public this(string value)
    {
        dos_qvariant_create_string(this.vptr, value.toStringz());
    }

    public this(float value)
    {
        dos_qvariant_create_float(this.vptr, value);
    }
    
    public this(double value)
    {
        dos_qvariant_create_double(this.vptr, value);
    }

    public this(QObject value)
    {
        dos_qvariant_create_qobject(this.vptr, value.voidPointer());
    }

    public this(void* vptr, bool hasOwnership = false)
    {
        this.vptr = vptr;
        this.hasOwnership = hasOwnership;
    }

    ~this()
    {
        if (this.hasOwnership)
            dos_qvariant_delete(this.vptr);
    }

    public void* voidPointer()
    {
        return this.vptr;
    }

    public void setValue(int value)
    {
        dos_qvariant_setInt(this.vptr, value);
    }

    public void setValue(bool value)
    {
        dos_qvariant_setBool(this.vptr, value);
    }

    public void setValue(string value)
    {
        dos_qvariant_setString(this.vptr, value.toStringz());
    }
  
    public void setValue(QObject value)
    {
        dos_qvariant_setQObject(this.vptr, value.voidPointer());
    }

    public void setValue(float value)
    {
        dos_qvariant_setFloat(this.vptr, value);
    }

    public void setValue(double value)
    {
        dos_qvariant_setDouble(this.vptr, value);
    }

    public void getValue(ref int value)
    {
        value = toInt();
    }

    public void getValue(ref bool value)
    {
        value = toBool();
    }

    public void getValue(ref string value)
    {
        value = toString();
    }

    public void getValue(ref float value)
    {
        value = toFloat();
    }
  
    public void getValue(ref double value)
    {
        value = toDouble();
    }

    public  bool isNull()
    {
        bool result;
        dos_qvariant_isnull(this.vptr, result);
        return result;
    }
  
    public  bool toBool()
    {
        bool result;
        dos_qvariant_toBool(this.vptr, result);
        return result;
    }
  
    public int toInt()
    {
        int result;
        dos_qvariant_toInt(this.vptr, result);
        return result;
    }

    public float toFloat()
    {
        float result;
        dos_qvariant_toFloat(this.vptr, result);
        return result;
    }

    public double toDouble()
    {
        double result;
        dos_qvariant_toDouble(this.vptr, result);
        return result;
    }
  
    public override string toString()
    {
        char* array;
        dos_qvariant_toString(this.vptr, array);
        string result = fromStringz(array).dup;
        dos_chararray_delete(array);
        return result;
    }

    private void* vptr = null;
    private bool hasOwnership = true;
}
