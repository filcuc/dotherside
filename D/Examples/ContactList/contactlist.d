import dqml;
import contact;
import std.stdio;
import std.format;

class ContactList : QObject 
{
    this()
    {
        contacts = new Contact[](0);
        registerSlot("getCount", [QMetaType.Int]);
        registerSignal("countChanged", [QMetaType.Int]);
        registerProperty("count", QMetaType.Int, "getCount", null, "countChanged");
        registerSlot("getContact", [QMetaType.QObject, QMetaType.Int]);
        registerSlot("addContact", [QMetaType.Void, QMetaType.String, QMetaType.String]);
    }
    
    ~this()
    {
        foreach (contact; this.contacts)
           destroy(contact);
    }
  
    public void addContact(string firstName, string lastName)
    {
        writefln("addContact %s %s", firstName, lastName);
        this.contacts ~= new Contact(firstName, lastName);
        emit ("countChanged", new QVariant(getCount()));
    }
  
    public QObject getContact(int index)
    {
        writefln("getContact index %d", index);
        return this.contacts[index];
    }
    
    public int getCount() 
    { 
        auto result = cast(int)this.contacts.length;
	writefln("getCount %d", result);
	return result;
    }

  override void onSlotCalled(QVariant slotName, QVariant[] arguments)
  {
    switch(slotName.toString())
      {
      case "addContact":
	assert(arguments.length == 3);
	addContact(arguments[1].toString(),
		   arguments[2].toString());
	break;
      case "getContact":
	arguments[0].setValue(getContact(arguments[1].toInt()));
	break;
      case "getCount":
	arguments[0].setValue(getCount());
	break;
      default:
	break;
      }
  }
  
    private Contact[] contacts;
}
