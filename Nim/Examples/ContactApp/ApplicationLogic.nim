import NimQml, NimQmlMacros, Contact, ContactList

QtObject:
  type ApplicationLogic* = ref object of QObject
    contactList: ContactList
    app: QApplication

  proc delete*(self: ApplicationLogic) =
    let qobject = self.QObject
    qobject.delete()

  proc newApplicationLogic*(app: QApplication): ApplicationLogic =
    new(result, delete)
    result.contactList = newContactList()
    result.app = app
    result.create()

  method getContactList(self: ApplicationLogic): QVariant {.slot.} = 
    return newQVariant(self.contactList)

  method onLoadTriggered(self: ApplicationLogic) {.slot.} =
    echo "Load Triggered"
    self.contactList.add("John", "Doo")

  method onSaveTriggered(self: ApplicationLogic) {.slot.} =
    echo "Save Triggered"  
    
  method onExitTriggered(self: ApplicationLogic) {.slot.} =
    self.app.quit()

  QtProperty[QVariant] contactList:
    read = getContactList
    write = ""
    notify = ""
