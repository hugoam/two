#ifndef USE_STL
#ifdef TWO_MODULES
module two.lang;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <lang/Api.h>
#endif

typedef struct WrenHandle WrenHandle;

namespace stl
{
	using namespace two;
	template class TWO_LANG_EXPORT vector<Pipe*>;
	template class TWO_LANG_EXPORT vector<Valve*>;
	template class TWO_LANG_EXPORT vector<ProcessInput*>;
	template class TWO_LANG_EXPORT vector<ProcessOutput*>;
	template class TWO_LANG_EXPORT vector<Process*>;
	template class TWO_LANG_EXPORT vector<Script*>;
	template class TWO_LANG_EXPORT vector<VisualScript*>;
	template class TWO_LANG_EXPORT vector<TextScript*>;
	template class TWO_LANG_EXPORT vector<StreamBranch>;
	template class TWO_LANG_EXPORT vector<StreamModifier>;
	template class TWO_LANG_EXPORT vector<unique<Valve>>;
	template class TWO_LANG_EXPORT vector<unique<Pipe>>;
	template class TWO_LANG_EXPORT vector<unique<Process>>;
	template class TWO_LANG_EXPORT vector<unique<Call>>;
	template class TWO_LANG_EXPORT unordered_map<int, ScriptError>;
	template class TWO_LANG_EXPORT unordered_map<void*, const TextScript*>;
	template class TWO_LANG_EXPORT unordered_map<string, WrenFunctionDecl>;

	template class TWO_LANG_EXPORT vector<WrenHandle*>;
	template class TWO_LANG_EXPORT unordered_map<void*, WrenHandle*>;
}
#endif
