## Please note we are using templates where ordinarily we would like to use procedures
## due to bug: https://github.com/Araq/Nim/issues/1821
import NimQml

type Contact = ref object of QObject 
  m_name: string

proc delete*(self: Contact) = 
  var qobject = self.QObject
  qobject.delete()

proc create*(self: Contact) =
  var qobject = self.QObject
  qobject.create()
  self.m_name = "InitialName"
  self.registerSlot("getName", [QMetaType.QString])
  self.registerSlot("setName", [QMetaType.Void, QMetaType.QString])
  self.registerSignal("nameChanged", [QMetaType.Void])
  self.registerProperty("name", QMetaType.QString, "getName", "setName", "nameChanged")
  
proc newContact*(): Contact = 
  new(result, delete)
  result.create()
  
method getName*(self: Contact): string =
  result = self.m_name

method setName*(self: Contact, name: string) =
  if self.m_name != name:
    self.m_name = name
    self.emit("nameChanged")

method onSlotCalled(self: Contact, slotName: string, args: openarray[QVariant]) = 
  case slotName:
    of "getName":
      args[0].stringVal = self.getName()
    of "setName":
      self.setName(args[1].stringVal)
    else:
      discard()
