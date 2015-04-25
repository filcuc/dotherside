import std.stdio;
import std.format;
import dqml;

class MyQObject : QObject 
{
  this()
  {
    m_name = "John Doo";
    registerSlot("name", [QMetaType.String]);
    registerSlot("setName", [QMetaType.Void, QMetaType.String]);
    registerSignal("nameChanged", [QMetaType.String]);
    registerProperty("name", QMetaType.String, "name", "setName", "nameChanged");
  }

  public string name()
  {
    return m_name;
  }

  public void setName(string name)
  {
    if (name == m_name)
      return;
    m_name = name;
    emit("nameChanged", new QVariant(name));
  }

  override void onSlotCalled(QVariant slotName, QVariant[] arguments)
  {
    switch(slotName.toString())
    {
    case "name":
        arguments[0].setValue(name());
        break;
    case "setName":
        setName(arguments[1].toString());
        break;
    default:
        break;
    }
  }

  private string m_name;
}
