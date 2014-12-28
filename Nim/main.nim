import NimQml
import macros
import typeinfo

type MyQObject = ref object of QObject 
  m_name: string

method getName(myQObject: MyQObject): string =
  result = myQObject.m_name

method setName(myQObject: MyQObject, name: string) =
  if myQObject.m_name != name:
    myQObject.m_name = name
    myQObject.emit("nameChanged")

method onSlotCalled(myQObject: MyQObject, slotName: string, args: openarray[QVariant]) = 
  case slotName:
    of "getName":
      args[0].stringVal = myQObject.getName()
    of "setName":
      myQObject.setName(args[1].stringVal)
    else:
      discard()

proc mainProc() =
  var app: QApplication
  app.create()
  finally: app.delete()
   
  var myQObject = MyQObject()
  myQObject.create()
  myQObject.m_name = "InitialName"
  finally: myQObject.delete() 
  myQObject.registerSlot("getName", [QMetaType.QString])
  myQObject.registerSlot("setName", [QMetaType.Void, QMetaType.QString])
  myQObject.registerSignal("nameChanged", [QMetaType.Void])
  myQObject.registerProperty("name", QMetaType.QString, "getName", "setName", "nameChanged")

  var engine: QQmlApplicationEngine
  engine.create()
  finally: engine.delete()

  var variant: QVariant
  variant.create(myQObject)
  finally: variant.delete()

  var rootContext: QQmlContext = engine.rootContext()
  rootContext.setContextProperty("myQObject", variant)
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

