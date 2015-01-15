## Please note we are using templates where ordinarily we would like to use procedures
## due to bug: https://github.com/Araq/Nim/issues/1821
import NimQml, NimQmlMacros, Contact

QtObject:
  type ContactList* = ref object of QObject
    contacts*: seq[Contact]

  proc delete*(self: ContactList) =
    let qobject = self.QObject
    qobject.delete
    for contact in self.contacts:
      contact.delete
    self.contacts = @[]
    
  proc newContactList*(): ContactList =
    new(result)
    result.contacts = @[]
    result.create()
    
  method getCount(self: ContactList): int {.slot.} = 
    return self.contacts.len

  method countChanged(self: ContactList) {.signal.}
    
  method add*(self: ContactList, name: string, surname: string) {.slot.} =
    let contact = newContact()
    contact.firstName = name
    contact.surname = surname
    self.contacts.add(contact)
    self.countChanged()
    
  method get*(self: ContactList, index: int): QObject {.slot.} =
    if index < 0 or index >= self.contacts.len:
      return nil
    result = self.contacts[index].QObject
    
  method del*(self: ContactList, index: int) {.slot.} =
    self.contacts.del(index)
    self.countChanged()
    
  QtProperty[int] count:
    read = getCount
    notify = countChanged
