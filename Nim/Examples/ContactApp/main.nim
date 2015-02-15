import NimQml, ApplicationLogic

proc mainProc() =
  let app = newQApplication()
  defer: app.delete
  let logic = newApplicationLogic(app)
  defer: logic.delete
  let engine = newQQmlApplicationEngine()
  defer: engine.delete
  let logicVariant = newQVariant(logic)
  defer: logicVariant.delete
  engine.rootContext.setContextProperty("logic", logicVariant)
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()
