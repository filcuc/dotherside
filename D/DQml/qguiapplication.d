import dothersideinterface;

class QGuiApplication
{ 
    this()
    {
        dos_qguiapplication_create();
    }
  
    ~this()
    {
        dos_qguiapplication_delete();
    }
  
    void exec()
    {
        dos_qguiapplication_exec();
    }

    void quit()
    {
        dos_qguiapplication_quit();
    }
}
