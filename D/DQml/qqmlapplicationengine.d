import dothersideinterface;
import std.string;

class QQmlApplicationEngine
{
  this()
  {
    dos_qqmlapplicationengine_create(data);
  }
  
  ~this()
  {
    dos_qqmlapplicationengine_delete(data);
  }
  
  void load(string filename)
  {
    immutable(char)* filenameAsCString = filename.toStringz();
    dos_qqmlapplicationengine_load(data, filenameAsCString);
  }
  
  private void* data;
}
