## Please note we are using templates where ordinarily we would like to use procedures
## due to bug: https://github.com/Araq/Nim/issues/1821
import NimQml

type Contact = ref object of QObject 
  m_name: string
  
template newContact*(): Contact = 
  var result = Contact(m_name: "initialName")
  result.create()
  result.m_name = "InitialName"
  result.registerSlot("getName", [QMetaType.QString])
  result.registerSlot("setName", [QMetaType.Void, QMetaType.QString])
  result.registerSignal("nameChanged", [QMetaType.Void])
  result.registerProperty("name", QMetaType.QString, "getName", "setName", "nameChanged")
  result

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