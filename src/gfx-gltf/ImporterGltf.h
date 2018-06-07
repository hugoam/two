#pragma once

#ifndef MUD_MODULES
#include <srlz/Serial.h>
#include <math/Vec.h>
#include <math/VecOps.h>
#include <math/Colour.h>
#endif
#include <gfx-gltf/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <map>
#include <vector>
#endif

// all the declarations here should fit the glTF 2.0 specification
// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0

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
};

export_ struct refl_ glTFBuffer
{
	attr_ mut_ std::string mime_type;
	attr_ mut_ std::string uri;
	attr_ mut_ int byte_length;
};

export_ struct refl_ glTFImage
{
	attr_ mut_ std::string mime_type;
	attr_ mut_ std::string uri;
	attr_ mut_ int buffer_view;
};

export_ struct refl_ glTFBufferView
{
	glTFBufferView() {}
	attr_ mut_ int buffer = 0;
	attr_ mut_ size_t byte_offset = 0;
	attr_ mut_ size_t byte_length = 0;
	attr_ mut_ size_t byte_stride = 0;
	attr_ mut_ int target = 0;
};

export_ struct refl_ glTFSparseIndices
{
	glTFSparseIndices() {}
	attr_ mut_ int buffer_view;
	attr_ mut_ int byte_offset = 0;
	attr_ mut_ glTFComponentType component_type;
};

export_ struct refl_ glTFSparseValues
{
	glTFSparseValues() {}
	attr_ mut_ int buffer_view;
	attr_ mut_ int byte_offset = 0;
};

export_ struct refl_ glTFSparse
{
	glTFSparse() {}
	attr_ mut_ int count = 0;
	attr_ mut_ glTFSparseIndices indices;
	attr_ mut_ glTFSparseValues values;
};

export_ struct refl_ glTFAccessor
{
	glTFAccessor() {}
	glTFAccessor(int buffer_view, int byte_offset, glTFComponentType component_type, bool normalized, int count, glTFType type)
		: buffer_view(buffer_view), byte_offset(byte_offset), component_type(component_type), normalized(normalized), count(count), type(type)
	{}
	attr_ mut_ int buffer_view = -1;
	attr_ mut_ int byte_offset = 0;
	attr_ mut_ glTFComponentType component_type;
	attr_ mut_ bool normalized = false;
	attr_ mut_ int count;
	attr_ mut_ glTFType type;
	// min is an array whose content depends on glTFType
	// max is an array whose content depends on glTFType

	attr_ mut_ glTFSparse sparse;
};

export_ struct refl_ glTFSampler
{
	glTFSampler() {}
	attr_ mut_ int mag_filter;
	attr_ mut_ int min_filter;
	attr_ mut_ int wrap_s = 10497;
	attr_ mut_ int wrap_t = 10497;
	attr_ mut_ std::string name;
};

export_ struct refl_ glTFTexture
{
	glTFTexture() {}
	attr_ mut_ int source;
	attr_ mut_ std::string name;
};

export_ struct refl_ glTFSkin
{
	attr_ mut_ std::string name;
	attr_ mut_ int skeleton = -1;
	attr_ mut_ std::vector<int> joints;
	attr_ mut_ int inverse_bind_matrices;
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
	attr_ mut_ int POSITION = -1;
	attr_ mut_ int NORMAL = -1;
	attr_ mut_ int TANGENT = -1;
	attr_ mut_ int TEXCOORD_0 = -1;
	attr_ mut_ int TEXCOORD_1 = -1;
	attr_ mut_ int COLOR_0 = -1;
	attr_ mut_ int JOINTS_0 = -1;
	attr_ mut_ int WEIGHTS_0 = -1;
};

export_ struct refl_ glTFMorphTarget
{
	attr_ mut_ int POSITION = -1;
	attr_ mut_ int NORMAL = -1;
	attr_ mut_ int TANGENT = -1;
};

export_ struct refl_ glTFPrimitive
{
	attr_ mut_ glTFAttributes attributes;
	attr_ mut_ int indices = -1;
	attr_ mut_ int material = -1;
	attr_ mut_ glTFPrimitiveType mode = glTFPrimitiveType::TRIANGLES;
	attr_ mut_ std::vector<glTFMorphTarget> targets;
};

export_ struct refl_ glTFMesh
{
	attr_ mut_ std::vector<glTFPrimitive> primitives;
	attr_ mut_ std::vector<float> weights;
};

export_ struct refl_ glTFPerspective
{
	attr_ mut_ float yfov;
	attr_ mut_ float zfar;
	attr_ mut_ float znear;
	attr_ mut_ float aspect_ration;
};

export_ struct refl_ glTFOrthographic
{
	attr_ mut_ float xmag;
	attr_ mut_ float ymag;
	attr_ mut_ float zfar;
	attr_ mut_ float znear;
};

export_ struct refl_ glTFCamera
{
	attr_ mut_ std::string type;
	attr_ mut_ glTFOrthographic orthographic;
	attr_ mut_ glTFPerspective perspective;
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
	attr_ mut_ int node;
	attr_ mut_ std::string path;
};

export_ struct refl_ glTFAnimationChannel
{
	attr_ mut_ int sampler;
	attr_ mut_ glTFAnimationTarget target;
};

export_ struct refl_ glTFAnimationSampler
{
	attr_ mut_ glTFInterpolation interpolation;
	attr_ mut_ int input;
	attr_ mut_ int output;
};

export_ struct refl_ glTFAnimation
{
	attr_ mut_ std::string name;
	attr_ mut_ std::vector<glTFAnimationSampler> samplers;
	attr_ mut_ std::vector<glTFAnimationChannel> channels;
};

export_ struct refl_ glTFTextureInfo
{
	glTFTextureInfo() {}
	attr_ mut_ int index = -1;
	attr_ mut_ float scale = 1.f;
};

export_ struct refl_ glTFMaterialPBR
{
	glTFMaterialPBR() {}
	attr_ mut_ mud::vec4 base_color_factor = to_vec4(mud::Colour::White);
	attr_ mut_ glTFTextureInfo base_color_texture;
	attr_ mut_ float metallic_factor = 1.f;
	attr_ mut_ float roughness_factor = 1.f;
	attr_ mut_ glTFTextureInfo metallic_roughness_texture;
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
	attr_ mut_ std::string name;
	attr_ mut_ glTFTextureInfo normal_texture;
	attr_ mut_ glTFTextureInfo occlusion_texture;
	attr_ mut_ mud::vec3 emissive_factor = to_vec3(mud::Colour::Black);
	attr_ mut_ glTFTextureInfo emissive_texture;
	attr_ mut_ bool double_sided = false;
	attr_ mut_ glTFAlphaMode alpha_mode = glTFAlphaMode::OPAQUE;

	attr_ mut_ glTFMaterialPBR pbr_metallic_roughness;
};

export_ struct refl_ glTFNode
{
	glTFNode() {}
	attr_ mut_ std::string name;

	attr_ mut_ int mesh = -1;
	attr_ mut_ int camera = -1;
	attr_ mut_ int skin = -1;

	attr_ mut_ mud::mat4 matrix = {};
	attr_ mut_ mud::vec3 translation = mud::Zero3;
	attr_ mut_ mud::quat rotation = mud::ZeroQuat;
	attr_ mut_ mud::vec3 scale = mud::Unit3;

	attr_ mut_ std::vector<int> children;

	int parent = -1;
	bool is_joint = false;
};

export_ struct refl_ glTFScene
{
	attr_ mut_ std::string name;
	attr_ mut_ std::vector<int> nodes;
};

export_ struct refl_ glTF
{
	attr_ mut_ std::vector<glTFBuffer> m_buffers;

	attr_ mut_ std::vector<glTFBufferView> m_buffer_views;
	attr_ mut_ std::vector<glTFAccessor> m_accessors;

	attr_ mut_ std::vector<glTFImage> m_images;
	attr_ mut_ std::vector<glTFTexture> m_textures;
	attr_ mut_ std::vector<glTFMaterial> m_materials;
	attr_ mut_ std::vector<glTFMesh> m_meshes;
	attr_ mut_ std::vector<glTFNode> m_nodes;
	attr_ mut_ std::vector<glTFSkin> m_skins;
	attr_ mut_ std::vector<glTFAnimation> m_animations;
	attr_ mut_ std::vector<glTFCamera> m_cameras;
	attr_ mut_ std::vector<glTFScene> m_scenes;

	std::vector<std::vector<uint8_t>> m_binary_buffers;
};

namespace mud
{
	using string = std::string;

	export_ class MUD_GFX_GLTF_EXPORT ImporterGltf
	{
	public:
		ImporterGltf(GfxSystem& gfx_system);

		GfxSystem& m_gfx_system;

		void import_model(Model& model, const string& path, const ModelConfig& config);
	};
}
