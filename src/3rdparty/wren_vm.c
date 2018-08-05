#include <wren_vm.c>

void wrenAssignVariable(WrenVM* vm, const char* module, const char* name, int value_slot)
{
  ASSERT(module != NULL, "Module cannot be NULL.");
  ASSERT(name != NULL, "Variable name cannot be NULL.");  
  validateApiSlot(vm, value_slot);
  
  Value moduleName = wrenStringFormat(vm, "$", module);
  wrenPushRoot(vm, AS_OBJ(moduleName));
  
  ObjModule* moduleObj = getModule(vm, moduleName);
  ASSERT(moduleObj != NULL, "Could not find module.");
  
  wrenPopRoot(vm); // moduleName.

  int variable_symbol = wrenSymbolTableFind(&moduleObj->variableNames,
                                            name, strlen(name));
  ASSERT(variable_symbol != -1, "Could not find variable.");
  
  Value value = vm->apiStack[value_slot];
  if(IS_OBJ(value)) wrenPushRoot(vm, AS_OBJ(value));

  moduleObj->variables.data[variable_symbol] = value;
  	 
  if(IS_OBJ(value)) wrenPopRoot(vm);
}
