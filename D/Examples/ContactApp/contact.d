import dqml;

@QtProperty(string.stringof, "firstName", "firstName", "setFirstName", "firstNameChanged")
@QtProperty(string.stringof, "lastName", "lastName", "setLastName", "lastNameChanged")
class Contact : QObject
{
    mixin InjectQObjectMacro;
    mixin(Q_OBJECT!(Contact));

    this(string firstName = "", string lastName = "")
    {
        this.m_firstName = firstName;
        this.m_lastName = lastName;
    }

    @QtSlot()
    public string firstName()
    {
        return this.m_firstName;
    }

    @QtSlot()
    public void setFirstName(string firstName)
    {
        if (this.m_firstName != firstName)
        {
            this.m_firstName = firstName;
            firstNameChanged(firstName);
        }
    }

    @QtSignal()
    public void firstNameChanged(string);

    @QtSlot()
    public string lastName()
    {
        return this.m_lastName;
    }

    @QtSlot()
    public void setLastName(string lastName)
    {
        if (this.m_lastName != lastName)
        {
            this.m_lastName = lastName;
            lastNameChanged(lastName);
        }
    }

    @QtSignal()
    public void lastNameChanged(string);

    private string m_firstName;
    private string m_lastName;
}
