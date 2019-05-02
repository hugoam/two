#ifndef USE_STL
#ifdef TWO_MODULES
module two.tool;
#else
#include <stl/vector.hpp>
#include <tool/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_TOOL_EXPORT vector<Entity>;
	template class TWO_TOOL_EXPORT vector<Transform*>;
	template class TWO_TOOL_EXPORT vector<unique<Gizmo>>;
	template class TWO_TOOL_EXPORT vector<unique<ToolOption>>;
	template class TWO_TOOL_EXPORT vector<unique<Brush>>;
	template class TWO_TOOL_EXPORT vector<unique<EditorAction>>;
}
#endif
