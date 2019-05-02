#ifndef USE_STL
#ifdef TWO_MODULES
module two.math;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <math/Api.h>
#endif

#include <stb_rect_pack.h>

namespace stl
{
	using namespace two;
	template class TWO_MATH_EXPORT vector<const char*>;
	template class TWO_MATH_EXPORT vector<bool>;
	template class TWO_MATH_EXPORT vector<char>;
	template class TWO_MATH_EXPORT vector<int>;
	template class TWO_MATH_EXPORT vector<uchar>;
	template class TWO_MATH_EXPORT vector<ushort>;
	template class TWO_MATH_EXPORT vector<uint>;
	template class TWO_MATH_EXPORT vector<ulong>;
	template class TWO_MATH_EXPORT vector<long>;
	template class TWO_MATH_EXPORT vector<llong>;
	template class TWO_MATH_EXPORT vector<ullong>;
	template class TWO_MATH_EXPORT vector<float>;
	template class TWO_MATH_EXPORT vector<uvec2>;
	template class TWO_MATH_EXPORT vector<uvec3>;
	template class TWO_MATH_EXPORT vector<ivec2>;
	template class TWO_MATH_EXPORT vector<ivec3>;
	template class TWO_MATH_EXPORT vector<ivec4>;
	template class TWO_MATH_EXPORT vector<vec2>;
	template class TWO_MATH_EXPORT vector<vec3>;
	template class TWO_MATH_EXPORT vector<vec4>;
	template class TWO_MATH_EXPORT vector<quat>;
	template class TWO_MATH_EXPORT vector<mat4>;
	template class TWO_MATH_EXPORT vector<Colour>;
	template class TWO_MATH_EXPORT vector<Image>;
	template class TWO_MATH_EXPORT vector<Sprite>;
	template class TWO_MATH_EXPORT unordered_map<uint64_t, ushort>;
	template class TWO_MATH_EXPORT unordered_map<ushort, ushort>;
	//template class TWO_MATH_EXPORT unordered_map<Type*, Colour>;

	template class TWO_MATH_EXPORT vector<stbrp_node>;
}
#endif
