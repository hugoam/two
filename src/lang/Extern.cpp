#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <lang/Extern.h>
#endif

using namespace mud;
namespace tinystl
{
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
