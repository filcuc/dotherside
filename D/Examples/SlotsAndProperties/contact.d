import dqml;
import std.traits;
import std.algorithm;
import std.string;
import std.stdio;

struct QtProperty {
    public enum Type { Read = 0, Write = 1}
    public string name;
    public Type type;

    this(string name, Type type)
    {
        this.name = name;
        this.type = type;
    }
}
struct QtSlot {};
struct QtSignal {};

string GenerateVariantConversionCall(string typeName)
{
    switch (typeName)
    {
    case "string":
        return "toString()";
    case "int":
        return "toInt()";
    default:
        throw new Exception("error");
    }
}

string GenerateArgumentList(string[] typeNames)
{
    string result = "";
    for (int i = 0; i < typeNames.length; ++i)
    {
        auto typeName = typeNames[i];
        auto variantCall = GenerateVariantConversionCall(typeName);
        result ~= i > 0 ? "," : "";
        result ~= format("arguments[%d].%s", i+1, variantCall);
    }
    return result;
}

string GenerateSlotCall(FunctionInfo info)
{
    auto args = GenerateArgumentList(info.parameterTypes);
    auto call = format("%s(%s)", info.name, args);
    auto formatStr = info.returnType != "void" ? "arguments[0].setValue(%s)" : "%s";
    return format(formatStr, call);
}

string GenerateCaseBlock(FunctionInfo info)
{
    string result = "";
    result ~= format("case \"%s\":\n", info.name);
    result ~= format("%s;\n", GenerateSlotCall(info));
    result ~= "break;\n";
    return result;
}

string GenerateOnSlotCalled(T)()
{
    string result = "protected override void onSlotCalled(QVariant slotName, QVariant[] arguments)\n";
    result ~= "{\n";
    result ~= "switch(slotName.toString())\n";
    result ~= "{\n";
    auto info = IterateUDA!(T)();
    foreach (slot; info.slots)
        result ~= GenerateCaseBlock(slot);
    result ~= "default: break;\n";
    result ~= "}\n"; // 
    result ~= "}";
    return result;
}

string GenerateSignalCall(FunctionInfo info)
{
    string args = "";
    string vars = "";
    for (int i = 0; i < info.parameterTypes.length; ++i) {
        if (i > 0) {
            args ~= ",";
            vars ~= ",";
        }
        args ~= format("%s val%d", info.parameterTypes[i], i);
        vars ~= format("val%d", i);
    }

    auto result = format("%s %s(%s) { emit(\"%s\", %s); }", info.returnType, info.name, args, info.name, vars);
    return result;
}

string GenerateQtSignals(T)()
{
    string result = "";

    auto info = IterateUDA!(T)();
    
    foreach (signal; info.signals)
    {
        result ~= GenerateSignalCall(signal) ~ "\n";
    }

    return result;
}

string GenerateMetaType(string typeName)
{
    switch(typeName)
    {
    case "void":
        return "QMetaType.Void";
    case "int":
        return "QMetaType.Int";
    case "string":
        return "QMetaType.String";
    default:
        throw new Exception(format("Unknown conversion from %s to QMetaType", typeName));
    }
}

string GenerateMetaTypesList(FunctionInfo info)
{
    string result = GenerateMetaType(info.returnType);
    foreach (typeName; info.parameterTypes)
        result ~= format(", %s", GenerateMetaType(typeName));
    return result;
}

string GenerateQObjectInit(T)()
{
    string result = "";
    result ~= "protected void qobjectInit()\n";
    result ~= "{\n";

    auto info = IterateUDA!(T)();
    
    foreach (slot; info.slots)
    {
        auto metaTypes = GenerateMetaTypesList(slot);
        result ~= format("registerSlot(\"%s\", [%s]);\n", slot.name, metaTypes);
    }
    
    result ~= "}";
    return result;
}

struct FunctionInfo
{
    string name;
    string returnType;
    string[] parameterTypes;
}

struct QtInfo
{
    FunctionInfo[] slots;
    FunctionInfo[] signals;
    QtProperty[] properties;
}

QtInfo IterateUDA(T)()
{
    QtInfo result;
    
    foreach (member; __traits(allMembers, T))
    {
        static if (isSomeFunction!(__traits(getMember, T, member)))
        {
            // Retrieve the UDA
            auto attributes = __traits(getAttributes, __traits(getMember, T, member));

            // Turn the tuple in an array of strings
            string[] attributeNames;
            foreach (attribute; attributes)
                attributeNames ~= typeof(attribute).stringof;

            bool isSlot = attributeNames.canFind("QtSlot");
            bool isSignal = attributeNames.canFind("QtSignal");
            bool isProperty = attributeNames.canFind("QtProperty");
            
            // Extract the Function Return Type and Arguments
            if (isSlot || isSignal)
            {
                FunctionInfo info;
                info.name = member;
                info.returnType = ReturnType!(__traits(getMember, T, member)).stringof;

                foreach (param; ParameterTypeTuple!(__traits(getMember, T, member)))
                    info.parameterTypes ~= param.stringof;

                if (isSlot)
                    result.slots ~= info;

                if (isSignal)
                    result.signals ~= info;
            }
        }
    }
  
    return result;
}


class Contact : QObject
{
    this()
    {
        registerSlot("getName", [QMetaType.String]);
        registerSlot("setName", [QMetaType.Void, QMetaType.String]);
        registerSignal("nameChanged", [QMetaType.String]);
        registerProperty("name", QMetaType.String, "getName", "setName", "nameChanged");

        auto info = IterateUDA!(Contact);
        
        foreach(slot; info.slots)
            writeln("Slot:", slot.name);
        
        foreach(signal; info.signals)
            writeln("Signals:", signal.name);
        
        foreach(property; info.properties)
            writeln("Property:", property.name);
        
        writeln(GenerateOnSlotCalled!(Contact));
//        writeln(GenerateQObjectInit!(Contact));
        writeln(GenerateQtSignals!(Contact));
    }
    
    ~this() {}

    @QtSlot()
    public string getName()
    {
        return m_name;
    }

    @QtSlot()
    public void setName(string name)
    {
        if (m_name != name)
        {
            m_name = name;
            emit("nameChanged", name);
        }
    }

    @QtSignal()
    public void nameChanged(string name);

    @QtSlot()
    public string getSurname()
    {
        return m_surname;
    }

    @QtSlot()
    public void setSurname(string surname)
    {
        m_surname = surname;
    }

    @QtSignal()
    void surnameChanged(string surname);

    mixin(GenerateOnSlotCalled!(Contact));
    mixin(GenerateQObjectInit!(Contact));
    mixin(GenerateQtSignals!(Contact));
    
    private string m_name;
    private string m_surname;
}
