type
  RawQVariantArray {.unchecked.} = array[0..0, RawQVariant]
  RawQVariantArrayPtr = ptr RawQVariantArray
  RawQVariantSeq = seq[RawQVariant]
  QObjectCallBack = proc(nimobject: ptr QObjectObj, slotName: RawQVariant, numArguments: cint, arguments: RawQVariantArrayPtr) {.cdecl.}
  
proc dos_qobject_create(qobject: var void,
                        nimobject: ptr QObjectObj,
                        qobjectCallback: QObjectCallBack) {.cdecl, dynlib:dOtherSideDll, importc.}

proc dos_qobject_delete(qobject: RawQObject) {.cdecl, dynlib:dOtherSideDll, importc.}

proc dos_qobject_slot_create(qobject: RawQObject,
                             slotName: cstring,
                             argumentsCount: cint,
                             argumentsMetaTypes: ptr cint,
                             slotIndex: var cint) {.cdecl, dynlib:dOtherSideDll, importc.}

proc dos_qobject_signal_create(qobject: RawQObject,
                               signalName: cstring,
                               argumentsCount: cint,
                               argumentsMetaTypes: ptr cint,
                               signalIndex: var cint) {.cdecl, dynlib:dOtherSideDll, importc.}

proc dos_qobject_signal_emit(qobject: RawQObject,
                             signalName: cstring,
                             argumentsCount: cint,
                             arguments: ptr RawQVariant) {.cdecl, dynlib:dOtherSideDll, importc.}

proc dos_qobject_property_create(qobject: pointer,
                                 propertyName: cstring,
                                 propertyType: cint,
                                 readSlot: cstring,
                                 writeSlot: cstring,
                                 notifySignal: cstring) {.cdecl, dynlib:dOtherSideDll, importc.}

proc toVariantSeq(args: RawQVariantArrayPtr, numArgs: cint): seq[QVariant] =
  result = @[]
  for i in 0..numArgs-1:
    result.add(newQVariant(args[i]))

proc toRawVariantSeq(args: openarray[QVariant]): RawQVariantSeq =
  result = @[]
  for variant in args:
    result.add(variant.data)

proc delete(sequence: seq[QVariant]) =
  for variant in sequence:
    variant.delete

proc toCIntSeq(metaTypes: openarray[QMetaType]): seq[cint] =
  result = @[]
  for metaType in metaTypes:
    result.add(cint(metaType))

method onSlotCalled*(nimobject: QObject, slotName: string, args: openarray[QVariant]) =
  ## Called from the NimQml bridge when a slot is called from Qml.
  ## Subclasses can override the given method for handling the slot call
  discard()

proc qobjectCallback(nimObject: ptr QObjectObj, slotName: RawQVariant, numArguments: cint, arguments: RawQVariantArrayPtr) {.cdecl, exportc.} =
  if qobjectRegistry[nimObject]:
    let qobject = cast[QObject](nimObject)
    GC_ref(qobject)
    let slotNameAsQVariant = newQVariant(slotName)
    defer: slotNameAsQVariant.delete
    let argumentsAsQVariant = arguments.toVariantSeq(numArguments)
    defer: argumentsAsQVariant.delete
    # Forward to args to the slot
    qobject.onSlotCalled(slotNameAsQVariant.stringVal, argumentsAsQVariant)
    # Update the slot return value
    dos_qvariant_assign(arguments[0], argumentsAsQVariant[0].data)
    GC_unref(qobject)

proc create(qobject: QObject) =
  ## Create a new QObject
  debugMsg("QObject", "create")
  qobject.deleted = false
  let qobjectPtr = addr(qobject[])
  dos_qobject_create(qobject.data, qobjectPtr, qobjectCallback)
  qobjectRegistry[qobjectPtr] = true
  
proc delete*(qobject: QObject) = 
  ## Delete the given QObject
  if not qobject.deleted:
    debugMsg("QObject", "delete")
    let qobjectPtr = addr(qobject[])
    qobjectRegistry.del qobjectPtr
    dos_qobject_delete(qobject.data)
    qobject.data = nil.RawQObject
    qobject.deleted = true
  
proc newQObject*(): QObject =
  ## Return a new QObject
  new(result, delete)
  result.create()

proc registerSlot*(qobject: QObject,
                   slotName: string, 
                   metaTypes: openarray[QMetaType]) =
  ## Register a slot in the QObject with the given name and signature
  # Copy the metatypes array
  var copy = toCIntSeq(metatypes)
  var index: cint 
  dos_qobject_slot_create(qobject.data, slotName, cint(copy.len), addr(copy[0].cint), index)

proc registerSignal*(qobject: QObject,
                     signalName: string, 
                     metatypes: openarray[QMetaType]) =
  ## Register a signal in the QObject with the given name and signature
  var index: cint 
  if metatypes.len > 0:
    var copy = toCIntSeq(metatypes)
    dos_qobject_signal_create(qobject.data, signalName, copy.len.cint, addr(copy[0].cint), index)
  else:
    dos_qobject_signal_create(qobject.data, signalName, 0, nil, index)

proc registerProperty*(qobject: QObject,
                       propertyName: string, 
                       propertyType: QMetaType, 
                       readSlot: string, 
                       writeSlot: string, 
                       notifySignal: string) =
  ## Register a property in the QObject with the given name and type.
  assert propertyName != nil, "property name cannot be nil"
  # don't convert a nil string, else we get a strange memory address
  let cReadSlot: cstring = if readSlot == nil: cast[cstring](nil) else: readSlot
  let cWriteSlot: cstring = if writeSlot == nil: cast[cstring](nil) else: writeSlot
  let cNotifySignal: cstring = if notifySignal == nil: cast[cstring](nil) else: notifySignal
  dos_qobject_property_create(qobject.data, propertyName, propertyType.cint, cReadSlot, cWriteSlot, cNotifySignal)

proc emit*(qobject: QObject, signalName: string, args: openarray[QVariant] = []) =
  ## Emit the signal with the given name and values
  if args.len > 0: 
    var copy = args.toRawVariantSeq
    dos_qobject_signal_emit(qobject.data, signalName, copy.len.cint, addr(copy[0]))
  else:
    dos_qobject_signal_emit(qobject.data, signalName, 0, nil)
