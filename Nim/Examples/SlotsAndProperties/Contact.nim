import NimQml

type Contact = ref object of QObject 
  m_name: string
  
proc newContact*(): Contact =
  result = Contact(m_name: "initialName")
  result.create()
  result.m_name = "InitialName"
  result.registerSlot("getName", [QMetaType.QString])
  result.registerSlot("setName", [QMetaType.Void, QMetaType.QString])
  result.registerSignal("nameChanged", [QMetaType.Void])
  result.registerProperty("name", QMetaType.QString, "getName", "setName", "nameChanged")

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
