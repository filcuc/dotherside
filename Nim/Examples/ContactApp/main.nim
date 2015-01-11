import NimQml, ApplicationLogic

proc mainProc() =
  let app = newQApplication()
  defer: app.delete
  let logic = newApplicationLogic(app)
  defer: logic.delete
  let engine = newQQmlApplicationEngine()
  defer: engine.delete
  engine.rootContext.setContextProperty("logic", newQVariant(logic))
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()
