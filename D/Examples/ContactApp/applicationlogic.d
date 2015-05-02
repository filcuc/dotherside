import dqml;
import contactlist;
import std.stdio;

class ApplicationLogic : QObject
{
    this(QApplication app)
    {
        this.m_app = app;
        this.m_contactList = new ContactList();
        this.registerSlot("contactList", [QMetaType.QObject]);
        this.registerSlot("onLoadTriggered", [QMetaType.Void]);
        this.registerSlot("onSaveTriggered", [QMetaType.Void]);
        this.registerSlot("onExitTriggered", [QMetaType.Void]);
        this.registerProperty("contactList", QMetaType.QObject, "contactList", null, null);
    }

    public ContactList contactList()
    {
        return this.m_contactList;
    }

    public void onLoadTriggered()
    {
        writefln("Load Triggered");
    }

    public void onSaveTriggered()
    {
        writefln("Save Triggered");
    }

    public void onExitTriggered()
    {
        this.m_app.quit();
    }

    protected override void onSlotCalled(QVariant slotName, QVariant[] arguments)
    {
        switch(slotName.toString())
        {
        case "contactList":
            return arguments[0].setValue(contactList());
        case "onExitTriggered":
            onExitTriggered();
            break;
        case "onSaveTriggered":
            onSaveTriggered();
            break;
        case "onLoadTriggered":
            onLoadTriggered();
            break;
        default:
            break;
        }
    }

    private QApplication m_app;
    private ContactList m_contactList;
}
