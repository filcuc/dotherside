import dqml;

class Contact : QObject
{
    this(string firstName = "", string lastName = "")
    {
        this.m_firstName = firstName;
        this.m_lastName = lastName;
        this.registerSlot("firstName", [QMetaType.String]);
        this.registerSlot("setFirstName", [QMetaType.Void, QMetaType.String]);
        this.registerSignal("firstNameChanged", [QMetaType.String]);
        this.registerSlot("lastName", [QMetaType.String]);
        this.registerSlot("setLastName", [QMetaType.Void, QMetaType.String]);
        this.registerSignal("lastNameChanged", [QMetaType.String]);
        this.registerProperty("firstName", QMetaType.String, "firstName", "setFirstName", "firstNameChanged");
        this.registerProperty("lastName", QMetaType.String, "lastName", "setLastName", "lastNameChanged");
    }

    public string firstName()
    {
        return this.m_firstName;
    }

    public void setFirstName(string firstName)
    {
        if (this.m_firstName != firstName)
        {
            this.m_firstName = firstName;
            emit("firstNameChanged", firstName);
        }
    }

    public string lastName()
    {
        return this.m_lastName;
    }

    public void setLastName(string lastName)
    {
        if (this.m_lastName != lastName)
        {
            this.m_lastName = lastName;
            emit ("lastNameChanged", lastName);
        }
    }

    protected override void onSlotCalled(QVariant slotName, QVariant[] arguments)
    {
        switch (slotName.toString())
        {
        case "firstName":
            arguments[0].setValue(firstName());
            break;
        case "setFirstName":
            setFirstName(arguments[1].toString());
            break;
        case "lastName":
            arguments[0].setValue(lastName());
            break;
        case "setLastName":
            setLastName(arguments[1].toString());
            break;
        default:
            break;
        }
    }

    private string m_firstName;
    private string m_lastName;
}
