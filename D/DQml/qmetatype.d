import qobject;
import qvariant;

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

public enum QMetaType
{
  Unknown = 0,
  Bool = 1,
  Int = 2,
  Void = 43,
  String = 10,
  QObject = 39,
  QVariant = 41
}

public QMetaType GetMetaType(T)() 
  if (is (T == int)
    || is (T == bool)
    || is (T == string)
    || is (T == void)
    || is (T == QObject)
    || is (T == QVariant))
{
  static if (is (T == bool))
    return QMetaType.Bool;
  else if (is (T == int))
    return QMetaType.Int;
  else if (is( T == void))
    return QMetaType.Void;
  else if (is (T == string))
    return QMetaType.String;
  else if (is (T == QObject))
    return QMetaType.QObject;
  else if (is (T == QVariant))
    return QMetaType.QVariant;
  else
    return QMetaType.Unknown;
}
