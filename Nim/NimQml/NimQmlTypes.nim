import tables

type 
  RawQVariant = distinct pointer 
  QVariant* = ref object of RootObj ## A QVariant
    data: RawQVariant
    deleted: bool

  RawQQmlApplicationEngine = distinct pointer
  QQmlApplicationEngine* = ref object of RootObj ## A QQmlApplicationEngine
    data: RawQQmlApplicationEngine
    deleted: bool
  
  QApplication* = ref object of RootObj ## A QApplication 
    deleted: bool

  QGuiApplication* = ref object of RootObj ## A QGuiApplication
    deleted: bool  
    
  RawQObject = distinct pointer
  QObjectObj = object of RootObj
    data: RawQObject
    slots: Table[string, cint]
    signals: Table[string, cint]
    properties: Table[string, cint]
    deleted: bool
  QObject* = ref QObjectObj

  RawBaseQObjectObj = distinct pointer
  BaseQObjectObj = object of QObjectObj
  BaseQObject* = ref BaseQObjectObj ## A QObject

  RawQAbstractListModel = distinct pointer
  QAbstractListModelObj = object of QObjectObj
  QAbstractListModel* = ref QAbstractListModelObj ## A QAbstractListModel
  
  RawQQuickView = distinct pointer 
  QQuickView = ref object of RootObj ## A QQuickView
    data: RawQQuickView
    deleted: bool

  QQmlContext* = distinct pointer ## A QQmlContext

  RawQModelIndex = distinct pointer
  QModelIndex* = ref object of RootObj ## A QModelIndex
    data: RawQModelIndex
    deleted: bool

  RawQHashIntByteArray = distinct pointer
  QHashIntByteArrayObj = object of RootObj
    data: RawQHashIntByteArray
    deleted: bool
  QHashIntByteArray* = ref QHashIntByteArrayObj ## A QHash<int,QByteArray>

  QtItemFlag* {.pure.} = enum 
    None = 0.cint, 
    IsSelectable = 1.cint,
    IsEditable = 2.cint,
    IsDragEnabled = 4.cint,
    IsDropEnabled = 8.cint,
    IsUserCheckable = 16.cint,
    IsEnabled = 32.cint,
    IsTristate = 64.cint,
    NeverHasChildren = 128.cint
  
  QtOrientation {.pure.} = enum
    Horizontal = 1.cint,
    Vertical = 2.cint
