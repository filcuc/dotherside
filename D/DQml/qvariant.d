import dothersideinterface;
import qobject;
import std.string;
import chararray;

class QVariant
{
  public this()
  {
    dos_qvariant_create(this.data);
  }
  
  public this(int value)
  {
    dos_qvariant_create_int(this.data, value);
  }
  
  public this(bool value)
  {
    dos_qvariant_create_bool(this.data, value);
  }
  
  public this(string value)
  {
    dos_qvariant_create_string(this.data, value.toStringz());
  }
  
  public this(QObject value)
  {
    dos_qvariant_create_qobject(this.data, value.data);
  }

  public  this(void* data, bool hasOwnership = false)
  {
    this.data = data;
    this.hasOwnership = hasOwnership;
  }

  ~this()
  {
    if (this.hasOwnership)
      dos_qvariant_delete(this.data);
  }

  public void* rawData()
  {
    return data;
  }

  public void setValue(int value)
  {
    dos_qvariant_setInt(this.data, value);
  }

  public void setValue(bool value)
  {
    dos_qvariant_setBool(this.data, value);
  }

  public void setValue(string value)
  {
    dos_qvariant_setString(this.data, value.toStringz());
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
  
  public  bool isNull()
  {
    bool result;
    dos_qvariant_isnull(this.data, result);
    return result;
  }
  
  public  bool toBool()
  {
    bool result;
    dos_qvariant_toBool(this.data, result);
    return result;
  }
  
  public int toInt()
  {
    int result;
    dos_qvariant_toInt(this.data, result);
    return result;
  }
  
  public override string toString()
  {
    auto result = new CharArray();
    scope(exit) destroy(result);
    dos_qvariant_toString(this.data, result.dataRef(), result.sizeRef());
    return result.toString();
  }

  private void* data = null;
  private bool hasOwnership = true;
}
