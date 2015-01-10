## Please note we are using templates where ordinarily we would like to use procedures
## due to bug: https://github.com/Araq/Nim/issues/1821
import NimQml, NimQmlMacros

QtObject:
  type Contact* = ref object of QObject
    m_name: string

  proc delete(self: Contact) = 
    var qobject = self.QObject
    qobject.delete()

  proc newContact*(): Contact =
    new(result, delete)
    result.m_name = "InitialName"
    result.create
  
  method getName*(self: Contact): string {.slot.} =
    result = self.m_name

  method nameChanged*(self: Contact) {.signal.}
  
  method setName*(self: Contact, name: string) {.slot.} =
    if self.m_name != name:
      self.m_name = name
      self.nameChanged()
  
  QtProperty[string] name:
    read = getName
    write = setName
    notify = nameChanged
