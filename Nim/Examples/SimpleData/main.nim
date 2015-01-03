import NimQml
import macros
import typeinfo

proc mainProc() =
  var app: QApplication
  app.create()
  defer: app.delete()
   
  var engine: QQmlApplicationEngine
  engine.create()
  defer: engine.delete()

  var qVar1: QVariant
  qVar1.create()
  defer: qVar1.delete()
  qVar1.intVal = 10

  var qVar2: QVariant
  qVar2.create()
  defer: qVar2.delete()
  qVar2.stringVal = "Hello World"

  var qVar3: QVariant
  qVar3.create()
  defer: qVar3.delete()
  qVar3.boolVal = false
  
  engine.rootContext.setContextProperty("qVar1", qVar1) 
  engine.rootContext.setContextProperty("qVar2", qVar2)
  engine.rootContext.setContextProperty("qVar3", qVar2)
  
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

