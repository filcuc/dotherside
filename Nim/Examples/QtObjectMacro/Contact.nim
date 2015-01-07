import NimQml, NimQmlMacros

QtObject:
  type Contact* = ref object of QObject
    m_name: string

  proc newContact*(): Contact =
    result = Contact(m_name: "initialName")
    result.create
  
  method getName*(contact: Contact): string {.slot.} =
    result = contact.m_name

  method nameChanged*(contact: Contact) {.signal.}
  
  method setName*(contact: Contact, name: string) {.slot.} =
    if contact.m_name != name:
      contact.m_name = name
      contact.nameChanged()
  
  QtProperty[string] name:
    read = getName
    write = setName
    notify = nameChanged
