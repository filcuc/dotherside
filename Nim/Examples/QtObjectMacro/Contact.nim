## Please note we are using templates where ordinarily we would like to use procedures
## due to bug: https://github.com/Araq/Nim/issues/1821
import NimQml, NimQmlMacros

QtObject:
  type Contact* = ref object of QObject
    m_name: string

  template newContact*(): Contact =
    var result = Contact(m_name: "initialName")
    result.create
    result
  
  method getName*(contact: Contact): string {.slot.} =
    result = contact.m_name

  method nameChanged*(contact: Contact) {.signal.}
  
  method setName*(contact: Contact, name: string) {.slot.} =
    if contact.m_name != name:
      contact.m_name = name
      contact.nameChanged()
  
  QtProperty name of string:
    read = getName
    write = setName
    notify = nameChanged
