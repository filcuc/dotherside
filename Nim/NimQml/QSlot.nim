macro slot(s: stmt): stmt = 
  echo "Invoked the slot macro"

  var procedureName = s[0]
  var procedureParameters = newStmtList()
  procedureParameters.add(s[3][0])
  for i in 1..s[3].len-1:
    procedureParameters.add(s[3][i][1])
  
  #############################
  #          Debug            #
  #############################
  #echo "Procedure Name: ", procedureName.toStrLit
  #var temp = "Procedure Parameters: "
  #for i in 0..procedureParameters.len-1:
  #  var paramType = $(procedureParameters[i].toStrLit)
  #  if paramType == "":
  #    paramType = "void"
  #  temp &= paramType 
  #  temp &= ", "
  #echo temp
  #############################

  result = newStmtList()

  var castProcedureName = newIdentNode($s[0].toStrLit() & "CastAdapter")
  var castProcedureParams: seq[PNimrodNode] = @[newEmptyNode(), newIdentDefs(newIdentNode("variant"), newIdentNode("QVariant"))]
  var castProcedureBody = newStmtList()
  
  var varStmtBody = newDotExpr(newIdentNode("variant"), newIdentNode("toInt"))
  var varStmt = newVarStmt(newIdentNode("argumentCast"), newCall(varStmtBody))
  castProcedureBody.add(varStmt)

  var castProcedure = newProc(castProcedureName, castProcedureParams, castProcedureBody, nnkProcDef)
  result.add(castProcedure)

  hint(treeRepr(result))

proc testSlot() {.slot.} =
  discard()

proc testSlotAdapter(variant: QVariant) {.dumpTree.} = 
  var arg = variant.toInt()
  testSlot(arg)

when isMainModule:
