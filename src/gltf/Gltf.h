#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/algorithm.h>
#include <stl/traits.h>
#include <srlz/Serial.h>
#include <math/Vec.h>
#include <math/Vec.hpp>
#include <math/Colour.h>
#endif
#include <gltf/Forward.h>

using mud::vector;
using mud::string;

export_ struct refl_ glTFNodeExtras
{
	bool occluder = false;
	bool collision = false;
};

// all the declarations here should fit the glTF 2.0 specification
// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0

// todo:
// - primitives other than TRIANGLES are not implemented
// - negative scale on a node will result on wrong-facing, the spec says we need to invert face winding
// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#transformations

export_ enum class refl_ glTFComponentType : unsigned int
{
	BYTE = 5120,
	UNSIGNED_BYTE = 5121,
	SHORT = 5122,
	UNSIGNED_SHORT = 5123,
	INT = 5125,
	FLOAT = 5126,
};

export_ enum class refl_ glTFType : unsigned int
{
	SCALAR,
	VEC2,
	VEC3,
	VEC4,
	MAT2,
	MAT3,
	MAT4,
	INVALID,
};

export_ struct refl_ glTFBuffer
{
	attr_ string name;
	attr_ string mime_type;
	attr_ string uri;
	attr_ size_t byte_length;
};

export_ struct refl_ glTFImage
{
	attr_ string name;
	attr_ string mime_type;
	attr_ string uri;
	attr_ int buffer_view;
};

export_ struct refl_ glTFBufferView
{
	glTFBufferView() {}
	attr_ string name;
	attr_ int buffer = 0;
	attr_ size_t byte_offset = 0;
	attr_ size_t byte_length = 0;
	attr_ size_t byte_stride = 0;
	attr_ int target = 0;
};

export_ struct refl_ glTFSparseIndices
{
	glTFSparseIndices() {}
	attr_ int buffer_view;
	attr_ int byte_offset = 0;
	attr_ glTFComponentType component_type;
};

export_ struct refl_ glTFSparseValues
{
	glTFSparseValues() {}
	attr_ int buffer_view;
	attr_ int byte_offset = 0;
};

export_ struct refl_ glTFSparse
{
	glTFSparse() {}
	attr_ int count = 0;
	attr_ glTFSparseIndices indices;
	attr_ glTFSparseValues values;
};

export_ struct refl_ glTFAccessor
{
	glTFAccessor() {}
	glTFAccessor(int buffer_view, int byte_offset, glTFComponentType component_type, bool normalized, int count, glTFType type)
		: buffer_view(buffer_view), byte_offset(byte_offset), component_type(component_type), normalized(normalized), count(count), type(type)
	{}
	attr_ string name;
	attr_ int buffer_view = -1;
	attr_ int byte_offset = 0;
	attr_ glTFComponentType component_type;
	attr_ bool normalized = false;
	attr_ int count;
	attr_ glTFType type = glTFType::INVALID;
	// min is an array whose content depends on glTFType
	// max is an array whose content depends on glTFType

	attr_ glTFSparse sparse;
};

export_ struct refl_ glTFSampler
{
	glTFSampler() {}
	attr_ int mag_filter;
	attr_ int min_filter;
	attr_ int wrap_s = 10497;
	attr_ int wrap_t = 10497;
	attr_ string name;
};

export_ struct refl_ glTFTexture
{
	glTFTexture() {}
	attr_ string name;
	attr_ int sampler = -1;
	attr_ int source = -1;
};

export_ struct refl_ glTFSkin
{
	attr_ string name;
	attr_ int skeleton = -1;
	attr_ vector<int> joints;
	attr_ int inverse_bind_matrices;
};

export_ enum class refl_ glTFPrimitiveType : unsigned int
{
	POINTS = 0,
	LINES = 1,
	LINE_LOOP = 2,
	LINE_STRIP = 3,
	TRIANGLES = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN = 6
};

export_ struct refl_ glTFAttributes
{
	attr_ int POSITION = -1;
	attr_ int NORMAL = -1;
	attr_ int TANGENT = -1;
	attr_ int TEXCOORD_0 = -1;
	attr_ int TEXCOORD_1 = -1;
	attr_ int COLOR_0 = -1;
	attr_ int JOINTS_0 = -1;
	attr_ int WEIGHTS_0 = -1;
};

export_ struct refl_ glTFMorphTarget
{
	attr_ int POSITION = -1;
	attr_ int NORMAL = -1;
	attr_ int TANGENT = -1;
};

export_ struct refl_ glTFPrimitive
{
	attr_ glTFAttributes attributes;
	attr_ int indices = -1;
	attr_ int material = -1;
	attr_ glTFPrimitiveType mode = glTFPrimitiveType::TRIANGLES;
	attr_ vector<glTFMorphTarget> targets;
};

export_ struct refl_ glTFMesh
{
	attr_ string name;
	attr_ vector<glTFPrimitive> primitives;
	attr_ vector<float> weights;
};

export_ struct refl_ glTFPerspective
{
	attr_ float yfov;
	attr_ float zfar;
	attr_ float znear;
	attr_ float aspect_ratio;
};

export_ struct refl_ glTFOrthographic
{
	attr_ float xmag;
	attr_ float ymag;
	attr_ float zfar;
	attr_ float znear;
};

export_ struct refl_ glTFCamera
{
	attr_ string name;
	attr_ string type;
	attr_ glTFOrthographic orthographic;
	attr_ glTFPerspective perspective;
};

export_ enum class refl_ glTFInterpolation : unsigned int
{
	LINEAR,
	STEP,
	CATMULLROMSPLINE,
	CUBIC_SPLINE
};

export_ struct refl_ glTFAnimationTarget
{
	attr_ int node;
	attr_ string path;
};

export_ struct refl_ glTFAnimationChannel
{
	attr_ int sampler;
	attr_ glTFAnimationTarget target;
};

export_ struct refl_ glTFAnimationSampler
{
	attr_ glTFInterpolation interpolation;
	attr_ int input;
	attr_ int output;
};

export_ struct refl_ glTFAnimation
{
	attr_ string name;
	attr_ vector<glTFAnimationSampler> samplers;
	attr_ vector<glTFAnimationChannel> channels;
};

export_ struct refl_ glTFTextureInfo
{
	glTFTextureInfo() {}
	attr_ int index = -1;
	attr_ float scale = 1.f;
};

export_ struct refl_ glTFMaterialPBR
{
	glTFMaterialPBR() {}
	attr_ mud::vec4 base_color_factor = mud::vec4(1.f);
	attr_ glTFTextureInfo base_color_texture;
	attr_ float metallic_factor = 1.f;
	attr_ float roughness_factor = 1.f;
	attr_ glTFTextureInfo metallic_roughness_texture;
};

export_ enum class refl_ glTFAlphaMode : unsigned int
{
	OPAQUE,
	MASK,
	BLEND,
};

export_ struct refl_ glTFMaterial
{
	glTFMaterial() {}
	attr_ string name;
	attr_ glTFTextureInfo normal_texture;
	attr_ glTFTextureInfo occlusion_texture;
	attr_ mud::vec3 emissive_factor = to_vec3(mud::Colour::Black);
	attr_ glTFTextureInfo emissive_texture;
	attr_ bool double_sided = false;
	attr_ glTFAlphaMode alpha_mode = glTFAlphaMode::OPAQUE;

	attr_ glTFMaterialPBR pbr_metallic_roughness;
};

export_ struct refl_ glTFNode
{
	glTFNode() {}
	attr_ string name;

	attr_ int mesh = -1;
	attr_ int camera = -1;
	attr_ int skin = -1;

	attr_ mud::mat4 matrix = {};
	attr_ mud::vec3 translation = mud::Zero3;
	attr_ mud::quat rotation = mud::ZeroQuat;
	attr_ mud::vec3 scale = mud::Unit3;

	attr_ vector<int> children;

	int parent = -1;
	bool is_joint = false;
};

export_ struct refl_ glTFScene
{
	attr_ string name;
	attr_ vector<int> nodes;
};

export_ struct refl_ glTF
{
	glTF(void* user = nullptr) : m_user(user) {}

	attr_ vector<glTFBuffer> m_buffers;

	attr_ vector<glTFBufferView> m_buffer_views;
	attr_ vector<glTFAccessor> m_accessors;

	attr_ vector<glTFImage> m_images;
	attr_ vector<glTFTexture> m_textures;
	attr_ vector<glTFMaterial> m_materials;
	attr_ vector<glTFMesh> m_meshes;
	attr_ vector<glTFNode> m_nodes;
	attr_ vector<glTFSkin> m_skins;
	attr_ vector<glTFAnimation> m_animations;
	attr_ vector<glTFCamera> m_cameras;
	attr_ vector<glTFSampler> m_samplers;
	attr_ vector<glTFScene> m_scenes;

	vector<vector<uint8_t>> m_binary_buffers;

	void* m_user = nullptr;
};

namespace mud
{
	export_ using glTFRepack = void(*)(glTF&, const string&, glTFPrimitive&);

	export_ MUD_GLTF_EXPORT void setup_gltf(Module& gltf);
	export_ MUD_GLTF_EXPORT void unpack_gltf(const string& path, const string& file, glTF& gltf);
	export_ MUD_GLTF_EXPORT void repack_gltf(glTF& gltf, const string& path, const string& file, const glTFRepack& repack);

	export_ MUD_GLTF_EXPORT int encode_accessor(glTF& gltf, int buffer_index, glTFAccessor& a, vector<double>& values, bool for_vertex);
	export_ MUD_GLTF_EXPORT vector<double> decode_accessor(const glTF& gltf, size_t accessor, bool for_vertex);

	export_ MUD_GLTF_EXPORT void setup_nodes(glTF& gltf);

	template <class T>
	vector<T> unpack_accessor(const glTF& gltf, size_t accessor, bool for_vertex)
	{
		vector<double> attribs = decode_accessor(gltf, accessor, for_vertex);
		vector<T> ret;
		vector_cast(attribs, ret);
		return ret;
	}

	template <class T, size_t size>
	vector<T> unpack_accessor(const glTF& gltf, size_t accessor, bool for_vertex)
	{
		vector<double> attribs = decode_accessor(gltf, accessor, for_vertex);
		vector<T> ret(attribs.size() / size);
		using U = remove_pointer<decltype(value_ptr(ret.front()))>;
		transform(attribs.begin(), attribs.end(), value_ptr(ret.front()), [](double v) { return static_cast<U>(v); });
		return ret;
	}

	template <class T>
	int pack_accessor(glTF& gltf, int buffer_index, glTFAccessor& accessor, const vector<T>& values, bool for_vertex)
	{
		vector<double> attribs(values.size());
		transform(values.begin(), values.end(), attribs.begin(), [](int v) { return static_cast<double>(v); });
		return encode_accessor(gltf, buffer_index, accessor, attribs, for_vertex);
	}

	template <class T, size_t size>
	int pack_accessor(glTF& gltf, int buffer_index, glTFAccessor& accessor, const vector<T>& values, bool for_vertex)
	{
		vector<double> attribs(values.size() * size);
		using U = remove_pointer<decltype(value_ptr(values.front()))>;
		transform(value_ptr(values.front()), value_ptr(values.back()) + size, attribs.begin(), [](U v) { return static_cast<double>(v); });
		return encode_accessor(gltf, buffer_index, accessor, attribs, for_vertex);
	}

	template <class T, size_t size>
	int pack_accessor_float(glTF& gltf, int buffer_index, const vector<T>& values, bool for_vertex)
	{
		static_assert(size > 0 && size <= 4, "incorrect size");
		glTFAccessor accessor = { 0, 0, glTFComponentType::FLOAT, false, int(values.size()), glTFType(size - 1) };
		int result = pack_accessor<T, size>(gltf, buffer_index, accessor, values, for_vertex);
		vector<T> debug = unpack_accessor<T, size>(gltf, result, for_vertex);
		return result;
	}
}