public class ISignal
{
}

public class DSignal(Args...) : ISignal
{
  void opCall(Args args)
  {
  }
};

public DSignal!(Args) CreateDSignal(Args...)()
{
  return new DSignal!(Args)();
}