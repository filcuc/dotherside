import std.string;
import std.stdio;
import std.conv;
import std.traits;
import std.functional;
import std.typecons;
import core.vararg;
import dothersideinterface;
import dobject;

/*
enum Type {
        UnknownType = 0, Bool = 1, Int = 2, UInt = 3, LongLong = 4, ULongLong = 5,
        Double = 6, Long = 32, Short = 33, Char = 34, ULong = 35, UShort = 36,
        UChar = 37, Float = 38,
        VoidStar = 31,
        QChar = 7, QString = 10, QStringList = 11, QByteArray = 12,
        QBitArray = 13, QDate = 14, QTime = 15, QDateTime = 16, QUrl = 17,
        QLocale = 18, QRect = 19, QRectF = 20, QSize = 21, QSizeF = 22,
        QLine = 23, QLineF = 24, QPoint = 25, QPointF = 26, QRegExp = 27,
        QEasingCurve = 29, QUuid = 30, QVariant = 41, QModelIndex = 42,
        QRegularExpression = 44,
        QJsonValue = 45, QJsonObject = 46, QJsonArray = 47, QJsonDocument = 48,
        QObjectStar = 39, SChar = 40,
        Void = 43,
        QVariantMap = 8, QVariantList = 9, QVariantHash = 28,
        QFont = 64, QPixmap = 65, QBrush = 66, QColor = 67, QPalette = 68,
        QIcon = 69, QImage = 70, QPolygon = 71, QRegion = 72, QBitmap = 73,
        QCursor = 74, QKeySequence = 75, QPen = 76, QTextLength = 77, QTextFormat = 78,
        QMatrix = 79, QTransform = 80, QMatrix4x4 = 81, QVector2D = 82,
        QVector3D = 83, QVector4D = 84, QQuaternion = 85, QPolygonF = 86,
        QSizePolicy = 121,
        User = 1024
    };
*/

public int GetMetaType(T)() 
  if (is (T == int) 
    || is (T == bool) 
    || is (T == string) 
    || is (T == void))
{
  if (is (T == bool))
    return 1;
  else if (is (T == int))
    return 2;
  else if (is( T == void))
    return 43;
  else if (is (T == string))
    return 10;
  else
    return 0;
}

class GuiApplication
{ 
  this()
  {
    dos_guiapplication_create();
  }
  
  ~this()
  {
    dos_guiapplication_delete();
  }
  
  void exec()
  {
    dos_guiapplication_exec();
  }
}

class QuickView
{ 
  this()
  {
    dos_quickview_create(data);
  }
  
  ~this()
  {
    dos_quickview_delete(data);
  }
  
  void show()
  {
    dos_quickview_show(data);
  }
  
  QQmlContext rootContext()
  {
    auto context = new QQmlContext();
    dos_quickview_rootContext(data, context.data);
    return context;
  }
  
  string source()
  {
    auto array = new CharArray();
    dos_quickview_source(data, array.dataRef(), array.sizeRef());
    return to!(string)(array.data());
  }
  
  void setSource(string filename)
  {
    immutable(char)* filenameAsCString = filename.toStringz();
    dos_quickview_set_source(data, filenameAsCString);
  }

  private void* data;
}

class QQmlContext
{
  string baseUrl()
  {
    auto array = new CharArray();
    dos_qmlcontext_baseUrl(data, array.dataRef(), array.sizeRef());
    return to!(string)(array.data());
  }
  
  void setContextProperty(string name, QVariant value)
  {
    dos_qmlcontext_setcontextproperty(data, name.ptr, value.data);
  }

  private void* data;
}

class QVariant
{
  this()
  {
    dos_qvariant_create(this.data);
  }
  
  this(int value)
  {
    dos_qvariant_create_int(this.data, value);
  }
  
  this(bool value)
  {
    dos_qvariant_create_bool(this.data, value);
  }
  
  this(string value)
  {
    dos_qvariant_create_string(this.data, value.toStringz());
  }
  
  this(DObject value)
  {
    dos_qvariant_create_qobject(this.data, value.data);
  }

  this(void* data, bool deleteLater = false)
  {
    this.data = data;
    this.deleteLater = deleteLater;
  }

  ~this()
  {
    if (this.deleteLater)
      dos_qvariant_delete(this.data);
  }

  void* rawData()
  {
    return data;
  }

  void setValue(int value)
  {
    dos_qvariant_setInt(this.data, value);
  }

  void setValue(bool value)
  {
    dos_qvariant_setBool(this.data, value);
  }

  void setValue(string value)
  {
    dos_qvariant_setString(this.data, value.toStringz());
  }

  void getValue(ref int value)
  {
    value = toInt();
  }

  void getValue(ref bool value)
  {
    value = toBool();
  }

  void getValue(ref string value)
  {
    value = toString();
  }
  
  bool isNull()
  {
    bool result;
    dos_qvariant_isnull(this.data, result);
    return result;
  }
  
  bool toBool()
  {
    bool result;
    dos_qvariant_toBool(this.data, result);
    return result;
  }
  
  int toInt()
  {
    int result;
    dos_qvariant_toInt(this.data, result);
    return result;
  }
  
  override string toString()
  {
    auto array = new CharArray();
    dos_qvariant_toString(this.data, array.dataRef(), array.sizeRef());
    return to!(string)(array.data());
  }

  private void* data;
  private bool deleteLater = true;
}

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

  private char* _data;
  private int _size;
}