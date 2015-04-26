## Contains helper macros for NimQml

import macros
import strutils
import typetraits
import tables

template debug(body: stmt): stmt =
  {.push warning[user]: off.}
  when defined(debug):
    {.pop.}
    body
  else:
    {.pop.}

let nimFromQtVariant {.compileTime.} = {
  "int" : "intVal",
  "string" : "stringVal",
  "bool" : "boolVal",
  "float" : "floatVal",
  "QObject" : "qobjectVal",                                      
}.toTable

let nim2QtMeta {.compileTime.} = {
    "bool": "Bool",
    "int" : "Int",
    "string" : "QString",
    "pointer" : "VoidStar",
    "QObject" : "QObjectStar",                              
    "QVariant": "QVariant",
    "" : "Void", # no return, which is represented by an nnkEmpty node
}.toTable

proc getNodeOf*(tree: NimNode, kind: NimNodeKind): NimNode {.compileTime.} =
  ## recursively looks for a node of kind, ``kind``, in the tree provided as ``tree``
  ## Returns the first node that satisfies this condition 
  for i in 0.. <tree.len:
    var child = tree[i]
    if child.kind == kind:
      return child
    var candidate = getNodeOf(child, kind)
    if not candidate.isNil:
      return candidate

static:
  type Context* = ref object of RootObj
  type NullContext* = ref object of Context  

type NodeModifier*[T] = proc(context: T, a: var NimNode): NimNode

# had to remove type bound on hook due to recent regression with generics
proc hookOnNode*[T](context: T, code: NimNode, hook: NodeModifier, 
    recursive: bool = false): NimNode {.compileTime.} =
  ## Iterates over the tree, ``code``, calling ``hook`` on each ``NimNode``
  ## encountered. If ``recursive`` is true, it will recurse over the tree, otherwise
  ## it will only visit ``code``'s children. ``hook`` should return a replacement for 
  ## the node that was passed in via it's return value. `hook` may return nil to remove
  ## the node from the tree.
  if code.len == 0:
    return code
  var newCode = newNimNode(code.kind)
  for i in 0.. <code.len:
    var child = code[i].copy()
    child = hook(context, child)
    if recursive:
      child = hookOnNode(context,child,hook,true)
    if child != nil:
      newCode.add child
  return newCode
  
proc removeOpenSym*(context: NullContext, 
  a: var NimNode): NimNode {.compileTime.} =
  ## replaces: ``nnkOpenSymChoice`` and ``nnkSym`` nodes with idents 
  ## corresponding to the symbols string representation. 
  if a.kind == nnkOpenSymChoice: 
    return ident($a[0].symbol)
  elif a.kind == nnkSym:
    return ident($a.symbol)  
  return a
  
proc newTemplate*(name = newEmptyNode(); 
    params: openArray[NimNode] = [newEmptyNode()];  
    body: NimNode = newStmtList()): NimNode {.compileTime.} =
  ## shortcut for creating a new template
  ##
  ## The ``params`` array must start with the return type of the template, 
  ## followed by a list of IdentDefs which specify the params.
  result = newNimNode(nnkTemplateDef).add(
    name,
    newEmptyNode(),
    newEmptyNode(),
    newNimNode(nnkFormalParams).add(params), ##params
    newEmptyNode(),  ## pragmas
    newEmptyNode(),
    body)

#FIXME: changed parent, typ from typedesc to expr to workaround Nim issue #1874    
template declareSuperTemplate*(parent: expr, typ: expr): stmt =
  template superType*(ofType: typedesc[typ]): typedesc[parent] =
    parent

proc getTypeName*(a: NimNode): NimNode {.compileTime.} =
  ## returns the node containing the name of an object in a 
  ## given type definition block 
  expectMinLen a, 1
  expectKind a, nnkTypeDef
  var testee = a
  if testee[0].kind == nnkPragmaExpr:
    testee = testee[0]
  if testee[0].kind in {nnkIdent}:
    return testee[0]
  elif testee[0].kind in {nnkPostfix}:
    return testee[0][1]

proc isExported(def: NimNode): bool {.compileTime.} =
  ## given a type definition, ``typedef``, determines whether or
  ## not the type is exported with a '*'
  assert def.kind in {nnkTypeDef, nnkProcDef, nnkMethodDef, nnkTemplateDef},
    "unsupported type: " & $def.kind
  if def[0].kind == nnkPostfix:
    return true

proc exportDef(def: NimNode) {.compileTime.} =
  ## Exports exportable definitions. Currently only supports
  ## templates, methods and procedures and types.
  if def.kind in {nnkProcDef, nnkMethodDef, nnkTemplateDef, nnkTypeDef}:
    if def.isExported:
      return
    def[0] = postfix(def[0], "*")
  else:
    error("node: " & $def.kind & " not supported")

proc unexportDef(def: NimNode) {.compileTime.} =
  ## unexports exportable definitions. Currently only supports
  ## templates, methods and procedures and types.
  if def.kind in {nnkProcDef, nnkMethodDef, nnkTemplateDef, nnkTypeDef}:
    if not def.isExported:
      return
    def[0] = ident unpackPostfix(def[0])[1]
  else:
    error("node: " & $def.kind & " not supported")

proc genSuperTemplate*(typeDecl: NimNode): NimNode {.compileTime.} =
  ## generates a template, with name: superType, that returns the super type
  ## of the object defined in the type defintion, ``typeDecl``. ``typeDecl``
  ## must contain an object inheriting from a base type.
  expectKind typeDecl, nnkTypeDef
  let inheritStmt = typeDecl.getNodeOf(nnkOfInherit)
  let typeName = getTypeName(typeDecl)
  if inheritStmt == nil: error("you must declare a super type for " & $typeName)
  # ident of superType (have to deal with generics)
  let superType = if inheritStmt[0].kind == nnkIdent: inheritStmt[0] 
    else: inheritStmt[0].getNodeOf(nnkIdent)
  let superTemplate = getAst declareSuperTemplate(superType, typeName)
  result = superTemplate[0]
  if typeDecl.isExported():
    result.exportDef()
  else:
    result.unexportDef()

proc getSuperType*(typeDecl: NimNode): NimNode {.compileTime.} =
  ## returns ast containing superType info, may not be an ident if generic
  let inheritStmt = typeDecl.getNodeOf(nnkOfInherit)
  if inheritStmt.isNil: return newEmptyNode()
  return inheritStmt[0]

proc getPragmaName*(child: NimNode): NimNode {.compileTime.} =
  ## name of child in a nnkPragma section
  if child.kind == nnkIdent:
    return child
  # assumes first ident is name of pragma
  let ident = child.getNodeOf(nnkIdent)
  result = ident

proc removePragma*(pragma: NimNode, toRemove: string): NimNode {.compileTime.} =
  ## removes a pragma from pragma definition, `pragma`, with name `toRemove`
  expectKind pragma, nnkPragma
  result = newNimNode(nnkPragma)
  for i in 0.. <pragma.len:
    let child = pragma[i]
    if $child.getPragmaName == toRemove:
      continue
    result.add child 
  if result.len == 0:
    return newEmptyNode() 

proc hasPragma*(node: NimNode, pragmaName: string): bool {.compileTime.} =
  ## Returns ``true`` iff the method, or proc definition: ``node``, has a pragma
  ## ``pragmaName``
  doAssert node.kind in {nnkMethodDef, nnkProcDef}
  result = false
  let pragma = node.pragma
  if pragma.kind == nnkEmpty:
    # denotes no pragma set
    return false
  for child in pragma.children():
    if $child.getPragmaName() == pragmaName:
      return true

proc getArgType*(arg: NimNode): NimNode  {.compileTime.} =
  ## returns the ``NimNode`` representing a parameters type
  if arg[1].kind == nnkIdent: 
    arg[1] 
  else: 
    arg[1].getNodeOf(nnkIdent)

proc getArgName*(arg: NimNode): NimNode  {.compileTime.} =
  ## returns the ``NimNode`` representing a parameters name
  if arg[0].kind == nnkIdent: 
    arg[0] 
  else: 
    arg[0].getNodeOf(nnkIdent)    

proc addSignalBody(signal: NimNode): NimNode {.compileTime.} =
  # e.g: produces: emit(MyQObject, "nameChanged")
  assert signal.kind in {nnkMethodDef, nnkProcDef}
  result = newStmtList()
  # if exported, will use postfix
  let name = if signal.name.kind == nnkIdent: signal.name else: signal.name[1]
  let params = signal.params
  # type signal defined on is the 1st arg
  let self = getArgName(params[1])
  var args = newSeq[NimNode]()
  args.add(self)
  args.add newLit($name)
  if params.len > 2: # more args than just type
    for i in 2.. <params.len:
      args.add getArgName params[i]
  result.add newCall("emit", args)

#FIXME: changed typ from typedesc to expr to workaround Nim issue #1874
# This is declared dirty so that identifers are not bound to symbols. 
# The alternative is to use `removeOpenSym` as we did for `prototypeCreate`.
# We should decide which method is preferable.
template prototypeOnSlotCalled(typ: expr): stmt {.dirty.} =
  method onSlotCalled(myQObject: typ, slotName: string, args: openarray[QVariant]) =
    var super = (typ.superType())(myQObject)
    procCall onSlotCalled(super, slotName, args)

#FIXME: changed parent, typ from typedesc to expr to workaround Nim issue #1874
template prototypeCreate(typ: expr): stmt {.dirty.}=
  proc create*(myQObject: var typ) =
    var super = (typ.superType())(myQObject)
    procCall create(super)

proc doRemoveOpenSym(a: var NimNode): NimNode {.compileTime.} =
  hookOnNode(NullContext(),a, removeOpenSym, true)

proc templateBody*(a: NimNode): NimNode {.compileTime.} =
  expectKind a, nnkTemplateDef
  result = a[6]
  
proc genArgTypeArray(params: NimNode): NimNode {.compileTime.} =
  expectKind params, nnkFormalParams
  result = newNimNode(nnkBracket)
  for i in 0 .. <params.len:
    if i == 1:
      # skip "self" param eg: myQObject: MyQObject
      continue
    let pType = if i != 0: getArgType params[i] else: params[i]
    let pTypeString = if pType.kind == nnkEmpty: "" else: $pType
    # function that maps Qvariant type to nim type
    let qtMeta = nim2QtMeta[pTypeString]
    if qtMeta == nil: error(pTypeString & " not supported yet")
    let metaDot = newDotExpr(ident "QMetaType", ident qtMeta)
    result.add metaDot

proc getIdentDefName*(a: NimNode): NimNode {.compileTime.} =
  ## returns object field name from ident def
  expectKind a, nnkIdentDefs
  if a[0].kind == nnkIdent:
    return a[0]
  elif a[0].kind == nnkPostFix:
    return a[0][1]

proc tryHandleSigSlot(def: NimNode, signals: var seq[NimNode], slots: var seq[NimNode],
    generatedCode: var NimNode): bool {.compileTime.} =
  ## Checks a method/proc definition for signals and slots. On finding a method/proc with
  ## a {.signal.} or {.slot.} pragma, it will strip the pragma, add the definition to the
  ## appropriate seq, append the stripped version to the generated code block and return true
  ## indicating the definition was a signal or a slot. If the method/proc is not a slot
  ## or a slot it will return false.
  expectKind generatedCode, nnkStmtList
  assert (not signals.isNil)
  assert (not slots.isNil)
  assert def.kind in {nnkMethodDef, nnkProcDef}
  result = false
  if def.hasPragma("slot"):
    let pragma = def.pragma()
    def.pragma = pragma.removePragma("slot")
    slots.add def # we need to gensome code later
    generatedCode.add def
    result = true
  elif def.hasPragma("signal"):
    let pragma = def.pragma()
    def.pragma = pragma.removePragma("signal")
    def.body = addSignalBody(def)
    generatedCode.add def
    signals.add def
    result = true

proc genCreateDecl(typ: NimNode): NimNode {.compileTime.} =
  ## generates forward declaration for ``create`` procedure
  expectKind typ, nnkTypeDef
  let typeName = typ.getTypeName()
  result = (getAst prototypeCreate(typeName))[0]
  result.body = newEmptyNode()
  if typ.isExported:
    result.exportDef()
  else:
    result.unexportDef()

proc genCreate(typ: NimNode, signals: seq[NimNode], slots: seq[NimNode],
    properties: seq[NimNode]): NimNode {.compileTime.} =
  expectKind typ, nnkTypeDef
  let typeName = typ.getTypeName()
  result = (getAst prototypeCreate(typeName))[0]
  # the template creates loads of openSyms - replace these with idents
  result = doRemoveOpenSym(result)
  if typ.isExported:
    result.exportDef()
  else:
    result.unexportDef()
  var createBody = result.body
  for slot in slots:
    let params = slot.params
    let regSlotDot = newDotExpr(ident "myQObject", ident "registerSlot")
    let name = ($slot.name).replace("*","")
    let argTypesArray = genArgTypeArray(params)
    let call = newCall(regSlotDot, newLit name, argTypesArray)
    createBody.add call
  for signal in signals:
    let params = signal.params
    let regSigDot = newDotExpr(ident "myQObject", ident "registerSignal")
    let name = ($signal.name).replace("*","")
    let argTypesArray = genArgTypeArray(params)
    let call = newCall(regSigDot, newLit name, argTypesArray)
    createBody.add call
  for property in properties:
    let bracket = property[0]
    expectKind bracket, nnkBracketExpr
    #Command
    #  BracketExpr
    #    Ident !"QtProperty"
    #    Ident !"string"
    #  Ident !"name"
    #  StmtList
    let nimPropType = bracket[1]
    let qtPropMeta = nim2QtMeta[$nimPropType]
    if qtPropMeta == nil: error($nimPropType & " not supported")
    let metaDot = newDotExpr(ident "QMetaType", ident qtPropMeta)
    let propertyName = property[1]
    var read, write, notify: NimNode
    let stmtList = property[2]
    # fields
    #  StmtList
    #   Asgn
    #     Ident !"read"
    #     Ident !"getName
    for asgn in stmtList.children:
      let name = asgn[0]
      case $name
      of "read":
        read = asgn[1]
      of "write":
        write = asgn[1]
      of "notify":
        notify = asgn[1]
      else:
        error("unknown property field: " & $name)
    let regPropDot = newDotExpr(ident "myQObject", ident "registerProperty")
    let readArg = if read == nil: newNilLit() else: newLit($read)
    let writeArg = if write == nil: newNilLit() else: newLit($write)
    let notifyArg = if notify == nil: newNilLit() else: newLit($notify)
    let call = newCall(regPropDot, newLit($propertyName), metaDot, readArg, writeArg, notifyArg)
    createBody.add call

proc genOnSlotCalled(typ: NimNode, slots: seq[NimNode]): NimNode {.compileTime.} =
  expectKind typ, nnkTypeDef
  let typeName = typ.getTypeName()
  result = (getAst prototypeOnSlotCalled(typeName))[0]
  var caseStmt = newNimNode(nnkCaseStmt)
  caseStmt.add ident("slotName")
  for slot in slots:
    var ofBranch = newNimNode(nnkOfBranch)
    # for exported procedures - strip * marker
    let slotName = ($slot.name).replace("*","")
    ofBranch.add newLit slotName
    let params = slot.params
    let hasReturn = not (params[0].kind == nnkEmpty)
    var branchStmts = newStmtList()
    var args = newSeq[NimNode]()
    # first params always the object
    args.add ident "myQObject"
    for i in 2.. <params.len:
      let pType = getArgType params[i]
      let argAccess = newNimNode(nnkBracketExpr)
          .add (ident "args")
          .add newIntLitNode(i-1)
      if $pType == "QVariant":
        args.add argAccess
      else:
        # function that maps QVariant type to nim type
        let mapper = nimFromQtVariant[$pType]
        let dot = newDotExpr(argAccess, ident mapper)
        args.add dot
    var call = newCall(ident slotName, args)
    if hasReturn:
      let retType = params[0]
      let argAccess = newNimNode(nnkBracketExpr)
        .add (ident "args")
        .add newIntLitNode(0)
      if $retType == "QVariant":
      # eg: args[0].assign(getName(myQObject))
        let dot = newDotExpr(argAccess, ident "assign")
        call = newCall(dot, call)
      else:
      # eg: args[0].strVal = getName(myQObject)
        let mapper = nimFromQtVariant[$retType]
        let dot = newDotExpr(argAccess, ident mapper)
        call = newAssignment(dot, call)
    branchStmts.add call
    ofBranch.add branchStmts
    caseStmt.add ofBranch
  # add else: discard
  caseStmt.add newNimNode(nnkElse)
    .add newStmtList().add newNimNode(nnkDiscardStmt).add newNimNode(nnkEmpty)
  result.body.add caseStmt

macro QtObject*(qtDecl: stmt): stmt {.immediate.} =
  ## Generates boiler plate code for registering signals, slots 
  ## and properties. 
  ##
  ## Currently generates:
  ## - create: a method to register signal, slots and properties
  ## - superType: a template that returns the super type of the
  ##   object defined within the macro body
  ## - onSlotCalled: a method to dispatch an on slot call to the
  ##   appropiate method.
  ##
  ## Current limitations:
  ## - only one type can be defined within the body of code sent to the 
  ##   the macro. It is assumed, but not checked, that somewhere in the
  ##   inheritance hierarchy this object derives from ``QObject``.
  ## - generics are not currently supported
  expectKind(qtDecl, nnkStmtList)
  #echo treeRepr qtDecl
  result = newStmtList()
  var slots = newSeq[NimNode]()
  var properties = newSeq[NimNode]()
  var signals = newSeq[NimNode]()
  # assume only one type per section for now
  var typ: NimNode
  for it in qtDecl.children():
    if it.kind == nnkTypeSection:
      let typeDecl = it.findChild(it.kind == nnkTypeDef)
      let superType = typeDecl.getSuperType()
      if superType.kind == nnkEmpty:
        # allow simple types and type aliases
        result.add it
      else:
        # may come in useful if we want to check objects inherit from QObject
        #let superName = if superType.kind == nnkIdent: superType 
        #  else: superType.getNodeOf(nnkIdent)
        if typ != nil:
          error("you may not define more than one type " &
                "within the code block passed to this macro")
        else: # without this else, it fails to compile
          typ = typeDecl
          result.add it
          result.add genSuperTemplate(typeDecl)
          result.add genCreateDecl(typeDecl)
    elif it.kind == nnkMethodDef:
      if tryHandleSigSlot(it, signals, slots, result): continue
      result.add it
    elif it.kind == nnkProcDef:
      if tryHandleSigSlot(it, signals, slots, result): continue
      result.add it
    elif it.kind == nnkCommand:
      let bracket = it[0]
      if bracket.kind != nnkBracketExpr:
        error("do not know how to handle: \n" & repr(it))
      # BracketExpr
      #   Ident !"QtProperty"
      #   Ident !"string"
      let cmdIdent = bracket[0]
      if cmdIdent == nil or cmdIdent.kind != nnkIdent or
          ($cmdIdent).toLower() != "qtproperty":
        error("do not know how to handle: \n" & repr(it))
      properties.add it
    else:
      # everything else should pass through unchanged
      result.add it
  if typ == nil:
    error("you must declare an object that inherits from QObject")

  result.add genOnSlotCalled(typ, slots)

  result.add genCreate(typ, signals, slots, properties)

  debug:
    echo repr result
