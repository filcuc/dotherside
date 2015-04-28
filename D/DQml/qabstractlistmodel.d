import dothersideinterface;
import qobject;

class QAbstractListModel : QObject
{
    this()
    {
        super(true);
        dos_qabstractlistmodel_create(this.data,
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
        dos_qabstractlistmodel_delete(data);
    }

    protected extern (C) static void rowCountCallback(void* modelPtr,
                                                      void* indexPtr,
                                                      ref int result)
    {}

    protected extern (C) static void columnCountCallback(void* modelPtr,
                                                         void* indexPtr,
                                                         ref int result)
    {}

    protected extern (C) static void dataCallback(void* modelPtr,
                                                  void* indexPtr,
                                                  int role,
                                                  void* result)
    {}

    protected extern (C) static void setDataCallback(void* modelPtr,
                                                     void* indexPtr,
                                                     void* valuePtr,
                                                     int role,
                                                     ref bool result)
    {}

    protected extern (C) static void roleNamesCallback(void* modelPtr,
                                                       void* result)
    {}
    
    protected extern (C) static void flagsCallback(void* modelPtr,
                                                   void* index,
                                                   ref int result)
    {}

    protected extern (C) static void headerDataCallback(void* modelPtr,
                                                   int section,
                                                   int orientation,
                                                   int role,
                                                   void* result)
    {}
}
