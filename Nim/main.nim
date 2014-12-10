import NimQml
import macros
import typeinfo

type MyQObject = ref object of QObject

method myVoidSlot(myQObject: MyQObject) = 
  echo "MyQObject: myVoidSlot called"
  myQObject.emit("intValueChanged", [])

method myIntSlot(myQObject: MyQObject, value: int) =
  echo "MyQObject: myIntSlot called with arg ", $value

method myIntSlot2(myQObject: MyQObject, value: int): int =
  echo "MyQObject: myIntSlot called with arg ", $value
  return -10

method onSlotCalled(myQObject: MyQObject, slotName: string, args: openarray[QVariant]) = 
  case slotName:
    of "myVoidSlot": 
      myQObject.myVoidSlot()
    of "myIntSlot": 
      myQObject.myIntSlot(args[1].intVal)
    of "myIntSlot2": 
      args[0].intVal = myQObject.myIntSlot2(args[1].intVal)
    else:
      discard()

proc mainProc() =
  var app: QApplication
  app.create()
  finally: app.delete()
   
  var myQObject = MyQObject()
  myQObject.create()
  finally: myQObject.delete() 
  myQObject.registerSlot("myVoidSlot", [QMetaType.Void])
  myQObject.registerSlot("myIntSlot", [QMetaType.Void, QMetaType.Int])
  myQObject.registerSlot("myIntSlot2", [QMetaType.Int, QMetaType.Int])
  myQObject.registerSignal("intValueChanged", [QMetaType.Void])

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

