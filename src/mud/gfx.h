#pragma once

#include <mud/pool.h>
#include <mud/geom.h>
#include <mud/ctx.glfw.h>
#include <mud/jobs.h>
#include <mud/tree.h>
#include <mud/bgfx.h>
#include <mud/ecs.h>
#include <mud/math.h>
#include <mud/ctx.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifndef MUD_MODULES
#endif



#ifndef MUD_GFX_EXPORT
#define MUD_GFX_EXPORT MUD_IMPORT
#endif

namespace mud
{
	enum class AnimationTarget : unsigned int;
    enum class Interpolation : unsigned int;
    enum class TextureHint : unsigned int;
    enum class ShaderType : unsigned int;
    enum ShaderOption : unsigned int;
    enum class TextureSampler : unsigned int;
    enum class PassType : unsigned int;
    enum class BlendMode : unsigned int;
    enum class CullMode : unsigned int;
    enum class DepthDraw : unsigned int;
    enum class DepthTest : unsigned int;
    enum class MaterialFlag : unsigned int;
    enum class TextureChannel : unsigned int;
	enum class Lighting : unsigned int;
    enum class PbrDiffuseMode : unsigned int;
    enum class PbrSpecularMode : unsigned int;
    enum PbrShaderOption : unsigned int;
    enum class ModelFormat : unsigned int;
    enum class EmitterFlow : unsigned int;
    enum class PrefabType : unsigned int;
    enum IsometricAngle : unsigned int;
    enum ShaderOptionResolve : unsigned int;
    enum ShaderOptionFilter : unsigned int;
    enum class LightType : unsigned int;
    enum ShadowFlags : unsigned int;
    enum class ItemShadow : unsigned int;
    enum class MSAA : unsigned int;
    enum class Shading : unsigned int;
    enum class BackgroundMode : unsigned int;
    enum class Month : unsigned int;
    
    template <class T> class AssetStore;
    template <class T> struct MaterialParam;
    
    struct AnimationCursor;
    class AnimationTrack;
    class Animation;
    class Node3;
    struct Bone;
    class Skeleton;
    struct Joint;
    class Skin;
    class Rig;
    struct AnimatedTrack;
    struct AnimationPlay;
    class Animated;
    class GfxContext;
    struct LocatedFile;
    class GfxSystem;
    class Texture;
    struct ShaderDefine;
    struct ShaderBlock;
    struct ProgramBlock;
    struct ProgramBlockArray;
    class Program;
    struct ShaderVersion;
    struct Pass;
    struct RenderFrame;
    struct Render;
    class GfxBlock;
    class DrawBlock;
    class RenderPass;
    struct DrawElement;
	struct DrawCluster;
    class DrawPass;
    class Renderer;
    struct BaseMaterialBlock;
    struct UnshadedMaterialBlock;
    struct FresnelMaterialBlock;
    struct PbrMaterialBlock;
    struct PbrBlock;
    class Material;
    struct ImportConfig;
	class Importer;
    struct ModelItem;
    class Model;
    struct GpuMesh;
    class Mesh;
    struct Particle;
    struct ParticleSort;
    struct ParticleFlow;
    struct ParticleVertex;
    struct Particles;
    class ParticleSystem;
    class BlockParticles;
    class PassParticles;
    struct PrefabNode;
    class Prefab;
    class Camera;
	class Culler;
	class Froxelizer;
    struct DepthParams;
    class PassDepth;
    class BlockDepth;
    class ImmediateDraw;
    class SymbolIndex;
    class BlockResolve;
    class PassEffects;
    class PassPostProcess;
    struct FilterUniform;
    class Filter;
    struct RenderQuad;
    class BlockFilter;
    class BlockCopy;
    class Frustum;
    struct FrustumSlice;
	struct ClusteredFrustum;
    class Light;
    class Gnode;
    class Item;
    class Viewport;
    struct ManualRender;
    struct PickQuery;
    class Picker;
    struct PassJobs;
    class Pipeline;
    class PassClear;
    class PassUnshaded;
    class PassBackground;
    class PassFlip;
    struct MinimalRenderer;
    struct UnshadedRenderer;
    struct ClearRenderer;
    class FrameBuffer;
    struct SwapBuffer;
    struct Cascade;
    class RenderTarget;
    struct Sun;
    struct Radiance;
    struct Background;
    struct Fog;
    struct Environment;
    class Scene;
    class Shot;
    struct Uniform;
    struct Sampler;
    struct UniformBlock;
    class BlockSky;
	class GIProbe;
	class ReflectionProbe;
	class Lightmap;
	class LightmapAtlas;
	class LightmapItem;
}


#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/vector.h>
#endif

namespace mud
{
	export_ enum class refl_ AnimationTarget : unsigned int
	{
		Position,
		Rotation,
		Scale
	};

	export_ enum class refl_ Interpolation : unsigned int
	{
		Nearest,
		Linear,
		Cubic
	};

	export_ struct MUD_GFX_EXPORT AnimationCursor
	{
		AnimationCursor() {}
		float m_time = 0.f;
		size_t m_prev = 0;
		size_t m_next = 1;
	};

	struct Value
	{
		char m_value[16];
	};

	export_ class refl_ MUD_GFX_EXPORT AnimationTrack
	{
	public:
		struct Key
		{
			Key() {}
			template <class T>
			Key(float time, const T& value, float transition = 1.f) : m_time(time), m_value(), m_transition(transition) {  *(T*)m_value.m_value = value; }
			float m_time;
			Value m_value;
			float m_transition = 1.f;
		};

		AnimationTrack();
		AnimationTrack(Animation& animation, size_t node, cstring node_name, AnimationTarget target);

		attr_ Animation* m_animation;
		attr_ size_t m_node;
		attr_ string m_node_name;
		attr_ AnimationTarget m_target;
		attr_ Type* m_value_type = nullptr;

		attr_ float m_length = 0.f;
		attr_ Interpolation m_interpolation = Interpolation::Linear;

		vector<Key> m_keys;

		void insert_key(float time, const Value& value, float transition = 1.f);
		size_t key_after(float time) const;
		size_t key_before(float time) const;
		Value sample(AnimationCursor& cursor) const;
		Value value(AnimationCursor& cursor, bool forward) const;
	};

	export_ class refl_ MUD_GFX_EXPORT Animation
	{
	public:
		explicit Animation(cstring name);

		vector<AnimationTrack> tracks;

		attr_ string m_name;
		attr_ float m_length = 1.f;
		attr_ float m_step = 0.1f;
	};
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#endif



namespace mud
{
	export_ MUD_GFX_EXPORT mat4 bxidentity();
	export_ MUD_GFX_EXPORT mat4 bxinverse(const mat4& mat);
	export_ MUD_GFX_EXPORT mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans);
	export_ MUD_GFX_EXPORT mat4 bxscale(const vec3& scale);
	// transpose because we are right-handed but bgfx assumes left-handed
	export_ MUD_GFX_EXPORT mat4 bxrotation(const quat& rot);
	//export_ MUD_GFX_EXPORT mat4 bxquat(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), &rot[0]); return result; }
	export_ MUD_GFX_EXPORT mat4 bxtranslation(const vec3& vec);
	export_ MUD_GFX_EXPORT mat4 bxmul(const mat4& lhs, const mat4& rhs);
	export_ MUD_GFX_EXPORT vec4 bxmul(const mat4& mat, const vec4& vec);
	export_ MUD_GFX_EXPORT vec3 bxmul(const mat4& mat, const vec3& vec);
	export_ MUD_GFX_EXPORT vec3 bxmulh(const mat4& mat, const vec3& vec);
	export_ MUD_GFX_EXPORT mat4 bxlookat(const vec3& eye, const vec3& at);
	export_ MUD_GFX_EXPORT void bxlookat(mat4& result, const vec3& eye, const vec3& at, const vec3& up);
	export_ MUD_GFX_EXPORT mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up);
	export_ MUD_GFX_EXPORT mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc);
	export_ MUD_GFX_EXPORT mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc);
	export_ MUD_GFX_EXPORT mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc);
	export_ MUD_GFX_EXPORT mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans);
	export_ MUD_GFX_EXPORT mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans);
	 
	void debug_print_mat(const mat4& mat);

	export_ class refl_ MUD_GFX_EXPORT Node3
	{
	public:
		// @todo factor out scene management stuff from items, nodes, lights and add it to the graph / scene
		Node3(Scene* scene = nullptr, Ref object = {});
		Node3(const mat4& transform);

		attr_ Scene* m_scene = nullptr;
		attr_ uint16_t m_index = 0;

		attr_ mat4 m_transform = bxidentity();
		attr_ bool m_visible = true;

		Ref m_object;
		size_t m_last_updated = 0;

		vec3 position() const;
		vec3 axis(const vec3& dir) const;
		vec3 direction() const;
	};
}

#include <bgfx/bgfx.h>

namespace mud
{
	MUD_GFX_EXPORT mat4 fix_bone_pose(Bone& bone);

	MUD_GFX_EXPORT void debug_draw_skeleton(Gnode& parent, const quat& position, const quat& rotation, Rig& rig);

	export_ struct refl_ MUD_GFX_EXPORT Bone
	{
		Bone() {}
		Bone(cstring name, int index, int parent = -1) : m_name(name), m_index(index), m_parent(parent) {}

		string m_name = "";
		int m_index = 0;
		int m_parent = -1;

		attr_ vec3 m_position = Zero3;
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = Unit3;

		mat4 m_pose_local;
		mat4 m_pose;

		vector<Node3*> m_attached_nodes;
	};

	export_ class refl_ MUD_GFX_EXPORT Skeleton
	{
	public:
		Skeleton();
		Skeleton(cstring name, int num_bones);

		Bone& add_bone(cstring name, int parent = -1);
		Bone* find_bone(cstring name);
		void update_bones();

		cstring m_name;
		vector<Bone> m_bones;
		vector<Animation*> m_animations;
	};

	export_ struct refl_ MUD_GFX_EXPORT Joint
	{
		size_t m_bone;
		mat4 m_inverse_bind;
		mat4 m_joint;
	};

	export_ class refl_ MUD_GFX_EXPORT Skin
	{
	public:
		Skin();
		Skin(Skeleton& skeleton, int num_joints);
		Skin(const Skin& copy, Skeleton& skeleton);
		~Skin();

		void add_joint(cstring bone, const mat4& inverse_bind);
		Joint* find_bone_joint(cstring name);
		void update_joints();

		Skeleton* m_skeleton;

		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
		const bgfx::Memory* m_memory = nullptr;
		//vector<float> m_texture_data;

		vector<Joint> m_joints;
	};

	export_ class refl_ MUD_GFX_EXPORT Rig
	{
	public:
		Rig();

		Rig(const Rig& rig);
		Rig& operator=(const Rig& rig);

		void update_rig();

		Skeleton m_skeleton;
		vector<Skin> m_skins;
	};
}

namespace mud
{
	export_ struct refl_ MUD_GFX_EXPORT AnimatedTrack
	{
		const AnimationTrack* m_track;
		// this used to be generic Ref, but until we actually need a generic animation system, switched to explicit type
		Bone* m_target; // node or bone
		AnimationCursor m_cursor;
		Value m_value;
	};

	export_ struct refl_ MUD_GFX_EXPORT AnimationPlay
	{
		AnimationPlay() {}
		AnimationPlay(const Animation& animation, bool loop, float speed, bool transient, Skeleton* skeleton = nullptr);
		
		void step(float delta, float speed);
		void update(float time, float delta, float interp);

		attr_ const Animation* m_animation = nullptr;
		attr_ bool m_loop = true;
		attr_ float m_speed = 1.f;
		attr_ bool m_transient = false;

		attr_ float m_fadeout = 0.f;
		attr_ float m_fadeout_left = 0.f;
		attr_ float m_cursor = 0.f;
		attr_ bool m_ended = false;

		vector<AnimatedTrack> m_tracks;
	};

	export_ class refl_ MUD_GFX_EXPORT Animated
	{
	public:
		Animated(Node3& node);
		~Animated();

		Node3& m_node;
		Rig m_rig;

		attr_ vector<AnimationPlay> m_playing;
		attr_ vector<Animation*> m_queue;

		attr_ bool m_active = true;

		attr_ float m_speed_scale = 1.f;
		attr_ float m_default_blend_time = 1.f;

		meth_ void start(cstring animation, bool loop, float blend = 0.f, float speed = 1.f, bool transient = false);
		meth_ void play(const Animation& animation, bool loop, float blend = 0.f, float speed = 1.f, bool transient = false);
		meth_ void seek(float time);
		meth_ void pause();
		meth_ void stop();
		meth_ void advance(float time);
		meth_ void next_animation();
		
		void add_item(Item& item);

		meth_ string playing() { return m_playing.empty() ? "" : m_playing.back().m_animation->m_name; }
	};
}


#ifndef MUD_MODULES
#include <stl/function.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/map.h>
#endif

namespace mud
{
	using cstring = const char*;

	export_ template <class T_Asset>
	class refl_ AssetStore : public NonCopy
	{
	public:
		using Loader = function<void(T_Asset&, const string&)>;

		AssetStore(GfxSystem& gfx_system, const string& path);
		AssetStore(GfxSystem& gfx_system, const string& path, const Loader& loader);
		AssetStore(GfxSystem& gfx_system, const string& path, const string& format);

		void add_format(const string& format, const Loader& loader);

		GfxSystem& m_gfx_system;

		string m_path;
		Loader m_loader;

		vector<string> m_formats;
		vector<Loader> m_format_loaders;

		meth_ T_Asset* get(const string& name);
		meth_ T_Asset& create(const string& name);
		meth_ T_Asset& fetch(const string& name);
		//meth_ bool locate(const string& name);
		meth_ T_Asset* file(const string& name);
		meth_ T_Asset& file_at(const string& path, const string& name);
		meth_ void destroy(const string& name);

		T_Asset* load(const string& path, const string& name);
		void load_files(const string& path);

		map<string, unique<T_Asset>> m_assets;
	};
}
//#include <gfx/Asset.hpp>




#ifndef MUD_MODULES
#include <stl/string.h>
#endif

#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#ifndef MUD_MODULES
namespace bx
{
	struct FileReaderI;
	struct FileWriterI;
}
#endif

namespace mud
{
	export_ enum class refl_ TextureHint : unsigned int
	{
		Black,
		White,
		Normal
	};

	export_ MUD_GFX_EXPORT void save_bgfx_texture(bx::AllocatorI& allocator, bx::FileWriterI& writer, cstring file_path, bgfx::TextureFormat::Enum target_format, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum texture_format, uint16_t width, uint16_t height, uint16_t depth = 1);
	export_ MUD_GFX_EXPORT bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, cstring name, void* data, size_t size, uint64_t flags = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info = nullptr, bool generate_mips = false);
	export_ MUD_GFX_EXPORT bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, bx::FileReaderI& reader, cstring file_path, uint64_t flags = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info = nullptr, bool generate_mips = false);
	export_ MUD_GFX_EXPORT bimg::ImageContainer* load_bgfx_image(bx::AllocatorI& allocator, bx::FileReaderI& reader, cstring file_path, bgfx::TextureFormat::Enum dst_format);

	export_ MUD_GFX_EXPORT void save_texture(GfxSystem& gfx_system, Texture& texture, const string& path);
	export_ MUD_GFX_EXPORT void load_texture(GfxSystem& gfx_system, Texture& texture, const string& path);
	export_ MUD_GFX_EXPORT void load_texture_mem(GfxSystem& gfx_system, Texture& texture, array<uint8_t> data);
	export_ MUD_GFX_EXPORT void load_texture_rgba(Texture& texture, uint16_t width, uint16_t height, array<uint8_t> data);

	export_ class refl_ MUD_GFX_EXPORT Texture
	{
	public:
		Texture(const string& name);
		~Texture();

		attr_ string m_name;
		attr_ uint16_t m_width = 0;
		attr_ uint16_t m_height = 0;
		attr_ uint32_t m_bits_per_pixel = 0;

		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
		bgfx::TextureFormat::Enum m_format;
	};
}


#ifndef MUD_MODULES
#include <stl/decls.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	using cstring = const char*;
	
	export_ enum class refl_ ShaderType : unsigned int
	{
		Compute,
		Fragment,
		Geometry,
		Vertex,
		Count
	};

	export_ struct MUD_GFX_EXPORT ShaderDefine
	{
		cstring m_name;
		cstring m_value;
	};

	export_ struct MUD_GFX_EXPORT ShaderBlock
	{
		array<cstring> m_options;
		array<cstring> m_modes;
		array<ShaderDefine> m_defines;
	};

	export_ struct MUD_GFX_EXPORT ProgramBlock
	{
		// maps a block shader option to the program option shift
		uint8_t m_option_shift;
		uint8_t m_mode_shift;
	};

	export_ struct MUD_GFX_EXPORT ProgramBlockArray
	{
		// maps a block index to its shader options array
		ProgramBlock m_shader_blocks[32];
		uint8_t m_next_option = 0;
	};

	export_ class refl_ MUD_GFX_EXPORT Program
	{
	public:
		struct Version
		{
			Version() {}
			uint64_t m_version = 0;
			uint32_t m_update = 0;
			bgfx::ProgramHandle m_program = BGFX_INVALID_HANDLE;
		};

	public:
		Program(const string& name, bool compute = false);
		Program(const string& name, array<GfxBlock*> blocks, array<cstring> sources);
		~Program();

		attr_ cstring name();

		uint8_t block_option_shift(uint8_t block) const
		{
			return m_blocks.m_shader_blocks[block].m_option_shift;
		}

		uint8_t block_mode_shift(uint8_t block) const
		{
			return m_blocks.m_shader_blocks[block].m_mode_shift;
		}

		void reload() { m_update++; }

		void compile(GfxSystem& gfx_system, Version& version, bool compute = false);

		void update(GfxSystem& gfx_system);

		bgfx::ProgramHandle default_version();
		bgfx::ProgramHandle version(const ShaderVersion& config);

		ShaderVersion shader_version(Version& version);

		void register_blocks(array<GfxBlock*> blocks);
		void register_block(const GfxBlock& block);
		void register_options(uint8_t block, array<cstring> options);
		void register_modes(uint8_t block, array<cstring> modes);

		ProgramBlockArray m_blocks;

		cstring m_sources[size_t(ShaderType::Count)] = {};

		bool m_compute = false;
		uint32_t m_update = 1;

		struct Impl;
		unique<Impl> m_impl;

		static GfxSystem* ms_gfx_system;
	};
}


#ifndef MUD_MODULES
#include <stl/string.h>
#endif

namespace bgfx
{
	struct Encoder;
}

namespace mud
{
	export_ enum class refl_ BlendMode : unsigned int
	{
		Mix,
		Add,
		Sub,
		Mul,
		Normal,
		Alpha
	};

	void blend_state(BlendMode blend_mode, uint64_t& bgfx_state);

	export_ enum class refl_ CullMode : unsigned int
	{
		None,
		Front,
		Back
	};

	export_ enum class refl_ DepthDraw : unsigned int
	{
		Enabled,
		Disabled
	};

	export_ enum class refl_ DepthTest : unsigned int
	{
		Enabled,
		Disabled
	};

	export_ enum class refl_ MaterialFlag : unsigned int
	{
		TriplanarUV1,
		TriplanarUV2,
		Count
	};

	export_ struct refl_ MUD_GFX_EXPORT BaseMaterialBlock
	{
		attr_ BlendMode m_blend_mode = BlendMode::Mix;
		attr_ CullMode m_cull_mode = CullMode::Back;
		attr_ DepthDraw m_depth_draw_mode = DepthDraw::Enabled;
		attr_ DepthTest m_depth_test = DepthTest::Enabled;

		attr_ vec2 m_uv0_scale = { 1.f, 1.f };
		attr_ vec2 m_uv0_offset = { 0.f, 0.f };
		attr_ vec2 m_uv1_scale = { 1.f, 1.f };
		attr_ vec2 m_uv1_offset = { 0.f, 0.f };

		attr_ bool m_is_alpha = false;
		attr_ bool m_screen_filter = false;

		uint m_geometry_filter = (1 << OUTLINE) | (1 << PLAIN);

#if 0
		BillboardMode m_billboard_mode;
#endif		
	};

	export_ enum class refl_ TextureChannel : unsigned int
	{
		Red,
		Green,
		Blue,
		Alpha,
		All
	};

	export_ template <class T_Param>
	struct refl_ struct_ MaterialParam
	{
		MaterialParam() {}
		MaterialParam(T_Param value, Texture* texture = nullptr, TextureChannel channel = TextureChannel::All) : m_value(value), m_texture(texture), m_channel(channel) {}
		attr_ T_Param m_value = {};
		attr_ Texture* m_texture = nullptr;
		attr_ TextureChannel m_channel = TextureChannel::All;
	};

	export_ extern template struct refl_ MaterialParam<Colour>;
	export_ extern template struct refl_ MaterialParam<float>;

	export_ struct refl_ MUD_GFX_EXPORT UnshadedMaterialBlock
	{
		attr_ bool m_enabled = false;

		attr_ MaterialParam<Colour> m_colour = { Colour::White, nullptr };
	};

	export_ struct refl_ MUD_GFX_EXPORT FresnelMaterialBlock
	{
		attr_ bool m_enabled = false;

		attr_ MaterialParam<Colour> m_value = { Colour::White, nullptr };

		attr_ float m_fresnel_scale = 1.f;
		attr_ float m_fresnel_bias = 0.01f;
		attr_ float m_fresnel_power = 5.f;
	};

	export_ enum class refl_ PbrDiffuseMode : unsigned int
	{
		Lambert,
		LambertHalf,
		OrenNayar,
		Burley,
		Toon,
	};

	export_ enum class refl_ PbrSpecularMode : unsigned int
	{
		SchlickGGX,
		Blinn,
		Phong,
		Toon,
		Disabled,
	};

	export_ enum PbrShaderOption : unsigned int
	{
		NORMAL_MAP,
		EMISSIVE,
		ANISOTROPY,
		AMBIENT_OCCLUSION,
		DEPTH_MAPPING,
		DEEP_PARALLAX,
		LIGHTMAP
	};

	export_ struct refl_ MUD_GFX_EXPORT PbrMaterialBlock
	{
		constr_ PbrMaterialBlock() {}
		constr_ PbrMaterialBlock(const Colour& albedo, float metallic = 0.f, float roughness = 1.f) : m_enabled(true), m_albedo(albedo, nullptr), m_metallic(metallic, nullptr, TextureChannel::Red), m_roughness(roughness, nullptr, TextureChannel::Red) {}

		PbrMaterialBlock& operator=(const PbrMaterialBlock&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		attr_ bool m_enabled = false;

		// basic
		attr_ MaterialParam<Colour> m_albedo = { Colour::White, nullptr };
		attr_ float m_specular = 0.5f;
		attr_ MaterialParam<float> m_metallic = { 0.f, nullptr, TextureChannel::Red };
		attr_ MaterialParam<float> m_roughness = { 1.f, nullptr, TextureChannel::Red };
		attr_ MaterialParam<Colour> m_emissive = { Colour::None, nullptr };
		attr_ float m_emissive_energy = 0.f;
		attr_ MaterialParam<float> m_normal = { 1.f, nullptr };

		// advanced
		attr_ MaterialParam<float> m_rim;
		attr_ float m_rim_tint;
		attr_ MaterialParam<float> m_clearcoat;
		attr_ float m_clearcoat_gloss;
		attr_ MaterialParam<float> m_anisotropy;
		attr_ MaterialParam<float> m_subsurface;
		attr_ MaterialParam<Colour> m_transmission;
		attr_ MaterialParam<float> m_refraction;
		attr_ MaterialParam<float> m_ambient_occlusion;
		attr_ MaterialParam<float> m_depth = { -0.02f, nullptr };

		attr_ bool m_deep_parallax = false;

		attr_ PbrDiffuseMode m_diffuse_mode = PbrDiffuseMode::Burley;
		attr_ PbrSpecularMode m_specular_mode = PbrSpecularMode::SchlickGGX;

		bool m_flags[size_t(MaterialFlag::Count)];
	};

	export_ GfxBlock& pbr_block(GfxSystem& gfx_system);

	export_ MUD_GFX_EXPORT void load_material(Material& material, Program& program);

	export_ class refl_ MUD_GFX_EXPORT Material
	{
	public:
		Material() {}
		Material(const string& name);

		Material& operator=(const Material&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		attr_ uint16_t m_index = 0;
		attr_ string m_name;
		attr_ bool m_builtin = false;
		attr_ Program* m_program = nullptr;

		attr_ BaseMaterialBlock m_base_block;
		attr_ UnshadedMaterialBlock m_unshaded_block;
		attr_ PbrMaterialBlock m_pbr_block;
		attr_ FresnelMaterialBlock m_fresnel_block;

		void state(uint64_t& bgfx_state) const;
		ShaderVersion shader_version(const Program& program) const;
		ShaderVersion shader_version(const Program& program, const Item& item, const ModelItem& model_item) const;

		void submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const Skin* skin = nullptr) const;

		static GfxSystem* ms_gfx_system;
	};
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#endif

namespace mud
{
	export_ struct refl_ ModelItem
	{
		attr_ size_t m_index;
		attr_ Mesh* m_mesh;
		attr_ bool m_has_transform;
		attr_ mat4 m_transform;
		attr_ int m_skin;
		attr_ Colour m_colour;
		attr_ Material* m_material;
	};

	export_ class refl_ MUD_GFX_EXPORT Model
	{
	public:
		Model(const string& name);
		~Model();

		attr_ string m_name;
		attr_ uint16_t m_index;

		Rig* m_rig = nullptr;

		vector<ModelItem> m_items;

		/*attr_*/ bool m_geometry[2] = { false, false };
		attr_ Aabb m_aabb = { Zero3, Zero3 };
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = Zero3;

		Mesh& add_mesh(const string& name, bool readback = false);
		Rig& add_rig(const string& name);
		ModelItem& add_item(Mesh& mesh, mat4 transform, int skin = -1, Colour colour = Colour::White, Material* material = nullptr);
		void prepare();

		static GfxSystem* ms_gfx_system;
	};

	export_ MUD_GFX_EXPORT Model& model_variant(GfxSystem& gfx_system, Model& original, const string& name, array<string> materials, array<Material*> substitutes);
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif


#ifndef MUD_MODULES
#endif


#include <stdint.h>

namespace mud
{
	enum ShaderOption : unsigned int
	{
		SKELETON,
		INSTANCING,
		BILLBOARD,
		QNORMALS,
		MRT,
		DEFERRED,
		CLUSTERED
	};

	export_ struct MUD_GFX_EXPORT ShaderVersion
	{
		ShaderVersion() {}
		ShaderVersion(const Program* program) : m_program(program) {}

		const Program* m_program = nullptr;
		uint32_t m_options = 0;
		uint8_t m_modes[4] = {};

		void clear() { m_options = 0; }

		inline void set(uint8_t option, bool active = true)
		{
			if(active)
				m_options |= (1 << option);
			else
				m_options &= ~(1 << option);
		}

		inline void set_option(uint8_t block, uint8_t option, bool active = true)
		{
			this->set(m_program->block_option_shift(block) + option, active);
		}

		inline void set_mode(uint8_t block, uint8_t mode, uint8_t value)
		{
			m_modes[m_program->block_mode_shift(block) + mode] = value;
		}

		uint32_t hash_modes() const { return (m_modes[0] << 0) + (m_modes[1] << 8) + (m_modes[2] << 16) + (m_modes[3] << 24); }
		uint64_t hash() const {	return uint64_t(m_options) + (uint64_t(hash_modes()) << 32); }
	};
}

#include <stdint.h>

#include <bgfx/bgfx.h>

namespace mud
{
#define GFX_TEXTURE_CLAMP BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
#define GFX_TEXTURE_CLAMP_UVW BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP
#define GFX_TEXTURE_POINT BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT

	MUD_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

	export_ enum class refl_ TextureSampler : unsigned int
	{
		Source0 = 0,
		Source1 = 1,
		Source2 = 2,
		Source3 = 3,
		SourceDepth = 3,

		Color = 0,
		Albedo = 0,
		Metallic = 1,
		Roughness = 2,
		Emissive = 3,
		Normal = 4,
		AO = 11,
		Depth = 12,

		Skeleton = 5,
		ShadowCSM = 6,
		ShadowAtlas = 7,
		Radiance = 8,
		ReflectionProbe = 9,
		GIProbe = 10,
		Lights = 13,
		Clusters = 14,
		LightRecords = 15,
		Lightmap = 7,  // can't be 16 because max samplers... FIX THIS
	};

	export_ enum class PassType : unsigned int
	{
		VoxelGI,
		Lightmap,
		Shadowmap,
		Probes,
		Clear,
		Depth,
		Geometry,
		Lights,
		Opaque,
		Background,
		Particles,
		Alpha,
		Unshaded,
		Effects,
		PostProcess,
		Flip,

		Count
	};

	export_ enum class refl_ Lighting : unsigned int
	{
		None = 0,
		Clustered = (1 << 0),
		Deferred = (1 << 1),
		VoxelGI = (1 << 2),
	};

	inline Lighting lighting(Lighting clustered = Lighting::None, Lighting deferred = Lighting::None, Lighting gi = Lighting::None)
	{
		return Lighting(uint(clustered) | uint(deferred) | uint(gi));
	}

	inline bool check_lighting(Lighting lighting, Lighting option)
	{
		return (uint(lighting) & uint(option)) != 0;
	}

	/*
	initial idea (reality is quite far from that)
	blocks
		- a block is a unit of renderer work
		- it contains all the information needed to be executed : target, bgfx view, viewport, clear, items, material, render state parameters, uniforms, textures, etc...
		- blocks can be nested : ex in main render pass block there are subblocks for each material
		- they can be complementary : inside a pbr render pass block the pbr material block fills in the missing pbr information
		- the sum of uniform blocks must be equivalent to the uniforms expected by the shader(blocks)
	blocks are functional components
	passes are the unit of renderer work
	both are orthogonal
	*/

	export_ struct MUD_GFX_EXPORT Pass
	{
		RenderTarget* m_target = nullptr;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		Viewport* m_viewport = nullptr;
		uint64_t m_bgfx_state = 0;
		bgfx::Encoder* m_encoder = nullptr;

		bool m_use_mrt = false;
		uint8_t m_index = 0;
		uint8_t m_sub_pass = 0;
	};

	export_ struct refl_ MUD_GFX_EXPORT RenderFrame
	{
		uint32_t m_frame;
		float m_time;
		float m_delta_time;
		uint8_t m_render_pass;
		uint32_t m_num_draw_calls = 0;
		uint32_t m_num_vertices = 0;
		uint32_t m_num_triangles = 0;
	};

	export_ struct MUD_GFX_EXPORT Render : public NonCopy
	{
		Render(Shading shading, Viewport& viewport, RenderTarget& target, RenderFrame& frame);
		Render(Shading shading, Viewport& viewport, bgfx::FrameBufferHandle& target_fbo, RenderFrame& frame);
		~Render();

		Shading m_shading;
		Scene& m_scene;
		RenderTarget* m_target;
		bgfx::FrameBufferHandle m_target_fbo;
		Viewport& m_viewport;
		Camera& m_camera;
		RenderFrame& m_frame;

		unique<Frustum> m_frustum;

		Environment* m_environment = nullptr;
		Entt m_filters;

		Lighting m_lighting = Lighting::None;
		bool m_needs_mrt = false;
		bool m_is_mrt = false;
		bool m_needs_depth_prepass = false;

		//ShadowAtlas* m_shadow_atlas = nullptr;
		//ReflectionAtlas* m_reflection_atlas = nullptr;

		uint8_t m_picking_pass_index = s_picking_pass_id;
		uint8_t m_preprocess_pass_index = s_preprocess_pass_id;
		uint8_t m_pass_index = s_render_pass_id;
		uint8_t m_debug_pass_index = s_debug_pass_id;
		uint8_t m_sub_pass_index = 0;

		unique<Shot> m_shot;

		uint32_t m_num_draw_calls = 0;
		uint32_t m_num_vertices = 0;
		uint32_t m_num_triangles = 0;

		Pass next_pass(const char* name, bool subpass = false);
		uint8_t next_pass_id() { return m_pass_index++; }

		uint8_t picking_pass() { return m_picking_pass_index++; }
		uint8_t preprocess_pass() { return m_preprocess_pass_index++; }
		uint8_t composite_pass() { return m_pass_index++; }
		uint8_t debug_pass() { return m_debug_pass_index++; }

		void set_uniforms(bgfx::Encoder& encoder) const;

		static const uint8_t s_picking_pass_id = 1;
		static const uint8_t s_preprocess_pass_id = 20;
		static const uint8_t s_shadow_atlas_pass_id = 50;
		static const uint8_t s_reflection_probe_pass_id = 70;
		static const uint8_t s_render_pass_id = 100;
		static const uint8_t s_debug_pass_id = 240;
		static const uint8_t s_resolve_pass_id = 254;
		static const uint8_t s_final_draw_pass_id = 254;
		static const uint8_t s_ui_pass_id = 255;
	};

	export_ class refl_ MUD_GFX_EXPORT GfxBlock
	{
	public:
		GfxBlock(GfxSystem& gfx_system, Type& type);
		virtual ~GfxBlock();

		template <class T>
		GfxBlock(GfxSystem& gfx_system, T& self) : GfxBlock(gfx_system, type<T>()) { UNUSED(self); }

		virtual void init_block() = 0;
		virtual void begin_frame(const RenderFrame& frame) { UNUSED(frame); }

		virtual void begin_render(Render& render) = 0;
		virtual void begin_pass(Render& render) = 0;
		virtual void submit_pass(Render& render) { UNUSED(render); }

		GfxSystem& m_gfx_system;
		attr_ Type& m_type;
		attr_ uint8_t m_index;

		unique<ShaderBlock> m_shader_block;

		bool m_draw_block = false;

		static uint8_t s_block_index;
	};

	export_ class refl_ MUD_GFX_EXPORT DrawBlock : public GfxBlock
	{
	public:
		DrawBlock(GfxSystem& gfx_system, Type& type) : GfxBlock(gfx_system, type) { m_draw_block = true; }

		virtual void begin_draw_pass(Render& render) = 0;

		virtual void options(Render& render, ShaderVersion& shader_version) const = 0;
		virtual void submit(Render& render, const Pass& render_pass) const = 0;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const { UNUSED(element); this->submit(render, render_pass); }
	};

	export_ class MUD_GFX_EXPORT RenderPass
	{
	public:
		RenderPass(GfxSystem& gfx_system, const char* name, PassType pass_type);
		virtual ~RenderPass() {}

		virtual void submit_render_pass(Render& render) = 0;

		void blocks_begin_render(Render& render) { for(GfxBlock* block : m_gfx_blocks) block->begin_render(render); }
		void blocks_begin_draw_pass(Render& render) { for(DrawBlock* block : m_draw_blocks) block->begin_draw_pass(render); }
		void blocks_begin_pass(Render& render) { for(GfxBlock* block : m_gfx_blocks) block->begin_pass(render); }

		GfxSystem& m_gfx_system;
		const char* m_name;
		PassType m_pass_type;
		array<GfxBlock*> m_gfx_blocks;
		array<DrawBlock*> m_draw_blocks;
	};
	
	export_ struct MUD_GFX_EXPORT DrawElement
	{
		DrawElement() {}
		DrawElement(Item& item, const Program& program, const ModelItem& model, const Material& material, const Skin* skin = nullptr);
		Item* m_item = nullptr;
		const Program* m_program = nullptr;
		const ModelItem* m_model = nullptr;
		const Material* m_material = nullptr;
		const Skin* m_skin = nullptr;

		uint64_t m_sort_key = 0;
		ShaderVersion m_shader_version = {};
		uint64_t m_bgfx_state = 0;
		bgfx::ProgramHandle m_bgfx_program = BGFX_INVALID_HANDLE;
	};

	export_ struct MUD_GFX_EXPORT DrawCluster
	{
		ShaderVersion m_shader_version = {};
		uint64_t m_bgfx_state = 0;
		array<Light*> m_lights = {};
	};

	export_ class MUD_GFX_EXPORT DrawPass : public RenderPass
	{
	public:
		DrawPass(GfxSystem& gfx_system, const char* name, PassType pass_type);
		~DrawPass();

		void init_blocks();
		void add_element(Render& render, DrawElement element);

		virtual void submit_render_pass(Render& render) final;

		void gather_draw_elements(Render& render);
		void submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& render_pass, size_t first, size_t count) const;

		virtual uint8_t num_draw_passes(Render& render) { UNUSED(render); return 1; }
		virtual void next_draw_pass(Render& render, Pass& render_pass) = 0;
		virtual void queue_draw_element(Render& render, DrawElement& element) = 0;

		struct Impl;
		unique<Impl> m_impl;
	};

	export_ class MUD_GFX_EXPORT Renderer : public NonCopy
	{
	public:
		Renderer(GfxSystem& gfx_system, Pipeline& pipeline, Shading shading);
		~Renderer();

		GfxSystem& m_gfx_system;
		Pipeline& m_pipeline;
		Shading m_shading;

		struct Impl;
		unique<Impl> m_impl;

		void init();

		bool has_block(GfxBlock& gfx_block);
		void add_block(GfxBlock& gfx_block);

		void gather(Render& render);
		void render(Render& render);
		void subrender(Render& render, Render& sub);

		RenderPass& add_pass(unique<RenderPass> pass);

		template <class T_Pass, class... T_Args>
		T_Pass& add_pass(T_Args&&... args) { return as<T_Pass>(add_pass(make_unique<T_Pass>(static_cast<T_Args&&>(args)...))); }
	};
}

#include <bgfx/bgfx.h>

namespace mud
{
	struct Particle
	{
		vec3 start;
		vec3 dir;
		quat rot;

		float speed_seed;
		float angle_seed;
		float blend_seed;
		float colour_seed;
		float scale_seed;
		float sprite_seed;

		float life;
		float lifetime;
	};

	struct ParticleSort
	{
		float    dist;
		uint32_t idx;
	};

	export_ enum class refl_ EmitterFlow : unsigned int
	{
		Outward,
		Absolute
	};

	export_ struct refl_ MUD_GFX_EXPORT ParticleFlow
	{
		ParticleFlow();
		ParticleFlow(const string& name);

		attr_ string m_name;

		// emitter
		attr_ float m_duration = 1.f;
		attr_ float m_start_time = 0.f;
		attr_ bool m_loop = false;
		attr_ ShapeVar m_shape = {};
		attr_ EmitterFlow m_flow = EmitterFlow::Outward;
		attr_ bool m_billboard = true;
		attr_ vec3 m_direction = { 0.f, 0.f, -1.f };
		attr_ quat m_rotation = ZeroQuat;
		attr_ BlendMode m_blend_mode = BlendMode::Normal;

		//attr_ ValueTrack<vec3> m_position = { Zero3 };
		//attr_ ValueTrack<quat> m_rotation = { ZeroQuat };
		attr_ ValueTrack<float> m_volume = { 1.f };

		attr_ ValueTrack<uint32_t> m_rate = { 0 };

		attr_ ValueTrack<float> m_lifetime = { 1.f };
		attr_ ValueTrack<float> m_gravity = { 0.f };

		// particles
		attr_ ValueTrack<float> m_speed = { 1.f };
		attr_ ValueTrack<float> m_angle = { 0.f };
		attr_ ValueTrack<float> m_blend = { vector<float>({ 0.8f, 0.0f }) };
		attr_ ValueTrack<Colour> m_colour = { Colour::White };
		attr_ ValueTrack<float> m_scale = { 0.1f };

		attr_ ValueTrack<float> m_sprite_frame = { 0.f };

		attr_ string m_sprite_name;

		const Sprite* m_sprite = nullptr;
	};

	struct ParticleVertex
	{
		vec3 m_pos;
		uint32_t m_abgr;
		vec2 m_uv;
		float m_blend;
		float m_radius;
		//float m_angle;

		static void init();
	};

	export_ struct refl_ MUD_GFX_EXPORT Particles : public ParticleFlow
	{
	public:
		Particles(Node3* node = nullptr, ShapeVar shape = {}, uint32_t max_particles = 1024);

		attr_ Node3* m_node = nullptr;

		bool ended() { return m_time > m_duration; }

		void upload();
		void update(float dt);
		void spawn(float dt);
		uint32_t render(const SpriteAtlas& atlas, const mat4& view, const vec3& eye, uint32_t first, uint32_t max, ParticleSort* outSort, ParticleVertex* outVertices);

		inline void write_vertex(ParticleVertex*& dest, ParticleVertex vertex);

		float m_time = 0.0f;
		float m_dt = 0.0f;
		bool m_ended = false;

		Aabb m_aabb;

		vector<Particle> m_particles;
		uint32_t m_max;
	};

#ifndef MUD_MODULES
	template <class T>
	class TPool;
#endif

	export_ class MUD_GFX_EXPORT ParticleSystem
	{
	public:
		ParticleSystem(GfxSystem& gfx_system, TPool<Particles>& emitters);
		~ParticleSystem();

		GfxSystem& m_gfx_system;
		BlockParticles& m_block;

		void shutdown();

		void update(float timestep);
		void render(bgfx::Encoder& encoder, uint8_t pass, const mat4& view, const vec3& eye);
		
		TPool<Particles>& m_emitters;

		bgfx::ProgramHandle m_program;

		uint32_t m_num = 0;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockParticles : public GfxBlock
	{
	public:
		BlockParticles(GfxSystem& gfx_system);
		~BlockParticles();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		unique<SpriteAtlas> m_sprites;
		bgfx::TextureHandle m_texture;

		bgfx::UniformHandle s_color;

		Sprite* create_sprite(cstring name, cstring path, uvec2 frames = uvec2(0U));
		Sprite* create_sprite(cstring name, uvec2 size, uvec2 frames, const void* data);
		void remove_sprite(Sprite& image);
	};

	export_ class MUD_GFX_EXPORT PassParticles : public RenderPass
	{
	public:
		PassParticles(GfxSystem& gfx_system);

		virtual void submit_render_pass(Render& render) final;
	};
}


#ifndef MUD_MODULES
#include <stl/vector.h>
//#include <refl/Method.h>
#endif


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	export_ struct ItemFlag
	{
		enum Enum : unsigned int
		{
			None = 0,
			Render = 1 << 0,
			Shadows = 1 << 1,
			Occluder = 1 << 2,
			Billboard = 1 << 3,
			Static = 1 << 4,
			Selectable = 1 << 5,
			Ui = 1 << 6,
			NoUpdate = 1 << 7,
			Lod0 = 1 << 8,
			Lod1 = 1 << 9,
			Lod2 = 1 << 10,
			Lod3 = 1 << 11,
			LodAll = Lod0 | Lod1 | Lod2 | Lod3,
			Default = Render | Shadows | LodAll
		};
	};

	export_ enum class refl_ ItemShadow : unsigned int
	{
		Default,
		DoubleSided
	};

	export_ class refl_ MUD_GFX_EXPORT Item
	{
	public:
		Item();
		Item(Node3& node, const Model& model, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
		~Item();

		attr_ Node3* m_node;
		attr_ Model* m_model = nullptr;
		attr_ uint32_t m_flags = 0;
		attr_ Colour m_colour = Colour::White;
		attr_ Material* m_material = nullptr;
		attr_ bool m_visible = true;
		attr_ ItemShadow m_shadow = ItemShadow::Default;
		attr_ Rig* m_rig = nullptr;

		Aabb m_aabb;

		void update();
		void update_instances();

		void submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelItem& item) const;

		vector<mat4> m_instances;

		vector<bgfx::InstanceDataBuffer> m_instance_buffers;
		
		vector<Light*> m_lights;
		//vector<ReflectionProbe*> m_reflection_probes;
		//vector<GIProbe*> m_gi_probes;
		
		vector<LightmapItem*> m_lightmaps;

		float m_depth = 0.f;
		uint32_t m_layer_mask = 1;
	};
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/map.h>
#endif

namespace mud
{
	export_ enum class refl_ ModelFormat : unsigned int
	{
		obj,
		gltf,

		Count
	};

	export_ struct refl_ MUD_GFX_EXPORT ImportConfig
	{
		ImportConfig() {}

		attr_ ModelFormat m_format = ModelFormat::obj;
		attr_ vec3 m_position = Zero3;
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = Unit3;
		attr_ mat4 m_transform = bxidentity();
		attr_ vector<string> m_exclude_elements = {};
		attr_ vector<string> m_exclude_materials = {};
		attr_ vector<string> m_include_elements = {};
		attr_ vector<string> m_include_materials = {};
		attr_ string m_suffix;
		attr_ bool m_force_reimport = false;
		attr_ bool m_cache_geometry = false;
		attr_ bool m_optimize_geometry = false;
		attr_ uint32_t m_flags = ItemFlag::None;

		bool filter_element(const string& name) const;
		bool filter_material(const string& name) const;
	};

	export_ class MUD_GFX_EXPORT Import
	{
	public:
		Import(GfxSystem& gfx_system, const string& filepath, const ImportConfig& config);

		string m_name;
		string m_file;
		string m_path;

		GfxSystem& m_gfx_system;
		const ImportConfig& m_config;

		vector<Mesh*> m_meshes;
		vector<Model*> m_models;
		vector<Texture*> m_images;
		vector<Material*> m_materials;

		map<int, Skeleton*> m_skeletons;

		struct Item { mat4 transform; Model* model; int skin; };
		vector<Item> m_items;
	};

	export_ class MUD_GFX_EXPORT Importer
	{
	public:
		virtual ~Importer() {}
		virtual void import(Import& import, const string& filepath, const ImportConfig& config) = 0;
		virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) = 0;
		virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) = 0;
		virtual void repack(const string& filepath, const ImportConfig& config) = 0;
	};

	export_ MUD_GFX_EXPORT void import_to_prefab(GfxSystem& gfx_system, Prefab& prefab, Import& state, uint32_t flags = 0);
}

namespace mud
{
#ifdef MUD_PREFABNODE
	export_ enum class refl_ PrefabType : unsigned int
	{
		None,
		Item,
		Model,
		Shape,
		Particles,
		Light
	};

	export_ struct refl_ MUD_GFX_EXPORT PrefabNode
	{
		PrefabNode();

		attr_ Transform m_transform = {};
		attr_ Ref m_object = {};
		attr_ PrefabType m_prefab_type = PrefabType::None;
		attr_ Call m_call = {};
		attr_ vector<PrefabNode> m_nodes;

		void draw(Gnode& parent);
	};
#endif

	export_ class refl_ MUD_GFX_EXPORT Prefab
	{
	public:
		Prefab(const string& name);

		attr_ string m_name;
#ifdef MUD_PREFABNODE
		attr_ PrefabNode m_node;
#endif

		vector<Node3> m_nodes;
		vector<Item> m_items;

		Aabb m_aabb;
	};

	export_ MUD_GFX_EXPORT Prefab& import_prefab(GfxSystem& gfx_system, ModelFormat format, const string& name, const ImportConfig& config);
	export_ MUD_GFX_EXPORT void destroy_prefab(GfxSystem& gfx_system, Prefab& prefab);
}

namespace mud
{
	export_ extern template class refl_ AssetStore<Texture>;
	export_ extern template class refl_ AssetStore<Program>;
	export_ extern template class refl_ AssetStore<Material>;
	export_ extern template class refl_ AssetStore<Model>;
	export_ extern template class refl_ AssetStore<ParticleFlow>;
	export_ extern template class refl_ AssetStore<Prefab>;
}


#include <stl/vector.h>

#include <bgfx/bgfx.h>

namespace mud
{

	class GpuBuffer
	{
	public:
		enum class ElementType : uint8_t
		{
			UINT8,
			INT8,
			UINT16,
			INT16,
			UINT32,
			INT32,
			HALF,
			FLOAT
		};

		struct Element
		{
			Element(ElementType type, uint8_t size) : type(type), size(size) {}
			ElementType type;
			uint8_t     size;
		};

		GpuBuffer() = default;

		GpuBuffer(Element element, size_t row_size, size_t row_count);
		~GpuBuffer();

		GpuBuffer(const GpuBuffer&) = delete;
		GpuBuffer& operator=(const GpuBuffer&) = delete;
		GpuBuffer(GpuBuffer&&) = default;
		GpuBuffer& operator=(GpuBuffer&&) = default;

		bgfx::TextureHandle m_texture;
		//utils::RangeSet<4> mDirtyRanges;
		Element m_element;
		uint32_t m_size = 0;
		uint16_t m_width = 0;
		uint16_t m_height = 0;
		uint16_t m_row_size = 0;
		bgfx::TextureFormat::Enum m_format;
	
		//vector<Range<float>> m_dirty_ranges;

		void invalidate() noexcept;
		void invalidate(size_t row, size_t count) noexcept;

		//bool dirty() const noexcept { return !mDirtyRanges.isEmpty(); }

		void commit(const bgfx::Memory* memory) noexcept;
	};

}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ enum refl_ IsometricAngle : unsigned int
	{
		NORTH = (1 << 0),
		SOUTH = (2 << 0),
		EAST = (1 << 8),
		WEST = (2 << 8)
	};

	export_ class refl_ MUD_GFX_EXPORT Camera : public NonCopy
	{
	public:
		Camera();
		Camera(mat4 transform, mat4 projection, bool ortho = false);
		Camera(mat4 transform, float fov, float aspect, float near, float far);
		Camera(mat4 transform, vec2 rect, float near, float far);
		~Camera();

		attr_ vec3 m_eye;
		attr_ vec3 m_target;

		attr_ mat4 m_transform;
		attr_ mat4 m_projection;

#if defined MUD_UNIFORM_BLOCKS
		attr_ FrustumBlock m_frustum;
#endif
		attr_ float m_fov = 60.f;
		attr_ float m_aspect = 1.f;
		attr_ float m_near = 0.1f;
		attr_ float m_far = 100.f;

		attr_ bool m_orthographic = false;
		attr_ float m_height = 1.f;

		attr_ bool m_optimize_ends = true;
		attr_ bool m_clustered = false;

		attr_ vec4 m_lod_offsets = { 0.1f, 0.3f, 0.6f, 0.8f };

		void update();

		void set_look_at(const vec3& eye, const vec3& target);
		void set_isometric(IsometricAngle angle, const vec3& position);

		Plane near_plane() const;
		Plane far_plane() const;

		mat4 projection(float near, float far, bool ndc = false);

		Ray ray(const vec2& offset) const;

		unique<Froxelizer> m_clusters;
	};
}


#ifdef MUD_MODULES
#define _GLIBCXX_TYPE_TRAITS
#include <xmmintrin.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#define GFX_TEXTURE_CLAMP BGFX_TEXTURE_U_CLAMP | BGFX_TEXTURE_V_CLAMP
#define GFX_TEXTURE_CLAMP_UVW BGFX_TEXTURE_U_CLAMP | BGFX_TEXTURE_V_CLAMP | BGFX_TEXTURE_W_CLAMP
#define GFX_TEXTURE_POINT BGFX_TEXTURE_MIN_POINT | BGFX_TEXTURE_MAG_POINT
#endif




#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ struct refl_ DepthParams
	{
		float m_depth_bias = 0.f;
		float m_depth_normal_bias = 0.f;
		float m_depth_z_far = 0.f;
		float _padding;
	};

	export_ class MUD_GFX_EXPORT PassDepth : public DrawPass
	{
	public:
		PassDepth(GfxSystem& gfx_system, cstring name, BlockDepth& block_depth);
		PassDepth(GfxSystem& gfx_system, BlockDepth& block_depth);

		virtual void next_draw_pass(Render& render, Pass& render_pass) override;
		virtual void queue_draw_element(Render& render, DrawElement& element) override;

		BlockDepth& m_block_depth;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockDepth : public DrawBlock
	{
	public:
		BlockDepth(GfxSystem& gfx_system);
		~BlockDepth();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		struct DepthUniform
		{
			void createUniforms()
			{
				u_depth_params = bgfx::createUniform("u_depth_params", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle u_depth_params;

		} u_depth;

		DepthParams* m_current_params = nullptr;

		DepthParams m_depth_params;

		Material* m_depth_material = nullptr;
		Material* m_depth_material_twosided = nullptr;
	};
}


#ifndef MUD_MODULES
#endif


#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	export_ struct MUD_GFX_EXPORT GpuMesh
	{
		GpuMesh() {}
		GpuMesh(uint32_t vertex_count, uint32_t index_count)
			: m_vertex_count(vertex_count), m_index_count(index_count)
		{}

		uint32_t m_vertex_format = 0;
		
		uint32_t m_vertex_count = 0;
		uint32_t m_index_count = 0;
		bool m_index32 = false;

		const bgfx::Memory* m_vertex_memory = nullptr;
		const bgfx::Memory* m_index_memory = nullptr;

		void* m_vertices = nullptr;
		void* m_indices = nullptr;

		MeshAdapter m_writer = {};
	};
	
	export_ MUD_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

	export_ MUD_GFX_EXPORT GpuMesh alloc_mesh(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count, bool index32);
	export_ MUD_GFX_EXPORT GpuMesh alloc_mesh(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count);

	export_ class refl_ MUD_GFX_EXPORT Mesh
	{
	public:
		Mesh(const string& name, bool readback = false);
		~Mesh();

		Mesh(Mesh&& other) = default;
		Mesh& operator=(Mesh&& other) = default;

		attr_ string m_name;
		attr_ uint16_t m_index;
		attr_ DrawMode m_draw_mode = PLAIN;
		attr_ Aabb m_aabb = {};
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = Zero3;
		attr_ bool m_readback = false;

		attr_ uint32_t m_vertex_format = 0;
		attr_ bool m_qnormals = false;

		attr_ uint32_t m_vertex_count = 0;
		attr_ uint32_t m_index_count = 0;
		attr_ bool m_index32 = false;

		attr_ Material* m_material = nullptr;

		bgfx::VertexBufferHandle m_vertex_buffer = BGFX_INVALID_HANDLE;
		bgfx::IndexBufferHandle m_index_buffer = BGFX_INVALID_HANDLE;

		struct UvBounds { vec2 min; vec2 max; };
		UvBounds m_uv0_rect = {};
		UvBounds m_uv1_rect = {};

		vector<uint8_t> m_cached_vertices;
		vector<uint8_t> m_cached_indices;

		MeshAdapter m_cache;

		void clear();
		void read(MeshAdapter& writer, const mat4& transform) const;
		void read(MeshPacker& packer, const mat4& transform) const;
		void write(DrawMode draw_mode, MeshPacker& packer, bool optimize = false);
		void upload(DrawMode draw_mode, const GpuMesh& gpu_mesh);
		void upload_opt(DrawMode draw_mode, const GpuMesh& gpu_mesh);
		void cache(const GpuMesh& gpu_mesh);
		
		uint64_t submit(bgfx::Encoder& encoder) const;
	};
}

namespace mud
{
	constexpr size_t c_max_shape_size = 256U;

	using cstring = const char*;

	export_ class refl_ MUD_GFX_EXPORT ImmediateDraw
	{
	public:
		ImmediateDraw(Material& material);

		struct Vertex
		{
			static const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Colour;
			vec3 m_position;
			uint32_t m_colour;
		};

		static bgfx::VertexDecl ms_vertex_decl;

		Material& m_material;

		struct Batch
		{
			//DrawMode m_draw_mode;
			vector<Vertex> m_vertices;
			vector<uint16_t> m_indices;
		};

		vector<Batch> m_batches[2];
		size_t m_cursor[2];

		void begin();

		Batch* batch(DrawMode draw_mode, size_t vertex_count);

		void shape(const mat4& transform, const ProcShape& shape);
		void draw(const mat4& transform, array<ProcShape> shapes);
		void draw(const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode);

		void draw(Batch& batch, const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode);

		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state);
		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode);
		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode, Batch& batch);
	};

	export_ class refl_ MUD_GFX_EXPORT SymbolIndex : public NonCopy
	{
	public:
		SymbolIndex();
		~SymbolIndex();

		Model& symbol_model(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		Material& symbol_material(GfxSystem& gfx_system, const Symbol& symbol, DrawMode draw_mode);

		struct Impl;
		unique<Impl> m_impl;
	};

	export_ MUD_GFX_EXPORT object<Model> draw_model(cstring name, const ProcShape& shape, bool readback = false);
	export_ MUD_GFX_EXPORT object<Model> draw_model(cstring name, const vector<ProcShape>& shapes, bool readback = false);

	export_ MUD_GFX_EXPORT void draw_model(const ProcShape& shape, Model& model, bool readback = false, Material* material = nullptr);
	export_ MUD_GFX_EXPORT void draw_model(const vector<ProcShape>& shapes, Model& model, bool readback = false, Material* material = nullptr);

	export_ MUD_GFX_EXPORT void draw_mesh(const ProcShape& shapes, Model& model, DrawMode draw_mode, bool readback = false, Material* material = nullptr);
	export_ MUD_GFX_EXPORT void draw_mesh(const vector<ProcShape>& shapes, Model& model, DrawMode draw_mode, bool readback = false, Material* material = nullptr);
	
	export_ MUD_GFX_EXPORT void draw_mesh(const vector<ProcShape>& shapes, Model& model, ShapeSize size, DrawMode draw_mode, bool readback = false, Material* material = nullptr);

}



namespace mud
{
	enum ShaderOptionResolve : unsigned int
	{
	};

	export_ class refl_ MUD_GFX_EXPORT BlockResolve : public GfxBlock
	{
	public:
		BlockResolve(GfxSystem& gfx_system, BlockCopy& copy);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		BlockCopy& m_copy;
	};

	export_ class MUD_GFX_EXPORT PassEffects : public RenderPass
	{
	public:
		PassEffects(GfxSystem& gfx_system);

		virtual void submit_render_pass(Render& render) final;
	};

	export_ class MUD_GFX_EXPORT PassPostProcess : public RenderPass
	{
	public:
		PassPostProcess(GfxSystem& gfx_system, BlockCopy& copy);

		virtual void submit_render_pass(Render& render) final;

		BlockCopy& m_copy;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ enum ShaderOptionFilter : unsigned int
	{
		FILTER_UNPACK_DEPTH,
		FILTER_SOURCE_DEPTH,
		FILTER_SOURCE_0_CUBE,
		FILTER_SOURCE_0_ARRAY,
		FILTER_DEBUG_UV,
	};

	export_ struct FilterUniform
	{
		void createUniforms()
		{
			s_source_0		= bgfx::createUniform("s_source_0",		bgfx::UniformType::Int1);
			s_source_1		= bgfx::createUniform("s_source_1",		bgfx::UniformType::Int1);
			s_source_2		= bgfx::createUniform("s_source_2",		bgfx::UniformType::Int1);
			s_source_3		= bgfx::createUniform("s_source_3",		bgfx::UniformType::Int1);
			s_source_depth	= bgfx::createUniform("s_source_depth",	bgfx::UniformType::Int1);

			u_source_0_level	 = bgfx::createUniform("u_source_0_level",		bgfx::UniformType::Int1);
			u_source_1_level	 = bgfx::createUniform("u_source_1_level",		bgfx::UniformType::Int1);
			u_source_2_level	 = bgfx::createUniform("u_source_2_level",		bgfx::UniformType::Int1);
			u_source_3_level	 = bgfx::createUniform("u_source_3_level",		bgfx::UniformType::Int1);
			u_source_depth_level = bgfx::createUniform("u_source_depth_level",	bgfx::UniformType::Int1);

			u_source_0_crop		 = bgfx::createUniform("u_source_0_crop",		bgfx::UniformType::Vec4);

			u_screen_size_pixel_size =		bgfx::createUniform("u_screen_size_pixel_size",		bgfx::UniformType::Vec4);
			u_camera_params =				bgfx::createUniform("u_camera_params",				bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle s_source_0;
		bgfx::UniformHandle s_source_1;
		bgfx::UniformHandle s_source_2;
		bgfx::UniformHandle s_source_3;
		bgfx::UniformHandle s_source_depth;

		bgfx::UniformHandle u_source_0_level;
		bgfx::UniformHandle u_source_1_level;
		bgfx::UniformHandle u_source_2_level;
		bgfx::UniformHandle u_source_3_level;
		bgfx::UniformHandle u_source_depth_level;

		bgfx::UniformHandle u_source_0_crop;

		bgfx::UniformHandle u_screen_size_pixel_size;
		bgfx::UniformHandle u_camera_params;
	};

	export_ class refl_ MUD_GFX_EXPORT Filter
	{
	public:
		virtual ~Filter() {}
	};

	export_ struct refl_ MUD_GFX_EXPORT RenderQuad
	{
		vec4 m_source;
		vec4 m_dest;
		bool m_fbo_flip = false;
		RenderQuad(vec4 crop, vec4 dest, bool fbo_flip = false) : m_source(crop), m_dest(dest), m_fbo_flip(fbo_flip) {}
		RenderQuad() {}
	};

	RenderQuad copy_quad(const FrameBuffer& target, const vec4& rect);

	//RenderQuad copy_quad(const FrameBuffer& source, const FrameBuffer& target, const vec4& source_rect, const vec4& dest_rect);
	
	export_ class refl_ MUD_GFX_EXPORT BlockFilter : public GfxBlock
	{
	public:
		BlockFilter(GfxSystem& gfx_system);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		void set_uniforms(Render& render, bgfx::Encoder& encoder);

		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags = 0U, bool render = false);

		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags = 0U, bool render = false);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, uint64_t flags = 0U, bool render = false);

		FilterUniform u_uniform;

		Program& m_quad_program;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockCopy : public GfxBlock
	{
	public:
		BlockCopy(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const uvec4& rect, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const uvec4& rect, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, uint64_t flags = 0U);

		void debug_show_texture(Render& render, bgfx::TextureHandle texture, const vec4& rect, bool is_depth = false, bool is_depth_packed = false, bool is_array = false, int level = 0);

		BlockFilter& m_filter;

		Program& m_program;
	};
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif


#include <stl/vector.h>


#ifndef MUD_MODULES
#endif

#if defined MUD_UNIFORM_BLOCKS


#if 0

#ifndef MUD_MODULES
#include <stl/string.h>
#endif

#include <bgfx/bgfx.h>

#include <algorithm>

namespace mud
{
	// @todo automatical definition of structs to uniforms using reflection
	// - vectors and floats are packed to Vec4 in the order they appear, adding padding if next vector is too big to fit
	// - enums are sent as a define switch using enum value label
	// - booleans are sent as a define switch using parameter name

	export_ struct MUD_GFX_EXPORT Uniform
	{
		Uniform(const string& name, size_t member, bgfx::UniformType::Enum type) : m_name(name), m_member(member), m_type(type), m_floats(16) {}

		string m_name;
		size_t m_member;
		bgfx::UniformType::Enum m_type;
		bgfx::UniformHandle m_uniform;
		vector<float> m_floats;

		struct Field
		{
			string m_name;
			size_t m_member;
			size_t m_size;
		};
		vector<Field> m_fields;
		size_t m_space = 4;

		void create()
		{
			m_uniform = bgfx::createUniform(m_name.c_str(), m_type);
		}

		template <class T>
		void upload(bgfx::Encoder& encoder, T& object)
		{
			if(m_fields.empty())
			{
				void* T::* mem = reinterpret_cast<void* T::*>(m_member.value);
				encoder.setUniform(m_uniform, &(object.*mem));
			}
			else
			{
				size_t offset = 0;
				for(Field& field : m_fields)
				{
					void* T::* mem = reinterpret_cast<void* T::*>(field.m_member.value);
					float* value = (float*) &(object.*mem);
					std::copy(value, value + field.m_size, m_floats.data() + offset);
					offset += field.m_size;
				}
				encoder.setUniform(m_uniform, m_floats.data());
			}
		}
	};

	export_ struct MUD_GFX_EXPORT Sampler
	{
		string m_name;
		size_t m_member;
		uint8_t m_stage;
		Texture* m_default;
		bgfx::UniformHandle m_uniform;

		void create()
		{
			m_uniform = bgfx::createUniform(m_name.c_str(), bgfx::UniformType::Int1);
		}

		template <class T>
		void upload(bgfx::Encoder& encoder, T& object)
		{
			void* T::* mem = reinterpret_cast<void* T::*>(m_member.value);
			Texture* texture = (Texture*)(object.*mem);
			encoder.setTexture(m_stage, m_uniform, texture ? texture->m_texture : m_default->m_texture);
		}
	};

	export_ struct MUD_GFX_EXPORT UniformBlock
	{
		UniformBlock(Type& type, const string& name);

		Type& m_type;
		string m_name;
		vector<Uniform> m_uniforms;
		vector<Sampler> m_samplers;
		string m_shader_decl;
		size_t m_num_packed = 0;

		void pack_member(size_t size, Member& member);
		void create_member(GfxSystem& gfx_system, const string& name, Member& member);
		string shader_decl();
		void create(GfxSystem& gfx_system);
	};
	
	template <class T>
	struct TypedUniformBlock : public UniformBlock
	{
		TypedUniformBlock(const string& name)
			: UniformBlock(type<T>(), name)
		{}

		void upload(T& object)
		{
			for(Uniform& uniform : m_uniforms)
				uniform.upload<T>(object);

			for(Sampler& sampler : m_samplers)
				sampler.upload<T>(object);
		}
	};
}
#endif
#endif

namespace mud
{
#if defined MUD_UNIFORM_BLOCKS
	export_ struct refl_ MUD_GFX_EXPORT FrustumBlock
	{
		attr_ float m_fov = 60.f;
		attr_ float m_aspect = 1.f;
		attr_ float m_near = 0.001f;
		attr_ float m_far = 100.f;

		static TypedUniformBlock<FrustumBlock> s_block;
	};
#endif

	export_ MUD_GFX_EXPORT Plane6 bounding_planes(const mat4& mat);
	export_ MUD_GFX_EXPORT Plane6 frustum_planes(const mat4& projection, const mat4& transform);
	export_ MUD_GFX_EXPORT Plane6 frustum_planes(const mat4& view, float fov, float aspect, float near, float far);
	export_ MUD_GFX_EXPORT Plane6 frustum_planes(const mat4& view, const vec2& rect, float near, float far);
	export_ MUD_GFX_EXPORT Point8 frustum_corners(const Plane6& planes);

	export_ MUD_GFX_EXPORT vec2 frustum_viewport_size(const mat4& projection);

	export_ class refl_ MUD_GFX_EXPORT Frustum
	{
	public:
		Frustum();
		Frustum(const mat4& transform, float fov, float aspect, float near, float far);
		Frustum(const mat4& transform, const vec2& rect, float near, float far);

		void compute();

		attr_ float m_fov = 60.f;
		attr_ float m_aspect = 1.f;
		attr_ float m_near;
		attr_ float m_far;

		Plane6 m_planes;
		Point8 m_corners;

		attr_ vec3 m_center;
		attr_ float m_radius;
	};

	export_ MUD_GFX_EXPORT Frustum optimized_frustum(Camera& camera, array<Item*> items);

	export_ struct refl_ MUD_GFX_EXPORT FrustumSlice
	{
		int m_index;
		Frustum m_frustum;
	};

	export_ MUD_GFX_EXPORT void split_frustum_slices(Camera& camera, array<FrustumSlice> slices, uint8_t num_splits, float split_distribution);
}

namespace mud
{
	export_ struct refl_ MUD_GFX_EXPORT ClusteredFrustum : public Frustum
	{
		uint16_t m_subdiv_x = 0;
		uint16_t m_subdiv_y = 0;
		uint16_t m_subdiv_z = 0;
		uint16_t m_cluster_count = 0;

		uvec2 m_tile_size = {};
		vec2 m_inv_tile_size = {};

		float m_linearizer = 0.f;
		float m_far_log2 = 0.f;
		vec2 m_clip_to_cluster = vec2(0.f);

		vector<float> m_distances_z;                // max 2.1 MiB (actual: resolution dependant)
		vector<vec4> m_planes_x;
		vector<vec4> m_planes_y;
		vector<vec4> m_bounding_spheres;

		uint16_t index(uint ix, uint iy, uint iz) const { return uint16_t(ix + (iy * m_subdiv_x) + (iz * m_subdiv_x * m_subdiv_y)); }

		uvec2 tile_index(const vec2& clip) const;
		uint slice(float z) const;

		Frustum cluster_frustum(uint x, uint y, uint z) const;

		void resize(const vec2& clip_size);
		void recompute(const mat4& projection, const vec2& clip_size);
	};

	export_ MUD_GFX_EXPORT void compute_frustum_subdiv(ClusteredFrustum& frustum, vec2 clip_size, size_t slices = 16);
	export_ MUD_GFX_EXPORT void compute_frustum_subdiv_square(ClusteredFrustum& frustum, vec2 clip_size, size_t slices = 16, size_t max_clusters = 8192);
}

#if defined MUD_UNIFORM_BLOCKS
#endif

namespace bgfx
{
	struct Encoder;
}

namespace mud
{
	constexpr uint32_t CONFIG_MAX_LIGHT_COUNT = 256;
	constexpr uint32_t CONFIG_MAX_LIGHT_INDEX = CONFIG_MAX_LIGHT_COUNT - 1;

	constexpr uint32_t CONFIG_FROXEL_SLICE_COUNT = 16;

	//
	// Light UBO           Froxel Record Buffer     per-froxel light list texture
	// {4 x vec4}         R_U8  {index into        RG_U16 {offset, point-count, spot-sount}
	// (spot/point            light texture}
	//
	//  +----+                     +-+                     +----+
	// 0|....| <------------+     0| |         +-----------|0221| (e.g. offset=02, 2-point, 1-spot)
	// 1|....|<--------+     \    1| |        /            |    |
	// 2:    :          \     +---2|0|<------+             |    |
	// 3:    : <-------- \--------3|3|                     :    :
	// 4:    :            +------- :1:                     :    :
	//  :    :                     : :                     :    :
	//  :    :                     | |                     |    |
	//  :    :                     | |                     |    |
	//  :    :                     +-+                     |    |
	//  :    :                  65536 max                  +----+
	//  |....|                                          h = num froxels
	//  |....|
	//  +----+
	// 256 lights max
	//

	// Max number of froxels limited by:
	// - max texture size [min 2048]
	// - chosen texture width [64]
	// - size of CPU-side indices [16 bits]
	// Also, increasing the number of froxels adds more pressure on the "record buffer" which stores
	// the light indices per froxel. The record buffer is limited to 65536 entries, so with
	// 8192 froxels, we can store 8 lights per froxels assuming they're all used. In practice, some
	// froxels are not used, so we can store more.
	static constexpr uint32_t FROXEL_BUFFER_ENTRY_COUNT_MAX = 8192;

	struct LightRecord
	{
#ifndef USE_STD_BITSET
		using Lights = bitset<uint64_t, (CONFIG_MAX_LIGHT_COUNT + 63) / 64>;
#else
		using Lights = std::bitset<CONFIG_MAX_LIGHT_COUNT>;
#endif
		Lights lights;
	};

	class MUD_GFX_EXPORT Froxelizer
	{
	public:
		Froxelizer();
		Froxelizer(GfxSystem& gfx_system);
		~Froxelizer();

		Froxelizer(Froxelizer&& other);
		Froxelizer& operator=(Froxelizer&& other);

		bool prepare(const Viewport& viewport, const mat4& projection, float near, float far);
		bool update(const Viewport& viewport, const mat4& projection, float near, float far);

		// update Records and Froxels texture with lights data. this is thread-safe.
		void froxelize_lights(const Camera& camera, array<Light*> lights);
		void froxelize_loop(const Camera& camera, array<Light*> lights);

		// send froxel data to GPU
		void upload();
		void submit(bgfx::Encoder& encoder) const;

		void compute_froxels();

		struct FroxelEntry
		{
			FroxelEntry() {}
			FroxelEntry(uint16_t offset, uint8_t point_count, uint8_t spot_count) : offset(offset), count{ point_count, spot_count } {}
			union
			{
				uint32_t u32 = 0;
				struct
				{
					uint16_t offset;
					uint8_t count[2];
				};
			};
		};

		bool update();
		void update_viewport();
		void update_projection();

		uint32_t record(uint32_t cluster);
		uint32_t count(uint32_t cluster, int type = 0);
		uint32_t light(uint32_t record);

		void froxelize_assign_records_compress(uint32_t num_lights);

		void froxelize_light_group(const Camera& camera, array<Light*> lights, uint32_t offset, uint32_t stride);

		GfxSystem& m_gfx_system;

		ClusteredFrustum m_frustum;

		vector<Frustum> m_debug_clusters;

		struct Impl;
		unique<Impl> m_impl;

		mat4 m_projection;

		// needed for update()
		const Viewport* m_viewport;
		vec4 m_params_z = {};
		uvec3 m_params_f = {};
		float m_near = 0.0f;        // camera near
		float m_light_far = 100.f;
		float m_light_near = 5.f;  // light near (first slice)

		// track if we need to update our internal state before froxelizing
		uint8_t m_dirty = 0;
		enum {
			VIEWPORT_CHANGED = 0x01,
			PROJECTION_CHANGED = 0x02
		};
	};

}


#ifndef MUD_MODULES
#include <stl/string.h>
#endif


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ enum class refl_ LightType : unsigned int
	{
		Direct,
		Point,
		Spot,
		Count
	};

	export_ enum refl_ ShadowFlags : unsigned int
	{
		CSM_Stabilize = 1 << 0,
		CSM_Optimize = 1 << 1,
		CSM_BlendSplits = 1 << 2
	};

	export_ class refl_ MUD_GFX_EXPORT Light
	{
	public:
		Light(Node3& node, LightType type = LightType::Point, bool shadows = false);
		~Light();

		attr_ Node3& m_node;

		attr_ LightType m_type = LightType::Point;
		attr_ bool m_visible = true;
		attr_ Colour m_colour = Colour::White;
		attr_ float m_range = 1.f;
		attr_ float m_energy = 1.f;
		attr_ float m_specular = 0.5f;
		attr_ float m_attenuation = 0.5f;
		attr_ bool m_shadows = false;
		attr_ Colour m_shadow_colour = Colour::Black;
		attr_ float m_shadow_range = 100.f;
		attr_ uint32_t m_layers = 0xFFFFFFFF;

		attr_ uint32_t m_last_render = 0;
		attr_ uint32_t m_last_update = 0;

		// spotlight
		attr_ float m_spot_angle = 45.f;
		attr_ float m_spot_attenuation = 0.5f;

		attr_ ShadowFlags m_shadow_flags = ShadowFlags(0 | CSM_Optimize);
		attr_ uint8_t m_shadow_num_splits = 1;
		attr_ float m_shadow_split_distribution = 0.6f;

		attr_ float m_shadow_normal_bias = 0.1f;
		attr_ float m_shadow_bias = 0.f;

		size_t m_shot_index = 0;
	};
}

namespace mud
{
namespace gfx
{
	export_ MUD_GFX_EXPORT func_ void update_item_lights(Item& item);
	export_ MUD_GFX_EXPORT func_ void update_item_aabb(Item& item);

	export_ MUD_GFX_EXPORT func_ Gnode& node(Gnode& parent, Ref object = {}, const vec3& position = Zero3, const quat& rotation = ZeroQuat, const vec3& scale = Unit3);
	export_ MUD_GFX_EXPORT Gnode& node(Gnode& parent, Ref object, const mat4& transform);
	export_ MUD_GFX_EXPORT Gnode& node(Gnode& parent, Ref object, const Transform& transform);
	export_ MUD_GFX_EXPORT Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale);
	export_ MUD_GFX_EXPORT Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation);
	export_ MUD_GFX_EXPORT func_ Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT void draw(Scene& scene, const mat4& transform, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	export_ MUD_GFX_EXPORT func_ void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	export_ MUD_GFX_EXPORT func_ Item& sprite(Gnode& parent, const Image256& image, const vec2& size, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Item& item(Gnode& parent, const Model& model, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0, array<mat4> transforms = {});
	export_ MUD_GFX_EXPORT func_ void prefab(Gnode& parent, const Prefab& prefab, bool transform = true, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0, array<mat4> transforms = {});
	export_ MUD_GFX_EXPORT func_ Item* model(Gnode& parent, const string& name, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Animated& animated(Gnode& parent, Item& item);
	export_ MUD_GFX_EXPORT func_ Particles& particles(Gnode& parent, const ParticleFlow& emitter, uint32_t flags = 0, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Light& light(Gnode& parent, LightType type, bool shadows, Colour colour, float range = 0.f, float attenuation = 0.5f);
	export_ MUD_GFX_EXPORT func_ Light& sun_light(Gnode& parent, float azimuth, float elevation);
	export_ MUD_GFX_EXPORT func_ void radiance(Gnode& parent, const string& texture, BackgroundMode background);

	using ManualJob = void(*)(Render&, const Pass&);
	using CustomSky = void(*)(Render&);

	export_ MUD_GFX_EXPORT void manual_job(Gnode& parent, PassType pass, ManualJob job);
	export_ MUD_GFX_EXPORT void custom_sky(Gnode& parent, CustomSky func);

	export_ MUD_GFX_EXPORT Light& direct_light_node(Gnode& parent);
	export_ MUD_GFX_EXPORT Light& direct_light_node(Gnode& parent, const quat& rotation);
	export_ MUD_GFX_EXPORT Light& direct_light_node(Gnode& parent, const vec3& direction);

	export_ MUD_GFX_EXPORT Material& pbr_material(GfxSystem& gfx, cstring name, const PbrMaterialBlock& pbr_block);
	export_ MUD_GFX_EXPORT Material& pbr_material(GfxSystem& gfx, cstring name, const Colour& albedo, float metallic = 0.f, float roughness = 1.f);
}
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#endif
#ifndef MUD_BGFX_EXPORT
#define MUD_BGFX_EXPORT MUD_GFX_EXPORT
#endif

namespace bx
{
	struct FileReaderI;
	struct FileWriterI;
}

namespace bgfx
{
	struct Encoder;
}

namespace mud
{
	class Vg;

	export_ class refl_ MUD_GFX_EXPORT GfxContext : public BgfxContext
	{
	public:
		GfxContext(GfxSystem& gfx_system, const string& name, int width, int height, bool fullScreen, bool init);
		~GfxContext();

		virtual void reset(uint16_t width, uint16_t height) override;

		GfxSystem& m_gfx_system;

		object<RenderTarget> m_target;

		uint16_t m_vg_handle = UINT16_MAX;
		using ResetVg = uint16_t(*)(GfxContext&, Vg&); ResetVg m_reset_vg;

		vector<Viewport*> m_viewports;
	};

	template <class T_Asset>
	class TPool;

	template <class T_Asset>
	class AssetStore;

	export_ struct LocatedFile
	{
		LocatedFile() {}
		LocatedFile(string location, string name, string extension, size_t extension_index)
			: m_located(true), m_location(location), m_name(name), m_extension(extension), m_extension_index(extension_index)
		{}
		bool m_located = false;
		string m_location;
		string m_name;
		string m_extension;
		size_t m_extension_index = 0;
		string path(bool ext) { return m_location + "/" + m_name + (ext ? m_extension : ""); }
		explicit operator bool() { return m_located; }
	};

	export_ class refl_ MUD_GFX_EXPORT GfxSystem : public BgfxSystem
	{
	public:
		constr_ GfxSystem(const string& resource_path);
		~GfxSystem();

		JobSystem* m_job_system = nullptr;
		Vg* m_vg = nullptr;

		bgfx::Encoder* m_encoders[8] = {};
		size_t m_num_encoders = 0;

		virtual void begin_frame() final;
		virtual bool next_frame() final;

		virtual object<Context> create_context(const string& name, int width, int height, bool full_screen) final;

		void init(GfxContext& context);

		using PipelineDecl = void(*)(GfxSystem& gfx_system, Pipeline& pipeline, bool deferred);
		void init_pipeline(PipelineDecl pipeline);

		meth_ void default_pipeline();

		meth_ void add_resource_path(const string& path, bool relative = true);

		void set_renderer(Shading shading, Renderer& renderer);
		Renderer& renderer(Shading shading);

		void render(Renderer& renderer, GfxContext& context, Viewport& viewport, RenderFrame& frame);
		RenderFrame render_frame();

		GfxContext& context(size_t index = 0);

		bx::FileReaderI& file_reader();
		bx::FileWriterI& file_writer();

		LocatedFile locate_file(const string& file);
		LocatedFile locate_file(const string& file, array<string> extensions);

		TPool<Mesh>& meshes();
		TPool<Rig>& rigs();
		TPool<Animation>& animations();

		attr_ AssetStore<Texture>& textures();
		attr_ AssetStore<Program>& programs();
		attr_ AssetStore<Material>& materials();
		attr_ AssetStore<Model>& models();
		attr_ AssetStore<ParticleFlow>& particles();
		attr_ AssetStore<Prefab>& prefabs();

		void add_importer(ModelFormat format, Importer& importer);
		Importer* importer(ModelFormat format);

		Texture& default_texture(TextureHint hint);

		meth_ Material& debug_material();
		meth_ Material& fetch_material(const string& name, const string& shader, bool builtin = true);
		meth_ Material& fetch_image256_material(const Image256& image);

		meth_ Model& fetch_symbol(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		meth_ Material& fetch_symbol_material(const Symbol& symbol, DrawMode draw_mode);

		void create_debug_materials();

	public:
		struct Impl;
		unique<Impl> m_impl;

		unique<Pipeline> m_pipeline;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	class SoundManager;
	class Sound;

	export_ class refl_ MUD_GFX_EXPORT Gnode : public Graph<Gnode>
	{
	public:
		Gnode();
		Gnode(Scene& scene, SoundManager* sound_manager = nullptr);
		Gnode(Gnode* parent, void* identity);
		~Gnode();
		
		void clear();

		// @todo fix this shit by making each node contain one object from one pool and destroy it with that pool
		Scene* m_scene = nullptr;
		Node3* m_attach = nullptr;
		Node3* m_node = nullptr;
		Item* m_item = nullptr;
		Animated* m_animated = nullptr;
		Particles* m_particles = nullptr;
		Light* m_light = nullptr;
		GIProbe* m_gi_probe = nullptr;
		LightmapAtlas* m_lightmap_atlas = nullptr;
		SoundManager* m_sound_manager = nullptr;
		Sound* m_sound = nullptr;
	};

	export_ MUD_GFX_EXPORT void debug_tree(Gnode& node, size_t index = 0, size_t depth = 0);
}





#ifndef MUD_MODULES
#include <stl/function.h>
#endif


#include <stl/vector.h>

#include <bgfx/bgfx.h>

class MaskedOcclusionCulling;

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT Culler
	{
	public:
		Culler(Viewport& viewport);
		~Culler();

		attr_ Viewport* m_viewport;

		MaskedOcclusionCulling* m_moc = nullptr;

		void render(Render& render);

		void begin(Viewport& viewport);
		void rasterize(Render& render);
		void cull(Render& render);
		void debug(Render& render);

		vector<float> m_depth_data;
		bgfx::TextureHandle m_depth_texture = BGFX_INVALID_HANDLE;
	};
}

namespace mud
{
	using cstring = const char*;

	export_ enum class refl_ MSAA : unsigned int
	{
		Disabled,
		X2,
		X4,
		X8,
		X16,
	};

	export_ enum class refl_ Shading : unsigned int
	{
		Wireframe,
		Unshaded,
		Shaded,
		Volume,
		Voxels,
		Lightmap,
		Clear,

		Count
	};

	export_ extern MUD_GFX_EXPORT GridECS* g_viewer_ecs;

	export_ class refl_ MUD_GFX_EXPORT Viewport : public Entt
	{
	public:
		Viewport(Camera& camera, Scene& scene, uvec4 rect = {}, bool scissor = false);
		~Viewport();

		attr_ Camera* m_camera;
		attr_ Scene* m_scene;

		attr_ uint16_t m_index = 0;
		attr_ bool m_active = true;
		attr_ uvec4 m_rect = uvec4(0U);
		attr_ bool m_scissor = false;
		attr_ Colour m_clear_colour = Colour::Black;
		attr_ Shading m_shading = Shading::Shaded;
		attr_ Lighting m_lighting = Lighting::Clustered;

		using RenderTask = function<void(Render&)>;
		vector<RenderTask> m_tasks;
		
		Culler m_culler;

		void render_pass(cstring name, const Pass& render_pass);

		void cull(Render& render);
		void render(Render& render);

		Ray ray(const vec2& pos);
		vec3 raycast(const Plane& plane, const vec2& pos);
	};
}

namespace mud
{
	export_ struct MUD_GFX_EXPORT ManualRender
	{
		ManualRender(Render& render, Shading shading, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect);
		ManualRender(Render& render, Shading shading, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection, bool ortho = false);

		void render(Renderer& renderer);

		Render& m_render;
		Camera m_camera;
		Viewport m_viewport;
		Render m_sub_render;
	};
}


#ifndef MUD_MODULES
#include <stl/function.h>
#include <stl/vector.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
#define PICKING_BUFFER_SIZE 8  // Size of the ID buffer

	using PickCallback = function<void(Item*)>;
	using MultipickCallback = function<void(array<Item*>)>;

	export_ struct PickQuery
	{
		PickQuery() {}
		PickQuery(uvec4 rect, Ray ray, float fov, float aspect, uint32_t mask)
			: m_rect(rect), m_center_ray(ray), m_fov(fov), m_aspect(aspect), m_mask(mask)
		{}

		uvec4 m_rect = uvec4(0U);
		Ray m_center_ray = {};
		float m_fov = 0.f;
		float m_aspect = 0.f;
		uint32_t m_mask = UINT32_MAX;

		uint32_t m_readback_ready = UINT32_MAX;

		PickCallback m_callback;
		MultipickCallback m_multi_callback;

		operator bool() const { return m_rect != uvec4(0U); }
	};

	export_ class MUD_GFX_EXPORT Picker
	{
	public:
		Picker(GfxSystem& system, FrameBuffer& target);
		~Picker();

		void pick_point(Viewport& viewport, vec2 position, PickCallback callback, uint32_t mask);
		void pick_rectangle(Viewport& viewport, vec4 rect, MultipickCallback callback, uint32_t mask);

		void process(Render& render, PickQuery& query);

		FrameBuffer& m_target;
		uvec2 m_size;

		Program& m_program;

		PickQuery m_query;

		bgfx::UniformHandle u_picking_id;

		bgfx::FrameBufferHandle m_fbo;
		bgfx::TextureHandle m_fbo_texture;

		bgfx::TextureHandle m_readback_texture = BGFX_INVALID_HANDLE;

		vector<uint32_t> m_data;
	};
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/function.h>
#endif

namespace mud
{
	using PassJob = function<void(Render&, const Pass&)>;

	export_ MUD_GFX_EXPORT void pipeline_minimal(GfxSystem& gfx_system, Pipeline& pipeline, bool deferred);

	export_ struct MUD_GFX_EXPORT PassJobs
	{
		enum_array<PassType, vector<PassJob>> m_jobs;
	};

	export_ class MUD_GFX_EXPORT Pipeline : public NonCopy
	{
	public:
		Pipeline(GfxSystem& gfx_system);
		~Pipeline();

		using GatherFunc = void(*)(Scene&, Render&);
		GatherFunc m_gather_func;

		template <class T_Block>
		T_Block* block() { for(auto& block : m_gfx_blocks) if(&(block->m_type) == &type<T_Block>()) return &as<T_Block>(*block); return nullptr; }

		template <class T_Block, class... T_Args>
		T_Block& add_block(T_Args&&... args) { m_gfx_blocks.push_back(make_unique<T_Block>(static_cast<T_Args&&>(args)...)); return as<T_Block>(*m_gfx_blocks.back()); }

		array<GfxBlock*> pass_blocks(PassType pass);

		vector<unique<GfxBlock>> m_gfx_blocks;

		enum_array<PassType, vector<GfxBlock*>> m_pass_blocks;
	};

	export_ class MUD_GFX_EXPORT PassClear : public RenderPass
	{
	public:
		PassClear(GfxSystem& gfx_system);

		virtual void submit_render_pass(Render& render) final;
	};

	export_ class MUD_GFX_EXPORT PassUnshaded : public DrawPass
	{
	public:
		PassUnshaded(GfxSystem& gfx_system);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_EXPORT PassBackground : public RenderPass
	{
	public:
		PassBackground(GfxSystem& gfx_system);

		virtual void submit_render_pass(Render& render) final;
	};

	export_ class MUD_GFX_EXPORT PassFlip : public RenderPass
	{
	public:
		PassFlip(GfxSystem& gfx_system, BlockCopy& copy);

		virtual void submit_render_pass(Render& render) final;

		BlockCopy& m_copy;
	};

	struct MinimalRenderer : public Renderer
	{
		MinimalRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct UnshadedRenderer : public Renderer
	{
		UnshadedRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct ClearRenderer : public Renderer
	{
		ClearRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};
}


#ifndef MUD_MODULES
#endif

#ifdef MUD_UNIFORM_BLOCKS
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	export_ MUD_GFX_EXPORT vec4 fbo_dest_quad(const uvec2& size, const vec4& rect, bool origin_fbo = false);
	export_ MUD_GFX_EXPORT vec4 fbo_source_quad(const uvec2& size, const vec4& rect, bool origin_fbo = false);

#ifdef MUD_UNIFORM_BLOCKS
	export_ struct refl_ MUD_GFX_EXPORT RenderBlock
	{
		attr_ vec2 m_render_size;
		attr_ vec2 m_pixel_size;

		static TypedUniformBlock<RenderBlock> s_block;
	};
#endif

	export_ class refl_ MUD_GFX_EXPORT FrameBuffer
	{
	public:
		FrameBuffer(uvec2 size);
		FrameBuffer(uvec2 size, bgfx::TextureFormat::Enum format, uint32_t textureFlags);
		FrameBuffer(uvec2 size, bgfx::FrameBufferHandle fbo);
		~FrameBuffer();

		uvec2 m_size;
		bgfx::FrameBufferHandle m_fbo;

		mat4 m_screen_view;
		mat4 m_screen_proj;

		vec4 dest_quad(const vec4& rect, bool origin_fbo = false) const { return fbo_dest_quad(m_size, rect, origin_fbo); }
		vec4 source_quad(const vec4& rect, bool origin_fbo = false) const { return fbo_source_quad(m_size, rect, origin_fbo); }

		vec4 dest_quad(bool origin_fbo = false) const { return dest_quad(vec4(vec2(0.f), vec2(m_size)), origin_fbo); }
		vec4 source_quad(bool origin_fbo = false) const { return source_quad(vec4(vec2(0.f), vec2(m_size)), origin_fbo); }

		vec4 dest_quad_mip(const vec4& rect, int level, bool origin_fbo = false) const { return fbo_dest_quad({ m_size.x >> level, m_size.y >> level }, rect, origin_fbo); }
		vec4 source_quad_mip(const vec4& rect, int level, bool origin_fbo = false) const { return fbo_source_quad({ m_size.x >> level, m_size.y >> level }, rect, origin_fbo); }

#ifdef MUD_UNIFORM_BLOCKS
		RenderBlock m_render_block;
#endif
	};

	export_ struct SwapBuffer
	{
		void create(uvec2 size, bgfx::TextureFormat::Enum color_format);
		~SwapBuffer();
		bgfx::FrameBufferHandle swap() { m_state = !m_state; return m_state ? m_one : m_two; }
		bgfx::TextureHandle last() { return m_state ? bgfx::getTexture(m_one) : bgfx::getTexture(m_two); }
		bgfx::FrameBufferHandle m_one;
		bgfx::FrameBufferHandle m_two;
		bool m_state = false;
	};

	export_ struct Cascade
	{
		void create(uvec2 size, bgfx::TextureFormat::Enum color_format);
		~Cascade();
		bgfx::FrameBufferHandle m_fbo;
		bgfx::TextureHandle m_texture;
		size_t m_num_mips;
		unique<FrameBuffer> m_mips[9] = {};
	};

	export_ class refl_ MUD_GFX_EXPORT RenderTarget : public FrameBuffer
	{
	public:
		RenderTarget(uvec2 size);
		~RenderTarget();

		MSAA m_msaa = MSAA::Disabled;

		bool m_mrt = true;
		bgfx::FrameBufferHandle m_fbo;

		bgfx::TextureHandle m_depth;
		bgfx::TextureHandle m_diffuse;

		bgfx::TextureHandle m_specular;
		bgfx::TextureHandle m_normal_rough;
		bgfx::TextureHandle m_sss;

		SwapBuffer m_ping_pong;
		SwapBuffer m_post_process;

		Cascade m_cascade;

		bool m_deferred = false;

		struct
		{
			bgfx::FrameBufferHandle m_fbo;

			bgfx::TextureHandle m_depth;
			bgfx::TextureHandle m_position;
			bgfx::TextureHandle m_normal;
			bgfx::TextureHandle m_albedo;
			bgfx::TextureHandle m_surface;

		} m_gbuffer;
	};
}


#ifndef MUD_MODULES
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	export_ struct refl_ Sun
	{
		attr_ float azimuth;
		attr_ float elevation;
		attr_ Colour m_colour = { 0.8f, 0.8f, 0.0f };
		attr_ float m_intensity = 0.f;
	};

	export_ struct refl_ Radiance
	{
		attr_ float m_energy = 1.0f;
		attr_ float m_ambient = 1.0f;
		attr_ Colour m_colour = Colour::Black;
		attr_ Texture* m_texture = nullptr;
		bgfx::TextureHandle m_roughness_array = BGFX_INVALID_HANDLE;
		bool m_preprocessed = false;
	};

	export_ enum class refl_ BackgroundMode : unsigned int
	{
		None,
		Panorama,
		Radiance,
		Custom
	};

	export_ struct refl_ Background
	{
		attr_ BackgroundMode m_mode = BackgroundMode::None;
		attr_ Colour m_colour = Colour::Black;
		attr_ Program* m_custom_program = nullptr;
		using CustomRender = void(*)(Render&); CustomRender m_custom_function;
	};

	export_ struct refl_ Fog
	{
		attr_ bool m_enabled = false;
		attr_ float m_density = 0.01f;
		attr_ Colour m_colour = Colour::White;

		attr_ bool m_depth = false;
		attr_ float m_depth_begin = 0.f;
		attr_ float m_depth_curve = 1.f;

		attr_ bool m_height = false;
		attr_ float m_height_min = 0.f;
		attr_ float m_height_max = 1.f;
		attr_ float m_height_curve = 0.1f;

		attr_ bool m_transmit = false;
		attr_ float m_transmit_curve = 1.f;
	};

	export_ struct refl_ Environment
	{
		attr_ Background m_background;
		attr_ Radiance m_radiance;
		attr_ Sun m_sun;
		attr_ Fog m_fog;
	};

	class Shot;

	export_ class refl_ MUD_GFX_EXPORT Scene : public NonCopy
	{
	public:
		Scene(GfxSystem& gfx_system);
		~Scene();

		GfxSystem& m_gfx_system;

		object<ImmediateDraw> m_immediate;
		object<ParticleSystem> m_particle_system;
		object<PassJobs> m_pass_jobs;

		unique<ObjectPool> m_pool;

		attr_ Gnode m_graph;
		attr_ Node3 m_root_node;
		attr_ Environment m_environment;
		attr_ Ref m_user;

		meth_ Gnode& begin();
		void update();

		void debug_items(Render& render);

		vector<Sound*> m_orphan_sounds;
	};

	export_ MUD_GFX_EXPORT void cull_items(Scene& scene, const Plane6& planes, vector<Item*>& items);

	export_ MUD_GFX_EXPORT void gather_items(Scene& scene, const Camera& camera, vector<Item*>& items);
	export_ MUD_GFX_EXPORT void gather_occluders(Scene& scene, const Camera& camera, vector<Item*>& occluders);
	export_ MUD_GFX_EXPORT void gather_lights(Scene& scene, vector<Light*>& lights);

	export_ MUD_GFX_EXPORT void gather_render(Scene& scene, Render& render);
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT Shot
	{
	public:
		vector<Item*> m_items;
		vector<Item*> m_occluders;
		vector<Light*> m_lights;
		vector<ReflectionProbe*> m_reflection_probes;
		vector<GIProbe*> m_gi_probes;
		vector<LightmapAtlas*> m_lightmaps;
		vector<ImmediateDraw*> m_immediate;
	};
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <stdint.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationTarget>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::CullMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::EmitterFlow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Interpolation>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::IsometricAngle>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ItemShadow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::LightType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Lighting>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MSAA>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialFlag>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ModelFormat>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Month>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrDiffuseMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrSpecularMode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Shading>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>();
    
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Animated>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Animation>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Material>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Model>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::ParticleFlow>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Prefab>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Program>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Texture>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Background>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BaseMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Bone>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Camera>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Culler>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DepthParams>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Environment>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Filter>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Fog>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::FresnelMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Frustum>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Gnode>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ImportConfig>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Item>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Joint>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Light>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Material>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<float>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::Colour>>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Mesh>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Model>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ModelItem>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Node3>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ParticleFlow>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::PbrMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Prefab>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Program>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Radiance>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::RenderFrame>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::RenderQuad>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Rig>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Scene>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Shot>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Skeleton>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Skin>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Sun>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::SymbolIndex>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Texture>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::UnshadedMaterialBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Viewport>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::ClusteredFrustum>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::Particles>();
    export_ template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>();
    
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Animated*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AnimatedTrack*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Animation*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AnimationPlay*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AnimationTrack*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Material>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Model>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::ParticleFlow>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Prefab>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Program>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::AssetStore<mud::Texture>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Background*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BaseMaterialBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Bone*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Camera*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Culler*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::DepthParams*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Environment*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Filter*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Fog*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::FrameBuffer*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::FresnelMaterialBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Frustum*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::FrustumSlice*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::GfxBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::GfxContext*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::GfxSystem*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Gnode*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ImmediateDraw*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ImportConfig*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Item*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Joint*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Light*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Material*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::MaterialParam<float>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::MaterialParam<mud::Colour>*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Mesh*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Model*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ModelItem*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Node3*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ParticleFlow*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::PbrMaterialBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Prefab*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Program*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Radiance*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::RenderFrame*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::RenderQuad*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Rig*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Scene*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Shot*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Skeleton*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Skin*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Sun*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::SymbolIndex*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Texture*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::UnshadedMaterialBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Viewport*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockCopy*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::DrawBlock*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockDepth*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockFilter*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockParticles*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockResolve*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::BlockSky*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::ClusteredFrustum*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::Particles*>>();
    export_ template <> MUD_GFX_EXPORT Type& type<vector<mud::RenderTarget*>>();
}
//s#include <gfx/Uniform.h>



#ifndef MUD_CPP_20
#include <stl/map.h>
#endif

namespace mud
{
	export_ enum class refl_ Month : unsigned int
	{
		January = 0,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};

	MUD_GFX_EXPORT quat sun_rotation(float azimuth, float altitude, const vec3& up = Y3, const vec3& north = X3);
	MUD_GFX_EXPORT quat sun_rotation(Month month, float latitude, float hour, float ecliptic_obliquity = 0.408407f, const vec3& up = Y3, const vec3& north = X3);

	export_ class refl_ MUD_GFX_EXPORT BlockSky : public GfxBlock
	{
	public:
		BlockSky(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		BlockFilter& m_filter;

		struct SkyboxUniform
		{
			void createUniforms()
			{
				u_skybox_matrix = bgfx::createUniform("u_skybox_matrix", bgfx::UniformType::Mat4);
				u_skybox_params = bgfx::createUniform("u_skybox_params", bgfx::UniformType::Vec4);
				s_skybox_map = bgfx::createUniform("s_skybox_map", bgfx::UniformType::Int1);
			}

			bgfx::UniformHandle u_skybox_matrix;
			bgfx::UniformHandle u_skybox_params;
			bgfx::UniformHandle s_skybox_map;

		} u_skybox;

		Program& m_skybox_program;
	};
}



#ifndef MUD_MODULES
//#include <srlz/Serial.h>
#endif

#include <cstdio>

namespace mud
{
	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, const string& path)
		: m_gfx_system(gfx_system)
		, m_path(path)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, const string& path, const Loader& loader)
		: m_gfx_system(gfx_system)
		, m_path(path)
		, m_loader(loader)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, const string& path, const string& format)
		: m_gfx_system(gfx_system)
		, m_path(path)
	{
		UNUSED(format);
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::add_format(const string& format, const Loader& loader)
	{
		m_formats.push_back(format);
		m_format_loaders.push_back(loader);
	}

	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::get(const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
			return nullptr;
		return m_assets[name].get();
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::create(const string& name)
	{
		if(m_assets.find(name) != m_assets.end())
			printf("WARNING: creating asset of already existing name: previous asset deleted\n");
		m_assets[name] = make_unique<T_Asset>(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::destroy(const string& name)
	{
		m_assets[name] = nullptr;
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::fetch(const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
			return this->create(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::file_at(const string& path, const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
		{
			m_assets[name] = make_unique<T_Asset>(name);
			m_loader(*m_assets[name], path + "/" + name);
		}
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::file(const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
		{
			string filename = m_path + string(name);
			LocatedFile location = m_formats.size() > 0 ? m_gfx_system.locate_file(filename, m_formats)
														: m_gfx_system.locate_file(filename);

			if(!location)
				return nullptr;

			m_assets[name] = make_unique<T_Asset>(name);
			Loader& loader = m_formats.size() > 0 ? m_format_loaders[location.m_extension_index] : m_loader;
			loader(*m_assets[name], location.path(false));
		}
		return m_assets[name].get();
	}
	
	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::load(const string& path, const string& file)
	{
		string filename = file;
		for(size_t i = 0; i < m_formats.size(); ++i)
			if(filename.find(m_formats[i]) != string::npos)
			{
				string name = filename.substr(0, filename.size() - m_formats[i].size());
				T_Asset& asset = this->create(name);
				m_format_loaders[i](asset, path + "/" + name);
				return &asset;
			}
		return nullptr;
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::load_files(const string& path)
	{
		auto visit_file = [&](const string& file)
		{
			this->load(path, file);
		};

		auto visit_folder = [&](const string& folder)
		{
			this->load_files(path + "/" + folder);
		};

		visit_files(path, visit_file);
		visit_folders(path, visit_folder);
	}
}

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <stl/unordered_set.h>

namespace stl
{
	using namespace mud;
	export_ extern template class vector<Texture*>;
	export_ extern template class vector<Material*>;
	export_ extern template class vector<Animation*>;
	export_ extern template class vector<Rig*>;
	export_ extern template class vector<Light*>;
	export_ extern template class vector<Mesh*>;
	export_ extern template class vector<Model*>;
	export_ extern template class vector<Animated*>;
	export_ extern template class vector<Particles*>;
	export_ extern template class vector<Item*>;
	export_ extern template class vector<Sound*>;
	export_ extern template class vector<Node3*>;
	export_ extern template class vector<ReflectionProbe*>;
	export_ extern template class vector<GIProbe*>;
	export_ extern template class vector<LightmapAtlas*>;
	export_ extern template class vector<ImmediateDraw*>;
	export_ extern template class vector<Scene*>;
	export_ extern template class vector<Viewport*>;
	export_ extern template class vector<Importer*>;
	export_ extern template class vector<Renderer*>;
	export_ extern template class vector<GfxBlock*>;
	export_ extern template class vector<DrawBlock*>;
	export_ extern template class vector<GfxContext*>;
	export_ extern template class vector<GfxSystem*>;
	export_ extern template class vector<Vertex>;
	export_ extern template class vector<ShapeVertex>;
	export_ extern template class vector<Tri>;
	export_ extern template class vector<ModelItem>;
	export_ extern template class vector<Item>;
	export_ extern template class vector<Node3>;
	export_ extern template class vector<Bone>;
	export_ extern template class vector<Joint>;
	export_ extern template class vector<Skin>;
	export_ extern template class vector<ShaderDefine>;
	export_ extern template class vector<PassJob>;
	export_ extern template class vector<AnimationTrack>;
	export_ extern template class vector<AnimationTrack::Key>;
	export_ extern template class vector<AnimationPlay>;
	export_ extern template class vector<AnimatedTrack>;
	export_ extern template class vector<Particle>;
	export_ extern template class vector<Viewport::RenderTask>;
	export_ extern template class vector<ImmediateDraw::Batch>;
	export_ extern template class vector<ImmediateDraw::Vertex>;
	export_ extern template class vector<Import::Item>;
	export_ extern template class vector<DrawElement>;
	export_ extern template class vector<ProcShape>;
	export_ extern template class vector<Frustum>;
	export_ extern template class vector<Froxelizer>;
	export_ extern template class vector<LightRecord>;
	export_ extern template class vector<Froxelizer::FroxelEntry>;
	export_ extern template class vector<carray<uint, 8193>>;
	export_ extern template class vector<unique<Gnode>>;
	export_ extern template class vector<unique<RenderPass>>;
	export_ extern template class vector<unique<GfxBlock>>;
	export_ extern template class vector<unique<Picker>>;
	export_ extern template class unordered_map<int, Skeleton*>;
	export_ extern template class unordered_set<Model*>;
	export_ extern template class vector<function<void(Texture&, const string&)>>;
	export_ extern template class vector<function<void(Material&, const string&)>>;
	export_ extern template class vector<function<void(Program&, const string&)>>;
	export_ extern template class vector<function<void(Model&, const string&)>>;
	export_ extern template class vector<function<void(ParticleFlow&, const string&)>>;
	export_ extern template class vector<function<void(Prefab&, const string&)>>;
	export_ extern template class unordered_map<string, unique<Texture>>;
	export_ extern template class unordered_map<string, unique<Material>>;
	export_ extern template class unordered_map<string, unique<Program>>;
	export_ extern template class unordered_map<string, unique<Model>>;
	export_ extern template class unordered_map<string, unique<ParticleFlow>>;
	export_ extern template class unordered_map<string, unique<Prefab>>;
	export_ extern template class unordered_map<uint, uint>;
	export_ extern template class unordered_map<uint64_t, Program::Version>;

	export_ extern template class vector<bgfx::InstanceDataBuffer>;
	export_ extern template class unordered_map<uint, bgfx::VertexDecl>;
}

