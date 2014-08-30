import std.stdio;
import std.container;
import std.conv;
import std.typecons;
import std.traits;
import dotherside;

public class ISlot
{
  void Execute(QVariant[]  arguments) {}
}

public DSlot!(T) CreateDSlot(T)(T t) if (isCallable!(T))
{
  return new DSlot!(T)(t);
}

public class DSlot(T) : ISlot
{ 
  alias ReturnType!T SlotReturnType;
  alias ParameterTypeTuple!T Arguments;
  
  public this(T callable)
  {
    _callable = callable;
    
    _parameterMetaTypes[0] = GetMetaType!SlotReturnType();
    foreach (i, arg; Arguments)
      _parameterMetaTypes[i+1] = GetMetaType!arg();
  }
  
  public override void Execute(QVariant[]  arguments)
  {
    Arguments argumentsTuple;
    
    foreach (i, arg; argumentsTuple) {
      arguments[i + 1].getValue(argumentsTuple[i]);
    }
    
    static if (is(SlotReturnType == void))
    {
      opCall(argumentsTuple);
    }
    else
    {
      auto result = opCall(argumentsTuple);
      arguments[0].setValue(result);
    }
  }
  
  public ReturnType!T opCall(Arguments arguments)
  {
    return _callable(arguments);
  }
  
  public int[] GetParameterMetaTypes() { return _parameterMetaTypes; }
  
  private T _callable;
  private int[] _parameterMetaTypes = new int[Arguments.length + 1];
};