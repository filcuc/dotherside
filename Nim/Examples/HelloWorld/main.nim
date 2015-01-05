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

  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

