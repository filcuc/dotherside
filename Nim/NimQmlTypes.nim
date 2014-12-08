import tables

type 
  QVariant* = distinct pointer
  QQmlApplicationEngine* = distinct pointer
  QQmlContext* = distinct pointer
  QApplication* = distinct pointer
  QObject* {.inheritable.} = ref object of RootObj
    data*: pointer
    slots*: Table[string, cint]
  QQuickView* = distinct pointer