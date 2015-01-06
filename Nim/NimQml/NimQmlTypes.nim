import tables

type 
  QVariant* = distinct pointer ## A QVariant
  QQmlApplicationEngine* = distinct pointer ## A QQmlApplicationEngine
  QQmlContext* = distinct pointer ## A QQmlContext
  QApplication* = distinct pointer ## A QApplication
  DynamicQObject* = distinct pointer
    ## internal representation of a QObject, as recognised by DOtherSide
  QObject* {.inheritable.} = ref object of RootObj ## A QObject
    name*: string
    data*: DynamicQObject
    slots*: Table[string, cint]
    signals*: Table[string, cint]
    properties*: Table[string, cint]
  QQuickView* = distinct pointer ## A QQuickView
