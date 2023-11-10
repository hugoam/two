#ifndef USE_STL
#ifdef TWO_MODULES
module two.gltf;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <gltf/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_GLTF_EXPORT vector<int>;
	template class TWO_GLTF_EXPORT vector<double>;
	template class TWO_GLTF_EXPORT vector<uchar>;
	template class TWO_GLTF_EXPORT vector<vector<uchar>>;
	template class TWO_GLTF_EXPORT vector<glTFAnimationSampler>;
	template class TWO_GLTF_EXPORT vector<glTFAnimationChannel>;
	template class TWO_GLTF_EXPORT vector<glTFMorphTarget>;
	template class TWO_GLTF_EXPORT vector<glTFPrimitive>;
	template class TWO_GLTF_EXPORT vector<glTFBuffer>;
	template class TWO_GLTF_EXPORT vector<glTFBufferView>;
	template class TWO_GLTF_EXPORT vector<glTFAccessor>;
	template class TWO_GLTF_EXPORT vector<glTFImage>;
	template class TWO_GLTF_EXPORT vector<glTFTexture>;
	template class TWO_GLTF_EXPORT vector<glTFMaterial>;
	template class TWO_GLTF_EXPORT vector<glTFMesh>;
	template class TWO_GLTF_EXPORT vector<glTFNode>;
	template class TWO_GLTF_EXPORT vector<glTFSkin>;
	template class TWO_GLTF_EXPORT vector<glTFAnimation>;
	template class TWO_GLTF_EXPORT vector<glTFCamera>;
	template class TWO_GLTF_EXPORT vector<glTFSampler>;
	template class TWO_GLTF_EXPORT vector<glTFScene>;
	template class TWO_GLTF_EXPORT unordered_map<string, int>;
	template class TWO_GLTF_EXPORT unordered_map<int, int>;
}
#endif
