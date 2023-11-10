#pragma once

extern "C"
{
#include <wren.h>

void wrenBegin(WrenVM* vm);

void wrenAssignVariable(WrenVM* vm, const char* module, const char* name,
						int value_slot);
}
