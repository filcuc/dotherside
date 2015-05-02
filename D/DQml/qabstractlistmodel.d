import dothersideinterface;
import qobject;
import qmodelindex;
import qvariant;
import std.string;

class QAbstractListModel : QObject
{
    this()
    {
        super(true);
        dos_qabstractlistmodel_create(this.vptr,
                                      cast(void*)this,
                                      &staticSlotCallback,
                                      &rowCountCallback,
                                      &columnCountCallback,
                                      &dataCallback,
                                      &setDataCallback,
                                      &roleNamesCallback,
                                      &flagsCallback,
                                      &headerDataCallback);
    }

    ~this()
    {
        dos_qabstractlistmodel_delete(this.vptr);
    }

    public int rowCount(QModelIndex parentIndex)
    {
        return 0;
    }

    public int columnCount(QModelIndex parentIndex)
    {
        return 1;
    }

    public QVariant data(QModelIndex index, int role)
    {
        return null;
    }

    public bool setData(QModelIndex index, QVariant value, int role)
    {
        return false;
    }

    public string[int] roleNames()
    {
        return null;
    }

    public int flags(QModelIndex index)
    {
        return 0;
    }

    public QVariant headerData(int section, int orienation, int role)
    {
        return null;
    }

    protected final void beginInsertRows(QModelIndex parent, int first, int last)
    {
        dos_qabstractlistmodel_beginInsertRows(this.vptr,
                                               parent.voidPointer(),
                                               first,
                                               last);
    }

    protected final void endInsertRows()
    {
        dos_qabstractlistmodel_endInsertRows(this.vptr);
    }

    protected final void beginRemoveRows(QModelIndex parent, int first, int last)
    {
        dos_qabstractlistmodel_beginRemoveRows(this.vptr,
                                               parent.voidPointer(),
                                               first,
                                               last);
    }

    protected final void endRemoveRows()
    {
        dos_qabstractlistmodel_endRemoveRows(this.vptr);
    }

    protected final void beginResetModel()
    {
        dos_qabstractlistmodel_beginResetModel(this.vptr);
    }

    protected final void endResetModel()
    {
        dos_qabstractlistmodel_endResetModel(this.vptr);
    }

    protected final void dataChanged(QModelIndex topLeft, QModelIndex bottomRight, int[] roles)
    {
        dos_qabstractlistmodel_dataChanged(this.vptr,
                                           topLeft.voidPointer(),
                                           bottomRight.voidPointer(),
                                           roles.ptr,
                                           cast(int)(roles.length));
    }

    private extern (C) static void rowCountCallback(void* modelPtr,
                                                    void* indexPtr,
                                                    ref int result)
    {
        auto model = cast(QAbstractListModel)(modelPtr);
        auto index = new QModelIndex(indexPtr);
        result = model.rowCount(index);
    }

    private extern (C) static void columnCountCallback(void* modelPtr,
                                                       void* indexPtr,
                                                       ref int result)
    {
        auto model = cast(QAbstractListModel)(modelPtr);
        auto index = new QModelIndex(indexPtr);
        result = model.columnCount(index);
    }

    private extern (C) static void dataCallback(void* modelPtr,
                                                void* indexPtr,
                                                int role,
                                                void* result)
    {
        auto model = cast(QAbstractListModel)(modelPtr);
        auto index = new QModelIndex(indexPtr);
        auto value = model.data(index, role);
        if (value is null)
            return;
        dos_qvariant_assign(result, value.voidPointer());
    }

    private extern (C) static void setDataCallback(void* modelPtr,
                                                   void* indexPtr,
                                                   void* valuePtr,
                                                   int role,
                                                   ref bool result)
    {
        auto model = cast(QAbstractListModel)(modelPtr);
        auto index = new QModelIndex(indexPtr);
        auto value = new QVariant(valuePtr);
        result = model.setData(index, value, role);
    }

    private extern (C) static void roleNamesCallback(void* modelPtr,
                                                     void* result)
    {
        auto model = cast(QAbstractListModel)(modelPtr);
        auto roles = model.roleNames();
        foreach(int key; roles.keys) {
            dos_qhash_int_qbytearray_insert(result, key, roles[key].toStringz());
        }
    }
    
    private extern (C) static void flagsCallback(void* modelPtr,
                                                 void* indexPtr,
                                                 ref int result)
    {
        auto model = cast(QAbstractListModel)(modelPtr);
        auto index = new QModelIndex(indexPtr);
        result = model.flags(index);
    }

    private extern (C) static void headerDataCallback(void* modelPtr,
                                                      int section,
                                                      int orientation,
                                                      int role,
                                                      void* result)
    {
        auto model = cast(QAbstractListModel)(modelPtr);
        QVariant value = model.headerData(section, orientation, role);
        if (value is null)
            return;
        dos_qvariant_assign(result, value.voidPointer());
    }
}
