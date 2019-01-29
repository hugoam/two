#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <lang/Api.h>

typedef struct WrenHandle WrenHandle;
//struct WrenHandle;

using namespace mud;
namespace tinystl
{
	export_ extern template class vector<Pipe*>;
	export_ extern template class vector<Valve*>;
	export_ extern template class vector<ProcessInput*>;
	export_ extern template class vector<ProcessOutput*>;
	export_ extern template class vector<Process*>;
	export_ extern template class vector<Script*>;
	export_ extern template class vector<VisualScript*>;
	export_ extern template class vector<TextScript*>;
	//export_ extern template class vector<WrenHandle*>;
	export_ extern template class vector<StreamBranch>;
	export_ extern template class vector<StreamModifier>;
	export_ extern template class vector<unique<Valve>>;
	export_ extern template class vector<unique<Pipe>>;
	export_ extern template class vector<unique<Process>>;
	export_ extern template class vector<unique<Call>>;
	export_ extern template class unordered_map<int, ScriptError>;
	export_ extern template class unordered_map<void*, TextScript*>;
	export_ extern template class unordered_map<string, WrenFunctionDecl>;

	export_ extern template class vector<WrenHandle*>;
	export_ extern template class unordered_map<void*, WrenHandle*>;
}
