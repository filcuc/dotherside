import std.stdio;
import std.conv;
import std.container;
import std.traits;
import std.string;
import dothersideinterface;
import dslot;
import dsignal;



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
  
  extern (C) static void staticSlotCallback(void* dobject, int slotIndex, int numParameters, ref void** parameters)
  {
    DObject dObject = cast(DObject) dobject;

    // Given the MetaType arguments construct a void*[] array with good D type
    void*[] args = new void*[numParameters / 2];
    
    // Retrieve the slot an call the slot
    ISlot slot = dObject._slotsByIndex[slotIndex];
    slot.Execute(args);
    
    if (numParameters > 0)
    {
      writeln("Parameters", numParameters);
      writeln("ResultType: ", *(cast(int*)parameters[0]));
      writeln("ResultValue: ", *(cast(int*)parameters[1]));
      writeln("ResultValue2: ", *(cast(int*)args[0]));
      
      (*(cast(int*)parameters[1])) = (*(cast(int*)args[0]));
    }
  }

  protected auto registerSlot(T)(string name, T t) {
    debug writeln("Registering Slot: \"", name, "\" of type \"", T.stringof, "\"");
    auto slot = CreateDSlot(t);
    auto rawName = name.toStringz();
    int slotIndex = -1;
    int[] parameterMetaTypes = slot.GetParameterMetaTypes();
    int numArgs = cast(int)parameterMetaTypes.length;
    dos_qobject_slot_create(data, rawName, numArgs, parameterMetaTypes.ptr, slotIndex);
    writeln("Slot index is", slotIndex);
    _slotsByName[name] = slot;
    _slotsByIndex[slotIndex] = slot;
    return slot;
  }
  
  protected auto registerSignal(Args...)(string name) {
    debug writeln("Registering Signal: \"", name, "\" of type \"", Args.stringof, "\"");
    auto signal = CreateDSignal!(Args)();
    _signals[name] = signal;
    return signal;
  }
  
  public void* data;
  private ISlot[string] _slotsByName;
  private ISlot[int] _slotsByIndex;
  private ISignal[string] _signals;
}

unittest
{
  auto test = new class DObject {
    this()
    {
      foo = registerSlot("foo", &_foo);
      bar = registerSlot("bar", &_bar);
      fooSignal = registerSignal!()("fooSignal");
      barSignal = registerSignal!(int)("barSignal");
    }
    
    DSlot!(void delegate()) foo;
    void _foo() { writeln("Called slot \"_foo\"");}
  
    DSlot!(void delegate(int)) bar;
    void _bar(int arg) { writeln("Calling slot \"_bar\" with arg \"", arg, "\""); }
    
    DSignal!() fooSignal;
    DSignal!int barSignal;
  };
  
  test.foo();
  test.bar(10);
  test.fooSignal();
  test.barSignal(10);
}