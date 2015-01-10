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
    
  RawQObject = distinct pointer
  QObjectObj = object of RootObj
    data: RawQObject
    slots: Table[string, cint]
    signals: Table[string, cint]
    properties: Table[string, cint]
    deleted: bool
  QObject* = ref QObjectObj ## A QObject

  RawQQuickView = distinct pointer 
  QQuickView = ref object of RootObj ## A QQuickView
    data: RawQQuickView
    deleted: bool

  QQmlContext* = distinct pointer ## A QQmlContext

