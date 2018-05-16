#pragma once

#include <gfx/Generated/Forward.h>
#include <math/Vec.h>
#include <math/VecOps.h>
#include <math/Colour.h>

#include <map>
#include <vector>

#ifndef MUD_META_GENERATOR
#include <json.hpp>
using nlohmann::json;
#else
struct json;
#endif


// all the declarations here should fit the glTF 2.0 specification
// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0

enum class _refl_ glTFComponentType : unsigned int
{
	BYTE = 5120,
	UNSIGNED_BYTE = 5121,
	SHORT = 5122,
	UNSIGNED_SHORT = 5123,
	INT = 5125,
	FLOAT = 5126,
};

enum class _refl_ glTFType : unsigned int
{
	SCALAR,
	VEC2,
	VEC3,
	VEC4,
	MAT2,
	MAT3,
	MAT4,
};

struct _refl_ glTFBuffer
{
	_attr_ _mut_ std::string mime_type;
	_attr_ _mut_ std::string uri;
	_attr_ _mut_ int byte_length;
};

struct _refl_ glTFImage
{
	_attr_ _mut_ std::string mime_type;
	_attr_ _mut_ std::string uri;
	_attr_ _mut_ int buffer_view;
};

struct _refl_ glTFBufferView
{
	glTFBufferView() {}
	_attr_ _mut_ int buffer = 0;
	_attr_ _mut_ size_t byte_offset = 0;
	_attr_ _mut_ size_t byte_length = 0;
	_attr_ _mut_ size_t byte_stride = 0;
	_attr_ _mut_ int target = 0;
};

struct _refl_ glTFSparseIndices
{
	glTFSparseIndices() {}
	_attr_ _mut_ int buffer_view;
	_attr_ _mut_ int byte_offset = 0;
	_attr_ _mut_ glTFComponentType component_type;
};

struct _refl_ glTFSparseValues
{
	glTFSparseValues() {}
	_attr_ _mut_ int buffer_view;
	_attr_ _mut_ int byte_offset = 0;
};

struct _refl_ glTFSparse
{
	glTFSparse() {}
	_attr_ _mut_ int count = 0;
	_attr_ _mut_ glTFSparseIndices indices;
	_attr_ _mut_ glTFSparseValues values;
};

struct _refl_ glTFAccessor
{
	glTFAccessor() {}
	glTFAccessor(int buffer_view, int byte_offset, glTFComponentType component_type, bool normalized, int count, glTFType type)
		: buffer_view(buffer_view), byte_offset(byte_offset), component_type(component_type), normalized(normalized), count(count), type(type)
	{}
	_attr_ _mut_ int buffer_view = -1;
	_attr_ _mut_ int byte_offset = 0;
	_attr_ _mut_ glTFComponentType component_type;
	_attr_ _mut_ bool normalized = false;
	_attr_ _mut_ int count;
	_attr_ _mut_ glTFType type;
	// min is an array whose content depends on glTFType
	// max is an array whose content depends on glTFType

	_attr_ _mut_ glTFSparse sparse;
};

struct _refl_ glTFSampler
{
	glTFSampler() {}
	_attr_ _mut_ int mag_filter;
	_attr_ _mut_ int min_filter;
	_attr_ _mut_ int wrap_s = 10497;
	_attr_ _mut_ int wrap_t = 10497;
	_attr_ _mut_ std::string name;
};

struct _refl_ glTFTexture
{
	glTFTexture() {}
	_attr_ _mut_ int source;
	_attr_ _mut_ std::string name;
};

struct _refl_ glTFSkin
{
	_attr_ _mut_ std::string name;
	_attr_ _mut_ int skeleton = -1;
	_attr_ _mut_ std::vector<int> joints;
	_attr_ _mut_ int inverse_bind_matrices;
};

enum class _refl_ glTFPrimitiveType : unsigned int
{
	POINTS = 0,
	LINES = 1,
	LINE_LOOP = 2,
	LINE_STRIP = 3,
	TRIANGLES = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN = 6
};

struct _refl_ glTFAttributes
{
	_attr_ _mut_ int POSITION = -1;
	_attr_ _mut_ int NORMAL = -1;
	_attr_ _mut_ int TANGENT = -1;
	_attr_ _mut_ int TEXCOORD_0 = -1;
	_attr_ _mut_ int TEXCOORD_1 = -1;
	_attr_ _mut_ int COLOR_0 = -1;
	_attr_ _mut_ int JOINTS_0 = -1;
	_attr_ _mut_ int WEIGHTS_0 = -1;
};

struct _refl_ glTFMorphTarget
{
	_attr_ _mut_ int POSITION = -1;
	_attr_ _mut_ int NORMAL = -1;
	_attr_ _mut_ int TANGENT = -1;
};

struct _refl_ glTFPrimitive
{
	_attr_ _mut_ glTFAttributes attributes;
	_attr_ _mut_ int indices = -1;
	_attr_ _mut_ int material = -1;
	_attr_ _mut_ glTFPrimitiveType mode = glTFPrimitiveType::TRIANGLES;
	_attr_ _mut_ std::vector<glTFMorphTarget> targets;
};

struct _refl_ glTFMesh
{
	_attr_ _mut_ std::vector<glTFPrimitive> primitives;
	_attr_ _mut_ std::vector<float> weights;
};

struct _refl_ glTFPerspective
{
	_attr_ _mut_ float yfov;
	_attr_ _mut_ float zfar;
	_attr_ _mut_ float znear;
	_attr_ _mut_ float aspect_ration;
};

struct _refl_ glTFOrthographic
{
	_attr_ _mut_ float xmag;
	_attr_ _mut_ float ymag;
	_attr_ _mut_ float zfar;
	_attr_ _mut_ float znear;
};

struct _refl_ glTFCamera
{
	_attr_ _mut_ std::string type;
	_attr_ _mut_ glTFOrthographic orthographic;
	_attr_ _mut_ glTFPerspective perspective;
};

enum class _refl_ glTFInterpolation : unsigned int
{
	LINEAR,
	STEP,
	CATMULLROMSPLINE,
	CUBIC_SPLINE
};

struct _refl_ glTFAnimationTarget
{
	_attr_ _mut_ int node;
	_attr_ _mut_ std::string path;
};

struct _refl_ glTFAnimationChannel
{
	_attr_ _mut_ int sampler;
	_attr_ _mut_ glTFAnimationTarget target;
};

struct _refl_ glTFAnimationSampler
{
	_attr_ _mut_ glTFInterpolation interpolation;
	_attr_ _mut_ int input;
	_attr_ _mut_ int output;
};

struct _refl_ glTFAnimation
{
	_attr_ _mut_ std::string name;
	_attr_ _mut_ std::vector<glTFAnimationSampler> samplers;
	_attr_ _mut_ std::vector<glTFAnimationChannel> channels;
};

struct _refl_ glTFTextureInfo
{
	glTFTextureInfo() {}
	_attr_ _mut_ int index = -1;
	_attr_ _mut_ float scale = 1.f;
};

struct _refl_ glTFMaterialPBR
{
	glTFMaterialPBR() {}
	_attr_ _mut_ mud::vec4 base_color_factor = to_vec4(mud::Colour::White);
	_attr_ _mut_ glTFTextureInfo base_color_texture;
	_attr_ _mut_ float metallic_factor = 1.f;
	_attr_ _mut_ float roughness_factor = 1.f;
	_attr_ _mut_ glTFTextureInfo metallic_roughness_texture;
};

enum class _refl_ glTFAlphaMode : unsigned int
{
	OPAQUE,
	MASK,
	BLEND,
};

struct _refl_ glTFMaterial
{
	glTFMaterial() {}
	_attr_ _mut_ std::string name;
	_attr_ _mut_ glTFTextureInfo normal_texture;
	_attr_ _mut_ glTFTextureInfo occlusion_texture;
	_attr_ _mut_ mud::vec3 emissive_factor = to_vec3(mud::Colour::Black);
	_attr_ _mut_ glTFTextureInfo emissive_texture;
	_attr_ _mut_ bool double_sided = false;
	_attr_ _mut_ glTFAlphaMode alpha_mode = glTFAlphaMode::OPAQUE;

	_attr_ _mut_ glTFMaterialPBR pbr_metallic_roughness;
};

struct _refl_ glTFNode
{
	glTFNode() {}
	_attr_ _mut_ std::string name;

	_attr_ _mut_ int mesh = -1;
	_attr_ _mut_ int camera = -1;
	_attr_ _mut_ int skin = -1;

	_attr_ _mut_ mud::mat4 matrix = {};
	_attr_ _mut_ mud::vec3 translation = mud::Zero3;
	_attr_ _mut_ mud::quat rotation = mud::ZeroQuat;
	_attr_ _mut_ mud::vec3 scale = mud::Unit3;

	_attr_ _mut_ std::vector<int> children;

	int parent = -1;
	bool is_joint = false;
};

struct _refl_ glTFScene
{
	_attr_ _mut_ std::string name;
	_attr_ _mut_ std::vector<int> nodes;
};

struct _refl_ glTF
{
	_attr_ _mut_ std::vector<glTFBuffer> m_buffers;

	_attr_ _mut_ std::vector<glTFBufferView> m_buffer_views;
	_attr_ _mut_ std::vector<glTFAccessor> m_accessors;

	_attr_ _mut_ std::vector<glTFImage> m_images;
	_attr_ _mut_ std::vector<glTFTexture> m_textures;
	_attr_ _mut_ std::vector<glTFMaterial> m_materials;
	_attr_ _mut_ std::vector<glTFMesh> m_meshes;
	_attr_ _mut_ std::vector<glTFNode> m_nodes;
	_attr_ _mut_ std::vector<glTFSkin> m_skins;
	_attr_ _mut_ std::vector<glTFAnimation> m_animations;
	_attr_ _mut_ std::vector<glTFCamera> m_cameras;
	_attr_ _mut_ std::vector<glTFScene> m_scenes;

	std::vector<std::vector<uint8_t>> m_binary_buffers;
};

namespace mud
{
	using string = std::string;

	class _refl_ glTFImport
	{
	public:
		glTFImport(GfxSystem& gfx_system, Model& model, const ModelConfig& model_config)
			: m_gfx_system(gfx_system), m_model(model), m_model_config(model_config)
		{}

		GfxSystem& m_gfx_system;
		Model& m_model;
		const ModelConfig& m_model_config;

		json m_json;
		std::vector<uint8_t> m_glb;

		_attr_ _mut_ glTF m_gltf;

		std::vector<Texture*> m_imported_images;
		std::vector<Material*> m_imported_materials;

		std::map<int, Skeleton*> m_skeletons;
	};

	class ImporterGltf
	{
	public:
		ImporterGltf(GfxSystem& gfx_system);

		GfxSystem& m_gfx_system;

		void import_model(Model& model, const string& path, const string& file, const ModelConfig& config);
	};
}
