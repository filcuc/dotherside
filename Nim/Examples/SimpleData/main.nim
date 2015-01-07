import NimQml
import macros
import typeinfo

proc mainProc() =
  let app = newQApplication()
  defer: app.delete()
   
  let engine = newQQmlApplicationEngine()
  defer: engine.delete()

  let qVar1 = newQVariant(10)
  defer: qVar1.delete()

  let qVar2 = newQVariant("Hello World")
  defer: qVar2.delete()

  let qVar3 = newQVariant(false)
  defer: qVar3.delete()
  
  engine.rootContext.setContextProperty("qVar1", qVar1) 
  engine.rootContext.setContextProperty("qVar2", qVar2)
  engine.rootContext.setContextProperty("qVar3", qVar3)
  
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

