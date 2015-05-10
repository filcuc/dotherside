import dqml;
import contactlist;
import std.stdio;

@QtProperty(QObject.stringof, "contactList", "contactList", null, null)
class ApplicationLogic : QObject
{
    mixin InjectQObjectMacro;
    mixin(Q_OBJECT!(ApplicationLogic));
    
    this(QApplication app)
    {
        this.m_app = app;
        this.m_contactList = new ContactList();
    }


    @QtSlot()
    public QObject contactList()
    {
        return this.m_contactList;
    }

    @QtSlot()
    public void onLoadTriggered()
    {
        writefln("Load Triggered");
    }

    @QtSlot()
    public void onSaveTriggered()
    {
        writefln("Save Triggered");
    }

    @QtSlot()
    public void onExitTriggered()
    {
        this.m_app.quit();
    }

    private QApplication m_app;
    private ContactList m_contactList;
}
