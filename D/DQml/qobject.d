import std.stdio;
import std.format;
import std.conv;
import std.container;
import std.traits;
import std.string;
import std.algorithm;
import dothersideinterface;
import qmetatype;
import qvariant;

public class QObject
{
    public this()
    {
        this(false);
    }

    protected this(bool disableDosCalls)
    {
        this.disableDosCalls = disableDosCalls;
        if (!this.disableDosCalls)
            dos_qobject_create(this.vptr, cast(void*)this, &staticSlotCallback);
    }

    ~this()
    {
        if (!this.disableDosCalls)
        {
            dos_qobject_delete(this.vptr);
            this.vptr = null;
        }
    }

    public void* voidPointer()
    {
        return this.vptr;
    }

    protected void onSlotCalled(QVariant slotName, QVariant[] parameters)
    {
    }

    protected void registerSlot(string name, QMetaType[] types)
    {
        int index = -1;
        int  length = cast(int)types.length;
        int[] array = to!(int[])(types);
        dos_qobject_slot_create(this.vptr,
                                name.toStringz(),
                                length,
                                array.ptr,
                                index);
    }

    protected void registerSignal(string name, QMetaType[] types)
    {
        int index = -1;
        int length = cast(int)types.length;
        int[] array = length > 0 ? to!(int[])(types) : null;
        dos_qobject_signal_create(this.vptr,
                                  name.toStringz(),
                                  length,
                                  array.ptr,
                                  index);
    }

    protected void registerProperty(string name,
                                    QMetaType type,
                                    string readSlotName,
                                    string writeSlotName,
                                    string notifySignalName)
    {
        dos_qobject_property_create(this.vptr,
                                    name.toStringz(),
                                    type,
                                    readSlotName.toStringz(),
                                    writeSlotName.toStringz(),
                                    notifySignalName.toStringz());
    }

    protected void emit(T)(string signalName, T t)
    {
        emit(signalName, new QVariant(t));
    }
  
    protected void emit(string signalName, QVariant value)
    {
        QVariant[] array = [value];
        emit(signalName, array);
    }

    protected void emit(string signalName, QVariant[] arguments = null)
    {
        int length = cast(int)arguments.length;
        void*[] array = null;
        if (length > 0) {
            array = new void*[length];
            foreach (int i, QVariant v; arguments)
                array[i] = v.voidPointer();
        }
        dos_qobject_signal_emit(this.vptr,
                                signalName.toStringz(),
                                length,
                                array.ptr);
    }

    protected extern (C) static void staticSlotCallback(void* qObjectPtr,
                                                        void* rawSlotName,
                                                        int numParameters,
                                                        void** parametersArray)
    {
        QVariant[] parameters = new QVariant[numParameters];
        for (int i = 0; i < numParameters; ++i)
            parameters[i] = new QVariant(parametersArray[i]);
        QObject qObject = cast(QObject) qObjectPtr;
        QVariant slotName = new QVariant(rawSlotName);
        qObject.onSlotCalled(slotName, parameters);
    }

    protected void* vptr;
    private bool disableDosCalls;
}
