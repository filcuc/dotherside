import std.stdio;
import std.conv;
import std.container;
import std.traits;
import std.string;
import dothersideinterface;
import dslot;
import dsignal;
import dotherside;

public class DObject
{
  this()
  {
    dos_qobject_create(this.data, cast (void*) this, &staticSlotCallback);
  }
  
  ~this()
  {
    dos_qobject_delete(this.data);
  }
  
  private extern (C) static void staticSlotCallback(void* dobject, int slotIndex, int numParameters, void** parameters)
  {
    QVariant[] arguments = new QVariant[numParameters];
    for (int i = 0; i < numParameters; ++i)
      arguments[i] = new QVariant(parameters[i]);
    DObject dObject = cast(DObject) dobject;
    ISlot slot = dObject._slotsByIndex[slotIndex];
    slot.Execute(arguments);
  }

  protected auto registerSlot(T)(string name, T t) {
    debug writefln("D: Registering Slot %s of type %s", name, T.stringof);
    auto slot = CreateDSlot(t);
    auto rawName = name.toStringz();
    int slotIndex = -1;
    int[] parameterMetaTypes = slot.GetParameterMetaTypes();
    int numArgs = cast(int)parameterMetaTypes.length;
    dos_qobject_slot_create(data, rawName, numArgs, parameterMetaTypes.ptr, slotIndex);
    debug writefln("D: Registered Slot has index %d", slotIndex);
    _slotsByName[name] = slot;
    _slotsByIndex[slotIndex] = slot;
    return slot;
  }
  
  protected auto registerSignal(Args...)(string name) {
    debug writefln("D: Registering Signal %s of type %s ", name, Args.stringof);
    auto signal = CreateDSignal!(Args)(this, name);
    auto rawName = name.toStringz();
    int index = -1;
    int[] parameterMetaTypes = signal.GetParameterMetaTypes();
    int numArgs = cast(int)parameterMetaTypes.length;
    dos_qobject_signal_create(data, rawName, numArgs, parameterMetaTypes.ptr, index);
    _signalsByName[name] = signal;
    _signalsByIndex[index] = signal;
    return signal;
  }
  
  public void* data;
  private ISlot[string] _slotsByName;
  private ISlot[int] _slotsByIndex;
  private ISignal[string] _signalsByName;
  private ISignal[int] _signalsByIndex;
}

unittest
{
  auto test = new class DObject {
    this()
    {
      fooSignal = registerSignal!()("fooSignal");
      barSignal = registerSignal!(int)("barSignal");
      foo = registerSlot("foo", &_foo);
      bar = registerSlot("bar", &_bar);
    }
    
    DSlot!(void delegate()) foo;
    void _foo() { writeln("D: Called slot \"foo\"");}
  
    DSlot!(void delegate(int)) bar;
    void _bar(int arg) { writeln("D: Calling slot \"_bar\" with arg \"", arg, "\""); }
    
    DSignal!() fooSignal;
    DSignal!int barSignal;
  };
  
  test.foo();
  test.bar(10);
  test.fooSignal();
  test.barSignal(10);
}