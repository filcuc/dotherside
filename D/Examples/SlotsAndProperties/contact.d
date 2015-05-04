import dqml;
import std.traits;
import std.algorithm;
import std.string;
import std.stdio;

struct Slot {};
struct Signal {};

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

string GenerateSlotCall(SlotInfo info)
{
    auto args = GenerateArgumentList(info.parameterTypes);
    auto call = format("%s(%s)", info.name, args);
    auto formatStr = info.returnType != "void" ? "arguments[0].setValue(%s)" : "%s";
    return format(formatStr, call);
}

string GenerateCaseBlock(SlotInfo info)
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
    foreach (info; IterateUDA!(T)())
        result ~= GenerateCaseBlock(info);
    result ~= "default: break;\n";
    result ~= "}\n"; // 
    result ~= "}";
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

string GenerateMetaTypesList(SlotInfo info)
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

    foreach (info; IterateUDA!(T)())
    {
        auto metaTypes = GenerateMetaTypesList(info);
        result ~= format("registerSlot(\"%s\", [%s]);\n", info.name, metaTypes);
    }
    
    result ~= "}";
    return result;
}

struct SlotInfo
{
    string name;
    string returnType;
    string[] parameterTypes;
}

SlotInfo[] IterateUDA(T)()
{
    SlotInfo[] result;
    
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
            
            // Extract the Function Return Type and Arguments
            if (attributeNames.canFind("Slot"))
            {
                SlotInfo slotInfo;
                slotInfo.name = member;
                slotInfo.returnType = ReturnType!(__traits(getMember, T, member)).stringof;

                foreach (param; ParameterTypeTuple!(__traits(getMember, T, member)))
                    slotInfo.parameterTypes ~= param.stringof;

                result ~= slotInfo;
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

        writeln(GenerateOnSlotCalled!(Contact));
        writeln(GenerateQObjectInit!(Contact));
    }
    
    ~this() {}

    @Slot()
    public string getName()
    {
        return m_name;
    }

    @Slot()
    public void setName(string name)
    {
        if (m_name != name)
        {
            m_name = name;
            emit("nameChanged", name);
        }
    }

    mixin(GenerateOnSlotCalled!(Contact));
    mixin(GenerateQObjectInit!(Contact));
    
    private string m_name;
}
