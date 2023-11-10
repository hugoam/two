#pragma once

#include <two/pool.h>
#include <two/geom.h>
#include <two/ctx.glfw.h>
#include <two/jobs.h>
#include <two/tree.h>
#include <two/bgfx.h>
#include <two/ecs.h>
#include <two/math.h>
#include <two/ctx.h>
#include <two/infra.h>
#include <two/type.h>



#ifndef TWO_MODULES
#endif



#ifndef TWO_GFX_EXPORT
#define TWO_GFX_EXPORT TWO_IMPORT
#endif

namespace two
{
	enum class AnimTarget : unsigned int;
    enum class Interpolation : unsigned int;
    enum class TextureHint : unsigned int;
    enum class ShaderType : unsigned int;
	enum class ShaderColor : unsigned int;
    enum ShaderOption : unsigned int;
    enum class TextureSampler : unsigned int;
    enum class PassType : unsigned int;
    enum class BlendMode : unsigned int;
    enum class CullMode : unsigned int;
    enum class DepthDraw : unsigned int;
    enum class DepthTest : unsigned int;
	enum class DepthMethod : unsigned int;
    enum class MaterialFlag : unsigned int;
	enum class TextureFormat : unsigned int;
    enum class TextureChannel : unsigned int;
	enum class MaterialBlock : unsigned int;
	enum class Lighting : unsigned int;
    enum class PbrDiffuseMode : unsigned int;
    enum class PbrSpecularMode : unsigned int;
	enum class PhongEnvBlendMode : unsigned int;
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

	struct AnimNode;
	struct AnimCursor;
	struct AnimPlay;
    class AnimTrack;
    class Animation;
    class Node3;
    class Skeleton;
    struct Joint;
    class Skin;
    class Rig;
    class Mime;
	struct MirrorCamera;
    class GfxWindow;
    struct LocatedFile;
    class GfxSystem;
    class Texture;
    struct ShaderDefine;
    struct ShaderBlock;
	struct ProgramMode;
    struct ProgramBlock;
    class Program;
    struct ProgramVersion;
    struct Pass;
    struct RenderFrame;
    struct Render;
    class GfxBlock;
    class DrawBlock;
    struct DrawElement;
	struct DrawCluster;
    class Renderer;
    struct MaterialBase;
	struct MaterialAlpha;
    struct MaterialSolid;
	struct MaterialPoint;
	struct MaterialLine;
	struct MaterialLit;
    struct MaterialFresnel;
    struct MaterialPbr;
	struct MaterialPhong;
	struct MaterialUser;
    class Material;
	class BlockMaterial;
	class Import;
    struct ImportConfig;
	class Importer;
    struct ModelElem;
    class Model;
    struct GpuMesh;
    class Mesh;
    struct Particle;
    struct ParticleSort;
    struct Flow;
    struct ParticleVertex;
    struct Flare;
    class ParticleSystem;
    class BlockParticles;
    class PassParticles;
    struct PrefabNode;
    class Prefab;
    class Camera;
	class Culler;
	class Froxelizer;
    struct DepthParams;
	struct DistanceParams;
    class PassDepth;
    class BlockDepth;
    class ImmediateDraw;
    class SymbolIndex;
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
	class Lines;
    class Gnode;
	class Item;
	class Direct;
	struct Batch;
    class Viewport;
    struct PickQuery;
    class Picker;
    struct PassJobs;
    class PassClear;
    class PassSolid;
    class PassBackground;
    class PassFlip;
    struct MinimalRenderer;
    struct SolidRenderer;
    struct ClearRenderer;
    class FrameBuffer;
	class SwapBuffer;
	class Cascade;
	class SwapCascade;
    class RenderTarget;
    struct Sun;
    struct Radiance;
	struct Skylight;
    struct Background;
    struct Fog;
    struct Zone;
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

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
#include <stl/span.h>
namespace stl
{
	export_ extern template struct refl_ span_ span<two::mat4>;

	export_ extern template struct refl_ span_ span<two::Node3>;
	export_ extern template struct refl_ span_ span<two::Item>;
	export_ extern template struct refl_ span_ span<two::Batch>;
	export_ extern template struct refl_ span_ span<two::Direct>;
	export_ extern template struct refl_ span_ span<two::Mime>;
	export_ extern template struct refl_ span_ span<two::Light>;
	export_ extern template struct refl_ span_ span<two::Flare>;

	export_ extern template struct refl_ span_ span<two::Texture*>;

	export_ extern template class refl_ seque_ vector<two::Mesh*>;
	export_ extern template class refl_ seque_ vector<two::Model*>;
	export_ extern template class refl_ seque_ vector<two::Texture*>;
	export_ extern template class refl_ seque_ vector<two::Material*>;

	export_ extern template class refl_ seque_ vector<two::Animation*>;
	export_ extern template class refl_ seque_ vector<two::AnimPlay>;
}
#endif


#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/vector.h>
#endif

namespace two
{
	export_ enum class refl_ AnimTarget : unsigned int
	{
		Position,
		Rotation,
		Scale,
		Weights,
		Count
	};

	export_ enum class refl_ Interpolation : unsigned int
	{
		Nearest,
		Linear,
		Cubic
	};

	export_ struct TWO_GFX_EXPORT AnimCursor
	{
		AnimCursor() {}
		float m_time = 0.f;
		size_t m_prev = 0;
		size_t m_next = 1;
	};

	struct Value
	{
		//char mem[16];
		char mem[32]; // need to be able to store vector<float>
	};

	export_ class refl_ TWO_GFX_EXPORT AnimTrack
	{
	public:
		struct Key
		{
			Key() {}
			float m_time;
			Value m_value;
			float m_transition = 1.f;

			template <class T>
			Key(float time, const T& value, float transition = 1.f)
				: m_time(time), m_value(), m_transition(transition)
			{
				static_assert(sizeof(T) <= sizeof(Value));
				new (stl::placeholder(), m_value.mem) T(value);
			}
		};

		AnimTrack();
		AnimTrack(Animation& animation, size_t node, cstring node_name, AnimTarget target);

		attr_ Animation* m_animation;
		attr_ size_t m_node;
		attr_ string m_node_name;
		attr_ AnimTarget m_target;
		attr_ Type* m_value_type = nullptr;

		attr_ float m_length = 0.f;
		attr_ Interpolation m_interpolation = Interpolation::Linear;

		vector<Key> m_keys;

		void insert_key(float time, const Value& value, float transition = 1.f);
		size_t key_after(float time) const;
		size_t key_before(float time) const;
		Value sample(AnimCursor& cursor) const;
		Value value(AnimCursor& cursor, bool forward) const;
	};

	export_ class refl_ TWO_GFX_EXPORT Animation
	{
	public:
		explicit Animation(cstring name);

		vector<AnimTrack> tracks;

		attr_ string m_name;
		attr_ float m_length = 1.f;
		attr_ float m_step = 0.1f;
	};
}


#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#endif



namespace two
{
	export_ TWO_GFX_EXPORT func_ mat4 bxidentity();
	export_ TWO_GFX_EXPORT func_ mat4 bxinverse(const mat4& mat);
	export_ TWO_GFX_EXPORT func_ mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans);
	export_ TWO_GFX_EXPORT func_ mat4 bxscale(const vec3& scale);
	// transpose because we are right-handed but bgfx assumes left-handed
	export_ TWO_GFX_EXPORT func_ mat4 bxrotation(const quat& rot);
	//export_ TWO_GFX_EXPORT mat4 bxquat(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), &rot[0]); return result; }
	export_ TWO_GFX_EXPORT func_ mat4 bxtranslation(const vec3& vec);
	export_ TWO_GFX_EXPORT func_ mat4 bxmul(const mat4& lhs, const mat4& rhs);
	export_ TWO_GFX_EXPORT func_ vec4 bxmul(const mat4& mat, const vec4& vec);
	export_ TWO_GFX_EXPORT func_ vec3 bxmul(const mat4& mat, const vec3& vec);
	export_ TWO_GFX_EXPORT func_ vec3 bxmulh(const mat4& mat, const vec3& vec);
	export_ TWO_GFX_EXPORT func_ mat4 bxlookat(const vec3& eye, const vec3& at);
	export_ TWO_GFX_EXPORT func_ void bxlookat(mat4& result, const vec3& eye, const vec3& at, const vec3& up);
	export_ TWO_GFX_EXPORT func_ mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up);
	export_ TWO_GFX_EXPORT func_ mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc);
	export_ TWO_GFX_EXPORT func_ mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc);
	export_ TWO_GFX_EXPORT func_ mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc);
	export_ TWO_GFX_EXPORT func_ mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans);
	export_ TWO_GFX_EXPORT func_ mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans);
	 
	void debug_print_mat(const mat4& mat);

	export_ class refl_ TWO_GFX_EXPORT Node3
	{
	public:
		constr_ Node3();
		constr_ Node3(const vec3& position, const quat& rotation = ZeroQuat, const vec3& scale = vec3(1.f));
		Node3(const mat4& transform, uint32_t parent = UINT32_MAX);

		attr_ uint32_t m_parent = UINT32_MAX;
		attr_ mat4 m_transform = bxidentity();

		//Ref m_object;
		Entity m_object;

		meth_ void apply(const vec3& position, const quat& rotation = ZeroQuat, const vec3& scale = vec3(1.f));
		meth_ void derive(const Node3& parent, const vec3& position, const quat& rotation = ZeroQuat, const vec3& scale = vec3(1.f));

		meth_ vec3 position() const;
		meth_ vec3 axis(const vec3& dir) const;
		meth_ vec3 direction() const;
	};
}


#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/span.h>
#include <stl/swap.h>
#endif

#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#ifndef TWO_MODULES
namespace bx
{
	struct FileReaderI;
	struct FileWriterI;
}
#endif

namespace two
{
	export_ using cstring = const char*;

	export_ enum class refl_ TextureHint : unsigned int
	{
		Black,
		White,
		Normal
	};

	export_ TWO_GFX_EXPORT void save_bgfx_texture(GfxSystem& gfx, const string& file_path, bgfx::TextureFormat::Enum target_format, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum texture_format, uint16_t width, uint16_t height, uint16_t depth = 1);
	export_ TWO_GFX_EXPORT bgfx::TextureHandle load_bgfx_texture(GfxSystem& gfx, const string& name, void* data, size_t size, uint64_t flags = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info = nullptr, bool generate_mips = false);
	export_ TWO_GFX_EXPORT bgfx::TextureHandle load_bgfx_texture(GfxSystem& gfx, const string& file_path, uint64_t flags = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info = nullptr, bool generate_mips = false);
	export_ TWO_GFX_EXPORT bimg::ImageContainer* load_bgfx_image(GfxSystem& gfx, const string& file_path, bgfx::TextureFormat::Enum dst_format);

	export_ TWO_GFX_EXPORT void save_texture(GfxSystem& gfx, Texture& texture, const string& path);
	export_ TWO_GFX_EXPORT void load_texture(GfxSystem& gfx, Texture& texture, const string& path, bool srgb = false, bool mips = false);
	export_ TWO_GFX_EXPORT void load_texture_mem(GfxSystem& gfx, Texture& texture, span<uint8_t> data);

	export_ enum class refl_ TextureFormat : unsigned int
	{
		R8      = bgfx::TextureFormat::R8,
		R16F    = bgfx::TextureFormat::R16F,
		R32U	= bgfx::TextureFormat::R32U,
		R32F    = bgfx::TextureFormat::R32F,
		RG8     = bgfx::TextureFormat::RG8,
		RG16F   = bgfx::TextureFormat::RG16F,
		RG32F   = bgfx::TextureFormat::RG32F,
		RGB8    = bgfx::TextureFormat::RGB8,
		BGRA8   = bgfx::TextureFormat::BGRA8,
		RGBA8   = bgfx::TextureFormat::RGBA8,
		RGB10A2 = bgfx::TextureFormat::RGB10A2,
		RGBA16F = bgfx::TextureFormat::RGBA16F,
		RGBA32F = bgfx::TextureFormat::RGBA32F,

		D16     = bgfx::TextureFormat::D16,
		D24     = bgfx::TextureFormat::D24,
		D24S8   = bgfx::TextureFormat::D24S8,
		D32     = bgfx::TextureFormat::D32,

		Count
	};

	export_ class refl_ TWO_GFX_EXPORT Texture
	{
	public:
		constr_ Texture(const string& name = "");
		constr_ Texture(const uvec2& size, bool mips, TextureFormat format, uint64_t flags = 0U, bool cube = false);
		Texture(const uvec2& size, bool mips, int layers, TextureFormat format, uint64_t flags = 0U);
		Texture(const uvec3& size, bool mips, TextureFormat format, uint64_t flags = 0U);
		~Texture();

		Texture(Texture&& other) : Texture(other) { other.m_tex = BGFX_INVALID_HANDLE; }
		Texture& operator=(Texture&& other) { bgfx::TextureHandle tex = m_tex; *this = other; other.m_tex = tex; return *this; }

		attr_ string m_name;
		attr_ string m_location;
		attr_ TextureFormat m_format;
		attr_ uvec2 m_size = uvec2(0U);
		attr_ uint16_t m_depth = 0;
		attr_ uint32_t m_memsize = 0;
		attr_ uint32_t m_bits_per_pixel = 0;
		attr_ bool m_is_depth = false;
		attr_ bool m_is_depth_packed = false;
		attr_ bool m_is_array = false;
		attr_ bool m_is_cube = false;
		attr_ bool m_is_fbo = false;
		attr_ bool m_mips = false;

		meth_ bool valid() const;

		meth_ void reload(GfxSystem& gfx, bool srgb = false, bool mips = false);

		void load_rgba(const uvec2& size, const bgfx::Memory& data);
		void load_float(const uvec2& size, const bgfx::Memory& data, uint8_t num_components = 4);

		meth_ void load_rgba(const uvec2& size, span<uint32_t> data, bool ref = false);
		meth_ void load_float(const uvec2& size, span<float> data, bool ref = false);

		bgfx::TextureHandle m_tex = BGFX_INVALID_HANDLE;

		operator bgfx::TextureHandle() const { return m_tex; }

	protected:
		Texture(const Texture& other) = default;
		Texture& operator=(const Texture& other) = default;
	};

	struct GpuTexture
	{
		Texture texture;
		vector<float> memory;
		vector<float> prev;
		uint16_t width = 1024;
		uint8_t stride = 4;
	};
}

#include <bgfx/bgfx.h>

namespace two
{
	TWO_GFX_EXPORT mat4 fix_bone_pose(Node3& bone);

	TWO_GFX_EXPORT void debug_draw_skeleton(Gnode& parent, const quat& position, const quat& rotation, Rig& rig);

	export_ class refl_ TWO_GFX_EXPORT Skeleton
	{
	public:
		Skeleton();
		Skeleton(cstring name, int num_bones);

		uint32_t add_bone(cstring name, uint32_t parent = UINT32_MAX);
		uint32_t bone_index(cstring name) const;
		Node3* find_bone(cstring name);

		cstring m_name;
		vector<string> m_names;
		vector<Node3> m_bones;
	};

	export_ struct refl_ TWO_GFX_EXPORT Joint
	{
		size_t m_bone;
		mat4 m_inverse_bind;
		mat4 m_joint;
	};

	export_ class refl_ TWO_GFX_EXPORT Skin
	{
	public:
		Skin();
		Skin(Skeleton& skeleton, int num_joints);
		Skin(const Skin& copy, Skeleton& skeleton);
		~Skin();

		void add_joint(cstring bone, const mat4& inverse_bind);
		void update_joints();

		Skeleton* m_skeleton;

		//Texture m_texture;
		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
		const bgfx::Memory* m_memory = nullptr;
		//vector<float> m_texture_data;

		vector<Joint> m_joints;
	};

	export_ class refl_ TWO_GFX_EXPORT Rig
	{
	public:
		Rig();

		Rig(const Rig& rig);
		Rig& operator=(const Rig& rig);

		void update_rig();

		Skeleton m_skeleton;
		vector<Skin> m_skins;

		vector<float> m_morphs;

		struct MorphWeight { uint32_t index; float weight; };
		vector<MorphWeight> m_weights;
	};
}

namespace two
{
	export_ struct refl_ TWO_GFX_EXPORT AnimNode
	{
		attr_ vec3 m_position = vec3(0.f);
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = vec3(1.f);
		attr_ mat4 m_transform;
	};

	export_ struct refl_ TWO_GFX_EXPORT AnimPlay
	{
		AnimPlay() {}
		AnimPlay(const Animation& animation, bool loop, float speed, bool transient, span<AnimNode> nodes, Rig* rig = nullptr);

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

		Rig* m_rig = nullptr;

		span<AnimNode> m_nodes;
		
		//span<float> m_weights;

		struct Track
		{
			const AnimTrack* m_track;
			AnimNode* m_node;
			AnimCursor m_cursor;
			Value m_value;
		};

		vector<Track> m_tracks;
	};

	export_ class refl_ TWO_GFX_EXPORT Mime
	{
	public:
		constr_ Mime();
		~Mime();

		Rig m_rig;

		vector<AnimNode> m_nodes;
		span<Node3> m_targets;

		span<Animation*> m_anims;

		attr_ vector<AnimPlay> m_playing;
		attr_ vector<Animation*> m_queue;

		attr_ bool m_active = true;

		attr_ float m_speed_scale = 1.f;
		attr_ float m_default_blend_time = 1.f;

		meth_ void start(const string& animation, bool loop, float blend = 0.f, float speed = 1.f, bool transient = false);
		meth_ void play(const Animation& animation, bool loop, float blend = 0.f, float speed = 1.f, bool transient = false);
		meth_ void seek(float time);
		meth_ void pause();
		meth_ void stop();
		meth_ void advance(float time);
		meth_ void next_animation();
		
		meth_ void add_item(Item& item);
		meth_ void add_nodes(span<Node3> nodes);

		meth_ string playing() { return m_playing.empty() ? "" : m_playing.back().m_animation->m_name; }
	};
}


#ifndef TWO_MODULES
#include <stl/function.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/map.h>
#endif

namespace two
{
	using cstring = const char*;

	struct NoConfig {};

	export_ template <class T_Asset>
	struct AssetConfig { using type = NoConfig; };

	export_ template <class T_Asset>
	class refl_ AssetStore
	{
	public:
		using Config = typename AssetConfig<T_Asset>::type;

		using Loader = function<void(T_Asset&, const string&, const Config&)>;
		using Init = function<void(T_Asset&)>;

		AssetStore(GfxSystem& gfx, const string& path);
		AssetStore(GfxSystem& gfx, const string& path, const Loader& loader);
		AssetStore(GfxSystem& gfx, const string& path, const string& format);

		AssetStore(const AssetStore& other) = delete;
		AssetStore& operator=(const AssetStore& other) = delete;

		void add_format(const string& format, const Loader& loader);

		GfxSystem& m_gfx;

		string m_path;
		Loader m_loader;

		vector<string> m_formats;
		vector<Loader> m_format_loaders;

		//meth_ bool locate(const string& name);
		meth_ T_Asset* get(const string& name);
		meth_ T_Asset& create(const string& name);
		meth_ T_Asset& fetch(const string& name);
		      T_Asset* file(const string& name, const Config& config);
		meth_ T_Asset* file(const string& name) { return this->file(name, {}); }
		      T_Asset& file_at(const string& path, const string& name, const Config& config);
		meth_ T_Asset& file_at(const string& path, const string& name) { return this->file_at(path, name, {}); }
			  T_Asset* load(const string& path, const string& name, const Config& config);
		meth_ T_Asset* load(const string& path, const string& name) { return this->load(path, name, {}); }
		meth_ void destroy(const string& name);
		meth_ void clear();

		T_Asset& create(const string& name, const Init& init);

		void load_files(const string& path);

		map<string, unique<T_Asset>> m_assets;
		vector<T_Asset*> m_vector;
	};
	
	export_ template <>
	struct AssetConfig<Prefab> { using type = ImportConfig; };
	
	export_ template <>
	struct AssetConfig<Model> { using type = ImportConfig; };
}
//#include <gfx/Asset.hpp>




#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/span.h>
#include <stl/table.h>
#include <stl/vector.h>
#endif

#include <bgfx/bgfx.h>

namespace two
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

	export_ enum class refl_ PassType : unsigned int
	{
		VoxelGI,
		Lightmap,
		Shadowmap,
		Probes,
		Clear,
		Depth,
		Normals,
		Shadow,
		Geometry,
		Lights,
		Opaque,
		Background,
		Particles,
		Alpha,
		Solid,
		Effects,
		PostProcess,
		Flip,

		Count
	};

	export_ struct refl_ TWO_GFX_EXPORT ShaderDefine
	{
		attr_ string m_name;
		attr_ string m_value;
	};

	export_ struct refl_ TWO_GFX_EXPORT ShaderBlock
	{
		constr_ ShaderBlock();
		ShaderBlock(span<cstring> options, span<cstring> modes);

		attr_ uint8_t m_index;
		attr_ vector<string> m_options;
		attr_ vector<string> m_modes;
		vector<ShaderDefine> m_defines;

		meth_ void add_option(const string& name) { m_options.push_back(name); }
		meth_ void add_mode(const string& name) { m_modes.push_back(name); }
		meth_ void add_define(const string& name, const string& value) { m_defines.push_back({ name, value }); }
	};

	export_ struct refl_ TWO_GFX_EXPORT ProgramMode
	{
		attr_ string name;
		attr_ uint32_t size;
		attr_ uint32_t shift;
		attr_ uint32_t mask;
	};

	export_ struct refl_ TWO_GFX_EXPORT ProgramBlock
	{
		// maps a block shader option to the program option shift
		attr_ bool m_enabled = false;
		attr_ uint8_t m_option_shift = 0;
		attr_ uint8_t m_mode_shift = 0;
	};

	export_ enum class refl_ MaterialBlock : unsigned int
	{
		Base,
		Alpha,
		Solid,
		Point,
		Line,
		Lit,
		Pbr,
		Phong,
		Fresnel,
		User,
		Count
	};

	export_ class refl_ TWO_GFX_EXPORT Program
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
		~Program();

		attr_ string m_name;

		meth_ void set_block(MaterialBlock block, bool enabled = true);
		meth_ void set_pass(PassType type, bool enabled = true);
		meth_ void set_source(ShaderType type, const string& source);

		string defines(const ProgramVersion& version) const;

		void reload() { m_update++; }

		void compile(GfxSystem& gfx, Version& version, bool compute = false);

		void update(GfxSystem& gfx);

		bgfx::ProgramHandle default_version();
		bgfx::ProgramHandle version(const ProgramVersion& config);

		ProgramVersion program(Version& version);

		meth_ void register_blocks(const Program& program);

		meth_ void register_block(const ShaderBlock& block);

		void set_blocks(span<MaterialBlock> blocks);
		void register_blocks(span<ShaderBlock*> blocks);
		void register_options(uint8_t block, span<string> options);
		void register_modes(uint8_t block, span<string> modes);

		// maps a block index to its shader options span
		ProgramBlock m_shader_blocks[32] = {};
		uint8_t m_next_option = 0;
		vector<ShaderBlock*> m_registered_blocks;

		table<MaterialBlock, bool> m_blocks = {};
		table<ShaderType, string> m_sources = {};
		table<PassType, bool> m_passes = {};

		vector<string> m_options;
		vector<string> m_modes;

		vector<ShaderDefine> m_defines;

		bool m_compute = false;
		uint32_t m_update = 1;

		uint32_t m_primitives = 0;

		static GfxSystem* ms_gfx;

	private:
		struct Impl;
		unique<Impl> m_impl;
	};
}


#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/table.h>
#include <stl/function.h>
#endif


#ifndef TWO_MODULES
#include <stl/memory.h>
#include <stl/span.h>
#include <stl/vector.h>
#endif


#ifndef TWO_MODULES
#include <stl/span.h>
#endif

#if defined TWO_UNIFORM_BLOCKS


#if 0

#ifndef TWO_MODULES
#include <stl/string.h>
#endif

#include <bgfx/bgfx.h>

#include <algorithm>

namespace two
{
	// @todo automatical definition of structs to uniforms using reflection
	// - vectors and floats are packed to Vec4 in the order they appear, adding padding if next vector is too big to fit
	// - enums are sent as a define switch using enum value label
	// - booleans are sent as a define switch using parameter name

	export_ struct TWO_GFX_EXPORT Uniform
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

	export_ struct TWO_GFX_EXPORT Sampler
	{
		string m_name;
		size_t m_member;
		uint8_t m_stage;
		Texture* m_default;
		bgfx::UniformHandle m_uniform;

		void create()
		{
			m_uniform = bgfx::createUniform(m_name.c_str(), bgfx::UniformType::Sampler);
		}

		template <class T>
		void upload(bgfx::Encoder& encoder, T& object)
		{
			void* T::* mem = reinterpret_cast<void* T::*>(m_member.value);
			Texture* texture = (Texture*)(object.*mem);
			encoder.setTexture(m_stage, m_uniform, texture ? texture->m_texture : m_default->m_texture);
		}
	};

	export_ struct TWO_GFX_EXPORT UniformBlock
	{
		UniformBlock(Type& type, const string& name);

		Type& m_type;
		string m_name;
		vector<Uniform> m_uniforms;
		vector<Sampler> m_samplers;
		string m_shader_decl;
		size_t m_num_packed = 0;

		void pack_member(size_t size, Member& member);
		void create_member(GfxSystem& gfx, const string& name, Member& member);
		string shader_decl();
		void create(GfxSystem& gfx);
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

namespace two
{
#if defined TWO_UNIFORM_BLOCKS
	export_ struct refl_ TWO_GFX_EXPORT FrustumBlock
	{
		attr_ float m_fov = 60.f;
		attr_ float m_aspect = 1.f;
		attr_ float m_near = 0.001f;
		attr_ float m_far = 100.f;

		static TypedUniformBlock<FrustumBlock> s_block;
	};
#endif

	export_ TWO_GFX_EXPORT Plane6 bounding_planes(const mat4& mat);
	export_ TWO_GFX_EXPORT Plane6 frustum_planes(const mat4& projection, const mat4& transform);
	export_ TWO_GFX_EXPORT Plane6 frustum_planes(const mat4& view, float fov, float aspect, float near, float far);
	export_ TWO_GFX_EXPORT Plane6 frustum_planes(const mat4& view, const vec2& rect, float near, float far);
	export_ TWO_GFX_EXPORT Point8 frustum_corners(const Plane6& planes);

	export_ TWO_GFX_EXPORT vec2 frustum_viewport_size(const mat4& projection);

	export_ class refl_ TWO_GFX_EXPORT Frustum
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

	export_ TWO_GFX_EXPORT Frustum optimized_frustum(Camera& camera, span<Item*> items);

	export_ struct refl_ TWO_GFX_EXPORT FrustumSlice
	{
		int m_index;
		Frustum m_frustum;
	};

	export_ TWO_GFX_EXPORT void split_frustum_slices(Camera& camera, span<FrustumSlice*> slices, uint8_t num_splits, float split_distribution);
}


#include <stdint.h>

#include <cassert>

namespace two
{
	enum ShaderOption : unsigned int
	{
		INSTANCING,
		BILLBOARD,
		SKELETON,
		MORPHTARGET,
		QNORMALS,
		VFLIP,
		MRT,
		DEFERRED,
		CLUSTERED,
		BUFFER_ZONES,
		BUFFER_LIGHTS,
		BUFFER_MATERIALS,
	};

	export_ struct refl_ TWO_GFX_EXPORT ProgramVersion
	{
		constr_ ProgramVersion() {}
		constr_ ProgramVersion(const Program& program) : m_program(&program) {}
		//constr_ explicit ProgramVersion(const Program& program) : m_program(&program) {}

		const Program* m_program = nullptr;
		uint32_t m_options = 0;
		uint8_t m_modes[4] = {};

		bgfx::ProgramHandle fetch() const { return const_cast<Program*>(m_program)->version(*this); }

		meth_ void clear() { m_options = 0; }

		inline void set(uint8_t option, bool active = true)
		{
			assert(option < 32);
			if(active) m_options |= (1 << option);
			else       m_options &= ~(1 << option);
		}

		meth_ inline void set_option(uint8_t block, uint8_t option, bool active = true)
		{
			assert(m_program->m_shader_blocks[block].m_enabled);
			const uint8_t block_shift = m_program->m_shader_blocks[block].m_option_shift;
			this->set(block_shift + option, active);
		}

		meth_ inline void set_mode(uint8_t block, uint8_t mode, uint8_t value)
		{
			assert(m_program->m_shader_blocks[block].m_enabled);
			const uint8_t mode_shift = m_program->m_shader_blocks[block].m_mode_shift;
			m_modes[mode_shift + mode] = value;
		}

		uint32_t hash_modes() const { return (m_modes[0] << 0) + (m_modes[1] << 8) + (m_modes[2] << 16) + (m_modes[3] << 24); }
		meth_ uint64_t hash() const {	return uint64_t(m_options) + (uint64_t(hash_modes()) << 32); }
	};
}


#ifndef TWO_MODULES
#include <stl/vector.h>
#endif

namespace two
{
	export_ class refl_ TWO_GFX_EXPORT Shot
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

#include <stdint.h>

#include <bgfx/bgfx.h>

#define ZONES_BUFFER 0
#define MATERIALS_BUFFER 0
#define LIGHTS_BUFFER 0

#define ZONES_LIGHTS_BUFFER 0

namespace two
{
#define TEXTURE_CLAMP  BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
#define TEXTURE_CLAMP3 BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP
#define TEXTURE_POINT  BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT

#ifdef TWO_PLATFORM_EMSCRIPTEN
// webgl doesn't usually support sampling depth textures with filtering on
#define TEXTURE_DEPTH TEXTURE_POINT
#else
#define TEXTURE_DEPTH 0
#endif

	TWO_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

	export_ enum class refl_ TextureSampler : unsigned int
	{
		// Screen
		Source0 = 0,
		Source1 = 1,
		Source2 = 2,
		Source3 = 3,
		SourceDepth = 3,

		// Material
		Color = 0,
		Albedo = 0,
		Diffuse = 0,
		Alpha = 1,
		Metallic = 2,
		Specular = 2,
		Roughness = 3,
		Shininess = 3,
		Emissive = 4,
		Normal = 5,
		AO = 6,
		Displace = 7,
		Depth = 7,

		// User
		// probably the least likely to collide with a user defined material
		User0 = 12,
		User1 = 13,
		User2 = 14,
		User3 = 15,
		User4 = 6,
		User5 = 7,

		// Scene
		Radiance = 10,
		Shadow = 11,
		Lightmap = 12,
		ReflectionProbe = 13,
		GIProbe = 14,

		// Model
		Skeleton = 15,

		// Buffers
		Zones = 0,
		Materials = 8,
		Lights = 9,

		Clusters = 13,	   // collides with Lightmap
		LightRecords = 14, // collides with GIProbe
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

	enum class GpuStorage
	{
		Uniform,
		Buffer,
		Texture,
	};

	template <class T>
	struct GpuState {};

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
	export_ struct refl_ TWO_GFX_EXPORT Pass
	{
		attr_ string m_name;
		attr_ RenderTarget* m_target = nullptr;
		attr_ FrameBuffer* m_fbo = nullptr;
		attr_ Viewport* m_viewport = nullptr;
		attr_ vec4 m_rect = vec4(0.f);
		attr_ uint64_t m_bgfx_state = 0;
		bgfx::Encoder* m_encoder = nullptr;
		attr_ PassType m_pass_type;

		attr_ bool m_use_mrt = false;
		attr_ uint8_t m_index = 0;
	};

	export_ struct refl_ TWO_GFX_EXPORT RenderFrame
	{
		attr_ uint32_t m_frame;
		attr_ float m_time;
		attr_ float m_delta_time;
		attr_ uint8_t m_render_pass;

		attr_ uint32_t m_num_draw_calls = 0;
		attr_ uint32_t m_num_vertices = 0;
		attr_ uint32_t m_num_triangles = 0;
	};

	using RenderFunc = void(*)(GfxSystem&, Render&);

	export_ struct refl_ TWO_GFX_EXPORT Render
	{
		constr_ Render() {}
		constr_ Render(Shading shading, Viewport& viewport, RenderTarget& target, RenderFrame& frame);
		constr_ Render(Shading shading, Viewport& viewport, RenderTarget& target, FrameBuffer& target_fbo, RenderFrame& frame);
		~Render();

		attr_ Shading m_shading;
		attr_ Scene* m_scene;
		attr_ RenderTarget* m_target;
		attr_ FrameBuffer* m_fbo;
		attr_ Viewport* m_viewport;
		attr_ vec4 m_rect;
		attr_ Camera* m_camera;
		attr_ RenderFrame* m_frame;

		RenderFunc m_renderer;

		attr_ Frustum m_frustum;

		attr_ Zone* m_env = nullptr;
		Entt m_filters;

		attr_ Lighting m_lighting = Lighting::None;
		attr_ bool m_vflip = false;
		attr_ bool m_needs_mrt = false;
		attr_ bool m_is_mrt = false;

		//ShadowAtlas* m_shadow_atlas = nullptr;
		//ReflectionAtlas* m_reflection_atlas = nullptr;

		attr_ uint8_t m_pass_index = s_render_pass_id;

		uint8_t m_picking_pass_index = s_picking_pass_id;
		uint8_t m_debug_pass_index = s_debug_pass_id;

		Shot m_shot;

		uint32_t m_num_draw_calls = 0;
		uint32_t m_num_vertices = 0;
		uint32_t m_num_triangles = 0;

		meth_ void subrender(const Render& render);

		meth_ Pass next_pass(cstring name, PassType type);
		meth_ Pass composite_pass(cstring name, FrameBuffer& fbo, const vec4& rect);
		Pass composite_pass(cstring name);

		uint8_t picking_pass() { return m_picking_pass_index++; }
		uint8_t debug_pass() { return m_debug_pass_index++; }

		void set_uniforms(const Pass& pass) const;

		static const uint8_t s_picking_pass_id = 1;
		static const uint8_t s_render_pass_id = 100;
		static const uint8_t s_debug_pass_id = 245;
	};

	export_ class refl_ TWO_GFX_EXPORT GfxBlock : public ShaderBlock
	{
	public:
		GfxBlock(GfxSystem& gfx, Type& type);
		virtual ~GfxBlock();

		template <class T>
		GfxBlock(GfxSystem& gfx, T& self) : GfxBlock(gfx, type<T>()) { UNUSED(self); }

		virtual void init_block() = 0;
		virtual void begin_frame(const RenderFrame& frame) { UNUSED(frame); }

		virtual void begin_render(Render& render) { UNUSED(render); }
		virtual void submit_pass(Render& render) { UNUSED(render); }

		GfxSystem& m_gfx;
		attr_ Type& m_type;

		bool m_draw_block = false;
	};

	export_ class refl_ TWO_GFX_EXPORT DrawBlock : public GfxBlock
	{
	public:
		DrawBlock(GfxSystem& gfx, Type& type) : GfxBlock(gfx, type) { m_draw_block = true; }

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const { UNUSED(render); UNUSED(element); UNUSED(program); }
		virtual void submit(Render& render, const Pass& pass) const = 0;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const = 0;
	};

	export_ struct TWO_GFX_EXPORT DrawElement
	{
		DrawElement() {}
		DrawElement(Item& item, const Program& program, const ModelElem& model, const Material& material, const Skin* skin, uint64_t sort_key);

		Item* m_item = nullptr;
		const ModelElem* m_elem = nullptr;
		const Material* m_material = nullptr;
		const Skin* m_skin = nullptr;

		uint64_t m_sort_key = 0;
		ProgramVersion m_program = {};
		uint64_t m_bgfx_state = 0;
		bgfx::ProgramHandle m_bgfx_program = BGFX_INVALID_HANDLE;

		void set_program(const Program& program);
	};

	export_ struct TWO_GFX_EXPORT DrawCluster
	{
		ProgramVersion m_shader_version = {};
		uint64_t m_bgfx_state = 0;
		span<Light*> m_lights = {};
	};

	export_ class refl_ TWO_GFX_EXPORT Renderer
	{
	public:
		Renderer(GfxSystem& gfx);
		~Renderer();

		GfxSystem& m_gfx;

		struct Impl;
		unique<Impl> m_impl;

		void init();

		void submit(Render& render, RenderFunc renderer);
		void render(Render& render, RenderFunc renderer);
		void subrender(Render& render, Render& sub, RenderFunc renderer);

		meth_ void gather(Render& render);
		meth_ void begin(Render& render);
		meth_ void end(Render& render);

		using Enqueue = bool(*)(GfxSystem&, Render&, Pass&, DrawElement&);
		using Submit = void(*)(GfxSystem&, Render&, Pass&, const DrawElement&);

		void begin_render_pass(Render& render, PassType pass_type);
		void submit_render_pass(Render& render, Pass& pass, Submit submit);

		void shader_options(Render& render, Pass& pass, ProgramVersion& version) const;
		void element_options(Render& render, Pass& pass, DrawElement& element);
		void add_element(Render& render, Pass& pass, DrawElement element);
		void clear_draw_elements(Render& render, Pass& pass);
		void gather_draw_elements(Render& render, Pass& pass);
		void submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, size_t first, size_t count) const;
		DrawElement draw_element(Item& item, const ModelElem& elem) const;

		void submit(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, const DrawElement& element) const;

		void pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit = nullptr, bool sorted = false);
		void sorted_pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit = nullptr);
		void direct_pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit = nullptr);

		using GatherFunc = void(*)(Scene&, Render&);
		GatherFunc m_gather_func;

		template <class T_Block>
		T_Block* block() { for(auto& block : m_gfx_blocks) if(&(block->m_type) == &type<T_Block>()) return &as<T_Block>(*block); return nullptr; }

		template <class T_Block, class... Args>
		T_Block& add_block(Args&&... args) { m_gfx_blocks.push_back(make_unique<T_Block>(static_cast<Args&&>(args)...)); return as<T_Block>(*m_gfx_blocks.back()); }

		vector<unique<GfxBlock>> m_gfx_blocks;

		table<PassType, vector<GfxBlock*>> m_pass_blocks;
	};
}

namespace bgfx
{
	struct Encoder;
}

namespace two
{
	export_ enum class refl_ BlendMode : unsigned int
	{
		None,
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
		Back,
		Count
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

	export_ enum class refl_ ShaderColor : unsigned int
	{
		Shader,
		Vertex,
		Face
	};

	export_ enum ShaderOptionBase : unsigned int
	{
		VERTEX_COLOR,
		DOUBLE_SIDED,
		FLAT_SHADED,
	};

	export_ enum ShaderOptionAlpha : unsigned int
	{
		ALPHA_MAP,
		ALPHA_TEST,
	};

	export_ enum class refl_ TextureChannel : unsigned int
	{
		Red,
		Green,
		Blue,
		Alpha,
		All
	};

	export_ template <class T>
	struct refl_ struct_ MaterialParam
	{
		MaterialParam() {}
		MaterialParam(T value, Texture* texture = nullptr, TextureChannel channel = TextureChannel::All) : m_value(value), m_texture(texture), m_channel(channel) {}
		//MaterialParam(Texture& texture, TextureChannel channel = TextureChannel::All) : m_value(T()), m_texture(texture), m_channel(channel) {}
		MaterialParam& operator=(const T& value) { m_value = value; return *this; }
		MaterialParam& operator=(Texture* texture) { m_texture = texture; return *this; }
		attr_ gpu_ T m_value = {};
		attr_ Texture* m_texture = nullptr;
		attr_ TextureChannel m_channel = TextureChannel::All;
	};

	export_ extern template struct refl_ MaterialParam<Colour>;
	export_ extern template struct refl_ MaterialParam<float>;
	export_ extern template struct refl_ MaterialParam<vec4>;

	export_ struct refl_ TWO_GFX_EXPORT MaterialBase
	{
		attr_ BlendMode m_blend_mode = BlendMode::None;
		attr_ CullMode m_cull_mode = CullMode::Back;
		attr_ DepthDraw m_depth_draw = DepthDraw::Enabled;
		attr_ DepthTest m_depth_test = DepthTest::Enabled;

		attr_ gpu_ vec2 m_uv0_scale = { 1.f, 1.f };
		attr_ gpu_ vec2 m_uv0_offset = { 0.f, 0.f };
		attr_ gpu_ vec2 m_uv1_scale = { 1.f, 1.f };
		attr_ gpu_ vec2 m_uv1_offset = { 0.f, 0.f };

		attr_ ShaderColor m_shader_color = ShaderColor::Shader;
		attr_ bool m_flat_shaded = false;

		attr_ bool m_screen_filter = false;
		attr_ float m_anisotropy;

		uint32_t m_geometry_filter = UINT32_MAX;

#if 0
		BillboardMode m_billboard_mode;
#endif
		
		static ShaderBlock s_block;
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialUser
	{
		attr_ Texture* m_tex0 = nullptr;
		attr_ Texture* m_tex1 = nullptr;
		attr_ Texture* m_tex2 = nullptr;
		attr_ Texture* m_tex3 = nullptr;
		attr_ Texture* m_tex4 = nullptr;
		attr_ Texture* m_tex5 = nullptr;

		attr_ vec4 m_attr0 = vec4(0.f);
		attr_ vec4 m_attr1 = vec4(0.f);
		attr_ vec4 m_attr2 = vec4(0.f);
		attr_ vec4 m_attr3 = vec4(0.f);
		attr_ vec4 m_attr4 = vec4(0.f);
		attr_ vec4 m_attr5 = vec4(0.f);

		static ShaderBlock s_block;
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialAlpha
	{
		attr_ gpu_ MaterialParam<float> m_alpha = { 1.f, nullptr };
		attr_ gpu_ float m_alpha_scissor = 0.5f;

		attr_ bool m_alpha_test = false;
		attr_ bool m_is_alpha = false;

		static ShaderBlock s_block;
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialSolid
	{
		attr_ MaterialParam<Colour> m_colour = { Colour::White, nullptr };

		static ShaderBlock s_block;
	};

	export_ enum ShaderOptionSolid : unsigned int
	{
		COLOR_MAP,
	};

	export_ enum ShaderOptionLine : unsigned int
	{
		DASH,
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialPoint
	{
		attr_ gpu_ float m_point_size = 1.f;
		attr_ gpu_ bool m_project = false;

		static ShaderBlock s_block;
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialLine
	{
		attr_ gpu_ float m_line_width = 1.f;

		attr_ bool m_dashed = false;
		attr_ gpu_ float m_dash_scale = 1.f;
		attr_ gpu_ float m_dash_size = 1.f;
		attr_ gpu_ float m_dash_gap = 1.f;
		// resolution

		static ShaderBlock s_block;
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialFresnel
	{
		attr_ gpu_ MaterialParam<Colour> m_value = { Colour::White, nullptr };

		attr_ gpu_ float m_fresnel_scale = 1.f;
		attr_ gpu_ float m_fresnel_bias = 0.01f;
		attr_ gpu_ float m_fresnel_power = 5.f;

		static ShaderBlock s_block;
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

	export_ enum ShaderOptionLit : unsigned int
	{
		NORMAL_MAP,
		EMISSIVE,
		AMBIENT_OCCLUSION,
		LIGHTMAP,
		DISPLACEMENT
	};

	export_ enum ShaderOptionPbr : unsigned int
	{
		ALBEDO_MAP,
		ROUGHNESS_MAP,
		METALLIC_MAP,
		//REFRACTION,
		//ANISOTROPY,
		DEPTH_MAPPING,
		DEEP_PARALLAX,
	};

	export_ enum ShaderModePbr : unsigned int
	{
		DIFFUSE_MODE,
		SPECULAR_MODE,
	};

	export_ enum ShaderOptionPhong : unsigned int
	{
		DIFFUSE_MAP,
		SPECULAR_MAP,
		SHININESS_MAP,
		REFRACTION,
		TOON,
	};

	export_ enum ShaderModePhong : unsigned int
	{
		ENV_BLEND,
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialLit
	{
		attr_ gpu_ MaterialParam<Colour> m_emissive = { rgba(0x00000000), nullptr };
		attr_ gpu_ float m_emissive_energy = 0.f;

		attr_ gpu_ MaterialParam<float> m_normal = { 1.f, nullptr };
		attr_ gpu_ MaterialParam<float> m_bump = { 1.f, nullptr };
		attr_ gpu_ MaterialParam<float> m_displace = { 1.f, nullptr };
		attr_ gpu_ float m_displace_bias = 0.f;

		attr_ gpu_ MaterialParam<float> m_occlusion;
		attr_ gpu_ MaterialParam<float> m_lightmap;

		attr_ bool m_no_envmap = false;

		static ShaderBlock s_block;
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialPbr
	{
		constr_ MaterialPbr() {}
		constr_ MaterialPbr(const Colour& albedo, float metallic = 0.f, float roughness = 1.f) : m_albedo(albedo, nullptr), m_metallic(metallic, nullptr, TextureChannel::Red), m_roughness(roughness, nullptr, TextureChannel::Red) {}

		MaterialPbr& operator=(const MaterialPbr&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		// basic
		attr_ gpu_ MaterialParam<Colour> m_albedo = { Colour::White, nullptr };
		attr_ gpu_ float m_specular = 0.5f;
		attr_ gpu_ MaterialParam<float> m_metallic = { 0.f, nullptr, TextureChannel::Red };
		attr_ gpu_ MaterialParam<float> m_roughness = { 1.f, nullptr, TextureChannel::Red };

		// advanced
		attr_ gpu_ MaterialParam<float> m_rim;
		attr_ gpu_ float m_rim_tint;
		attr_ gpu_ MaterialParam<float> m_clearcoat;
		attr_ gpu_ float m_clearcoat_gloss;
		attr_ gpu_ MaterialParam<float> m_anisotropy;
		attr_ gpu_ MaterialParam<float> m_subsurface;
		attr_ gpu_ MaterialParam<float> m_refraction;
		attr_ gpu_ MaterialParam<float> m_depth = { -0.02f, nullptr };
		attr_ gpu_ MaterialParam<Colour> m_transmission;

		attr_ bool m_deep_parallax = false;

		attr_ PbrDiffuseMode m_diffuse_mode = PbrDiffuseMode::Burley;
		attr_ PbrSpecularMode m_specular_mode = PbrSpecularMode::SchlickGGX;

		table<MaterialFlag, bool> m_flags;

		static ShaderBlock s_block;
	};

	export_ enum class refl_ PhongEnvBlendMode : unsigned int
	{
		Mul,
		Mix,
		Add,
	};

	export_ struct refl_ TWO_GFX_EXPORT MaterialPhong
	{
		attr_ gpu_ MaterialParam<Colour> m_diffuse = { rgb(0xffffff), nullptr };
		attr_ gpu_ MaterialParam<Colour> m_specular = { rgb(0x111111), nullptr };
		attr_ gpu_ MaterialParam<float> m_shininess = { 30.f, nullptr };

		attr_ gpu_ MaterialParam<float> m_reflectivity = { 1.f, nullptr };
		attr_ gpu_ MaterialParam<float> m_refraction = { 0.f, nullptr }; // 0.98f if active

		attr_ PhongEnvBlendMode m_env_blend = PhongEnvBlendMode::Mul;

		attr_ bool m_toon = false;

		static ShaderBlock s_block;
	};

	export_ class refl_ TWO_GFX_EXPORT BlockMaterial : public GfxBlock
	{
	public:
		BlockMaterial(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void submit(Render& render, const Pass& pass);

		// only reason for this split hack is bgfx/webgl precision mismatch issue
		bgfx::UniformHandle u_state = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_state_vertex = BGFX_INVALID_HANDLE;

		bgfx::UniformHandle s_materials = BGFX_INVALID_HANDLE;
		GpuTexture m_materials_texture = {};
	};

	export_ TWO_GFX_EXPORT void load_material(Material& material, Program& program);

	export_ class refl_ TWO_GFX_EXPORT Material
	{
	public:
		Material() {}
		Material(const string& name);

		Material& operator=(const Material&) = default; // @kludge because clang-modules bug doesn't have copy-assign with member arrays ?

		attr_ uint16_t m_index = 0;
		attr_ string m_name;
		attr_ bool m_builtin = false;
		attr_ Program* m_program = nullptr;

		attr_ MaterialBase m_base;
		attr_ MaterialAlpha m_alpha;
		attr_ MaterialSolid m_solid;
		attr_ MaterialPoint m_point;
		attr_ MaterialLine m_line;
		attr_ MaterialLit m_lit;
		attr_ MaterialPbr m_pbr;
		attr_ MaterialPhong m_phong;
		attr_ MaterialFresnel m_fresnel;
		attr_ MaterialUser m_user;

		function<void(bgfx::Encoder&)> m_pass;
		function<void(bgfx::Encoder&)> m_submit;

		void state(uint64_t& bgfx_state) const;
		ProgramVersion program(const Program& program) const;
		ProgramVersion program(const Program& program, const Item& item, const ModelElem& elem) const;

		void submit(const Program& program, bgfx::Encoder& encoder, uint64_t& bgfx_state, const Skin* skin = nullptr) const;

		static GfxSystem* ms_gfx;
	};
}


#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/span.h>
#include <stl/table.h>
#endif

namespace two
{
	export_ struct refl_ ModelElem
	{
		attr_ size_t m_index;
		attr_ Mesh* m_mesh;
		attr_ bool m_has_transform;
		attr_ mat4 m_transform;
		attr_ int m_skin;
		attr_ Colour m_colour;
		attr_ Material* m_material;
	};

	export_ class refl_ TWO_GFX_EXPORT Model
	{
	public:
		Model(const string& name);
		~Model();

		attr_ string m_name;
		attr_ uint16_t m_index;

		vector<ModelElem> m_items;
		bool m_no_transform = true;

		attr_ Aabb m_aabb = { vec3(0.f), vec3(0.f) };
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = vec3(0.f);

		table<PrimitiveType, bool> m_geometry = { { 0 } };

		Rig* m_rig = nullptr;

		vector<Animation*> m_anims;

		meth_ Mesh& get_mesh(size_t index);
		meth_ Mesh& add_mesh(const string& name, bool readback = false);
		meth_ Rig& add_rig(const string& name);
		meth_ ModelElem& add_item(Mesh& mesh, const mat4& transform, int skin = -1, const Colour& colour = Colour::White, Material* material = nullptr);
		meth_ void prepare();

		static GfxSystem* ms_gfx;
	};

	export_ TWO_GFX_EXPORT Model& model_variant(GfxSystem& gfx, Model& original, const string& name, span<string> materials, span<Material*> substitutes);
}


#ifndef TWO_MODULES
#include <stl/vector.h>
#endif

#include <bgfx/bgfx.h>

namespace two
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

	// alternate names: spout, flux, jet
	export_ struct refl_ TWO_GFX_EXPORT Flow
	{
		Flow();
		Flow(const string& name);

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

		//attr_ ValueTrack<vec3> m_position = { vec3(0.f) };
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
	};

	// alternate names: jet, flow, surge, spray
	export_ struct refl_ TWO_GFX_EXPORT Flare : public Flow
	{
	public:
		Flare(Node3* node = nullptr, ShapeVar shape = {}, uint32_t max_particles = 1024);

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

#ifndef TWO_MODULES
	template <class T>
	class TPool;
#endif

	export_ class TWO_GFX_EXPORT ParticleSystem
	{
	public:
		ParticleSystem(GfxSystem& gfx, TPool<Flare>& emitters);
		~ParticleSystem();

		GfxSystem& m_gfx;
		BlockParticles& m_block;

		void shutdown();

		void update(float timestep);
		void render(bgfx::Encoder& encoder, uint8_t pass, const mat4& view, const vec3& eye);
		
		TPool<Flare>& m_emitters;

		bgfx::ProgramHandle m_program;

		uint32_t m_num = 0;
	};

	export_ class refl_ TWO_GFX_EXPORT BlockParticles : public GfxBlock
	{
	public:
		BlockParticles(GfxSystem& gfx);
		~BlockParticles();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		unique<SpriteAtlas> m_sprites;
		Texture m_texture;

		bgfx::UniformHandle s_color;

		Sprite* create_sprite(cstring name, cstring path, uvec2 frames = uvec2(0U));
		Sprite* create_sprite(cstring name, const uvec2& size, uvec2 frames, const void* data);
		void remove_sprite(Sprite& image);
	};

	export_ TWO_GFX_EXPORT void pass_particles(GfxSystem& gfx, Render& render);
}


#ifndef TWO_MODULES
#include <stl/vector.h>
//#include <refl/Method.h>
#endif


#ifndef TWO_MODULES
#include <stl/vector.h>
#endif

#include <bgfx/bgfx.h>

namespace two
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
			NoCull = 1 << 8,
			Lod0 = 1 << 9,
			Lod1 = 1 << 10,
			Lod2 = 1 << 11,
			Lod3 = 1 << 12,
			LodAll = Lod0 | Lod1 | Lod2 | Lod3,
			Default = Render | Shadows | LodAll
		};
	};

	export_ enum class refl_ ItemShadow : unsigned int
	{
		Default,
		DoubleSided
	};

	export_ struct refl_ TWO_GFX_EXPORT Batch
	{
		constr_ Batch();
		constr_ Batch(Item& item, uint16_t stride);

		attr_ Item* m_item = nullptr;
		attr_ uint16_t m_stride;

		bgfx::InstanceDataBuffer m_buffer;
		vector<bgfx::InstanceDataBuffer> m_buffers;
		vector<float> m_cache;
		//span<mat4> m_transforms;

		meth_ void update_aabb(span<mat4> instances);
		meth_ void transforms(span<mat4> instances);

		meth_ span<float> begin(uint32_t count);
		meth_ void commit(span<float> data);
		meth_ void cache(span<float> data);

		meth_ void transform(const mat4& m);

		void submit(bgfx::Encoder& encoder, const ModelElem& item); // const;
	};

	export_ class refl_ TWO_GFX_EXPORT Item
	{
	public:
		constr_ Item();
		constr_ Item(Node3& node, const Model& model, uint32_t flags = 0, Material* material = nullptr);

		attr_ Node3* m_node = nullptr;
		attr_ Model* m_model = nullptr;
		attr_ uint32_t m_flags = 0;
		attr_ Colour m_colour = Colour::White;
		attr_ Material* m_material = nullptr;
		attr_ bool m_visible = true;
		attr_ ItemShadow m_shadow = ItemShadow::Default;
		attr_ Rig* m_rig = nullptr;

		attr_ Aabb m_aabb;
		attr_ Batch* m_batch = nullptr;

		meth_ void update_aabb();

		void submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelElem& item) const;

		vector<LightmapItem*> m_lightmaps;

		float m_depth = 0.f;
		uint32_t m_layer_mask = 1;
	};
}


#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/map.h>
#endif

namespace two
{
	export_ enum class refl_ ModelFormat : unsigned int
	{
		obj,
		ply,
		gltf,

		Count
	};

	export_ struct refl_ TWO_GFX_EXPORT ImportConfig
	{
		ImportConfig() {}

		attr_ ModelFormat m_format = ModelFormat::obj;
		attr_ vec3 m_position = vec3(0.f);
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = vec3(1.f);
		attr_ mat4 m_transform = bxidentity();
		attr_ vector<string> m_exclude_elements; // = {};
		attr_ vector<string> m_exclude_materials; // = {};
		attr_ vector<string> m_include_elements; // = {};
		attr_ vector<string> m_include_materials; // = {};
		attr_ string m_suffix;
		attr_ bool m_force_reimport = false;
		attr_ bool m_cache_geometry = false;
		attr_ bool m_optimize_geometry = false;
		attr_ bool m_need_normals = true;
		attr_ bool m_need_uvs = true;
		attr_ bool m_no_transforms = false;
		attr_ uint32_t m_flags = ItemFlag::None;

		bool filter_element(const string& name) const;
		bool filter_material(const string& name) const;
	};

	export_ class refl_ TWO_GFX_EXPORT Import
	{
	public:
		Import(GfxSystem& gfx, const string& filepath, const ImportConfig& config);

		attr_ string m_name;
		attr_ string m_file;
		attr_ string m_path;

		GfxSystem& m_gfx;
		attr_ ImportConfig m_config;

		attr_ vector<Mesh*> m_meshes;
		attr_ vector<Model*> m_models;
		attr_ vector<Texture*> m_images;
		attr_ vector<Material*> m_materials;
		attr_ vector<Animation*> m_animations;

		map<int, Skeleton*> m_skeletons;

		vector<Node3> m_nodes;

		struct Item { uint32_t node; Model* model; int skin; };
		vector<Item> m_items;
	};

	export_ class TWO_GFX_EXPORT Importer
	{
	public:
		virtual ~Importer() {}
		virtual void import(Import& import, const string& filepath, const ImportConfig& config) = 0;
		virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) = 0;
		virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) = 0;
		virtual void repack(const string& filepath, const ImportConfig& config) = 0;
	};

	export_ TWO_GFX_EXPORT void import_to_prefab(GfxSystem& gfx, Prefab& prefab, Import& state, uint32_t flags = 0);
}

namespace two
{
#ifdef TWO_PREFABNODE
	export_ enum class refl_ PrefabType : unsigned int
	{
		None,
		Item,
		Model,
		Shape,
		Flare,
		Light
	};

	export_ struct refl_ TWO_GFX_EXPORT PrefabNode
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

	export_ class refl_ TWO_GFX_EXPORT Prefab
	{
	public:
		Prefab(const string& name);

		attr_ string m_name;
#ifdef TWO_PREFABNODE
		attr_ PrefabNode m_node;
#endif

		meth_ void add(Scene& scene, Mime* mime = nullptr);

		vector<Node3> m_nodes;
		struct Elem { uint32_t node; Item item; };
		vector<Elem> m_items;

		Aabb m_aabb;

		vector<Animation*> m_anims;
	};

	export_ TWO_GFX_EXPORT Prefab& import_prefab(GfxSystem& gfx, ModelFormat format, const string& name, const ImportConfig& config);
	export_ TWO_GFX_EXPORT void destroy_prefab(GfxSystem& gfx, Prefab& prefab);
}

namespace two
{
	export_ extern template class refl_ AssetStore<Texture>;
	export_ extern template class refl_ AssetStore<Program>;
	export_ extern template class refl_ AssetStore<Material>;
	export_ extern template class refl_ AssetStore<Model>;
	export_ extern template class refl_ AssetStore<Flow>;
	export_ extern template class refl_ AssetStore<Prefab>;
}


#include <stl/vector.h>

#include <bgfx/bgfx.h>

namespace two
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

		Texture m_texture;
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


#ifndef TWO_MODULES
#include <stl/span.h>
#endif

namespace two
{
	export_ enum refl_ IsometricAngle : unsigned int
	{
		NORTH = (1 << 0),
		SOUTH = (2 << 0),
		EAST = (1 << 8),
		WEST = (2 << 8)
	};

	export_ class refl_ TWO_GFX_EXPORT Camera
	{
	public:
		Camera();
		Camera(mat4 transform, mat4 projection, bool ortho = false);
		Camera(vec3 eye, vec3 at, vec3 up, float fov, float aspect, float near, float far);
		Camera(mat4 transform, float fov, float aspect, float near, float far);
		Camera(mat4 transform, vec2 rect, float near, float far);
		~Camera();

		attr_ vec3 m_eye = Z3;
		attr_ vec3 m_target = vec3(0.f);
		attr_ vec3 m_up = Y3;

		attr_ mat4 m_view;
		attr_ mat4 m_proj;

#if defined TWO_UNIFORM_BLOCKS
		attr_ FrustumBlock m_frustum;
#endif
		attr_ gpu_ float m_fov = 60.f;
		attr_ gpu_ float m_aspect = 1.f;
		attr_ gpu_ float m_near = 0.1f;
		attr_ gpu_ float m_far = 100.f;

		attr_ bool m_orthographic = false;
		attr_ float m_height = 1.f;

		attr_ bool m_no_update = false;

		attr_ bool m_optimize_ends = true;

		attr_ vec4 m_lod_offsets = { 0.1f, 0.3f, 0.6f, 0.8f };

		void update();

		meth_ void set_look_at(const vec3& eye, const vec3& target);
		meth_ void set_isometric(IsometricAngle angle, const vec3& position);

		Plane near_plane() const;
		Plane far_plane() const;

		mat4 projection(float near, float far, bool ndc = false);

		meth_ Ray ray(const vec2& offset) const;

		meth_ vec3 transform(const vec3& point) const;
		meth_ vec3 project(const vec3& point) const;
	};

	struct refl_ MirrorCamera
	{
		attr_ bool m_visible = false;
		attr_ Camera m_camera;
		attr_ mat4 m_mirror;
	};

	TWO_GFX_EXPORT func_ MirrorCamera mirror_camera(const Camera& sourcecam, Node3& node, float clipBias = 0.f);
}


#ifdef TWO_MODULES
#define _GLIBCXX_TYPE_TRAITS
#include <xmmintrin.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#define TEXTURE_CLAMP BGFX_TEXTURE_U_CLAMP | BGFX_TEXTURE_V_CLAMP
#define TEXTURE_CLAMP_UVW BGFX_TEXTURE_U_CLAMP | BGFX_TEXTURE_V_CLAMP | BGFX_TEXTURE_W_CLAMP
#define TEXTURE_POINT BGFX_TEXTURE_MIN_POINT | BGFX_TEXTURE_MAG_POINT
#endif




#ifndef TWO_MODULES
#include <stl/table.h>
#endif

namespace two
{
	export_ enum class refl_ DepthMethod : unsigned int
	{
		Depth,
		DepthPacked,
		Distance,
		Count
	};

	export_ struct refl_ DepthParams
	{
		attr_ gpu_ float m_depth_bias = 0.f;
		attr_ gpu_ float m_depth_normal_bias = 0.f;
		attr_ gpu_ float m_depth_z_far = 0.f;
	};

	export_ struct refl_ DistanceParams
	{
		attr_ gpu_ vec3 m_eye = vec3(0.f);
		attr_ gpu_ float m_near = 0.f;
		attr_ gpu_ float m_far = 1.f;
	};

	export_ TWO_GFX_EXPORT bool queue_depth(GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element);
	export_ TWO_GFX_EXPORT void pass_depth(GfxSystem& gfx, Render& render, Pass& pass, bool submit = true);
	export_ TWO_GFX_EXPORT void pass_depth(GfxSystem& gfx, Render& render);

	export_ class refl_ TWO_GFX_EXPORT BlockDepth : public DrawBlock
	{
	public:
		BlockDepth(GfxSystem& gfx);
		~BlockDepth();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		struct DepthUniform
		{
			void createUniforms()
			{
				u_depth_p0 = bgfx::createUniform("u_depth_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
				u_distance_p0 = bgfx::createUniform("u_distance_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
				u_distance_p1 = bgfx::createUniform("u_distance_p1", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle u_depth_p0;
			bgfx::UniformHandle u_distance_p0;
			bgfx::UniformHandle u_distance_p1;

		} u_depth;

		DepthMethod m_depth_method = DepthMethod::Depth;
		DepthParams m_depth_params = {};
		DistanceParams m_distance_params = {};

		Program* m_depth_program = nullptr;
		Program* m_distance_program = nullptr;
	};
}


#ifndef TWO_MODULES
#endif


#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/span.h>
#endif

#include <bgfx/bgfx.h>

namespace two
{
	export_ struct refl_ TWO_GFX_EXPORT GpuMesh
	{
		GpuMesh();
		GpuMesh(PrimitiveType primitive, uint32_t vertex_count, uint32_t index_count);

		PrimitiveType m_primitive = PrimitiveType::Triangles;
		uint32_t m_vertex_format = 0;
		
		uint32_t m_vertex_count = 0;
		uint32_t m_index_count = 0;
		bool m_index32 = false;
		bool m_dynamic = false;

		const bgfx::Memory* m_vertex_memory = nullptr;
		const bgfx::Memory* m_index_memory = nullptr;

		span<void> m_vertices = {};
		span<void> m_indices = {};

		MeshAdapter m_writer = {};
	};
	
	export_ TWO_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

	export_ TWO_GFX_EXPORT GpuMesh alloc_mesh(PrimitiveType primitive, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count, bool index32);
	export_ TWO_GFX_EXPORT GpuMesh alloc_mesh(PrimitiveType primitive, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count);
	export_ TWO_GFX_EXPORT GpuMesh alloc_mesh(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count);

	export_ class refl_ TWO_GFX_EXPORT Mesh
	{
	public:
		Mesh(const string& name, bool readback = false);
		~Mesh();

		Mesh(Mesh&& other) = default;
		Mesh& operator=(Mesh&& other) = default;

		attr_ string m_name;
		attr_ uint16_t m_index;
		attr_ PrimitiveType m_primitive = PrimitiveType::Triangles;
		attr_ Aabb m_aabb = {};
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = vec3(0.f);
		attr_ bool m_readback = false;

		attr_ uint32_t m_vertex_format = 0;
		attr_ bool m_qnormals = false;

		attr_ uint32_t m_vertex_count = 0;
		attr_ uint32_t m_index_count = 0;
		attr_ bool m_index32 = false;

		attr_ Material* m_material = nullptr;

		bgfx::VertexBufferHandle m_vertices = BGFX_INVALID_HANDLE;
		bgfx::IndexBufferHandle m_indices = BGFX_INVALID_HANDLE;

		struct Morph
		{
			bgfx::VertexBufferHandle m_vertices = BGFX_INVALID_HANDLE;
		};

		vector<Morph> m_morphs;

		attr_ bool m_is_dynamic = false;
		attr_ bool m_is_direct = false;

		struct Range { uint32_t m_start = 0U; uint32_t m_count = 0U; };
		Range m_range;

		struct Dynamic
		{
			bgfx::DynamicVertexBufferHandle m_vertices = BGFX_INVALID_HANDLE;
			bgfx::DynamicIndexBufferHandle m_indices = BGFX_INVALID_HANDLE;

		} m_dynamic;

		struct Direct
		{
			bgfx::TransientVertexBuffer m_vertices;
			bgfx::TransientIndexBuffer m_indices;
			MeshAdapter m_adapter;

		} m_direct;

		struct UvBounds { vec2 min; vec2 max; };
		UvBounds m_uv0_rect = {};
		UvBounds m_uv1_rect = {};

		vector<uint8_t> m_cached_vertices;
		vector<uint8_t> m_cached_indices;

		attr_ MeshAdapter m_cache;

		meth_ void clear();
		meth_ void write(const MeshPacker& packer, bool optimize = false, bool dynamic = false);
		meth_ void xwrite(const MeshPacker& packer, const mat4& transform, bool optimize = false, bool dynamic = false);
		meth_ void morph(const MeshPacker& packer);
		meth_ void upload(const GpuMesh& gpu_mesh, bool optimize = false);
		meth_ void cache(const GpuMesh& gpu_mesh);

		GpuMesh begin();
		void update(const GpuMesh& gpu_mesh);

		meth_ MeshAdapter& direct(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count = 0);

		uint64_t submit(bgfx::Encoder& encoder) const;

		void submit_morph(bgfx::Encoder& encoder, size_t index, size_t morph) const;
	};
}

namespace two
{
	constexpr size_t c_max_shape_size = 256U;

	using cstring = const char*;

	export_ class refl_ TWO_GFX_EXPORT Direct
	{
	public:
		constr_ Direct();
		constr_ Direct(Item& item);

		//void begin();
		//Mesh& batch(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count = 0);

		//attr_ Mesh m_mesh;
		//attr_ Model m_model;
		attr_ Item* m_item = nullptr;

		//vector<Mesh> m_batches;
	};

	export_ class refl_ TWO_GFX_EXPORT ImmediateDraw
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
		void draw(const mat4& transform, span<ProcShape> shapes);
		void draw(const mat4& transform, span<ProcShape> shapes, DrawMode draw_mode);

		void draw(Batch& batch, const mat4& transform, span<ProcShape> shapes, ShapeSize size, DrawMode draw_mode);

		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state);
		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode);
		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode, Batch& batch);
	};

	export_ class refl_ TWO_GFX_EXPORT SymbolIndex
	{
	public:
		SymbolIndex();
		~SymbolIndex();

		Model& symbol_model(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		Material& symbol_material(GfxSystem& gfx, const Symbol& symbol, DrawMode draw_mode);

		struct Impl;
		unique<Impl> m_impl;
	};

	export_ TWO_GFX_EXPORT object<Model> gen_model(cstring name, const ProcShape& shape, bool readback = false);
	export_ TWO_GFX_EXPORT object<Model> gen_model(cstring name, span<ProcShape> shapes, bool readback = false);

	export_ TWO_GFX_EXPORT void gen_model(const ProcShape& shape, Model& model, bool readback = false, Material* material = nullptr);
	export_ TWO_GFX_EXPORT void gen_model(span<ProcShape> shapes, Model& model, bool readback = false, Material* material = nullptr);

	export_ TWO_GFX_EXPORT void gen_mesh(const ProcShape& shapes, Model& model, DrawMode draw_mode, bool readback = false, Material* material = nullptr);
	export_ TWO_GFX_EXPORT void gen_mesh(span<ProcShape> shapes, Model& model, DrawMode draw_mode, bool readback = false, Material* material = nullptr);

	export_ TWO_GFX_EXPORT void gen_geom(const ProcShape& shapes, MeshPacker& model, DrawMode draw_mode);
	export_ TWO_GFX_EXPORT void gen_geom(span<ProcShape> shapes, MeshPacker& model, DrawMode draw_mode);


	export_ class refl_ TWO_GFX_EXPORT Lines
	{
	public:
		constr_ Lines();
		constr_ Lines(const vector<vec3>& points);
		constr_ Lines(const Curve3& curve, size_t subdiv);

		struct Segment { vec3 pos0; float dist0; vec3 pos1; float dist1; Colour col0; Colour col1; };
		vector<Segment> m_segments;
		bool m_started = false;

		Aabb m_aabb;
		float m_radius;

		meth_ void add(const vec3& start, const vec3& end, const Colour& start_colour = Colour(1.f), const Colour& end_colour = Colour(1.f));
		meth_ void start(const vec3& position, const Colour& colour = Colour(1.f));
		meth_ void next(const vec3& position, const Colour& colour = Colour(1.f));
		meth_ void setup();
		meth_ void write(Mesh& mesh);
		meth_ void commit(Batch& batch);

		void update_aabb();
		void update_sphere();
	};
}



namespace two
{
	export_ TWO_GFX_EXPORT void pass_resolve(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT void pass_effects(GfxSystem& gfx, Render& render);
}


#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/map.h>
#endif

namespace two
{
	export_ enum ShaderOptionFilter : unsigned int
	{
		UNPACK_DEPTH,
		SOURCE_DEPTH,
		SOURCE_0_CUBE,
		SOURCE_0_ARRAY,
		DEBUG_UV,
	};

	export_ struct FilterUniform
	{
		void createUniforms()
		{
			s_source_0		= bgfx::createUniform("s_source_0",		bgfx::UniformType::Sampler);
			s_source_1		= bgfx::createUniform("s_source_1",		bgfx::UniformType::Sampler);
			s_source_2		= bgfx::createUniform("s_source_2",		bgfx::UniformType::Sampler);
			s_source_3		= bgfx::createUniform("s_source_3",		bgfx::UniformType::Sampler);
			s_source_depth	= bgfx::createUniform("s_source_depth",	bgfx::UniformType::Sampler);
			
			u_filter_p0		= bgfx::createUniform("u_filter_p0",	bgfx::UniformType::Vec4);

			u_source_levels = bgfx::createUniform("u_source_levels", bgfx::UniformType::Vec4);
			u_source_crop	= bgfx::createUniform("u_source_crop",	 bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle s_source_0;
		bgfx::UniformHandle s_source_1;
		bgfx::UniformHandle s_source_2;
		bgfx::UniformHandle s_source_3;
		bgfx::UniformHandle s_source_depth;

		bgfx::UniformHandle u_filter_p0;

		bgfx::UniformHandle u_source_levels;
		bgfx::UniformHandle u_source_crop;
	};

	export_ class refl_ TWO_GFX_EXPORT BlockFilter : public GfxBlock
	{
	public:
		BlockFilter(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		meth_ void submit(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		meth_ void quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, uint64_t flags = 0U, bool render = false);

		meth_ void multiply(float mul);

		meth_ void source0p(Texture& texture, ProgramVersion& program, int level = 0, uint32_t flags = UINT32_MAX);

		meth_ void source0(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source1(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source2(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source3(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void sourcedepth(Texture& texture, uint32_t flags = UINT32_MAX);

		void uniform(const Pass& pass, const string& name, const mat4& value);
		meth_ void uniform(const Pass& pass, const string& name, const vec4& value);
		meth_ void uniforms(const Pass& pass, const string& name, span<float> values);
		void uniforms4(const Pass& pass, const string& name, span<vec4> values);

		FilterUniform u_uniform;

		map<string, bgfx::UniformHandle> m_uniforms;

		Program& m_quad_program;

		float m_multiply = 1.f;
	};

	export_ class refl_ TWO_GFX_EXPORT BlockCopy : public GfxBlock
	{
	public:
		BlockCopy(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		meth_ void submit(const Pass& pass, FrameBuffer& fbo, Texture& texture, const RenderQuad& quad, uint64_t flags = 0U);
		meth_ void quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, uint64_t flags = 0U);

		meth_ void debug_show_texture(Render& render, Texture& texture, const vec4& rect, int level = 0);

		BlockFilter& m_filter;

		Program& m_program;
	};
}


#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/span.h>
#endif


#include <stl/vector.h>

namespace two
{
	export_ struct refl_ TWO_GFX_EXPORT ClusteredFrustum : public Frustum
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

	export_ TWO_GFX_EXPORT void compute_frustum_subdiv(ClusteredFrustum& frustum, vec2 clip_size, size_t slices = 16);
	export_ TWO_GFX_EXPORT void compute_frustum_subdiv_square(ClusteredFrustum& frustum, vec2 clip_size, size_t slices = 16, size_t max_clusters = 8192);
}

#if defined TWO_UNIFORM_BLOCKS
#endif

namespace bgfx
{
	struct Encoder;
}

namespace two
{
	constexpr uint32_t CONFIG_MAX_LIGHT_COUNT = 256;
	constexpr uint32_t CONFIG_MAX_LIGHT_INDEX = CONFIG_MAX_LIGHT_COUNT - 1;

	constexpr uint32_t CONFIG_CLUSTER_SLICE_COUNT = 16;

	//
	// Light UBO           Froxel Record Buffer     per-cluster light list texture
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
	//  |....|                                          h = num clusters
	//  |....|
	//  +----+
	// 256 lights max
	//

	// Max number of clusters limited by:
	// - max texture size [min 2048]
	// - chosen texture width [64]
	// - size of CPU-side indices [16 bits]
	// Also, increasing the number of clusters adds more pressure on the "record buffer" which stores
	// the light indices per cluster. The record buffer is limited to 65536 entries, so with
	// 8192 clusters, we can store 8 lights per clusters assuming they're all used. In practice, some
	// clusters are not used, so we can store more.
	static constexpr uint32_t CLUSTER_BUFFER_ENTRY_COUNT_MAX = 8192;

	class TWO_GFX_EXPORT Froxelizer
	{
	public:
		Froxelizer(GfxSystem& gfx);
		~Froxelizer();

		void setup();
		bool update(const uvec4& rect, const mat4& projection, float near, float far);

		// update Records and Froxels texture with lights data. this is thread-safe.
		void clusterize_lights(const Camera& camera, span<Light*> lights);
		void clusterize_loop(const Camera& camera, span<Light*> lights);

		// send cluster data to GPU
		void upload();
		void submit(const Pass& pass) const;
		void submit(bgfx::Encoder& encoder) const;

		void compute_clusters();

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

		void clusterize_assign_records_compress(uint32_t num_lights);

		void clusterize_light_group(const Camera& camera, span<Light*> lights, uint32_t offset, uint32_t stride);

		GfxSystem& m_gfx;

		ClusteredFrustum m_frustum;

		vector<Frustum> m_debug_clusters;

		struct Impl;
		unique<Impl> m_impl;

		mat4 m_proj;

		// needed for update()
		uvec4 m_viewport;
		vec4 m_pz = {};
		uvec3 m_pf = {};
		float m_near = 0.0f;        // camera near
		float m_light_far = 100.f;
		float m_light_near = 5.f;  // light near (first slice)

		// track if we need to update our internal state before clusterizing
		uint8_t m_dirty = 0;
		enum class Dirty {
			None = 0,
			Viewport,
			Projection
		};
	};

}


#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/span.h>
#endif


#ifndef TWO_MODULES
#endif

namespace two
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

	export_ struct AtlasIndex { uint8_t slice = UINT8_MAX; uint16_t slot = UINT16_MAX; };

	export_ class refl_ TWO_GFX_EXPORT Light
	{
	public:
		constr_ Light(Node3& node, LightType type = LightType::Point, bool shadows = false, Colour colour = Colour::White, float energy = 1.f, float range = 1.f);

		attr_ Node3* m_node = nullptr;
		attr_ LightType m_type = LightType::Point;
		attr_ bool m_visible = true;
		attr_ Colour m_colour = Colour::White;
		attr_ float m_range = 1.f;
		attr_ float m_energy = 1.f;
		attr_ float m_specular = 1.f;
		attr_ float m_attenuation = 0.5f;
		attr_ bool m_shadows = false;
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

		uint32_t m_index = 0;
		AtlasIndex m_shadow_index = {};
	};
}

namespace two
{
namespace gfx
{
	export_ TWO_GFX_EXPORT func_ void setup_pipeline_minimal(GfxSystem& gfx);

	export_ TWO_GFX_EXPORT meth_ TPool<Node3>&  nodes(Scene& scene);
	export_ TWO_GFX_EXPORT meth_ TPool<Item>&   items(Scene& scene);
	export_ TWO_GFX_EXPORT meth_ TPool<Batch>&  batches(Scene& scene);
	export_ TWO_GFX_EXPORT meth_ TPool<Direct>& directs(Scene& scene);
	export_ TWO_GFX_EXPORT meth_ TPool<Mime>&   mimes(Scene& scene);
	export_ TWO_GFX_EXPORT meth_ TPool<Light>&  lights(Scene& scene);
	export_ TWO_GFX_EXPORT meth_ TPool<Flare>&	flares(Scene& scene);

	export_ TWO_GFX_EXPORT func_ Gnode& node(Gnode& parent, const vec3& position = vec3(0.f), const quat& rotation = ZeroQuat, const vec3& scale = vec3(1.f));
	export_ TWO_GFX_EXPORT Gnode& node(Gnode& parent, const mat4& transform);
	export_ TWO_GFX_EXPORT Gnode& node(Gnode& parent, const Transform& transform);
	export_ TWO_GFX_EXPORT Gnode& transform(Gnode& parent, const vec3& position, const quat& rotation, const vec3& scale);
	export_ TWO_GFX_EXPORT Gnode& transform(Gnode& parent, const vec3& position, const quat& rotation);
	export_ TWO_GFX_EXPORT func_ Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0, Material* material = nullptr);
	export_ TWO_GFX_EXPORT void draw(Scene& scene, const mat4& transform, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	export_ TWO_GFX_EXPORT func_ void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	export_ TWO_GFX_EXPORT func_ Item& sprite(Gnode& parent, const Image256& image, const vec2& size, uint32_t flags = 0, Material* material = nullptr);
	export_ TWO_GFX_EXPORT func_ Item& item(Gnode& parent, const Model& model, uint32_t flags = 0, Material* material = nullptr);
	export_ TWO_GFX_EXPORT func_ Batch& batch(Gnode& parent, Item& item, uint16_t stride);
	export_ TWO_GFX_EXPORT func_ Batch& instances(Gnode& parent, Item& item, span<mat4> transforms = {});
	export_ TWO_GFX_EXPORT func_ void prefab(Gnode& parent, const Prefab& prefab, bool transform = true, uint32_t flags = 0, Material* material = nullptr);
	export_ TWO_GFX_EXPORT func_ Item* model(Gnode& parent, const string& name, uint32_t flags = 0, Material* material = nullptr);
	export_ TWO_GFX_EXPORT func_ Mime& animated(Gnode& parent, Item& item);
	export_ TWO_GFX_EXPORT func_ Flare& flows(Gnode& parent, const Flow& emitter, uint32_t flags = 0);
	export_ TWO_GFX_EXPORT func_ Light& light(Gnode& parent, LightType type, bool shadows, Colour colour, float range = 0.f, float attenuation = 0.5f);
	export_ TWO_GFX_EXPORT func_ Light& sun_light(Gnode& parent, float azimuth, float elevation);
	export_ TWO_GFX_EXPORT func_ void radiance(Gnode& parent, const string& texture, BackgroundMode background);

	using ManualJob = void(*)(GfxSystem&, Render&, const Pass&);
	using CustomSky = void(*)(GfxSystem&, Render&);

	export_ TWO_GFX_EXPORT void manual_job(Gnode& parent, PassType pass, ManualJob job);
	export_ TWO_GFX_EXPORT void custom_sky(Gnode& parent, CustomSky func);

	export_ TWO_GFX_EXPORT Light& direct_light_node(Gnode& parent);
	export_ TWO_GFX_EXPORT Light& direct_light_node(Gnode& parent, const quat& rotation);
	export_ TWO_GFX_EXPORT func_ Light& direct_light_node(Gnode& parent, const vec3& direction);

	export_ TWO_GFX_EXPORT func_ Material& solid_material(GfxSystem& gfx, const string& name, const Colour& colour);

	export_ TWO_GFX_EXPORT Material& pbr_material(GfxSystem& gfx, const string& name, const MaterialPbr& pbr_block);
	export_ TWO_GFX_EXPORT func_ Material& pbr_material(GfxSystem& gfx, const string& name, const Colour& albedo, float metallic = 0.f, float roughness = 1.f);

	export_ TWO_GFX_EXPORT func_ Model& model_suzanne(GfxSystem& gfx);
}
}


#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/function.h>
#include <stl/span.h>
#endif
#ifndef TWO_BGFX_EXPORT
#define TWO_BGFX_EXPORT TWO_GFX_EXPORT
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

namespace two
{
	class Vg;

	export_ class refl_ TWO_GFX_EXPORT GfxWindow : public BgfxContext
	{
	public:
		GfxWindow(GfxSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main = true);
		~GfxWindow();

		virtual void reset_fb(const uvec2& size) override;

		GfxSystem& m_gfx;
		Vg* m_vg = nullptr;

		object<RenderTarget> m_target;

		uint16_t m_vg_handle = UINT16_MAX;
		using ResetVg = uint16_t(*)(GfxWindow&, Vg&); ResetVg m_reset_vg;

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

	export_ class refl_ TWO_GFX_EXPORT GfxSystem : public BgfxSystem
	{
	public:
		constr_ GfxSystem(const string& resource_path);
		~GfxSystem();

		JobSystem* m_job_system = nullptr;

		bgfx::Encoder* m_encoders[8] = {};
		size_t m_num_encoders = 0;

		attr_ Renderer m_renderer;

		attr_ BlockCopy* m_copy = nullptr;
		attr_ BlockFilter* m_filter = nullptr;

		attr_ bool m_flip_y = false;

		attr_ RenderFrame m_render_frame;

		meth_ RenderTarget& main_target();

		virtual bool begin_frame() final;
		virtual void end_frame() final;

		void render_contexts();

		void init(GfxWindow& context);

		using PipelineDecl = void(*)(GfxSystem& gfx, Renderer& pipeline, bool deferred);
		void init_pipeline(PipelineDecl pipeline);

		meth_ void default_pipeline();

		meth_ void add_resource_path(const string& path, bool relative = true);

		void set_renderer(Shading shading, const RenderFunc& renderer);
		RenderFunc renderer(Shading shading);

		void render(Shading shading, RenderFunc renderer, RenderTarget& target, Viewport& viewport);
		RenderFrame render_frame();

		GfxWindow& context(size_t index = 0);

		bx::FileReaderI& file_reader();
		bx::FileWriterI& file_writer();

		LocatedFile locate_file(const string& file);
		LocatedFile locate_file(const string& file, span<string> extensions);

		TPool<Mesh>& meshes();
		TPool<Rig>& rigs();
		TPool<Animation>& animations();

		attr_ AssetStore<Texture>& textures();
		attr_ AssetStore<Program>& programs();
		attr_ AssetStore<Material>& materials();
		attr_ AssetStore<Model>& models();
		attr_ AssetStore<Flow>& flows();
		attr_ AssetStore<Prefab>& prefabs();

		void add_importer(ModelFormat format, Importer& importer);
		Importer* importer(ModelFormat format);

		Texture& default_texture(TextureHint hint);

		meth_ Material& debug_material();
		meth_ Model& create_model(const string& name);
		meth_ Model& create_model_geo(const string& name, const MeshPacker& geometry, bool readback = false, bool optimize = false);
		meth_ Model& create_model_gpu(const string& name, const GpuMesh& gpu_mesh, bool readback = false, bool optimize = false);
		meth_ Material& fetch_material(const string& name, const string& shader, bool builtin = true);
		meth_ Material& fetch_image256_material(const Image256& image);

		meth_ Model& shape(const Shape& shape, const Symbol& symbol = {}, DrawMode draw_mode = PLAIN);
		meth_ Material& symbol_material(const Symbol& symbol, DrawMode draw_mode = PLAIN);

		void create_debug_materials();

	public:
		struct Impl;
		unique<Impl> m_impl;
	};
}


#ifndef TWO_MODULES
#ifdef _MSC_VER
#endif
#endif

namespace two
{
	class SoundManager;
	class Sound;

#ifndef _MSC_VER
	export_ extern template class Graph<Gnode>;
#endif

	export_ class refl_ TWO_GFX_EXPORT Gnode : public Graph<Gnode>
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
		Batch* m_batch = nullptr;
		Direct* m_direct = nullptr;
		Mime* m_animated = nullptr;
		Flare* m_particles = nullptr;
		Light* m_light = nullptr;
		GIProbe* m_gi_probe = nullptr;
		LightmapAtlas* m_lightmap_atlas = nullptr;
		SoundManager* m_sound_manager = nullptr;
		Sound* m_sound = nullptr;
	};

	export_ extern template class refl_ TPool<Node3>;
	export_ extern template class refl_ TPool<Item>;
	export_ extern template class refl_ TPool<Batch>;
	export_ extern template class refl_ TPool<Direct>;
	export_ extern template class refl_ TPool<Mime>;
	export_ extern template class refl_ TPool<Light>;
	export_ extern template class refl_ TPool<Flare>;

	export_ TWO_GFX_EXPORT void debug_tree(Gnode& node, size_t index = 0, size_t depth = 0);
}


#ifndef TWO_MODULES
#include <stl/function.h>
#include <stl/vector.h>
#include <stl/span.h>
#endif


#ifndef TWO_MODULES
#include <stl/span.h>
#endif


#ifndef TWO_MODULES
#include <stl/function.h>
#endif


#include <stl/vector.h>

#include <bgfx/bgfx.h>

class MaskedOcclusionCulling;

namespace two
{
	export_ class refl_ TWO_GFX_EXPORT Culler
	{
	public:
		Culler(Viewport& viewport);
		~Culler();

		attr_ Viewport* m_viewport;

		MaskedOcclusionCulling* m_moc = nullptr;

		void render(Render& render);

		void begin(Render& render);
		void rasterize(Render& render);
		void cull(Render& render);
		void debug(Render& render);

		vector<float> m_depth_data;
		Texture m_depth_texture;
	};
}

namespace two
{
	using cstring = const char*;

	export_ enum class refl_ MSAA : unsigned int
	{
		Disabled,
		X2,
		X4,
		X8,
		X16,
		Count
	};

	export_ enum class refl_ Shading : unsigned int
	{
		Wireframe,
		Solid,
		Shaded,
		Volume,
		Voxels,
		Lightmap,
		Clear,

		Count
	};

	export_ extern TWO_GFX_EXPORT GridECS* g_viewer_ecs;

	export_ class refl_ TWO_GFX_EXPORT Viewport : public OEntt
	{
	public:
		constr_ Viewport() {}
		constr_ Viewport(Camera& camera, Scene& scene, const vec4& rect = vec4(0.f), bool scissor = false);
		~Viewport();

		Viewport(Viewport&& other) = default;
		Viewport& operator=(Viewport&& other) = default;

		attr_ Camera* m_camera;
		attr_ Scene* m_scene;

		attr_ uint16_t m_index = 0;
		attr_ bool m_autorender = true;
		attr_ vec4 m_rect = vec4(0.f);
		attr_ bool m_scissor = false;
		attr_ Colour m_clear_colour = Colour::Black;
		attr_ Shading m_shading = Shading::Shaded;
		attr_ Lighting m_lighting = Lighting::Clustered;
		attr_ bool m_clustered = false;
		attr_ bool m_to_gamma = false;

		using RenderTask = function<void(Render&)>;
		vector<RenderTask> m_tasks;
		
		unique<Culler> m_culler;

		unique<Froxelizer> m_clusters;

		void pass(const Pass& pass);

		meth_ void cull(Render& render);
		meth_ void render(Render& render);

		meth_ void set_clustered(GfxSystem& gfx);

		Ray ray(const vec2& pos);
		vec3 raycast(const Plane& plane, const vec2& pos);
	};
}

#ifdef TWO_UNIFORM_BLOCKS
#endif

#include <bgfx/bgfx.h>

namespace two
{
	export_ struct refl_ TWO_GFX_EXPORT RenderQuad
	{
		attr_ vec4 m_source = vec4(vec2(0.f), vec2(1.f));
		attr_ vec4 m_dest = vec4(vec2(0.f), vec2(1.f));
		attr_ bool m_fbo_flip = false;
		attr_ bool m_relative = false;
		bool m_blit = false;
		constr_ RenderQuad() {}
		constr_ RenderQuad(const vec4& crop, const vec4& dest, bool fbo_flip = false, bool relative = false)
			: m_source(crop), m_dest(dest), m_fbo_flip(fbo_flip), m_relative(relative)
		{}
		constr_ RenderQuad(const vec4& rect, bool fbo_flip = false, bool relative = false)
			: m_source(rect), m_dest(rect), m_fbo_flip(fbo_flip), m_relative(relative), m_blit(true)
		{}
	};

	export_ class refl_ TWO_GFX_EXPORT FrameBuffer
	{
	public:
		constr_ FrameBuffer();
		constr_ FrameBuffer(const uvec2& size, TextureFormat format, uint64_t flags = 0U);
		constr_ FrameBuffer(const uvec2& size, span<Texture*> textures);
		FrameBuffer(const uvec2& size, void* window = nullptr);
		FrameBuffer(const uvec2& size, Texture& texture, span<bgfx::Attachment> attach);
		FrameBuffer(Texture& texture);
		~FrameBuffer();

		FrameBuffer(FrameBuffer&& other);
		FrameBuffer& operator=(FrameBuffer&& other);

		attr_ uvec2 m_size;
		attr_ Texture m_tex;

		Texture* m_attach[6] = {};
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		
		meth_ bool valid() const;

		//Texture& tex(size_t i) { return *m_attach[i]; }

		operator bgfx::FrameBufferHandle() const { return m_fbo; }

	private:
		FrameBuffer(const FrameBuffer& other) = default;
		FrameBuffer& operator=(const FrameBuffer& other) = default;
	};

	export_ class refl_ SwapBuffer
	{
	public:
		constr_ SwapBuffer() {}
		meth_ void create(const uvec2& size, TextureFormat color_format);
		~SwapBuffer();
		meth_ FrameBuffer& swap() { m_state = !m_state; return m_state ? m_one : m_two; }
		meth_ FrameBuffer& current() { return m_state ? m_one : m_two; }
		meth_ Texture& last() { return m_state ? m_one.m_tex : m_two.m_tex; }
		attr_ FrameBuffer m_one;
		attr_ FrameBuffer m_two;
		bool m_state = false;
	};

	export_ class refl_ Cascade
	{
	public:
		constr_ Cascade() {}
		meth_ void create(const uvec2& size, TextureFormat color_format);
		~Cascade();
		attr_ Texture m_texture;
		attr_ size_t m_num_mips;
		unique<FrameBuffer> m_fbos[9] = {};

		// @todo expose array members to reflection and get rid of this
		meth_ FrameBuffer& level(uint8_t index) { return *m_fbos[index]; }
	};

	export_ class refl_ SwapCascade
	{
	public:
		constr_ SwapCascade() {}
		meth_ void create(const uvec2& size, TextureFormat color_format);
		~SwapCascade();
		meth_ Cascade& swap() { m_state = !m_state; return m_state ? m_one : m_two; }
		meth_ Cascade& last() { return m_state ? m_one : m_two; }
		attr_ Cascade m_one;
		attr_ Cascade m_two;
		bool m_state = false;
	};

	export_ struct TWO_GFX_EXPORT GBuffer : public FrameBuffer
	{
		void create(const uvec2& size, TextureFormat color_format, uint64_t flags);

		Texture m_depth;
		Texture m_position;
		Texture m_normal;
		Texture m_albedo;
		Texture m_surface;
	};

	export_ class refl_ TWO_GFX_EXPORT RenderTarget : public FrameBuffer
	{
	public:
		RenderTarget(const uvec2& size, void* window = nullptr);
		~RenderTarget();

		attr_ FrameBuffer m_backbuffer;

		attr_ MSAA m_msaa = MSAA::Disabled;

		attr_ bool m_mrt = true;

		attr_ Texture m_depth;
		attr_ Texture m_diffuse;

		attr_ Texture m_specular;
		attr_ Texture m_normal_rough;
		attr_ Texture m_sss;

		attr_ SwapBuffer m_ping_pong;
		attr_ SwapBuffer m_post;

		attr_ Cascade m_cascade;
		attr_ SwapCascade m_swap_cascade;

		attr_ bool m_deferred = false;

		GBuffer m_gbuffer;
	};
}

#include <bgfx/bgfx.h>

namespace two
{
#define PICKING_BUFFER_SIZE 8  // Size of the ID buffer

	using PickCallback = function<void(Item*)>;
	using MultipickCallback = function<void(span<Item*>)>;

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

	export_ class TWO_GFX_EXPORT Picker
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

		FrameBuffer m_fbo;
		Texture m_fbo_texture;
		Texture m_fbo_depth;

		Texture m_readback_texture;

		vector<uint32_t> m_data;
	};
}


#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/function.h>
#include <stl/table.h>
#endif

namespace two
{
	using PassJob = function<void(GfxSystem&, Render&, const Pass&)>;

	export_ TWO_GFX_EXPORT void pipeline_minimal(GfxSystem& gfx, Renderer& pipeline, bool deferred);

	export_ struct TWO_GFX_EXPORT PassJobs
	{
		table<PassType, vector<PassJob>> m_jobs;
	};

	export_ TWO_GFX_EXPORT func_ void pass_clear_fbo(GfxSystem& gfx, Render& render, FrameBuffer& fbo, const Colour& colour, float depth = 1.f);

	export_ TWO_GFX_EXPORT func_ void pass_clear(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_gclear(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_depth(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_background(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_solid(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_flip(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_EXPORT func_ void render_minimal(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void render_solid(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void render_clear(GfxSystem& gfx, Render& render);
}


#ifndef TWO_MODULES
#endif

#include <bgfx/bgfx.h>

namespace two
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
		attr_ gpu_ Colour m_colour = Colour::White;
		attr_ gpu_ float m_energy = 1.0f;
		attr_ gpu_ Colour m_ambient = Colour::Black;
		attr_ Texture* m_texture = nullptr;
		attr_ Texture* m_filtered = nullptr;
		attr_ bool m_filter = true;
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
		attr_ Texture* m_texture = nullptr;
		using CustomRender = void(*)(GfxSystem&, Render&); CustomRender m_custom_function;
	};

	export_ struct refl_ Skylight
	{
		attr_ bool m_enabled = false;
		attr_ float m_intensity = 1.f;
		attr_ vec3 m_position = vec3(0.f, 1.f, 0.f);
		attr_ gpu_ vec3 m_direction;
		attr_ gpu_ Colour m_color;
		attr_ gpu_ Colour m_ground;
	};

	export_ struct refl_ Fog
	{
		attr_ bool m_enabled = false;
		attr_ gpu_ float m_density = 0.01f;
		attr_ gpu_ Colour m_colour = Colour::White;

		attr_ gpu_ bool m_depth = false;
		attr_ gpu_ float m_depth_begin = 0.f;
		attr_ gpu_ float m_depth_end = 0.f;
		attr_ gpu_ float m_depth_curve = 1.f;

		attr_ gpu_ bool m_height = false;
		attr_ gpu_ float m_height_min = 0.f;
		attr_ gpu_ float m_height_max = 1.f;
		attr_ gpu_ float m_height_curve = 0.1f;

		attr_ gpu_ bool m_transmit = false;
		attr_ gpu_ float m_transmit_curve = 1.f;
	};

	export_ struct refl_ Zone
	{
		attr_ Background m_background;
		attr_ Radiance m_radiance;
		attr_ Sun m_sun;
		attr_ Skylight m_skylight;
		attr_ Fog m_fog;
	};

	class Shot;

	export_ class refl_ TWO_GFX_EXPORT Scene
	{
	public:
		constr_ Scene(GfxSystem& gfx);
		~Scene();

		GfxSystem& m_gfx;

		object<ImmediateDraw> m_immediate;
		object<ParticleSystem> m_particle_system;
		object<PassJobs> m_pass_jobs;

		unique<ObjectPool> m_pool;

		attr_ uint32_t m_index;
		attr_ Gnode m_graph;
		attr_ Node3 m_root_node;
		attr_ Zone m_env;
		attr_ Ref m_user;

		meth_ Gnode& begin();
		meth_ void update();

		void debug_items(Render& render);

		vector<Sound*> m_orphan_sounds;
	};

	export_ TWO_GFX_EXPORT void cull_items(Scene& scene, const Plane6& planes, vector<Item*>& items);

	export_ TWO_GFX_EXPORT void gather_items(Scene& scene, const Camera& camera, vector<Item*>& items);
	export_ TWO_GFX_EXPORT void gather_occluders(Scene& scene, const Camera& camera, vector<Item*>& occluders);
	export_ TWO_GFX_EXPORT void gather_lights(Scene& scene, vector<Light*>& lights);

	export_ TWO_GFX_EXPORT void gather_render(Scene& scene, Render& render);
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_MODULES
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_GFX_EXPORT Type& type<two::AnimTarget>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Interpolation>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TextureHint>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TextureFormat>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShaderType>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::PassType>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TextureSampler>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Lighting>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlendMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::CullMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DepthDraw>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DepthTest>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialFlag>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShaderColor>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TextureChannel>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::PbrDiffuseMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::PbrSpecularMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::PhongEnvBlendMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::EmitterFlow>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ItemShadow>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ModelFormat>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::IsometricAngle>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DepthMethod>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::LightType>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShadowFlags>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MSAA>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Shading>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BackgroundMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Month>();
    
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::mat4>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Node3>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Item>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Batch>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Direct>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Mime>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Light>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Flare>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::span<two::Texture*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Mesh*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Model*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Texture*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Material*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Animation*>>();
    export_ template <> TWO_GFX_EXPORT Type& type<stl::vector<two::AnimPlay>>();
    
    export_ template <> TWO_GFX_EXPORT Type& type<two::Node3>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AnimTrack>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Animation>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Texture>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Skeleton>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Joint>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Skin>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Rig>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AnimNode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AnimPlay>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Mime>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShaderDefine>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ShaderBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ProgramMode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ProgramBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Program>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Frustum>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::FrustumSlice>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ProgramVersion>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Shot>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Pass>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::RenderFrame>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Render>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::GfxBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DrawBlock>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Renderer>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::Colour>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<float>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::vec4>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialBase>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialUser>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialAlpha>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialSolid>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialPoint>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialLine>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialFresnel>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialLit>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialPbr>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MaterialPhong>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockMaterial>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Material>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ModelElem>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Model>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Flow>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Flare>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockParticles>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Batch>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Item>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ImportConfig>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Import>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Prefab>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Texture>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Program>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Material>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Model>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Flow>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Prefab>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Camera>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::MirrorCamera>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DepthParams>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::DistanceParams>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockDepth>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::GpuMesh>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Mesh>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Direct>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ImmediateDraw>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::SymbolIndex>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Lines>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockFilter>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockCopy>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::ClusteredFrustum>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Light>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::GfxWindow>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::GfxSystem>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Gnode>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Node3>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Item>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Batch>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Direct>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Mime>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Light>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Flare>>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Culler>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Viewport>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::RenderQuad>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::FrameBuffer>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::SwapBuffer>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Cascade>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::SwapCascade>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::RenderTarget>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Sun>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Radiance>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Background>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Skylight>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Fog>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Zone>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::Scene>();
    export_ template <> TWO_GFX_EXPORT Type& type<two::BlockSky>();
}
//s#include <gfx/Uniform.h>


#include <stl/map.h>

namespace two
{
	enum ShaderOptionSkybox : unsigned int
	{
	};

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

	TWO_GFX_EXPORT quat sun_rotation(float azimuth, float altitude, const vec3& up = Y3, const vec3& north = X3);
	TWO_GFX_EXPORT quat sun_rotation(Month month, float latitude, float hour, float ecliptic_obliquity = 0.408407f, const vec3& up = Y3, const vec3& north = X3);

	export_ class refl_ TWO_GFX_EXPORT BlockSky : public GfxBlock
	{
	public:
		BlockSky(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void submit_pass(Render& render) override;

		BlockFilter& m_filter;

		struct SkyboxUniform
		{
			void createUniforms()
			{
				u_skybox_matrix = bgfx::createUniform("u_skybox_matrix", bgfx::UniformType::Mat4);
			}

			bgfx::UniformHandle u_skybox_matrix;

		} u_skybox;

		Program& m_skybox_program;
	};
}



#ifndef TWO_MODULES
#include <stl/span.h>
#include <stl/algorithm.h>
//#include <srlz/Serial.h>
#endif

#include <cstdio>

namespace two
{
	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx, const string& path)
		: m_gfx(gfx)
		, m_path(path)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx, const string& path, const Loader& loader)
		: m_gfx(gfx)
		, m_path(path)
		, m_loader(loader)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx, const string& path, const string& format)
		: m_gfx(gfx)
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
		{
			printf("[warning] creating asset %s of already existing name: previous asset deleted\n", name.c_str());
			remove(m_vector, &*m_assets[name]);
		}
		m_assets[name] = make_unique<T_Asset>(name);
		m_vector.push_back(&*m_assets[name]);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::create(const string& name, const Init& init)
	{
		T_Asset& asset = this->create(name);
		init(asset);
		return asset;
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::destroy(const string& name)
	{
		remove(m_vector, &*m_assets[name]);
		m_assets[name] = nullptr;
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::clear()
	{
		m_vector.clear();
		m_assets.clear();
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::fetch(const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
			return this->create(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::file_at(const string& path, const string& name, const Config& config)
	{
		if(m_assets.find(name) == m_assets.end())
		{
			T_Asset& asset = this->create(name);
			m_loader(asset, path + "/" + name, config);
		}
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::file(const string& name, const Config& config)
	{
		if(m_assets.find(name) == m_assets.end())
		{
			string filename = m_path + string(name);
			LocatedFile location = m_formats.size() > 0 ? m_gfx.locate_file(filename, m_formats)
														: m_gfx.locate_file(filename);

			if(!location)
				return nullptr;

			T_Asset& asset = this->create(name);
			Loader& loader = m_formats.size() > 0 ? m_format_loaders[location.m_extension_index] : m_loader;
			loader(asset, location.path(false), config);
		}
		return m_assets[name].get();
	}
	
	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::load(const string& path, const string& file, const Config& config)
	{
		string filename = file;
		for(size_t i = 0; i < m_formats.size(); ++i)
			if(filename.find(m_formats[i]) != string::npos)
			{
				string name = filename.substr(0, filename.size() - m_formats[i].size());
				T_Asset& asset = this->create(name);
				m_format_loaders[i](asset, path + "/" + name, config);
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


namespace two
{
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx;
#else
#endif

#include <cstring>

#define PAD 0.f

namespace two
{
#if !MATERIALS_BUFFER
	template <>
	struct GpuState<MaterialBase>
	{
		void init()
		{
			u_uv0_scale_offset = bgfx::createUniform("u_material_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_uv1_scale_offset = bgfx::createUniform("u_material_p1", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, const MaterialBase& block) const
		{
			encoder.setUniform(u_uv0_scale_offset, &block.m_uv0_scale.x);
			//encoder.setUniform(u_uv1_scale_offset, &block.m_uv1_scale.x);
		}

		bgfx::UniformHandle u_uv0_scale_offset = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_uv1_scale_offset = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialAlpha>
	{
		void init()
		{
			u_alpha = bgfx::createUniform("u_alpha", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialAlpha& block) const
		{
			vec4 alpha = { block.m_alpha.m_value, PAD, PAD, PAD };
			encoder.setUniform(u_alpha, &alpha);
		}

		bgfx::UniformHandle u_alpha = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialSolid>
	{
		void init()
		{
			u_color = bgfx::createUniform("u_color", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialSolid& block) const
		{
			vec4 colour = to_vec4(block.m_colour.m_value);
			encoder.setUniform(u_color, &colour);
		}

		bgfx::UniformHandle u_color = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPoint>
	{
		void init()
		{
			u_point_p0 = bgfx::createUniform("u_point_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPoint& block) const
		{
			vec4 params = { block.m_point_size, float(block.m_project), PAD, PAD };
			encoder.setUniform(u_point_p0, &params);
		}

		bgfx::UniformHandle u_point_p0 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialLine>
	{
		void init()
		{
			// @kludge those are split only as a workaround for precision mismatch between frag and vertex shaders in bgfx
			u_line_p0 = bgfx::createUniform("u_line_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_line_p1 = bgfx::createUniform("u_line_p1", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLine& block) const
		{
			vec4 p0 = { block.m_line_width, block.m_dash_scale, PAD, PAD };
			vec4 p1 = { block.m_dash_size, block.m_dash_gap, PAD, PAD };
			encoder.setUniform(u_line_p0, &p0);
			encoder.setUniform(u_line_p1, &p1);
		}

		bgfx::UniformHandle u_line_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_line_p1 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialFresnel>
	{
		void init()
		{
			u_fresnel_p0 = bgfx::createUniform("u_fresnel_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_fresnel_value = bgfx::createUniform("u_fresnel_value", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialFresnel& block) const
		{
			vec4 value = to_vec4(block.m_value.m_value);
			vec4 params = { block.m_fresnel_bias, block.m_fresnel_scale, block.m_fresnel_power, 1.f };
			encoder.setUniform(u_fresnel_value, &value);
			encoder.setUniform(u_fresnel_p0, &params);
		}

		bgfx::UniformHandle u_fresnel_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fresnel_value = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialLit>
	{
		void init()
		{
			u_lit_p0 = bgfx::createUniform("u_lit_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_lit_p1 = bgfx::createUniform("u_lit_p1", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_emissive = bgfx::createUniform("u_emissive", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLit& block) const
		{
			vec4 p0 = { block.m_normal.m_value, PAD, PAD, PAD };
			encoder.setUniform(u_lit_p0, &p0);

			vec4 emissive = to_vec4(block.m_emissive.m_value);
			encoder.setUniform(u_emissive, &emissive);

			vec4 p1 = { block.m_displace.m_value, block.m_displace_bias, PAD, PAD };
			encoder.setUniform(u_lit_p1, &p1);
		}

		bgfx::UniformHandle u_lit_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_lit_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_emissive = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPbr>
	{
		void init()
		{
			u_albedo = bgfx::createUniform("u_albedo", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_pbr_p0 = bgfx::createUniform("u_pbr_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_pbr_p1 = bgfx::createUniform("u_pbr_p1", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_pbr_channels_0 = bgfx::createUniform("u_pbr_channels_0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_emissive = bgfx::createUniform("u_emissive", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPbr& block) const
		{
			vec4 albedo = { to_vec3(block.m_albedo.m_value), 1.f }; //block.m_alpha.m_value };
			encoder.setUniform(u_albedo, &albedo);

			vec4 pbr_p0 = { block.m_specular, block.m_metallic.m_value, block.m_roughness.m_value, PAD };
			encoder.setUniform(u_pbr_p0, &pbr_p0);

			vec4 pbr_p1 = { block.m_anisotropy.m_value, block.m_refraction.m_value, block.m_subsurface.m_value, block.m_depth.m_value };
			encoder.setUniform(u_pbr_p1, &pbr_p1);

			//vec4 pbr_channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), float(block.m_occlusion.m_channel), PAD };
			vec4 pbr_channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), PAD, PAD };
			encoder.setUniform(u_pbr_channels_0, &pbr_channels);
		}

		bgfx::UniformHandle u_albedo = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_pbr_channels_0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_emissive = BGFX_INVALID_HANDLE;
		//bgfx::UniformHandle u_lightmap_p0;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPhong>
	{
		void init()
		{
			u_diffuse = bgfx::createUniform("u_diffuse", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_specular = bgfx::createUniform("u_specular", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_phong_p0 = bgfx::createUniform("u_phong_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPhong& block) const
		{
			vec4 diffuse = { to_vec3(block.m_diffuse.m_value), 1.f };
			encoder.setUniform(u_diffuse, &diffuse);

			vec4 specular = { to_vec3(block.m_specular.m_value), 1.f };
			encoder.setUniform(u_specular, &specular);

			vec4 p0 = { block.m_shininess.m_value, block.m_reflectivity.m_value, block.m_refraction.m_value, PAD };
			encoder.setUniform(u_phong_p0, &p0);
		}

		bgfx::UniformHandle u_diffuse = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_specular = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_phong_p0 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialUser>
	{
		void init()
		{
			u_p0 = bgfx::createUniform("u_user_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_p1 = bgfx::createUniform("u_user_p1", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_p2 = bgfx::createUniform("u_user_p2", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_p3 = bgfx::createUniform("u_user_p3", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_p4 = bgfx::createUniform("u_user_p4", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
			u_p5 = bgfx::createUniform("u_user_p5", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::Group);
		}

		void upload(bgfx::Encoder& encoder, const MaterialUser& block) const
		{
			encoder.setUniform(u_p0, &block.m_attr0);
			encoder.setUniform(u_p1, &block.m_attr1);
			encoder.setUniform(u_p2, &block.m_attr2);
			encoder.setUniform(u_p3, &block.m_attr3);
			encoder.setUniform(u_p4, &block.m_attr4);
			encoder.setUniform(u_p5, &block.m_attr5);
		}

		bgfx::UniformHandle u_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p2 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p3 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p4 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_p5 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Material>
	{
		void upload(bgfx::Encoder& encoder, const Material& material) const
		{
			GpuState<MaterialBase>::me.upload(encoder, material.m_base);
			GpuState<MaterialAlpha>::me.upload(encoder, material.m_alpha);
			GpuState<MaterialSolid>::me.upload(encoder, material.m_solid);
			GpuState<MaterialPoint>::me.upload(encoder, material.m_point);
			GpuState<MaterialLine>::me.upload(encoder, material.m_line);
			GpuState<MaterialLit>::me.upload(encoder, material.m_lit);
			GpuState<MaterialPbr>::me.upload(encoder, material.m_pbr);
			GpuState<MaterialPhong>::me.upload(encoder, material.m_phong);
			GpuState<MaterialFresnel>::me.upload(encoder, material.m_fresnel);
			GpuState<MaterialUser>::me.upload(encoder, material.m_user);
		}

		static GpuState me;
	};
#else

	template <>
	struct GpuState<MaterialBase>
	{
		constexpr static size_t rows = 2;

		void pack(const MaterialBase& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 uv0_scale_offset = { block.m_uv0_scale, block.m_uv0_offset };
			vec4 uv1_scale_offset = { block.m_uv1_scale, block.m_uv1_offset };

			memcpy(dest + offset, &uv0_scale_offset, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &uv1_scale_offset, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialAlpha>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialAlpha& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 alpha = { block.m_alpha.m_value, PAD, PAD, PAD };

			memcpy(dest + offset, &alpha, sizeof(float) * 1);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialSolid>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialSolid& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 color = { to_vec4(block.m_colour.m_value) };

			memcpy(dest + offset, &color, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPoint>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialPoint& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 params = { block.m_point_size, float(block.m_project), PAD, PAD };

			memcpy(dest + offset, &params, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialLine>
	{
		constexpr static size_t rows = 1;

		void pack(const MaterialLine& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 params = { block.m_line_width, block.m_dash_scale, block.m_dash_size, block.m_dash_gap };

			memcpy(dest + offset, &params, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialLit>
	{
		constexpr static size_t rows = 3;

		void pack(const MaterialLit& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 p0 = { block.m_normal.m_value, PAD, PAD, PAD };
			vec4 emissive = { to_vec3(block.m_emissive.m_value), block.m_emissive.m_value.a };
			vec4 p1 = { block.m_displace.m_value, block.m_displace_bias, PAD, PAD };

			memcpy(dest + offset, &p0, sizeof(float) * 1);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &emissive, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &p1, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPbr>
	{
		constexpr static size_t rows = 5;

		void pack(const MaterialPbr& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 albedo = { to_vec3(block.m_albedo.m_value), PAD };
			vec4 spec_met_rough = { block.m_specular, block.m_metallic.m_value, block.m_roughness.m_value, PAD };
			vec4 channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), PAD, PAD };
			vec4 params1 = { block.m_anisotropy.m_value, block.m_refraction.m_value, block.m_subsurface.m_value, block.m_depth.m_value };
			vec4 params2 = { block.m_rim.m_value, block.m_rim_tint, block.m_clearcoat.m_value, block.m_clearcoat_gloss };

			memcpy(dest + offset, &albedo, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &spec_met_rough, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &channels, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params1, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params2, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialPhong>
	{
		constexpr static size_t rows = 3;

		void pack(const MaterialPhong& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			vec4 diffuse = { to_vec3(block.m_diffuse.m_value), PAD };
			vec4 specular = { to_vec3(block.m_specular.m_value), PAD };
			vec4 p0 = { block.m_shininess.m_value, block.m_reflectivity.m_value, block.m_refraction.m_value, PAD };

			memcpy(dest + offset, &diffuse, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &specular, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &p0, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<MaterialUser>
	{
		constexpr static size_t rows = 6;

		void pack(const MaterialUser& block, size_t& offset, const GpuTexture& buffer, float* dest)
		{
			memcpy(dest + offset, &block.m_attr0, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr1, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr2, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr3, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr4, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &block.m_attr5, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};
	template <>
	struct GpuState<Material>
	{
		void pack(const Material& material, size_t index, const GpuTexture& buffer, uint32_t height, size_t memsize, float* dest)
		{
			const size_t line = buffer.width * buffer.stride;
			size_t offset = (index % buffer.width) * buffer.stride 
				          + (index / buffer.width) * line * height;

			GpuState<MaterialBase>::me.pack(material.m_base, offset, buffer, dest);
			GpuState<MaterialAlpha>::me.pack(material.m_alpha, offset, buffer, dest);
			GpuState<MaterialSolid>::me.pack(material.m_solid, offset, buffer, dest);
			GpuState<MaterialPoint>::me.pack(material.m_point, offset, buffer, dest);
			GpuState<MaterialLine>::me.pack(material.m_line, offset, buffer, dest);
			GpuState<MaterialLit>::me.pack(material.m_lit, offset, buffer, dest);
			GpuState<MaterialPbr>::me.pack(material.m_pbr, offset, buffer, dest);
			GpuState<MaterialPhong>::me.pack(material.m_phong, offset, buffer, dest);
			//GpuState<MaterialFresnel>::me.pack(material.m_fresnel, offset, buffer, dest);
			GpuState<MaterialUser>::me.pack(material.m_user, offset, buffer, dest);
		}

		void pack(GpuTexture& buffer, span<Material*> materials)
		{
			const uint32_t height = GpuState<MaterialBase>::me.rows
								  + GpuState<MaterialAlpha>::me.rows
								  + GpuState<MaterialSolid>::me.rows
								  + GpuState<MaterialPoint>::me.rows
								  + GpuState<MaterialLine>::me.rows
								  + GpuState<MaterialLit>::me.rows
								  + GpuState<MaterialPbr>::me.rows
								  + GpuState<MaterialPhong>::me.rows
								  + GpuState<MaterialUser>::me.rows;
			const uint32_t lines = 1 + materials.size() / buffer.width;
			const uvec2 size = uvec2(buffer.width, lines * height);

			if(buffer.texture.m_size != size)
				buffer.texture = { size, false, TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP };

			const size_t memsize = size.x * size.y * buffer.stride;
			buffer.memory.resize(memsize);

			for(size_t index = 0; index < materials.size(); ++index)
			{
				this->pack(*materials[index], index, buffer, height, memsize, buffer.memory.data());
			}

			const bgfx::Memory* mem = bgfx::makeRef(buffer.memory.data(), sizeof(float) * buffer.memory.size());
			bgfx::updateTexture2D(buffer.texture, 0, 0, 0, 0, buffer.width, uint16_t(lines * height), mem);
		}

		static GpuState me;
	};
#endif
}

#undef PAD
