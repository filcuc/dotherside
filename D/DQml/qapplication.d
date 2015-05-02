import dothersideinterface;

class QApplication
{ 
    this()
    {
        dos_qapplication_create();
    }
  
    ~this()
    {
        dos_qapplication_delete();
    }
  
    void exec()
    {
        dos_qapplication_exec();
    }

    void quit()
    {
        dos_qapplication_quit();
    }
}
