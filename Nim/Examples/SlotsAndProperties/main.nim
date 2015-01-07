import NimQml
import Contact

proc mainProc() =
  let app = newQApplication()
  defer: app.delete()
   
  let contact = newContact()
  defer: contact.delete() 
  
  let engine = newQQmlApplicationEngine()
  defer: engine.delete()

  let variant = newQVariant(contact)
  defer: variant.delete()

  let rootContext: QQmlContext = engine.rootContext()
  rootContext.setContextProperty("contact", variant)
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

