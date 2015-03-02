import dqml;
import contact;
import std.stdio;

class ContactList : QObject 
{
    this()
    {
        contacts = new Contact[](0);
        getCount = registerSlot("getCount", &_getCount);
        countChanged = registerSignal!(int)("countChanged");
        registerProperty!(int)("count", "getCount", null, "countChanged");
        getContact = registerSlot("getContact", &_getContact);
        addContact = registerSlot("addContact", &_addContact);
    }
    
    ~this()
    {
        foreach (contact; this.contacts)
        {
            destroy(contact);
        }
    }
  
    public QSlot!(int delegate()) getCount;
    public QSignal!(int) countChanged;
  
    public QSlot!(QObject delegate(int)) getContact;
    public QSlot!(void delegate(string, string)) addContact;
    
    private void _addContact(string firstName, string lastName)
    {
        this.contacts ~= new Contact(firstName, lastName);
        countChanged(_getCount());
    }
  
    private QObject _getContact(int index)
    {
        return this.contacts[index];
    }
    
    private int _getCount() 
    { 
        return cast(int)this.contacts.length; 
    }
  
    private Contact[] contacts;
}