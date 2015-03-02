import dqml;

class Contact : QObject
{
    this(string firstName, string lastName)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        
        getFirstName = registerSlot("getFirstName", &_getFirstName);
        setFirstName = registerSlot("setFirstName", &_setFirstName);
        firstNameChanged = registerSignal!(string)("firstNameChanged");
        registerProperty!(string)("firstName", "getFirstName", "setFirstName", "firstNameChanged");
        
        getLastName = registerSlot("getLastName", &_getLastName);
        setLastName = registerSlot("setLastName", &_setLastName);
        lastNameChanged = registerSignal!(string)("lastNameChanged");
        registerProperty!(string)("lastName", "getLastName", "setLastName", "lastNameChanged");
    }
    
    public QSlot!(string delegate()) getFirstName;
    public QSlot!(void delegate(string)) setFirstName;
    public QSignal!(string) firstNameChanged;
    
    public QSlot!(string delegate()) getLastName;
    public QSlot!(void delegate(string)) setLastName;
    public QSignal!(string) lastNameChanged;
    
    private string _getFirstName() 
    { 
        return this.firstName; 
    }
    
    private void _setFirstName(string firstName)
    {
        if (this.firstName != firstName)
        {
            this.firstName = firstName;
            firstNameChanged(firstName);
        }
    }
    
    private string _getLastName() 
    { 
        return this.lastName; 
    }
    
    private void _setLastName(string lastName)
    {
        if (this.lastName != lastName)
        {
            this.lastName = lastName;
            lastNameChanged(lastName);
        }
    }
    
    private string firstName;
    private string lastName;
}