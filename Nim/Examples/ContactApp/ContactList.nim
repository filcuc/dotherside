import NimQml, NimQmlMacros, Contact, Tables

QtObject:
  type
    ContactList* = ref object of QAbstractListModel
      contacts*: seq[Contact]
    ContactRoles = enum
      FirstNameRole = 0
      SurnameRole = 1

  converter toCInt(value: ContactRoles): cint = return value.cint
  converter toCInt(value: int): cint = return value.cint
  converter toInt(value: ContactRoles): int = return value.int
  converter toInt(value: cint): int = return value.int
  converter toQVariant(value: string): QVariant = return value.newQVariant 

  proc delete(self: ContactList) =
    let model = self.QAbstractListModel
    model.delete
    for contact in self.contacts:
      contact.delete
    self.contacts = @[]
    
  proc newContactList*(): ContactList =
    new(result, delete)
    result.contacts = @[]
    result.create

  method rowCount(self: ContactList, index: QModelIndex = nil): cint =
    return self.contacts.len
  
  method data(self: ContactList, index: QModelIndex, role: cint): QVariant =
    if not index.isValid:
      return
    if index.row < 0 or index.row >= self.contacts.len:
      return
    if role == FirstNameRole:
      return self.contacts[index.row].firstName
    elif role == SurnameRole:
      return self.contacts[index.row].surname
    else:
      return

  method roleNames(self: ContactList): Table[cint, cstring] =
    result = initTable[cint, cstring]()
    result[FirstNameRole] = "firstName"
    result[SurnameRole] = "surname"
    
  method add*(self: ContactList, name: string, surname: string) {.slot.} =
    let contact = newContact()
    contact.firstName = name
    contact.surname = surname
    self.beginInsertRows(newQModelIndex(), self.contacts.len, self.contacts.len)
    self.contacts.add(contact)
    self.endInsertRows()
    
  method del*(self: ContactList, pos: int) {.slot.} =
    if pos < 0 or pos >= self.contacts.len:
      return 
    self.beginRemoveRows(newQModelIndex(), pos, pos)
    self.contacts.del(pos)    
    self.endRemoveRows
