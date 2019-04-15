#ifndef USE_STL
#ifdef MUD_MODULES
module mud.tool;
#else
#include <stl/vector.hpp>
#include <tool/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_TOOL_EXPORT vector<Entity>;
	template class MUD_TOOL_EXPORT vector<Transform*>;
	template class MUD_TOOL_EXPORT vector<unique<Gizmo>>;
	template class MUD_TOOL_EXPORT vector<unique<ToolOption>>;
	template class MUD_TOOL_EXPORT vector<unique<Brush>>;
	template class MUD_TOOL_EXPORT vector<unique<EditorAction>>;
}
#endif
