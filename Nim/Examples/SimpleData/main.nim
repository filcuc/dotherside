import NimQml
import macros
import typeinfo

proc mainProc() =
  var app = newQApplication()
  defer: app.delete()
   
  var engine = newQQmlApplicationEngine()
  defer: engine.delete()

  var qVar1 = newQVariant(10)
  defer: qVar1.delete()

  var qVar2 = newQVariant("Hello World")
  defer: qVar2.delete()

  var qVar3 = newQVariant(false)
  defer: qVar3.delete()

  var qVar4 = newQVariant(3.5.float)
  defer: qVar4.delete()
  
  engine.rootContext.setContextProperty("qVar1", qVar1) 
  engine.rootContext.setContextProperty("qVar2", qVar2)
  engine.rootContext.setContextProperty("qVar3", qVar3)
  engine.rootContext.setContextProperty("qVar4", qVar4)
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()
  GC_fullcollect()

