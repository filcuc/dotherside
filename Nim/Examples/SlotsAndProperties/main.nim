import NimQml
import Contact

proc mainProc() =
  var app: QApplication
  app.create()
  defer: app.delete()
   
  var contact = newContact()
  defer: contact.delete() 
  
  var engine: QQmlApplicationEngine
  engine.create()
  defer: engine.delete()

  var variant: QVariant
  variant.create(contact)
  defer: variant.delete()

  var rootContext: QQmlContext = engine.rootContext()
  rootContext.setContextProperty("contact", variant)
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

