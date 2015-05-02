import dqml;

class Contact : QObject
{
    this()
    {
        registerSlot("getName", [QMetaType.String]);
        registerSlot("setName", [QMetaType.Void, QMetaType.String]);
        registerSignal("nameChanged", [QMetaType.String]);
        registerProperty("name", QMetaType.String, "getName", "setName", "nameChanged");
    }
    
    ~this() {}


    public string getName()
    {
        return m_name;
    }

    public void setName(string name)
    {
        if (m_name != name)
        {
            m_name = name;
            emit("nameChanged", name);
        }
    }

    protected override void onSlotCalled(QVariant slotName, QVariant[] arguments)
    {
        switch (slotName.toString())
        {
        case "getName":
            arguments[0].setValue(getName());
            break;
        case "setName":
            setName(arguments[1].toString());
            break;
        default:
            break;
        }
    }

    private string m_name;
}
