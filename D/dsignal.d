import dotherside;
import dobject;
import dothersideinterface;
import std.stdio;
import std.conv;
import std.string;

public class ISignal
{
}

public class DSignal(Args...) : ISignal
{
	public this(DObject dObject, string name)
	{
		this.dObject = dObject;
		this.name = name;
		foreach(i, arg; Args)
		    _parameterMetaTypes[i] = GetMetaType!arg();
	}

	void opCall(Args args)
	{
		QVariant[] temp = new QVariant[args.length];
		void*[] temp2 = new void*[args.length];
		foreach(i, arg; args)
		{
			auto variant = new QVariant(arg);
		    temp[i] = variant;
		    temp2[i] = variant.rawData();
		}

	    dos_qobject_signal_emit(this.dObject.data, this.name.toStringz(), cast(int)temp2.length, temp2.ptr);
	}

	public int[] GetParameterMetaTypes() 
	{ 
		return _parameterMetaTypes;
	}

	private DObject dObject;
	private string name;
	private int[] _parameterMetaTypes = new int[Args.length];
};

public DSignal!(Args) CreateDSignal(Args...)(DObject dObject, string name)
{
	return new DSignal!(Args)(dObject, name);
}