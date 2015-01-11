import NimQml
import Contact

proc mainProc() =
  var app = newQApplication()
  defer: app.delete()
   
  var contact = newContact()
  defer: contact.delete() 

  var engine = newQQmlApplicationEngine()
  defer: engine.delete()

  var variant = newQVariant(contact)
  defer: variant.delete()

  engine.rootContext.setContextProperty("contact", variant)
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()
  GC_fullcollect()
