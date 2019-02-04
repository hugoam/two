#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <math/Api.h>

#include <stb_rect_pack.h>

#ifdef USE_UVECTOR
#define vector uvector
#elif defined USE_BUFFER
#define vector buffer
#endif

namespace stl
{
	using namespace mud;
	export_ extern template class vector<const char*>;
	export_ extern template class vector<char>;
	export_ extern template class vector<uchar>;
	export_ extern template class vector<ushort>;
	export_ extern template class vector<uint>;
	export_ extern template class vector<ulong>;
	export_ extern template class vector<long>;
	export_ extern template class vector<llong>;
	export_ extern template class vector<ullong>;
	export_ extern template class vector<float>;
	export_ extern template class vector<uvec2>;
	export_ extern template class vector<uvec3>;
	export_ extern template class vector<ivec2>;
	export_ extern template class vector<ivec3>;
	export_ extern template class vector<ivec4>;
	export_ extern template class vector<vec2>;
	export_ extern template class vector<vec3>;
	export_ extern template class vector<vec4>;
	export_ extern template class vector<quat>;
	export_ extern template class vector<mat4>;
	export_ extern template class vector<Colour>;
	export_ extern template class vector<Image>;
	export_ extern template class vector<Sprite>;
	export_ extern template class unordered_map<Type*, Colour>;

	export_ extern template class vector<stbrp_node>;
}
