import std.stdio;
import std.container;
import std.conv;
import std.typecons;
import std.traits;

public class ISlot
{
  void Execute(void*[]  arguments) {}
}

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
{
  if (is (T == bool))
    return 1;
  else if (is (T == int))
    return 2;
  else if (is (T == uint))
    return 3;
  else if (is (T == double))
    return 6;
  else if (is (T == long))
    return 32;
  else if (is (T == short))
    return 33;
  else if (is (T == float))
    return 38;
  else if (is (T == int))
    return 2;
  else if (is( T == void))
    return 43;
  else
    return 0;
}

public class DSlot(T) : ISlot
{ 
  alias ReturnType!T SlotReturnType;
  alias ParameterTypeTuple!T Arguments;
  
  
  this(T callable)
  {
    _callable = callable;
    
    _parameterMetaTypes[0] = GetMetaType!SlotReturnType();
    foreach (i, arg; Arguments)
      _parameterMetaTypes[i+1] = GetMetaType!arg();
  }
  
  override void Execute(void*[]  arguments)
  {
    Arguments argumentsTuple;
    
    foreach (i, arg; argumentsTuple) {
      argumentsTuple[i] = *cast(Arguments[i]*)arguments[i + 1];
    }
    
    static if (is(SlotReturnType == void))
    {
      opCall(argumentsTuple);
    }
    else
    {
      auto result = new SlotReturnType;
      *result = opCall(argumentsTuple);
      arguments[0] = result;
    }
  }
  
  ReturnType!T opCall(Arguments arguments)
  {
    return _callable(arguments);
  }
  
  int[] GetParameterMetaTypes() { return _parameterMetaTypes; }
  
  T _callable;
  int[] _parameterMetaTypes = new int[Arguments.length + 1];
};

public DSlot!(T) CreateDSlot(T)(T t) if (isCallable!(T))
{
  return new DSlot!(T)(t);
}

unittest
{
  // Initialize the test case
  int a = 10;
  char b = 'a';
  string c = "prova";
  
  void*[] arguments = new void*[4];
  arguments[0] = cast(void*)&a;
  arguments[1] = cast(void*)&a;
  arguments[2] = cast(void*)&b;
  arguments[3] = cast(void*)&c;
  
  // Testing with a function
  auto testFunction = (int a, char b, string c) {
    writeln("The other values are: ", to!string(a), ", ", to!string(b), ", ", c);
  };
 
  auto slot = CreateDSlot(testFunction);
  slot(arguments);
  slot(a,b,c);
  
  // Testing with a delegate
  int outerValue = 20;
  auto testDelegate = (int a, char b, string c) {
    outerValue += outerValue;
    writeln("The other values are: ", to!string(a), ", ", to!string(b), ", ", c, ", ", outerValue);
  };
  
  auto slot2 = CreateDSlot(testDelegate);
  slot2(arguments);
  slot2(a,b,c);
  
  // Testing with a callable
  auto testCallable = new class {
    void opCall(int a, char b, string c) {
      writeln("The other values are: ", to!string(a), ", ", to!string(b), ", ", c);
    }
  };
  
  auto slot3 = CreateDSlot(testCallable);
  slot3(arguments);
  slot3(a,b,c);
}