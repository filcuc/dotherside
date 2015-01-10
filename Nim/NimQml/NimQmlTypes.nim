import tables

type 
  RawQVariant = distinct pointer ## A QVariant
  QVariant* = ref object of RootObj
    data: RawQVariant
    deleted: bool
    
  QQmlApplicationEngine* = distinct pointer ## A QQmlApplicationEngine
  QQmlContext* = distinct pointer ## A QQmlContext
  QApplication* = distinct pointer ## A QApplication

  DynamicQObject = distinct pointer
  QObjectObj = object of RootObj ## A QObject
    data: DynamicQObject
    slots: Table[string, cint]
    signals: Table[string, cint]
    properties: Table[string, cint]
    deleted: bool
  QObject* = ref QObjectObj

  QQuickView* = distinct pointer ## A QQuickView
