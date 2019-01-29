#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <math/Extern.h>
#endif

namespace tinystl
{
	using namespace mud;
	template class MUD_MATH_EXPORT vector<const char*>;
	template class MUD_MATH_EXPORT vector<char>;
	template class MUD_MATH_EXPORT vector<uchar>;
	template class MUD_MATH_EXPORT vector<ushort>;
	template class MUD_MATH_EXPORT vector<uint>;
	template class MUD_MATH_EXPORT vector<ulong>;
	template class MUD_MATH_EXPORT vector<long>;
	template class MUD_MATH_EXPORT vector<llong>;
	template class MUD_MATH_EXPORT vector<ullong>;
	template class MUD_MATH_EXPORT vector<float>;
	template class MUD_MATH_EXPORT vector<uvec2>;
	template class MUD_MATH_EXPORT vector<uvec3>;
	template class MUD_MATH_EXPORT vector<ivec2>;
	template class MUD_MATH_EXPORT vector<ivec3>;
	template class MUD_MATH_EXPORT vector<ivec4>;
	template class MUD_MATH_EXPORT vector<vec2>;
	template class MUD_MATH_EXPORT vector<vec3>;
	template class MUD_MATH_EXPORT vector<vec4>;
	template class MUD_MATH_EXPORT vector<quat>;
	template class MUD_MATH_EXPORT vector<mat4>;
	template class MUD_MATH_EXPORT vector<Colour>;
	template class MUD_MATH_EXPORT vector<Image>;
	template class MUD_MATH_EXPORT vector<Sprite>;
	template class MUD_MATH_EXPORT unordered_map<Type*, Colour>;

	template class MUD_MATH_EXPORT vector<stbrp_node>;
}
