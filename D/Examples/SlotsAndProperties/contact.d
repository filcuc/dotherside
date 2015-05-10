import dqml;

@QtProperty(string.stringof, "name", "getName", "setName", "nameChanged")
@QtProperty(string.stringof, "surname", "getSurname", "setSurname", "surnameChanged")
class Contact : QObject
{
    mixin InjectQObjectMacro;
    mixin(Q_OBJECT!(Contact));
    
    this()
    {}
    
    ~this()
    {}

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

    private string m_name;
    private string m_surname;
}
