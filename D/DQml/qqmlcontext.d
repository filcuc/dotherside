import dothersideinterface;
import qvariant;
import chararray;

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
    auto array = new CharArray();
    scope(exit) destroy(array);
    dos_qqmlcontext_baseUrl(data, array.dataRef(), array.sizeRef());
    return array.toString();
  }
  
  public void setContextProperty(string name, QVariant value)
  {
    dos_qqmlcontext_setcontextproperty(data, name.ptr, value.rawData());
  }

  private void* data;
}
