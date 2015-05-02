import dqml;
import std.stdio;


class ListModel : QAbstractListModel
{
    this()
    {
        this.names = ["John", "Max", "Paul", "Anna"];
        this.roles[Roles.Name] = "name";
    }

    public override int rowCount(QModelIndex parent = null)
    {
        if (parent && parent.isValid())
            return 0;
        return cast(int)(names.length);
    }

    public override QVariant data(QModelIndex index, int role)
    {
        if (index is null)
            return null;
        
        if (!index.isValid())
            return null;
        
        if (index.row() < 0 || index.row() >= rowCount())
            return null;
        
        switch(role)
        {
        case Roles.Name:
            return new QVariant(names[index.row]);
        default:
            return null;
        }
    }

    public override string[int] roleNames()
    {
        return roles;
    }

    private string[] names;
    private string[int] roles;
    private enum Roles : int { Name = 0 };
}
