import NimQml
import macros
import typeinfo

type MyQObject = ref object of QObject 
  m_name: string

method name(myQObject: MyQObject): string =
  result = myQObject.m_name

method `name=`(myQObject: MyQObject, name: string) =
  if myQObject.m_name != name:
    myQObject.m_name = name
    myQObject.emit("nameChanged")

method onSlotCalled(myQObject: MyQObject, slotName: string, args: openarray[QVariant]) = 
  case slotName:
    of "name":
      args[0].stringVal = myQObject.m_name
    of "`name=`":
      myQObject.m_name = args[1].stringVal
      myQObject.emit("nameChanged")
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
  myQObject.registerSlot("name", [QMetaType.QString])
  myQObject.registerSlot("`name=`", [QMetaType.Void, QMetaType.QString])
  myQObject.registerSignal("nameChanged", [QMetaType.Void])
  myQObject.registerProperty("name", QMetaType.QString, "name", "`name=`", "nameChanged")

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

