#pragma once

#include <two/gfx.h>
#include <two/geom.h>
#include <two/ecs.h>
#include <two/math.h>
#include <two/infra.h>
#include <two/type.h>




#ifndef TWO_GFX_PBR_EXPORT
#define TWO_GFX_PBR_EXPORT TWO_IMPORT
#endif

namespace two
{
    enum ShaderOptionLight : unsigned int;
    enum ShaderOptionRadiance : unsigned int;
    enum ShaderOptionShadow : unsigned int;
    enum ShaderModeShadow : unsigned int;
    enum ShadowFilterMode : unsigned int;
    enum ShaderOptionBlur : unsigned int;
    enum ShaderOptionDofBlur : unsigned int;
    enum ShaderOptionGlow : unsigned int;
    enum TonemapShaderOption : unsigned int;
    enum TonemapShaderMode : unsigned int;
    enum class TonemapMode : unsigned int;
    
    
	class BlockGeometry;
    class BlockLight;
    struct ReflectionRenderer;
    struct ForwardRenderer;
	struct DeferredRenderer;
    class BlockRadiance;
    class CubeTarget;
	class CubeCamera;
    class ReflectionAtlas;
    class ReflectionProbe;
	class PassGeometry;
	class PassLights;
	class PassOpaque;
	class PassAlpha;
    class PassProbes;
    class BlockReflection;
    struct ShadowmapCube;
    class ShadowAtlas;
    struct CSMShadow;
	struct CSMSlice;
    class PassShadow;
    class PassShadowmap;
    struct ShadowRenderer;
    struct LightBounds;
    struct LightShadow;
    class BlockShadow;
    struct EffectBlurUniform;
    struct BlurKernel;
    class BlockBlur;
	struct DofParams;
    struct DofBlur;
    struct DofBlurUniform;
    class BlockDofBlur;
    struct Glow;
    struct GlowUniform;
	class BlockGI;
	class BlockGIBake;
	class BlockGITrace;
	class BlockLightmap;
    class BlockGlow;
    struct BCS;
    struct Tonemap;
    struct TonemapUniform;
    class BlockTonemap;
}



namespace two
{
	enum ShaderOptionLight : unsigned int
	{
		SKY_LIGHT,
		FOG,
	};

	struct gpu_ GpuBone
	{
		attr_ mat4 matrix;
	};

	struct gpu_ GpuShadow
	{
		attr_ float matrix;
		attr_ float bias;
		attr_ float radius;
		attr_ float range;
		attr_ vec2 atlas_slot;
		attr_ vec2 atlas_subdiv;
	};

	struct gpu_ GpuCSMShadow
	{
		attr_ float num_slices;
		attr_ vec4 splits;
		attr_ vec4 matrices;
	};

	struct gpu_ GpuLight
	{
		attr_ vec3 position;
		attr_ float range;
		attr_ vec3 energy;
		attr_ float specular;
		attr_ vec3 direction;
		attr_ float attenuation;
		attr_ float spot_attenuation;
		attr_ float spot_cutoff;

		attr_ GpuShadow shadow;
		attr_ GpuCSMShadow csm;
	};

	export_ TWO_GFX_PBR_EXPORT void debug_draw_light_clusters(Gnode& parent, Viewport& viewport, Camera& camera);
	export_ TWO_GFX_PBR_EXPORT void debug_draw_light_slices(Gnode& parent, Light& light, bool frustums = true, bool bounds = true);

#ifdef TWO_PLATFORM_EMSCRIPTEN
	constexpr size_t c_max_forward_lights = 32;
#else
	constexpr size_t c_max_forward_lights = 64;
#endif

	struct ZoneLights
	{
		vec4 m_light_indices[c_max_forward_lights];
		vec4 m_light_counts;
		vec4 m_shadow_counts;
		uint16_t m_light_count;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockLight : public DrawBlock
	{
	public:
		BlockLight(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const final;
		virtual void submit(Render& render, const Pass& pass) const final;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const final;

		void setup_lights(Render& render, const mat4& view);
		void setup_zones(Render& render);

		void upload_lights(Render& render);
		void upload_zones(Render& render);

		void commit_zones(Render& render, const Pass& pass) const;
		void commit_lights(Render& render, const Pass& pass) const;

		struct ShotUniform
		{
			void createUniforms()
			{
				s_zones = bgfx::createUniform("s_zones", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
				s_lights = bgfx::createUniform("s_lights", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle s_zones;
			bgfx::UniformHandle s_lights;

		} u_shot;

		uint16_t m_light_count;

		ZoneLights m_zones[1];

		vector<GpuLight> m_gpu_lights;

		GpuTexture m_zones_texture = {};
		GpuTexture m_lights_texture = {};
	};
}




namespace two
{
	export_ class refl_ TWO_GFX_PBR_EXPORT LightmapItem
	{
	public:
		LightmapItem() {}
		LightmapItem(size_t item, Texture& lightmap, vec4 uv_scale_offset) : m_item(item), m_lightmap(&lightmap), m_uv_scale_offset(uv_scale_offset) {}
		size_t m_item = SIZE_MAX;
		Texture* m_lightmap = nullptr;
		vec4 m_uv_scale_offset = vec4(1.f, 1.f, 0.f, 0.f);
	};

	struct ModelUnwrap
	{
		vector<bool> success;
		uvec2 size;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT Lightmap
	{
	public:
		Lightmap(uint32_t size);

		uint32_t m_size = 0;
		float m_density = 1.f;
		bool m_dirty = false;

		TextureAtlas m_atlas;

		Texture m_texture = {};

		vector<LightmapItem> m_items;

		void add_item(size_t index, Item& item, bool valid, const vec4& uv_scale_offset);
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT LightmapAtlas
	{
	public:
		LightmapAtlas(uint32_t size, float density);
		~LightmapAtlas();

		LightmapAtlas(const LightmapAtlas& other) = delete;
		LightmapAtlas& operator=(const LightmapAtlas& other) = delete;

		Lightmap& add_lightmap() { m_layers.push_back(make_unique<Lightmap>(m_size)); return *m_layers.back(); }

		uint32_t m_size;
		float m_density = 1.f;
		bool m_dirty = false;
		string m_save_path;

		mat4 m_capture_transform;
		vec3 m_capture_extents;

		vector<unique<Lightmap>> m_layers;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockLightmap : public DrawBlock
	{
	public:
		BlockLightmap(GfxSystem& gfx, BlockLight& block_light, BlockGIBake& block_gi_bake);

		BlockLight& m_block_light;
		BlockGIBake& m_block_gi_bake;

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void bake_geometry(span<Item*> items, LightmapAtlas& atlas);
		void bake_lightmaps(Scene& scene, LightmapAtlas& atlas, const mat4& transform, const vec3& extents);

		struct VoxelGIUniform
		{
			void createUniforms()
			{
				s_lightmap = bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle s_lightmap;

		} u_lightmap;

		Program* m_lightmap;

		struct BakeEntry { Scene* scene; LightmapAtlas* atlas; };
		vector<BakeEntry> m_bake_queue;
	};
}


namespace two
{
	export_ class refl_ TWO_GFX_EXPORT BlockGeometry : public DrawBlock
	{
	public:
		BlockGeometry(GfxSystem& gfx);
		~BlockGeometry();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const final;
		virtual void submit(Render& render, const Pass& pass) const final;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const final;

		Material* m_material = nullptr;
		Material* m_material_twosided = nullptr;
	};

	export_ TWO_GFX_PBR_EXPORT func_ void begin_pbr_render(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pass_gi_probes(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_shadowmaps(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_shadow(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_opaque(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_alpha(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pass_geometry(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_lights(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pass_voxel_gi(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_lightmap(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pass_begin_post(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_post_auto(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_post_effects(GfxSystem& gfx, Render& render, DofBlur& dof, Glow& glow, Tonemap& tonemap, BCS& bcs);

	export_ TWO_GFX_PBR_EXPORT func_ void render_pbr_forward(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_pbr_deferred(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_shadow(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_voxel(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_lightmap(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_reflection(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT void gather_gi_probes(Scene& scene, vector<GIProbe*>& gi_probes);
	export_ TWO_GFX_PBR_EXPORT void gather_lightmaps(Scene& scene, vector<LightmapAtlas*>& atlases);
	export_ TWO_GFX_PBR_EXPORT void gather_reflection_probes(Scene& scene, vector<ReflectionProbe*>& reflection_probes);

	export_ TWO_GFX_PBR_EXPORT func_ void pipeline_pbr(GfxSystem& gfx, Renderer& pipeline, bool deferred = false);
	
namespace gfx
{
	export_ TWO_GFX_PBR_EXPORT func_ void setup_pipeline_pbr(GfxSystem& gfx);
}
}


namespace two
{
	enum ShaderOptionRadiance : unsigned int
	{
		RADIANCE_ENVMAP,
		RADIANCE_CUBE,
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockRadiance : public DrawBlock
	{
	public:
		BlockRadiance(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy);

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void prefilter_radiance(Radiance& radiance);

		struct RadianceUniform
		{
			void createUniforms()
			{
				s_radiance = bgfx::createUniform("s_radiance", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle s_radiance;

		} u_radiance;

		struct PrefilterUniform
		{
			void createUniforms()
			{
				u_prefilter_envmap_p0 = bgfx::createUniform("u_prefilter_envmap_p0", bgfx::UniformType::Vec4);
				u_prefilter_cube = bgfx::createUniform("u_prefilter_cube", bgfx::UniformType::Mat4);
			}

			bgfx::UniformHandle u_prefilter_envmap_p0;
			bgfx::UniformHandle u_prefilter_cube;

		} u_prefilter;

		BlockFilter& m_filter;
		BlockCopy& m_copy;

		Program& m_prefilter_program;

		vector<Radiance*> m_prefilter_queue;
		map<Texture*, Texture*> m_prefiltered;
	};
}





#include <bgfx/bgfx.h>

namespace two
{
	export_ class refl_ TWO_GFX_PBR_EXPORT CubeTarget
	{
	public:
		constr_ CubeTarget() {}
		meth_ void create(uint32_t size);
		meth_ FrameBuffer& side(size_t i) { return m_fbos[i]; }
		FrameBuffer m_fbos[6]; // @todo reflect array members
		attr_ Texture m_cubemap;
		attr_ Texture m_depth;
		attr_ uint32_t m_size;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT CubeCamera
	{
	public:
		constr_ CubeCamera() {}
		constr_ CubeCamera(Scene& scene, float near, float far, uint32_t size);

		Camera m_cameras[6];
		Viewport m_viewports[6];

		attr_ CubeTarget m_cubemap;
		attr_ uvec2 m_size;

		meth_ Render render(GfxSystem& gfx, Render& render, SignedAxis axis);

		void render(GfxSystem& gfx, Render& render, RenderFunc renderer);
		void clear(GfxSystem& gfx, Render& render, Colour color, float depth, uint8_t stencil);
	};

	export_ class TWO_GFX_PBR_EXPORT ReflectionAtlas
	{
	public:
		ReflectionAtlas(uint16_t size, uint16_t subdiv);
		~ReflectionAtlas();

		uint16_t m_size = 0;
		uint16_t m_subdiv = 0;

		FrameBuffer m_fbo[6];
		Texture m_color;

		vec4 probe_rect(ReflectionProbe& probe);
		uvec4 render_update(Render& render, ReflectionProbe& probe);

		struct Slot
		{
			size_t m_index;
			ReflectionProbe* m_probe;
			uvec4 m_urect;
			vec4 m_rect;
			uint32_t m_last_update;
		};

		vector<Slot> m_slots;
		vector<Slot*> m_free_slots;
	};
}

namespace two
{
	struct gpu_ GpuReflectionProbe
	{
		attr_ gpu_ vec3 extents;
		attr_ gpu_ float intensity;
		attr_ gpu_ vec4 atlas_rect;
		attr_ gpu_ mat4 transform;
	};

	template <uint16_t num_probes>
	struct ReflectionProbeArray
	{
		vec4 extents_intensity[num_probes];
		vec4 ambient[num_probes];
		vec4 atlas_rect[num_probes];
		mat4 matrix[num_probes];

		vec4 indices[num_probes];
		vec4 counts;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT ReflectionProbe
	{
	public:
		ReflectionProbe(Node3& node);

		attr_ Node3& m_node;

		attr_ bool m_visible = true;
		attr_ float m_intensity = 1.f;
		attr_ vec3 m_extents = vec3(0.f);
		attr_ bool m_shadows = false;

		ReflectionAtlas* m_atlas;
		int m_atlas_index = -1;

		attr_ bool m_dirty = true;
	};

	export_ TWO_GFX_PBR_EXPORT void pass_probes(GfxSystem& gfx, Render& render);

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockReflection : public DrawBlock
	{
	public:
		BlockReflection(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void upload_reflection_probes(Render& render, Pass& pass, span<ReflectionProbe*> probes);
		void render_reflection_probe(Render& render, ReflectionProbe& reflection_probe);

		CubeTarget& find_cubemap(uint16_t size);

		struct ReflectionUniform
		{
			static constexpr size_t max_reflection_probes = 16;

			void createUniforms(uint16_t max_probes)
			{
				u_extents_intensity		= bgfx::createUniform("u_reflection_extents_intensity",	bgfx::UniformType::Vec4, max_probes);
				u_ambient				= bgfx::createUniform("u_reflection_ambient",			bgfx::UniformType::Vec4, max_probes);
				u_atlas_rect			= bgfx::createUniform("u_reflection_atlas_rect",		bgfx::UniformType::Mat4, max_probes);
				u_matrix				= bgfx::createUniform("u_reflection_matrix",			bgfx::UniformType::Vec4, max_probes);

				//u_indices		= bgfx::createUniform("u_reflection_indices",		bgfx::UniformType::Sampler, max_probes);
				//u_count		= bgfx::createUniform("u_reflection_count",			bgfx::UniformType::Sampler);
			}

			template <uint16_t size>
			void setUniforms(bgfx::Encoder& encoder, ReflectionProbeArray<size>& data, uint16_t probe_count)
			{
				encoder.setUniform(u_extents_intensity,		&data.extents_intensity,	probe_count);
				encoder.setUniform(u_ambient,				&data.ambient,				probe_count);
				encoder.setUniform(u_atlas_rect,			&data.atlas_rect,			probe_count);
				encoder.setUniform(u_matrix,				&data.matrix,				probe_count);
			}

			bgfx::UniformHandle u_extents_intensity;
			bgfx::UniformHandle u_ambient;
			bgfx::UniformHandle u_atlas_rect;
			bgfx::UniformHandle u_matrix;

			bgfx::UniformHandle u_indices;
			bgfx::UniformHandle u_count;

			bgfx::UniformHandle s_atlas;
		};

		ReflectionUniform u_uniform;

		vector<CubeTarget> m_cubemaps;

		ReflectionAtlas m_atlas;

		float m_reflection_multiplier;
	};
}




#include <bgfx/bgfx.h>

namespace two
{
	class ShadowAtlas
	{
	public:
		ShadowAtlas() {}
		ShadowAtlas(uint16_t size, uint8_t num_slices);

		uint16_t m_side = 0;
		uvec2 m_size;

		Texture m_color;
		Texture m_depth;
		FrameBuffer m_fbo;

		struct Block;

		struct Slot
		{
			uint16_t m_index;
			Light* m_light = nullptr;
			vec4 m_rect;
			uvec4 m_trect;
			uint32_t m_frame = 0;
			uint16_t m_block = UINT16_MAX;
		};

		struct Block
		{
			uint32_t m_slots[8];
		};

		struct Slice;

		Slice& light_slice(Light& light);
		Slot& light_slot(Light& light);

		void begin_frame(const RenderFrame& frame);
		void subdiv(Slice& slice, uint16_t subdiv);
		
		Slot& alloc(Slice& slice, bool block6 = false);
		void yield(Slice& slice, uint32_t index);

		vec4 render_update(Render& render, Light& light);
		bool update_light(Light& light, uint32_t render, float coverage, uint32_t light_version);
		void remove_light(Light& light, bool block = false);

		struct Slice
		{
			Slice() {}
			Slice(uint8_t index, const uvec2& size, const vec4& rect);

			uint8_t m_index;
			uvec2 m_size;
			vec4 m_rect;

			uint16_t m_subdiv = 0;
			uvec2 m_slot_size;
			vector<Slot> m_slots;
			vector<Block> m_blocks;

			vector<uint32_t> m_free_slots;
			vector<uint32_t> m_free_blocks;
		};

		vector<Slice> m_slices;
	};
}

namespace two
{
	enum ShaderOptionShadow : unsigned int
	{
		SHADOWS,
		CSM_BLEND,
	};

	enum ShaderModeShadow : unsigned int
	{
		PCF_LEVEL,
	};

	enum ShadowFilterMode : unsigned int
	{
		PCF_NONE = 0,
		PCF_HARD = 1,
		PCF_5 = 2,
		PCF_13 = 3
	};

	struct Shadowmap
	{
		Shadowmap() {}
		~Shadowmap() {}

		Shadowmap(const Shadowmap& other) = delete;
		Shadowmap& operator=(const Shadowmap& other) = delete;

		void create(const uvec2& size, DepthMethod method = DepthMethod::Depth);

		uvec2 m_size = uvec2(0U);
		DepthMethod m_depth_method = DepthMethod::Depth;
		FrameBuffer m_fbo;
		Texture m_depth;
		Texture m_color;

		const Texture& texture() const { return m_depth_method == DepthMethod::Depth ? m_depth : m_color; }
	};

	struct ShadowmapCube
	{
		ShadowmapCube() {}
		~ShadowmapCube() { if(bgfx::isValid(m_depth)) bgfx::destroy(m_depth); }

		void create(uint32_t size);

		uint32_t m_size = 0U;
		FrameBuffer m_fbos[6];
		Texture m_depth;
	};

	export_ TWO_GFX_PBR_EXPORT void pass_shadowmaps(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT void pass_shadow(GfxSystem& gfx, Render& render);

	export_ struct LightBounds
	{
		vec3 min = { 9000.0f,  9000.0f,  9000.0f };
		vec3 max = { -9000.0f, -9000.0f, -9000.0f };
	};

	export_ struct refl_ TWO_GFX_PBR_EXPORT LightShadow
	{
		Light* m_light = nullptr;

		FrameBuffer* m_fbo = nullptr;
		vec4 m_rect = {};
		
		float m_near = 0.f;
		float m_far = 100.f;
		mat4 m_proj = {};
		mat4 m_transform = {};

		mat4 m_shadow_matrix = {};
		DepthMethod m_depth_method = DepthMethod::Depth;
		float m_bias_scale = 1.f;

		FrustumSlice m_frustum_slice;
		LightBounds m_light_bounds;

		vector<Item*> m_items;
	};

	export_ struct refl_ TWO_GFX_PBR_EXPORT CSMSlice : public LightShadow, public FrustumSlice
	{};

	export_ struct refl_ TWO_GFX_PBR_EXPORT CSMShadow
	{
		Light* m_light;

		vector<CSMSlice> m_slices;
	};

#ifdef TWO_PLATFORM_EMSCRIPTEN
	constexpr size_t c_max_shadows = 8;
#else
	constexpr size_t c_max_shadows = 32;
#endif

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockShadow : public DrawBlock
	{
	public:
		BlockShadow(GfxSystem& gfx, BlockDepth& block_depth, BlockLight& block_light);

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void setup_shadows(Render& render);
		void commit_shadows(Render& render, const mat4& view);
		void upload_shadows(Render& render, const Pass& pass) const;

		void update_csm(Render& render, Light& light, CSMShadow& csm);

		BlockDepth& m_block_depth;
		BlockLight& m_block_light;

		DepthMethod m_depth_method = DepthMethod::Depth;
		DepthParams m_depth_params = {};
		DistanceParams m_distance_params = {};

		struct ShadowUniform
		{
			void createUniforms()
			{
				s_shadow_atlas = bgfx::createUniform("s_shadow_atlas", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
				u_shadow_atlas = bgfx::createUniform("u_shadow_atlas", bgfx::UniformType::Vec4,    1U, bgfx::UniformSet::View);
				u_pcf_p0   = bgfx::createUniform("u_pcf_p0",   bgfx::UniformType::Vec4,    1U, bgfx::UniformSet::View);
				u_csm_p0 = bgfx::createUniform("u_csm_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle s_shadow_atlas;
			bgfx::UniformHandle u_shadow_atlas;
			bgfx::UniformHandle u_pcf_p0;
			bgfx::UniformHandle u_csm_p0;

		} u_shadow;

#ifdef TWO_PLATFORM_EMSCRIPTEN
		ShadowFilterMode m_pcf_level = PCF_HARD; // @todo can't get true pcf working on WebGL so far
#else
		ShadowFilterMode m_pcf_level = PCF_5;
#endif

		ShadowAtlas m_atlas;

		vector<CSMShadow> m_csm_shadows;
		vector<LightShadow> m_shadows;

		vector<mat4> m_shadow_matrices;
	};
}




namespace two
{
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif



namespace two
{
    // Exported types
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::TonemapMode>();
    
    
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLight>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapItem>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::Lightmap>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapAtlas>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLightmap>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGeometry>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockRadiance>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeTarget>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeCamera>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::ReflectionProbe>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockReflection>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::LightShadow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMSlice>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMShadow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockShadow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::GIProbe>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGITrace>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGIBake>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockBlur>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::DofParams>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::DofBlur>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockDofBlur>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::Glow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGlow>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BCS>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::Tonemap>();
    export_ template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockTonemap>();
}




namespace two
{
namespace gfx
{
	export_ TWO_GFX_EXPORT func_ GIProbe& gi_probe(Gnode& parent, uint16_t subdiv, const vec3& extents);
	export_ TWO_GFX_EXPORT func_ LightmapAtlas& lightmap(Gnode& parent, uint32_t resolution, float density = 8.f, const string& save_path = "");
}

	enum ShaderOptionGI : unsigned int
	{
		GI_CONETRACE
	};

	enum class GIProbeMode
	{
		Voxelize,
		LoadVoxels,
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT GIProbe
	{
	public:
		GIProbe(Node3& node);
		~GIProbe();

		void resize(uint16_t subdiv, const vec3& extents);
		void lightmap(uint32_t size, float density, const string& save_path = "");

		Node3& m_node;

		Texture m_raster = {};
		Texture m_voxels_color = {};
		Texture m_voxels_normals = {};
		Texture m_voxels_light = {};
		FrameBuffer m_fbo = {};

		Texture m_voxels_light_rgba = {};

		bool m_enabled = true;
		mat4 m_transform;
		uint16_t m_subdiv = 0;
		vec3 m_extents = vec3(0.f);
		GIProbeMode m_mode = GIProbeMode::Voxelize;
		bool m_dirty = false;

		int m_dynamic_range = 4;
		float m_diffuse = 3.0f;
		float m_specular = 1.0f;
		int m_bounces = 0;
		float m_propagation = 1.0f;
		
		float m_bias = 0.0f;
		float m_normal_bias = 0.8f;
	};

	export_ TWO_GFX_PBR_EXPORT void save_gi_probe(GfxSystem& gfx, GIProbe& gi_probe, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path);
	export_ TWO_GFX_PBR_EXPORT void load_gi_probe(GfxSystem& gfx, GIProbe& gi_probe, const string& path);

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockGITrace : public DrawBlock
	{
	public:
		BlockGITrace(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void upload_gi_probes(Render& render, const Pass& pass) const;

		struct GIProbeUniform
		{
			static const int max_gi_probes = 2;

			void createUniforms()
			{
				s_gi_probe = bgfx::createUniform("s_gi_probe", bgfx::UniformType::Sampler, max_gi_probes, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle s_gi_probe;

		} u_gi_probe;
	};

	struct gpu_ GpuVoxelGI
	{
		attr_ gpu_ vec3 extents;
		attr_ gpu_ vec3 subdiv;
		attr_ gpu_ mat4 world;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockGIBake : public DrawBlock
	{
	public:
		BlockGIBake(GfxSystem& gfx, BlockLight& block_light, BlockShadow& block_shadow, BlockGITrace& block_trace);

		BlockLight& m_block_light;
		BlockShadow& m_block_shadow;
		BlockGITrace& m_block_trace;

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void voxelize(Render& render, GIProbe& gi_probe);
		void compute(Render& render, GIProbe& gi_probe);
		void bounce(Render& render, GIProbe& gi_probe);
		void output(Render& render, GIProbe& gi_probe);

		struct VoxelGIUniform
		{
			void createUniforms()
			{
				s_voxels_albedo    = bgfx::createUniform("s_voxels_albedo",  bgfx::UniformType::Sampler);
				s_voxels_normals   = bgfx::createUniform("s_voxels_normals", bgfx::UniformType::Sampler);
				s_voxels_light     = bgfx::createUniform("s_voxels_light",   bgfx::UniformType::Sampler);

				s_voxels_light_rgba  = bgfx::createUniform("s_voxels_light_rgba",   bgfx::UniformType::Sampler);
			}

			bgfx::UniformHandle s_voxels_albedo;
			bgfx::UniformHandle s_voxels_normals;
			bgfx::UniformHandle s_voxels_light;
			bgfx::UniformHandle s_voxels_light_rgba;

		} u_voxelgi;

		Program* m_direct_light;
		Program* m_bounce_light;
		Program* m_output_light;
		Program* m_voxelize;

		GIProbe* m_bake_probe = nullptr;

		bool m_direct_light_compute = false;
	};
}



namespace two
{
	enum ShaderOptionBlur : unsigned int
	{
		GAUSSIAN_HORIZONTAL,
		GAUSSIAN_VERTICAL,
	};

	struct EffectBlurUniform
	{
		void createUniforms()
		{
			u_blur_p0 = bgfx::createUniform("u_blur_p0", bgfx::UniformType::Vec4);
			u_blur_kernel_0_3 = bgfx::createUniform("u_blur_kernel_0_3", bgfx::UniformType::Vec4);
			u_blur_kernel_4_7 = bgfx::createUniform("u_blur_kernel_4_7", bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle u_blur_p0;
		bgfx::UniformHandle u_blur_kernel_0_3;
		bgfx::UniformHandle u_blur_kernel_4_7;
	};

	struct gpu_ GpuBlurKernel
	{
		attr_ gpu_ float m_kernel[8];
	};

	struct BlurKernel
	{
		float m_horizontal[7];
		float m_vertical[5];
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockBlur : public GfxBlock
	{
	public:
		BlockBlur(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		
		void blur(Render& render, RenderTarget& target);

		void gaussian_pass(Render& render, RenderTarget& target, const vec4& rect, uint8_t lod, bool horizontal, const BlurKernel& kernel);

		BlockFilter& m_filter;

		EffectBlurUniform u_uniform;
		Program& m_program;
	};
}



namespace two
{
	enum ShaderOptionDofBlur : unsigned int
	{
		DOF_FIRST_PASS,
	};

	export_ struct refl_ DofParams
	{
		attr_ gpu_ float m_distance;
		attr_ gpu_ float m_transition;
		attr_ gpu_ float m_radius;
	};

	export_ struct refl_ DofBlur
	{
		attr_ bool m_enabled = false;
		attr_ gpu_ DofParams m_far = { 10.f, 5.f, 5.f };
		attr_ gpu_ DofParams m_near = { 2.f, 1.f, 5.f };
		attr_ gpu_ float m_max_coc_radius = 8.f;
	};

	export_ TWO_GFX_PBR_EXPORT func_ void pass_dofblur(GfxSystem& gfx, Render& render, const DofBlur& blur);

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockDofBlur : public GfxBlock
	{
	public:
		BlockDofBlur(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		BlockFilter& m_filter;

		Program& m_program;
	};
}



namespace two
{
	enum ShaderOptionGlow : unsigned int
	{
		GLOW_FILTER_BICUBIC,
	};

	export_ struct refl_ TWO_GFX_PBR_EXPORT Glow
	{
		attr_ bool m_enabled = false;
		attr_ gpu_ vec4 m_levels_1_4 = { 1.f, 0.f, 0.f, 0.f };
		attr_ gpu_ vec4 m_levels_5_8 = vec4(0.f);
		attr_ gpu_ float m_intensity = 0.4f;
		attr_ gpu_ float m_bloom = 0.0f;
		attr_ gpu_ float m_bleed_threshold = 1.0f;
		attr_ gpu_ float m_bleed_scale = 2.0f;
		attr_ gpu_ bool m_bicubic_filter = false;
	};

	export_ TWO_GFX_PBR_EXPORT func_ void pass_glow(GfxSystem& gfx, Render& render, Glow& glow);

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockGlow : public GfxBlock
	{
	public:
		BlockGlow(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy, BlockBlur& blur);

		virtual void init_block() override;

		Program& m_bleed_program;
		Program& m_merge_program;
	};
}



namespace two
{
	enum TonemapShaderOption : unsigned int
	{
		TO_GAMMA,
		ADJUST_BCS,
		COLOR_LUT,
	};

	enum TonemapShaderMode : unsigned int
	{
		TONEMAP_MODE,
	};

	export_ enum class refl_ TonemapMode : unsigned int
	{
		Linear,
		Reinhardt,
		Filmic,
		ACES,
		Cineon,
		Uncharted2
	};

	export_ struct refl_ BCS
	{
		attr_ gpu_ bool m_enabled = false;
		attr_ gpu_ float m_brightness = 1.0f;
		attr_ gpu_ float m_contrast = 1.0f;
		attr_ gpu_ float m_saturation = 1.0f;
	};

	export_ struct refl_ Tonemap
	{
		attr_ TonemapMode m_mode = TonemapMode::Linear;
		attr_ bool m_enabled = false;
		attr_ gpu_ float m_exposure = 1.0f;
		attr_ gpu_ float m_white_point = 1.0f;

		Texture* m_color_lut = nullptr;
	};

	export_ TWO_GFX_PBR_EXPORT func_ void pass_tonemap(GfxSystem& gfx, Render& render, Tonemap& tonemap, BCS& bcs);

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockTonemap : public GfxBlock
	{
	public:
		BlockTonemap(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy);

		virtual void init_block() override;

		Program& m_program;
	};


}



namespace two
{
	template <> struct TypedBuffer<Tonemap> { static uint32_t index() { return 0; } };
	template <> struct TypedBuffer<BCS> { static uint32_t index() { return 1; } };
	template <> struct TypedBuffer<Glow> { static uint32_t index() { return 2; } };
	template <> struct TypedBuffer<DofBlur> { static uint32_t index() { return 3; } };
}




namespace two
{
	template <>
	struct GpuState<GpuBlurKernel>
	{
		void init()
		{
			u_blur_kernel_0_3 = bgfx::createUniform("u_blur_kernel_0_3", bgfx::UniformType::Vec4);
			u_blur_kernel_4_7 = bgfx::createUniform("u_blur_kernel_4_7", bgfx::UniformType::Vec4);
		}

		void upload(const GpuBlurKernel& kernel)
		{
			bgfx::setUniform(u_blur_kernel_0_3, kernel.m_kernel + 0);
			bgfx::setUniform(u_blur_kernel_4_7, kernel.m_kernel + 4);
		}

		bgfx::UniformHandle u_blur_kernel_0_3;
		bgfx::UniformHandle u_blur_kernel_4_7;

		static GpuState me;
	};
}



namespace two
{
	template <>
	struct GpuState<DofBlur>
	{
		void init()
		{
			u_dof_near_p0 = bgfx::createUniform("u_dof_near_p0", bgfx::UniformType::Vec4);
			u_dof_far_p0 = bgfx::createUniform("u_dof_far_p0", bgfx::UniformType::Vec4);
			u_dof_p0 = bgfx::createUniform("u_dof_p0", bgfx::UniformType::Vec4);
		}

		void upload(const DofBlur& dof)
		{
			vec4 dof_near_p0 =
			{
				dof.m_near.m_distance,
				dof.m_near.m_distance - dof.m_near.m_transition,
				dof.m_near.m_radius,
				1.f / dof.m_near.m_radius,
			};

			vec4 dof_far_p0 =
			{
				dof.m_far.m_distance,
				dof.m_far.m_distance + dof.m_far.m_transition,
				dof.m_far.m_radius,
				0.f
			};

			vec4 dof_p0 = { dof.m_max_coc_radius, 0.f, 0.f, 0.f };

			bgfx::setUniform(u_dof_near_p0, &dof_near_p0);
			bgfx::setUniform(u_dof_far_p0, &dof_far_p0);
			bgfx::setUniform(u_dof_p0, &dof_p0);
		}

		bgfx::UniformHandle u_dof_near_p0;
		bgfx::UniformHandle u_dof_far_p0;
		bgfx::UniformHandle u_dof_p0;

		static GpuState me;
	};
}



namespace two
{
	template <>
	struct GpuState<Glow>
	{
		void init()
		{
			u_glow_p0 = bgfx::createUniform("u_glow_p0", bgfx::UniformType::Vec4);
			u_glow_p1 = bgfx::createUniform("u_glow_p1", bgfx::UniformType::Vec4);
			u_glow_levels_1_4 = bgfx::createUniform("u_glow_levels_1_4", bgfx::UniformType::Vec4);
			u_glow_levels_5_8 = bgfx::createUniform("u_glow_levels_5_8", bgfx::UniformType::Vec4);
		}

		void upload(const Glow& glow)
		{
			vec4 glow_p0 = { 0.f, glow.m_bloom, glow.m_bleed_threshold, glow.m_bleed_scale };
			bgfx::setUniform(u_glow_p0, &glow_p0);

			vec4 glow_p1 = { glow.m_intensity, 0.f, 0.f, 0.f }; // float(render.m_target->m_size.x), float(render.m_target->m_size.y)
			bgfx::setUniform(u_glow_p1, &glow_p1);
			bgfx::setUniform(u_glow_levels_1_4, &glow.m_levels_1_4);
			bgfx::setUniform(u_glow_levels_5_8, &glow.m_levels_5_8);
		}

		bgfx::UniformHandle u_glow_p0;
		bgfx::UniformHandle u_glow_p1;
		bgfx::UniformHandle u_glow_levels_1_4;
		bgfx::UniformHandle u_glow_levels_5_8;

		static GpuState me;
	};
}



#include <cstring>

#define PAD 0.f

namespace two
{
	template <>
	struct GpuState<GpuShadow>
	{
		void init()
		{
			u_shadow_matrix = bgfx::createUniform("u_shadow_matrix", bgfx::UniformType::Mat4, c_max_shadows, bgfx::UniformSet::View);
		}

		void upload(const Pass& pass, span<mat4> matrices)
		{
			bgfx::setViewUniform(pass.m_index, u_shadow_matrix, matrices.m_pointer, uint16_t(matrices.size()));
		}

		bgfx::UniformHandle u_shadow_matrix;

		static GpuState me;
	};

#if !LIGHTS_BUFFER
	template <>
	struct GpuState<GpuLight>
	{
		void init()
		{
			u_light_position_range			= bgfx::createUniform("u_light_position_range",			bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_energy_specular			= bgfx::createUniform("u_light_energy_specular",		bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_direction_attenuation	= bgfx::createUniform("u_light_direction_attenuation",	bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_spot_p0					= bgfx::createUniform("u_light_spot_p0",				bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_shadow_p0				= bgfx::createUniform("u_light_shadow_p0",				bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_shadowmap_p0			= bgfx::createUniform("u_light_shadowmap_p0",			bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_csm_p0					= bgfx::createUniform("u_light_csm_p0",					bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_csm_p1					= bgfx::createUniform("u_light_csm_p1",					bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_csm_p2					= bgfx::createUniform("u_light_csm_p2",					bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
		}

		void upload(const Pass& pass, span<GpuLight> lights) const
		{
			vec4 position_range[c_max_forward_lights];
			vec4 energy_specular[c_max_forward_lights];
			vec4 direction_attenuation[c_max_forward_lights];
			vec4 spot_p0[c_max_forward_lights];
			vec4 shadow_p0[c_max_forward_lights];
			vec4 shadowmap_p0[c_max_forward_lights];
			vec4 csm_p0[c_max_forward_lights];
			vec4 csm_p1[c_max_forward_lights];
			vec4 csm_p2[c_max_forward_lights];
			//mat4 shadow_matrix[c_max_forward_lights];

			for(size_t i = 0; i < lights.size(); ++i)
			{
				const GpuLight& l = lights[i];
				const GpuShadow& s = l.shadow;
				const GpuCSMShadow& csm = l.csm;

				position_range[i] = { l.position, l.range };
				energy_specular[i] = { l.energy, l.specular };
				direction_attenuation[i] = { l.direction, l.attenuation };
				spot_p0[i] = { l.spot_attenuation, l.spot_cutoff, PAD, PAD };

				shadow_p0[i] = { s.matrix, s.bias, s.radius, s.range };
				shadowmap_p0[i] = { s.atlas_slot, s.atlas_subdiv };

				csm_p0[i] = { csm.num_slices, PAD, PAD, PAD };
				csm_p1[i] = csm.matrices;
				csm_p2[i] = csm.splits;
			}

			bgfx::setViewUniform(pass.m_index, u_light_position_range,			&position_range,		uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_energy_specular,			&energy_specular,		uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_direction_attenuation,	&direction_attenuation,	uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_spot_p0,					&spot_p0,				uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_shadow_p0,				&shadow_p0,				uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_shadowmap_p0,			&shadowmap_p0,			uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_csm_p0,					&csm_p0,				uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_csm_p1,					&csm_p1,				uint16_t(lights.size()));
			bgfx::setViewUniform(pass.m_index, u_light_csm_p2,					&csm_p2,				uint16_t(lights.size()));
		}

		bgfx::UniformHandle u_light_position_range;
		bgfx::UniformHandle u_light_energy_specular;
		bgfx::UniformHandle u_light_direction_attenuation;
		bgfx::UniformHandle u_light_spot_p0;
		bgfx::UniformHandle u_light_shadow_p0;
		bgfx::UniformHandle u_light_shadowmap_p0;
		bgfx::UniformHandle u_light_csm_p0;
		bgfx::UniformHandle u_light_csm_p1;
		bgfx::UniformHandle u_light_csm_p2;

		static GpuState me;
	};
#else
	template <>
	struct GpuState<GpuLight>
	{
		void pack(GpuLight& gpu_light, size_t index, const GpuTexture& buffer, float* dest)
		{
			size_t offset = index * buffer.stride;// + (index % texture_size) * height;

			//memcpy(pack, &gpu_light, sizeof(GpuLight));

			memcpy(dest + offset, &gpu_light.position, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.energy, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.direction, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.spot_attenuation, sizeof(float) * 2);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.shadow.matrix, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.shadow.atlas_slot, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.csm.num_slices, sizeof(float) * 1);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.csm.matrices, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &gpu_light.csm.splits, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		void pack(GpuTexture& buffer, span<GpuLight> lights)
		{
			const size_t height = 9;
			const size_t lines = 1;
			const uvec2 size = uvec2(buffer.width, uint16_t(lines * height));

			// swap two buffers so that bgfx can still read the previous one
			swap(buffer.memory, buffer.prev);

			if(buffer.texture.m_size != size)
				buffer.texture = { size, false, TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP };

			const uint32_t memsize = uint32_t(size.x * size.y * buffer.stride);
			buffer.memory.resize(memsize);
			for(size_t index = 0; index < lights.size(); ++index)
			{
				this->pack(lights[index], index, buffer, buffer.memory.data());
			}

			const bgfx::Memory* mem = bgfx::makeRef(buffer.memory.data(), sizeof(float) * buffer.memory.size());
			bgfx::updateTexture2D(buffer.texture, 0, 0, 0, 0, buffer.width, uint16_t(lines * height), mem);
		}

		static GpuState me;
	};
#endif
}

#undef PAD



namespace two
{
	template <>
	struct GpuState<BCS>
	{
		void init()
		{
			u_bcs = bgfx::createUniform("u_tonemap_bcs", bgfx::UniformType::Vec4);
		}

		void upload(const BCS& bcs)
		{
			vec4 bcs_values = { bcs.m_brightness, bcs.m_contrast, bcs.m_saturation, 0.f };
			bgfx::setUniform(u_bcs, &bcs_values);
		}

		bgfx::UniformHandle u_bcs;

		static GpuState me;
	};

	template <>
	struct GpuState<Tonemap>
	{
		void init()
		{
			u_exposure_p0 = bgfx::createUniform("u_exposure_p0", bgfx::UniformType::Vec4);
		}

		void upload(const Tonemap& tonemap)
		{
			vec4 exposure_p0 = { tonemap.m_exposure, tonemap.m_white_point, 0.f, 0.f };
			bgfx::setUniform(u_exposure_p0, &exposure_p0);
		}

		bgfx::UniformHandle u_exposure_p0;

		static GpuState me;
	};
}




namespace two
{
	template <>
	struct GpuState<GIProbe>
	{
		void init(uint16_t array_size = 1U)
		{
			u_transform   = bgfx::createUniform("u_gi_probe_transform",    bgfx::UniformType::Mat4, array_size);
			u_bounds      = bgfx::createUniform("u_gi_probe_bounds4",      bgfx::UniformType::Vec4, array_size);
			u_p0      = bgfx::createUniform("u_gi_probe_p0",       bgfx::UniformType::Vec4, array_size);
			u_inv_extents = bgfx::createUniform("u_gi_probe_inv_extents4", bgfx::UniformType::Vec4, array_size);
			u_cell_size   = bgfx::createUniform("u_gi_probe_cell_size4",   bgfx::UniformType::Vec4, array_size);
		}

		void upload(bgfx::Encoder& encoder, const GIProbe& gi_probe, const mat4& view) const
		{
			float diffuse = gi_probe.m_dynamic_range * gi_probe.m_diffuse;
			float specular = gi_probe.m_dynamic_range * gi_probe.m_specular;

			mat4 transform = gi_probe.m_transform * inverse(view);
			vec4 params = { diffuse, specular, gi_probe.m_bias, gi_probe.m_normal_bias };
			vec4 bounds = { gi_probe.m_extents * 2.f, 0.f };
			vec4 inv_extents = { vec3(1.f) / gi_probe.m_extents, 1.f };
			vec4 cell_size = { gi_probe.m_extents * 2.f / float(gi_probe.m_subdiv), 1.f };

			encoder.setUniform(u_transform, &transform);
			encoder.setUniform(u_bounds, &bounds);
			encoder.setUniform(u_p0, &params);
			encoder.setUniform(u_inv_extents, &inv_extents);
			encoder.setUniform(u_cell_size, &cell_size);
		}

		bgfx::UniformHandle u_transform;
		bgfx::UniformHandle u_bounds;
		bgfx::UniformHandle u_p0;
		bgfx::UniformHandle u_inv_extents;
		bgfx::UniformHandle u_cell_size;

		static GpuState me;
	};

	template <>
	struct GpuState<GpuVoxelGI>
	{
		void init()
		{
			u_world  = bgfx::createUniform("u_voxelgi_world",  bgfx::UniformType::Mat4);
			u_normal = bgfx::createUniform("u_voxelgi_normal", bgfx::UniformType::Mat3);

			u_p0 = bgfx::createUniform("u_voxelgi_p0", bgfx::UniformType::Vec4);
			u_p1 = bgfx::createUniform("u_voxelgi_p1", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, GIProbe& gi_probe) const
		{
			vec4 voxelgi_extents = { gi_probe.m_extents, 0.f };
			vec4 voxelgi_subdiv = { vec3(float(gi_probe.m_subdiv)), 0.f };

			mat4 voxelgi_world = gi_probe.m_transform;
			//mat3 voxelgi_normal = {};

			encoder.setUniform(u_p0, &voxelgi_extents);
			encoder.setUniform(u_p1, &voxelgi_subdiv);

			encoder.setUniform(u_world, &voxelgi_world);
			//encoder.setUniform(u_normal, &voxelgi_normal);
		}

		bgfx::UniformHandle u_world;
		bgfx::UniformHandle u_normal;
		bgfx::UniformHandle u_p0;
		bgfx::UniformHandle u_p1;

		static GpuState me;

	};
}


#include <bgfx/bgfx.h>

module two.gfx.pbr;

#include <cstring>

#define PAD 1.f

namespace two
{
#if !ZONES_LIGHTS_BUFFER
	template <>
	struct GpuState<ZoneLights>
	{
		void init()
		{
			u_light_indices = bgfx::createUniform("u_light_indices", bgfx::UniformType::Vec4, c_max_forward_lights, bgfx::UniformSet::View);
			u_light_counts = bgfx::createUniform("u_light_counts", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_shadow_counts = bgfx::createUniform("u_shadow_counts", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
		}

		void upload(uint16_t view, const ZoneLights& lights) const
		{
			bgfx::setViewUniform(view, u_light_counts, &lights.m_light_counts);
			bgfx::setViewUniform(view, u_shadow_counts, &lights.m_shadow_counts);
			if(lights.m_light_count > 0U)
				bgfx::setViewUniform(view, u_light_indices, lights.m_light_indices, lights.m_light_count);
		}

		bgfx::UniformHandle u_light_indices = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_light_counts = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_shadow_counts = BGFX_INVALID_HANDLE;

		static GpuState me;
	};
#else
	template <>
	struct GpuState<ZoneLights>
	{
		constexpr static size_t rows = 1 + BlockLight::ShotUniform::max_lights;

		void pack(const ZoneLights& lights, size_t& offset, GpuTexture& buffer, float* dest)
		{
			memcpy(dest + offset, &lights.m_light_counts, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			for(size_t i = 0; i < BlockLight::ShotUniform::max_lights; ++i)
			{
				memcpy(dest + offset, lights.m_light_indices + i, sizeof(float) * 4);
				offset += buffer.width * buffer.stride;
			}
		}

		static GpuState me;
	};
#endif

#if !ZONES_BUFFER
	template <>
	struct GpuState<Radiance>
	{
		void init()
		{
			u_radiance_p0 = bgfx::createUniform("u_radiance_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_ambient_p0 = bgfx::createUniform("u_ambient_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
		}

		void upload(const Pass& pass, const Radiance& radiance) const
		{
			vec4 radiance_p0 = { to_vec3(radiance.m_colour), radiance.m_energy };
			vec4 ambient_p0 = { to_vec3(radiance.m_ambient), PAD };

			bgfx::setViewUniform(pass.m_index, u_radiance_p0, &radiance_p0);
			bgfx::setViewUniform(pass.m_index, u_ambient_p0, &ambient_p0);
		}

		bgfx::UniformHandle u_radiance_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_ambient_p0 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Skylight>
	{
		void init()
		{
			u_skylight_p0 = bgfx::createUniform("u_skylight_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_skylight_p1 = bgfx::createUniform("u_skylight_p1", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_skylight_p2 = bgfx::createUniform("u_skylight_p2", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
		}

		void upload(const Pass& pass, const Skylight& skylight) const
		{
			vec4 skylight_p0 = { normalize(skylight.m_direction), PAD };
			vec4 skylight_p1 = { to_vec3(skylight.m_color) * skylight.m_intensity, PAD };
			vec4 skylight_p2 = { to_vec3(skylight.m_ground) * skylight.m_intensity, PAD };

			bgfx::setViewUniform(pass.m_index, u_skylight_p0, &skylight_p0);
			bgfx::setViewUniform(pass.m_index, u_skylight_p1, &skylight_p1);
			bgfx::setViewUniform(pass.m_index, u_skylight_p2, &skylight_p2);
		}

		bgfx::UniformHandle u_skylight_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_skylight_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_skylight_p2 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Fog>
	{
		void init()
		{
			u_fog_p0 = bgfx::createUniform("u_fog_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_fog_p1 = bgfx::createUniform("u_fog_p1", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_fog_p2 = bgfx::createUniform("u_fog_p2", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_fog_p3 = bgfx::createUniform("u_fog_p3", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
		}

		void upload(const Pass& pass, const Fog& fog) const
		{
			vec4 params_0 = { fog.m_density, to_vec3(fog.m_colour) };
			vec4 params_1 = { float(fog.m_depth), fog.m_depth_begin, fog.m_depth_end, fog.m_depth_curve };
			vec4 params_2 = { float(fog.m_height), fog.m_height_max, fog.m_height_max, fog.m_height_curve };
			vec4 params_3 = { float(fog.m_transmit), fog.m_transmit_curve, PAD, PAD };

			bgfx::setViewUniform(pass.m_index, u_fog_p0, &params_0);
			bgfx::setViewUniform(pass.m_index, u_fog_p1, &params_1);
			bgfx::setViewUniform(pass.m_index, u_fog_p2, &params_2);
			bgfx::setViewUniform(pass.m_index, u_fog_p3, &params_3);
		}

		bgfx::UniformHandle u_fog_p0 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_p1 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_p2 = BGFX_INVALID_HANDLE;
		bgfx::UniformHandle u_fog_p3 = BGFX_INVALID_HANDLE;

		static GpuState me;
	};

	template <>
	struct GpuState<Zone>
	{
		void upload(const Pass& pass, const Zone& zone) const
		{
			GpuState<Radiance>::me.upload(pass, zone.m_radiance);
			GpuState<Skylight>::me.upload(pass, zone.m_skylight);
			GpuState<Fog>::me.upload(pass, zone.m_fog);
		}

		static GpuState me;
	};
#else
	template <>
	struct GpuState<Radiance>
	{
		constexpr static size_t rows = 2;

		void pack(const Radiance& radiance, size_t& offset, GpuTexture& buffer, float* dest)
		{
			vec4 radiance_p0 = { to_vec3(radiance.m_colour), radiance.m_energy };
			vec4 ambient_p0 = { to_vec3(radiance.m_ambient), PAD };

			memcpy(dest + offset, &radiance_p0, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &ambient_p0, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<Skylight>
	{
		constexpr static size_t rows = 3;

		void pack(const Skylight& skylight, size_t& offset, GpuTexture& buffer, float* dest)
		{
			vec4 skylight_p0 = { normalize(skylight.m_direction), PAD };
			vec4 skylight_p1 = { to_vec3(skylight.m_color) * skylight.m_intensity, PAD };
			vec4 skylight_p2 = { to_vec3(skylight.m_ground) * skylight.m_intensity, PAD };

			memcpy(dest + offset, &skylight_p0, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &skylight_p1, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &skylight_p2, sizeof(float) * 3);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<Fog>
	{
		constexpr static size_t rows = 4;

		void pack(const Fog& fog, size_t& offset, GpuTexture& buffer, float* dest)
		{
			vec4 params_0 = { fog.m_density, to_vec3(fog.m_colour) };
			vec4 params_1 = { float(fog.m_depth), fog.m_depth_begin, fog.m_depth_end, fog.m_depth_curve };
			vec4 params_2 = { float(fog.m_height), fog.m_height_max, fog.m_height_max, fog.m_height_curve };
			vec4 params_3 = { float(fog.m_transmit), fog.m_transmit_curve, PAD, PAD };

			memcpy(dest + offset, &params_0, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params_1, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params_2, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;

			memcpy(dest + offset, &params_3, sizeof(float) * 4);
			offset += buffer.width * buffer.stride;
		}

		static GpuState me;
	};

	template <>
	struct GpuState<Zone>
	{
		void pack(const Zone& zone, size_t offset, GpuTexture& buffer, float* dest)
		{
			GpuState<Radiance>::me.pack(zone.m_radiance, offset, buffer, dest);
			if(zone.m_fog.m_enabled)
				GpuState<Fog>::me.pack(zone.m_fog, offset, buffer, dest);
		}

		void pack(Texture& texture, span<Zone> zones)
		{
			GpuTexture buffer = { texture, 1024, 4 };

			const uint32_t height = GpuState<Radiance>::me.rows
								  + GpuState<Skylight>::me.rows;
								  + GpuState<Fog>::me.rows;
			const uint32_t lines = 1;
			const uvec2 size = uvec2(buffer.width, lines * height);

			if(texture.m_size != size)
				texture = { size, bgfx::TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP };

			const bgfx::Memory* memory = bgfx::alloc(buffer.width * lines * height * buffer.stride * sizeof(float));

			for(size_t index = 0; index < zones.size(); ++index)
			{
				this->pack(zones[index], index * buffer.stride, buffer, (float*)memory->data);
			}

			bgfx::updateTexture2D(texture, 0, 0, 0, 0, buffer.width, uint16_t(lines * height), memory);
		}

		static GpuState me;
	};
#endif
}

#undef PAD
