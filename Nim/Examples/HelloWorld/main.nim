import NimQml
import macros
import typeinfo

proc mainProc() =
  let app = newQApplication()
  defer: app.delete()
   
  let engine = newQQmlApplicationEngine()
  defer: engine.delete()

  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

