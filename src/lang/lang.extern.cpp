#ifndef USE_STL
#ifdef MUD_MODULES
module mud.lang;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <lang/Api.h>
#endif

typedef struct WrenHandle WrenHandle;

namespace stl
{
	using namespace mud;
	template class MUD_LANG_EXPORT vector<Pipe*>;
	template class MUD_LANG_EXPORT vector<Valve*>;
	template class MUD_LANG_EXPORT vector<ProcessInput*>;
	template class MUD_LANG_EXPORT vector<ProcessOutput*>;
	template class MUD_LANG_EXPORT vector<Process*>;
	template class MUD_LANG_EXPORT vector<Script*>;
	template class MUD_LANG_EXPORT vector<VisualScript*>;
	template class MUD_LANG_EXPORT vector<TextScript*>;
	template class MUD_LANG_EXPORT vector<StreamBranch>;
	template class MUD_LANG_EXPORT vector<StreamModifier>;
	template class MUD_LANG_EXPORT vector<unique<Valve>>;
	template class MUD_LANG_EXPORT vector<unique<Pipe>>;
	template class MUD_LANG_EXPORT vector<unique<Process>>;
	template class MUD_LANG_EXPORT vector<unique<Call>>;
	template class MUD_LANG_EXPORT unordered_map<int, ScriptError>;
	template class MUD_LANG_EXPORT unordered_map<void*, const TextScript*>;
	template class MUD_LANG_EXPORT unordered_map<string, WrenFunctionDecl>;

	template class MUD_LANG_EXPORT vector<WrenHandle*>;
	template class MUD_LANG_EXPORT unordered_map<void*, WrenHandle*>;
}
#endif
