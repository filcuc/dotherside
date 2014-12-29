import tables

type 
  QVariant* = distinct pointer
  QQmlApplicationEngine* = distinct pointer
  QQmlContext* = distinct pointer
  QApplication* = distinct pointer
  QObject* {.inheritable.} = ref object of RootObj
    name*: string
    data*: pointer
    slots*: Table[string, cint]
    signals*: Table[string, cint]
    properties*: Table[string, cint]
  QQuickView* = distinct pointer