import dqml;

class MyQObject : QObject 
{
  this()
  {
    getName = registerSlot("getName", &_getName);
    setName = registerSlot("setName", &_setName);
    nameChanged = registerSignal!(string)("nameChanged");
    registerProperty!(string)("name", "getName", "setName", "nameChanged");
   }
  
  public QSlot!(string delegate()) getName;
  private string _getName() { return this.name; }

  public QSlot!(void delegate(string)) setName;
  private void _setName(string name)
  {
    if (this.name != name)
    {
      this.name = name;
      nameChanged(this.name);
    }
  }

  public QSignal!(string) nameChanged;

  private string name;
}
