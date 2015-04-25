import dothersideinterface;
import qvariant;

class QModelIndex
{
    this()
    {
        dos_qmodelindex_create(this.ptr);
    }

    ~this()
    {
        dos_qmodelindex_delete(this.ptr);
        ptr = null;
    }

    public void* internalPtr()
    {
        return this.ptr;
    }

    public int row()
    {
        int result = -1;
        dos_qmodelindex_row(this.ptr, result);
        return result;
    }

    public int column()
    {
        int result = -1;
        dos_qmodelindex_column(this.ptr, result);
        return result;
    }

    public bool isValid()
    {
        bool result = false;
        dos_qmodelindex_isValid(this.ptr, result);
        return result;
    }

    public QVariant data(int role)
    {
        auto result = new QVariant();
        dos_qmodelindex_data(this.ptr, role, result.rawData());
        return result;
    }

    public QModelIndex parent()
    {
        auto result = new QModelIndex();
        dos_qmodelindex_parent(this.ptr, result.ptr);
        return result;
    }

    public QModelIndex child(int row, int column)
    {
        auto result = new QModelIndex();
        dos_qmodelindex_child(this.ptr, row, column, result.ptr);
        return result;
    }

    public QModelIndex sibling(int row, int column)
    {
        auto result = new QModelIndex();
        dos_qmodelindex_sibling(this.ptr, row, column, result.ptr);
        return result;
    }

    private void* ptr;
}
