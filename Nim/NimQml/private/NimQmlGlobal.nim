when defined(windows):
  const dOtherSideDll* = "libDOtherSide.dll"
elif defined(macosx):
  const dOtherSideDll* = "libDOtherSide.dylib"
else:
  const dOtherSideDll* = "libDOtherSide.so"

template debugMsg(message: string) = 
  when defined(debug):
    echo "NimQml: ", message
  
template debugMsg(typeName: string, procName: string) =
  when defined(debug):
    var message = typeName
    message &= ": "
    message &= procName
    debugMsg(message)

template debugMsg(typeName: string, procName: string, userMessage: string) = 
  when defined(debug):
    var message = typeName
    message &= ": "
    message &= procName
    message &= " "
    message &= userMessage
    debugMsg(message)

var qobjectRegistry = initTable[ptr QObjectObj, bool]()
