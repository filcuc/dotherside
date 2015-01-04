## This example replicates the functionality of Examples/Simple but uses
## the helper macro, QtObject, from NimQmlMacros, to remove some of the boiler plate. 
## Please note we are using templates where ordinarily we would like to use procedures
## due to bug: https://github.com/Araq/Nim/issues/1821

import NimQml, NimQmlMacros

QtObject:
  type MyQObject = ref object of QObject
    m_name: string

  template newMyQObject(initial: string): MyQObject =
    var result = MyQObject(m_name: initial)
    result.create
    result
  
  method getName(myQObject: MyQObject): string {.slot.} =
    echo "nameChanged"
    result = myQObject.m_name

  method nameChanged(myQObject: MyQObject) {.signal.}
  
  method setName(myQObject: MyQObject, name: string) {.slot.} =
    echo "setName"
    if myQObject.m_name != name:
      myQObject.m_name = name
      myQObject.nameChanged()
  
  QtProperty name of string:
    read = getName
    write = setName
    notify = nameChanged

proc mainProc() =
  var app: QApplication
  app.create()
  defer: app.delete()
   
  var myQObject = newMyQObject("InitialName")
  defer: myQObject.delete() 

  var engine: QQmlApplicationEngine
  engine.create()
  defer: engine.delete()

  var variant: QVariant
  variant.create(myQObject)
  defer: variant.delete()

  var rootContext: QQmlContext = engine.rootContext()
  rootContext.setContextProperty("myQObject", variant)
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

