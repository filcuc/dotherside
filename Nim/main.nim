import NimQml

type MyQObject = object of QObject

when isMainModule:
  var app: QApplication
  app.create()
  finally: app.delete()
   
  var myQObject = new(MyQObject)
  myQObject.create()
  finally: myQObject.delete()
  myQObject.registerSlot("myVoidSlot", [QMetaType.Void, QMetaType.Int])

  var engine: QQmlApplicationEngine
  engine.create()
  finally: engine.delete()

  var variant: QVariant
  variant.create(myQObject)
  finally: variant.delete()

  var rootContext: QQmlContext = engine.rootContext()
  rootContext.setContextProperty("myObject", variant)
  engine.load("main.qml")
  app.exec()