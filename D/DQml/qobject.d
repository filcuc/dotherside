import std.stdio;
import std.conv;
import std.container;
import std.traits;
import std.string;
import dothersideinterface;
import qmetatype;
import qvariant;
import qslot;
import qsignal;

public class QObject
{
  this()
  {
    dos_qobject_create(this.data, cast (void*) this, &staticSlotCallback);
  }
  
  ~this()
  {
    dos_qobject_delete(this.data);
  }
  
  private extern (C) static void staticSlotCallback(void* qObjectPtr,
						    void* slotName,
						    int numParameters,
						    void** parametersArray)
  {
    QVariant[] parameters = new QVariant[numParameters];
    for (int i = 0; i < numParameters; ++i)
      parameters[i] = new QVariant(parametersArray[i]);
    QObject qObject = cast(QObject) qObjectPtr;
    QVariant name = new QVariant(slotName);
    ISlot slot = qObject.slotsByName[name.toString()];
    slot.Execute(parameters);
  }

  protected auto registerSlot(T)(string name, T t) {
    auto slot = CreateQSlot(t);
    auto rawName = name.toStringz();
    int slotIndex = -1;
    int[] parameterMetaTypes = slot.GetParameterMetaTypes();
    int numArgs = cast(int)parameterMetaTypes.length;
    dos_qobject_slot_create(data, rawName, numArgs, parameterMetaTypes.ptr, slotIndex);
    slotsByName[name] = slot;
    return slot;
  }
  
  protected auto registerSignal(Args...)(string name) {
    auto signal = CreateQSignal!(Args)(this, name);
    auto rawName = name.toStringz();
    int index = -1;
    int[] parameterMetaTypes = signal.GetParameterMetaTypes();
    int numArgs = cast(int)parameterMetaTypes.length;
    dos_qobject_signal_create(data, rawName, numArgs, parameterMetaTypes.ptr, index);
    signalsByName[name] = signal;
    return signal;
  }

  protected void registerProperty(T)(string name,
				     string readSlotName,
				     string writeSlotName,
				     string notifySignalName)
  {
    int propertyMetaType = GetMetaType!(T)();
    dos_qobject_property_create(data,
				name.toStringz(),
				propertyMetaType,
				readSlotName.toStringz(),
				writeSlotName.toStringz(),
				notifySignalName.toStringz());
  }
  
  public void* data;
  private ISlot[string] slotsByName;
  private ISignal[string] signalsByName;
}

unittest
{
  auto test = new class QObject {
    this()
    {
      fooSignal = registerSignal!()("fooSignal");
      barSignal = registerSignal!(int)("barSignal");
      foo = registerSlot("foo", &_foo);
      bar = registerSlot("bar", &_bar);
    }
    
    QSlot!(void delegate()) foo;
    void _foo() { writeln("D: Called slot \"foo\"");}
  
    QSlot!(void delegate(int)) bar;
    void _bar(int arg) { writeln("D: Calling slot \"_bar\" with arg \"", arg, "\""); }
    
    QSignal!() fooSignal;
    QSignal!int barSignal;
  };
  
  test.foo();
  test.bar(10);
  test.fooSignal();
  test.barSignal(10);
}
