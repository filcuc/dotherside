import std.stdio;
import std.conv;
import std.container;
import std.traits;
import std.string;
import dothersideinterface;
import dslot;
import dsignal;


void NoConversionAssign(T)(void* lValue, void* rValue)
{
  *(cast(T*)lValue) = *(cast(T*)rValue);
}

void SafeAssignCpp(int metaType, void* lValue, void* rValue)
{
  if (metaType == 2) NoConversionAssign!int(lValue, rValue);
}

void SafeAssignD(int metaType, void* lValue, void* rValue)
{
  if (metaType == 2) NoConversionAssign!int(lValue, rValue);
}

void* Allocate(int metaType)
{
  if (metaType == 2) { int* result = new int(); *result = 0; return result; }
  assert(false);
}


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
  
  extern (C) static void staticSlotCallback(void* dobject, int slotIndex, int numMetaTypes, int* metaTypes, int numParameters, ref void** parameters)
  {
    DObject dObject = cast(DObject) dobject;
    
    writeln("D: Received ", numMetaTypes, " metaTypes for ", numParameters, " parameters" );

    // Given the MetaType arguments construct a void*[] array with good D type for the arguments 
    // without the return value. So we start from 1
    void*[] args = new void*[numParameters];
    
    for (int i = 1; i < numMetaTypes; ++i)
    {
      int metaType = metaTypes[i];
      args[i] = Allocate(metaType);
      SafeAssignD(metaType, args[i], parameters[i]);
    }
    
    // Retrieve the slot an call it
    ISlot slot = dObject._slotsByIndex[slotIndex];
    slot.Execute(args);
    
    // Adapt the return type for being a good c++ value
    SafeAssignCpp(metaTypes[0], parameters[0] , args[0]);
  }

  protected auto registerSlot(T)(string name, T t) {
    debug writeln("D: Registering Slot \"", name, "\" of type \"", T.stringof, "\"");
    auto slot = CreateDSlot(t);
    auto rawName = name.toStringz();
    int slotIndex = -1;
    int[] parameterMetaTypes = slot.GetParameterMetaTypes();
    int numArgs = cast(int)parameterMetaTypes.length;
    dos_qobject_slot_create(data, rawName, numArgs, parameterMetaTypes.ptr, slotIndex);
    writeln("D: Registered Slot has index ", slotIndex);
    _slotsByName[name] = slot;
    _slotsByIndex[slotIndex] = slot;
    return slot;
  }
  
  protected auto registerSignal(Args...)(string name) {
    debug writeln("D: Registering Signal \"", name, "\" of type \"", Args.stringof, "\"");
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
    void _foo() { writeln("D: Called slot \"_foo\"");}
  
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