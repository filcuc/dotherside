import std.traits;
import std.algorithm;
import std.string;
import std.stdio;

struct QtProperty 
{
    public string type;
    public string name;
    public string read;
    public string write;
    public string notify;

    this(string type, string name, string read, string write, string notify)
    {
        this.type = type;
        this.name = name;
        this.read = read;
        this.write = write;
        this.notify = notify;
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
    case "bool":
        return "toBool()";
    case "QVariant":
        return "";
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

string GenerateOnSlotCalled(QtInfo info)
{
    string result = "protected override void onSlotCalled(QVariant slotName, QVariant[] arguments)\n";
    result ~= "{\n";
    result ~= "switch(slotName.toString())\n";
    result ~= "{\n";
    foreach (slot; info.slots)
        result ~= GenerateCaseBlock(slot);
    result ~= "default: super.onSlotCalled(slotName, arguments);\n";
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

    auto result = format("public %s %s(%s) { emit(\"%s\", %s); }", info.returnType, info.name, args, info.name, vars);
    return result;
}

string GenerateQtSignals(QtInfo info)
{
    string result = "";
    foreach (signal; info.signals)
        result ~= GenerateSignalCall(signal) ~ "\n";
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
    case "QObject":
        return "QMetaType.QObject";
    case "QVariant":
        return "QMetaType.QVariant";
    case "bool":
        return "QMetaType.Bool";
    default:
        throw new Exception(format("Unknown conversion from %s to QMetaType", typeName));
    }
}

string GenerateMetaTypesListForSlot(FunctionInfo info)
{
    string result = GenerateMetaType(info.returnType);
    result ~= ", ";
    result ~= GenerateMetaTypesListForSignal(info);
    return result;
}

string GenerateMetaTypesListForSignal(FunctionInfo info)
{
    string result = "";
    for (int i = 0; i < info.parameterTypes.length; ++i)
    {
        if (i > 0)
            result ~= ", ";
        result ~= GenerateMetaType(info.parameterTypes[i]);
    }
    return result;
}

string GenerateQObjectInit(QtInfo info)
{
    string result = "";
    result ~= "protected override void qobjectInit()\n";
    
    foreach (slot; info.slots)
    {
        auto metaTypes = GenerateMetaTypesListForSlot(slot);
        result ~= format("registerSlot(\"%s\", [%s]);\n", slot.name, metaTypes);
    }

    foreach (signal; info.signals)
    {
        auto metaTypes = GenerateMetaTypesListForSignal(signal);
        result ~= format("registerSignal(\"%s\", [%s]);\n", signal.name, metaTypes);
    }

    foreach (property; info.properties)
    {
        result ~= format("registerProperty(\"%s\", %s, \"%s\", \"%s\", \"%s\");\n", property.name, GenerateMetaType(property.type), property.read, property.write, property.notify);
    }
    
    result ~= "super.qobjectInit();\n";
    
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
    
mixin template InjectQObjectMacro()
{
    private static QtInfo GetQtUDA(T)()
    {
        QtInfo result;

        foreach (attribute; __traits(getAttributes, T)) {
            static if (is (typeof(attribute) == QtProperty)) {
                result.properties ~= attribute;
            }
        }
        
        foreach (member; __traits(allMembers, T))
        {
            static if (__traits(compiles, __traits(getMember, T, member))
                       && isSomeFunction!(__traits(getMember, T, member)))
            {
                // Retrieve the UDA
                auto attributes = __traits(getAttributes, __traits(getMember, T, member));

                // Turn the tuple in an array of strings
                string[] attributeNames;
                foreach (attribute; attributes)
                    attributeNames ~= typeof(attribute).stringof;

                bool isSlot = attributeNames.canFind("QtSlot");
                bool isSignal = attributeNames.canFind("QtSignal");
            
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

    private static string Q_OBJECT(T)()
    {
        string result = "";
        auto info = T.GetQtUDA!(T);
        result ~= GenerateOnSlotCalled(info) ~ "\n";
        result ~= GenerateQObjectInit(info) ~ "\n";
        result ~= GenerateQtSignals(info) ~ "\n";
        return result;
    }
}


