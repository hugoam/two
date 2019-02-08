#ifndef USE_STL
#ifdef MUD_MODULES
module mud.gltf;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <gltf/Api.h>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_GLTF_EXPORT vector<int>;
	template class MUD_GLTF_EXPORT vector<double>;
	template class MUD_GLTF_EXPORT vector<uchar>;
	template class MUD_GLTF_EXPORT vector<vector<uchar>>;
	template class MUD_GLTF_EXPORT vector<glTFAnimationSampler>;
	template class MUD_GLTF_EXPORT vector<glTFAnimationChannel>;
	template class MUD_GLTF_EXPORT vector<glTFMorphTarget>;
	template class MUD_GLTF_EXPORT vector<glTFPrimitive>;
	template class MUD_GLTF_EXPORT vector<glTFBuffer>;
	template class MUD_GLTF_EXPORT vector<glTFBufferView>;
	template class MUD_GLTF_EXPORT vector<glTFAccessor>;
	template class MUD_GLTF_EXPORT vector<glTFImage>;
	template class MUD_GLTF_EXPORT vector<glTFTexture>;
	template class MUD_GLTF_EXPORT vector<glTFMaterial>;
	template class MUD_GLTF_EXPORT vector<glTFMesh>;
	template class MUD_GLTF_EXPORT vector<glTFNode>;
	template class MUD_GLTF_EXPORT vector<glTFSkin>;
	template class MUD_GLTF_EXPORT vector<glTFAnimation>;
	template class MUD_GLTF_EXPORT vector<glTFCamera>;
	template class MUD_GLTF_EXPORT vector<glTFSampler>;
	template class MUD_GLTF_EXPORT vector<glTFScene>;
	template class MUD_GLTF_EXPORT unordered_map<string, int>;
	template class MUD_GLTF_EXPORT unordered_map<int, int>;
}
#endif
