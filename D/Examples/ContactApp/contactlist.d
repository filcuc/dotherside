import dqml;
import contact;
import std.stdio;
import std.algorithm;

class ContactList : QAbstractListModel
{
    this()
    {
        this.m_contacts = [];
        this.m_roleNames[Roles.FirstName] = "firstName";
        this.m_roleNames[Roles.LastName] = "lastName";
        this.registerSlot("add", [QMetaType.Void, QMetaType.String, QMetaType.String]);
        this.registerSlot("del", [QMetaType.Void, QMetaType.Int]);
    }

    public override int rowCount(QModelIndex parent = null)
    {
        if (parent && parent.isValid())
            return 0;
        return cast(int)(this.m_contacts.length);
    }

    public override QVariant data(QModelIndex index, int role)
    {
        if (index is null)
            return null;
        
        if (!index.isValid())
            return null;
        
        if (index.row() < 0 || index.row() >= rowCount())
            return null;

        auto contact = this.m_contacts[index.row];
        
        switch(role)
        {
        case Roles.FirstName:
            return new QVariant(contact.firstName());
        case Roles.LastName:
            return new QVariant(contact.lastName());
        default:
            return null;
        }
    }

    public override string[int] roleNames()
    {
        return this.m_roleNames;
    }

    public void add(string firstName, string lastName)
    {
        auto index = new QModelIndex();
        auto pos = rowCount();
        writefln("Adding %s %s in pos %d", firstName, lastName, pos);
        beginInsertRows(index, pos, pos);
        this.m_contacts ~= new Contact(firstName, lastName);
        endInsertRows();
    }

    public void del(int pos)
    {
        if (pos < 0 || pos >= rowCount())
            return;
        auto index = new QModelIndex();
        writefln("Removing at pos %d", pos);
        beginRemoveRows(index, pos, pos);
        this.m_contacts = remove(this.m_contacts, pos);
        endRemoveRows();
    }

    protected override void onSlotCalled(QVariant slotName, QVariant[] arguments)
    {
        switch (slotName.toString())
        {
        case "add":
            add(arguments[1].toString(), arguments[2].toString());
            break;
        case "del":
            del(arguments[1].toInt());
            break;
        default:
            break;
        }
    }

    private Contact[] m_contacts;
    private string[int] m_roleNames;
    private enum Roles : int { FirstName = 0, LastName};
}
