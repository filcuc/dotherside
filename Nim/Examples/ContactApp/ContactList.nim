import NimQml, NimQmlMacros, Contact, Tables

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

proc create(self: ContactList) =
  var model = self.QAbstractListModel
  model.create
  self.contacts = @[]

proc delete(self: ContactList) =
  let model = self.QAbstractListModel
  model.delete
  for contact in self.contacts:
    contact.delete
  self.contacts = @[]
    
proc newContactList*(): ContactList =
  new(result, delete)
  result.create()

proc isRowValid(self: ContactList, row: cint): bool =
  return row >= 0 and row < self.contacts.len

method rowCount(self: ContactList, index: QModelIndex = nil): cint =
  return self.contacts.len
  
method data(self: ContactList, index: QModelIndex, role: cint): QVariant =
  if not index.isValid:
    return
  if not self.isRowValid(index.row):
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
    
method add*(self: ContactList, name: string, surname: string) =
  let contact = newContact()
  contact.firstName = name
  contact.surname = surname
  self.beginInsertRows(newQModelIndex(), self.contacts.len, self.contacts.len)
  self.contacts.add(contact)
  self.endInsertRows()
    
method get*(self: ContactList, pos: int): QObject =
  if not self.isRowValid(pos):
    return nil
  result = self.contacts[pos].QObject
    
method del*(self: ContactList, pos: int) =
  if not self.isRowValid(pos):
    return 
  self.beginRemoveRows(newQModelIndex(), pos, pos)
  self.contacts.del(pos)    
  self.endRemoveRows
