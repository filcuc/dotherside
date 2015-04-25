import dqml;
import std.format;
import std.stdio;

class Contact : QObject
{
    this(string firstName, string lastName)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        
        registerSlot("getFirstName", [QMetaType.String]);
        registerSlot("setFirstName", [QMetaType.Void, QMetaType.String]);
        registerSignal("firstNameChanged", [QMetaType.String]);
        registerProperty("firstName", QMetaType.String, "getFirstName", "setFirstName", "firstNameChanged");
        
        registerSlot("getLastName", [QMetaType.String]);
        registerSlot("setLastName", [QMetaType.Void, QMetaType.String]);
        registerSignal("lastNameChanged", [QMetaType.String]);
        registerProperty("lastName", QMetaType.String, "getLastName", "setLastName", "lastNameChanged");
    }
    
    public string getFirstName() 
    { 
        return this.firstName; 
    }
    
    public void setFirstName(string firstName)
    {
        if (this.firstName != firstName)
        {
            this.firstName = firstName;
            emit("firstNameChanged", firstName);
        }
    }
    
    public string getLastName() 
    {
      writefln("Returning %s", this.lastName);
        return this.lastName; 
    }
    
    public void setLastName(string lastName)
    {
        if (this.lastName != lastName)
        {
            this.lastName = lastName;
	    emit("lastNameChanged", lastName);
        }
    }

  protected override void onSlotCalled(QVariant slotName, QVariant[] arguments)
  {
    switch(slotName.toString())
      {
      case "getFirstName":
	arguments[0].setValue(getFirstName());
	break;
      case "setFirstName":
	setFirstName(arguments[1].toString());
	break;
      case "getLastName":
	arguments[0].setValue(getLastName());
	break;
      case "setLastName":
	setLastName(arguments[1].toString());
	break;
      default:
	break;
      }
  }
    
    private string firstName;
    private string lastName;
}
