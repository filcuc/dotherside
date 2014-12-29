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
  defer: app.delete()
   
  var myQObject = MyQObject()
  myQObject.create()
  defer: myQObject.delete() 
  myQObject.m_name = "InitialName"
  myQObject.registerSlot("getName", [QMetaType.QString])
  myQObject.registerSlot("setName", [QMetaType.Void, QMetaType.QString])
  myQObject.registerSignal("nameChanged", [QMetaType.Void])
  myQObject.registerProperty("name", QMetaType.QString, "getName", "setName", "nameChanged")

  var engine: QQmlApplicationEngine
  engine.create()
  defer: engine.delete()

  var variant: QVariant
  variant.create(myQObject)
  defer: variant.delete()

  var rootContext: QQmlContext = engine.rootContext()
  rootContext.setContextProperty("myQObject", variant)
  engine.load("main.qml")
  app.exec()

when isMainModule:
  mainProc()

