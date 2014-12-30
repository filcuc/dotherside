import dothersideinterface;
import std.string;

class CharArray
{  
  this()
  {
    _size = 0;
    dos_chararray_create(_data, _size);
  }
  
  this(int size)
  {
    _size = size;
    dos_chararray_create(_data, _size);
  }
  
  this(char* data, int size)
  {
    _data = data;
    _size = size;
  }
  
  ~this()
  {
    dos_chararray_delete(_data);
  }
  
  char* data()
  {
    return _data;
  }
  
  int size()
  {
    return _size;
  }
  
  ref char* dataRef()
  {
    return _data;
  }
  
  ref int sizeRef()
  {
    return _size;
  }

  override string toString()
  {
    return fromStringz(_data).dup;
  }

  private char* _data;
  private int _size;
}
