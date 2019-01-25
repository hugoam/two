#pragma once

#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/ecs.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>



#ifndef MUD_GFX_PBR_EXPORT
#define MUD_GFX_PBR_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum ShaderOptionLight : unsigned int;
    enum ShaderOptionRadiance : unsigned int;
    enum ShaderOptionShadow : unsigned int;
    enum ShaderModeShadow : unsigned int;
    enum CSMFilterMode : unsigned int;
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
    struct ReflectionCubemap;
    class ReflectionAtlas;
    class ReflectionProbe;
	class PassGeometry;
	class PassLights;
	class PassOpaque;
	class PassAlpha;
    class PassProbes;
    class BlockReflection;
    struct ShadowCubemap;
    class ShadowAtlas;
    struct CSMShadow;
    class PassShadow;
    class PassShadowmap;
    struct ShadowRenderer;
    struct LightBounds;
    struct LightShadow;
    class BlockShadow;
    struct EffectBlurUniform;
    struct BlurKernel;
    class BlockBlur;
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



#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	enum ShaderOptionLight : unsigned int
	{
		FOG,
		DIRECT_LIGHT
	};

	template <uint16_t num_lights, uint16_t num_direct = 1>
	struct LightArray
	{
		vec4 position_range[num_lights];
		vec4 energy_specular[num_lights];
		vec4 direction_attenuation[num_lights];
		vec4 shadow_color_enabled[num_lights];
		mat4 shadow_matrix[num_lights];
		vec4 spot_params[num_lights];

		vec4 light_indices[num_lights];
		vec4 light_counts;

		mat4 csm_matrix[num_direct][4];
		vec4 csm_splits[num_direct];
	};

	export_ MUD_GFX_PBR_EXPORT void debug_draw_light_clusters(Gnode& parent, Camera& camera);
	export_ MUD_GFX_PBR_EXPORT void debug_draw_light_slices(Gnode& parent, Light& light, bool frustums = true, bool bounds = true);

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockLight : public DrawBlock
	{
	public:
		BlockLight(GfxSystem& gfx_system, BlockShadow& block_shadow);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const final;
		virtual void submit(Render& render, const Pass& render_pass) const final;

		void update_lights(Render& render, const mat4& view, array<Light*> lights, array<LightShadow> shadows);

		void upload_environment(Render& render, const Pass& render_pass, Environment* environment) const;
		void upload_fog(Render& render, const Pass& render_pass, Fog& fog) const;
		void upload_lights(const Pass& render_pass) const;
		
		BlockShadow& m_block_shadow;

		uint16_t m_direct_light_index = 0;
		Light* m_direct_light = nullptr;
		vector<Light*> m_direct_lights;

		struct LightUniform
		{
			void createUniforms(uint16_t max_direct, uint16_t max_lights)
			{
				u_light_position_range			= bgfx::createUniform("u_light_position_range",			bgfx::UniformType::Vec4, max_lights);
				u_light_energy_specular			= bgfx::createUniform("u_light_energy_specular",		bgfx::UniformType::Vec4, max_lights);
				u_light_direction_attenuation	= bgfx::createUniform("u_light_direction_attenuation",	bgfx::UniformType::Vec4, max_lights);
				u_light_shadow					= bgfx::createUniform("u_light_shadow",					bgfx::UniformType::Vec4, max_lights);
				u_light_shadow_matrix			= bgfx::createUniform("u_light_shadow_matrix",			bgfx::UniformType::Mat4, max_lights);
				u_light_spot_params				= bgfx::createUniform("u_light_spot_params",			bgfx::UniformType::Vec4, max_lights);
				u_csm_matrix					= bgfx::createUniform("u_csm_matrix",					bgfx::UniformType::Mat4, max_direct * 4);
				u_csm_splits					= bgfx::createUniform("u_csm_splits",					bgfx::UniformType::Vec4, max_direct);
			}

			template <uint16_t size>
			void setUniforms(bgfx::Encoder& encoder, const LightArray<size>& data, uint16_t direct_light_count, uint16_t light_count) const
			{
				encoder.setUniform(u_light_position_range,			&data.position_range,			light_count);
				encoder.setUniform(u_light_energy_specular,			&data.energy_specular,			light_count);
				encoder.setUniform(u_light_direction_attenuation,	&data.direction_attenuation,	light_count);
				encoder.setUniform(u_light_shadow,					&data.shadow_color_enabled,		light_count);
				encoder.setUniform(u_light_shadow_matrix,			&data.shadow_matrix,			light_count);
				encoder.setUniform(u_light_spot_params,				&data.spot_params,				light_count);

				encoder.setUniform(u_csm_matrix, &data.csm_matrix[0], direct_light_count * 4);
				encoder.setUniform(u_csm_splits, &data.csm_splits,	direct_light_count);
			}

			bgfx::UniformHandle u_light_position_range;
			bgfx::UniformHandle u_light_energy_specular;
			bgfx::UniformHandle u_light_direction_attenuation;
			bgfx::UniformHandle u_light_shadow;
			bgfx::UniformHandle u_light_shadow_matrix;
			bgfx::UniformHandle u_light_spot_params;
			bgfx::UniformHandle u_csm_matrix;
			bgfx::UniformHandle u_csm_splits;
		};

		struct ShotUniform
		{
			static constexpr size_t max_lights = 64;
			static constexpr size_t max_shadows = 32;
			static constexpr size_t max_forward_lights = 16;
			static constexpr size_t max_direct_lights = 1;

			void createUniforms()
			{
				u_light_indices = bgfx::createUniform("u_light_indices", bgfx::UniformType::Vec4, max_lights);
				u_light_counts  = bgfx::createUniform("u_light_counts",  bgfx::UniformType::Vec4);

				u_light_array.createUniforms(uint16_t(max_direct_lights), uint16_t(max_lights));
			}

			bgfx::UniformHandle u_light_indices;
			bgfx::UniformHandle u_light_counts;

			LightUniform u_light_array;

		} u_shot;

		struct SceneUniform
		{
			void createUniforms()
			{
				u_radiance_color_energy =  bgfx::createUniform("u_radiance_color_energy",	bgfx::UniformType::Vec4);
				u_ambient_params =		   bgfx::createUniform("u_ambient_params",			bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle u_radiance_color_energy;
			bgfx::UniformHandle u_ambient_params;

		} u_scene;

		struct FogUniform
		{
			void createUniforms()
			{
				u_fog_params_0 = bgfx::createUniform("u_fog_params_0", bgfx::UniformType::Vec4);
				u_fog_params_1 = bgfx::createUniform("u_fog_params_1", bgfx::UniformType::Vec4);
				u_fog_params_2 = bgfx::createUniform("u_fog_params_2", bgfx::UniformType::Vec4);
				u_fog_params_3 = bgfx::createUniform("u_fog_params_3", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle u_fog_params_0;
			bgfx::UniformHandle u_fog_params_1;
			bgfx::UniformHandle u_fog_params_2;
			bgfx::UniformHandle u_fog_params_3;

		} u_fog;

		LightArray<ShotUniform::max_lights> m_lights_data;
		uint16_t m_light_count;
	};
}



#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class refl_ MUD_GFX_PBR_EXPORT LightmapItem
	{
	public:
		LightmapItem() {}
		LightmapItem(size_t item, bgfx::TextureHandle lightmap, vec4 uv_scale_offset) : m_item(item), m_lightmap(lightmap), m_uv_scale_offset(uv_scale_offset) {}
		size_t m_item = SIZE_MAX;
		bgfx::TextureHandle m_lightmap = BGFX_INVALID_HANDLE;
		vec4 m_uv_scale_offset = vec4(1.f, 1.f, 0.f, 0.f);
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT Lightmap
	{
	public:
		Lightmap(uint32_t size);

		uint32_t m_size = 0;
		float m_density = 1.f;
		bool m_dirty = false;

		TextureAtlas m_atlas;

		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;

		vector<LightmapItem> m_items;

		void add_item(size_t index, Item& item, bool valid, const vec4& uv_scale_offset);
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT LightmapAtlas : public NonCopy
	{
	public:
		LightmapAtlas(uint32_t size, float density);
		~LightmapAtlas();

		Lightmap& add_lightmap() { m_layers.emplace_back(make_unique<Lightmap>(m_size)); return *m_layers.back(); }

		uint32_t m_size;
		float m_density = 1.f;
		bool m_dirty = false;
		string m_save_path;

		mat4 m_capture_transform;
		vec3 m_capture_extents;

		vector<unique<Lightmap>> m_layers;
	};

	struct LightmapRenderer : public Renderer
	{
		LightmapRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ class MUD_GFX_PBR_EXPORT PassLightmap : public DrawPass
	{
	public:
		PassLightmap(GfxSystem& gfx_system, BlockLightmap& block_lightmap);

		BlockLightmap& m_block_lightmap;

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockLightmap : public DrawBlock
	{
	public:
		BlockLightmap(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake);

		BlockLight& m_block_light;
		BlockGIBake& m_block_gi_bake;

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const override;

		void bake_geometry(array<Item*> items, LightmapAtlas& atlas);
		void bake_lightmaps(Scene& scene, LightmapAtlas& atlas, const mat4& transform, const vec3& extents);

		struct VoxelGIUniform
		{
			void createUniforms()
			{
				s_lightmap = bgfx::createUniform("s_lightmap",        bgfx::UniformType::Int1);
			}

			bgfx::UniformHandle s_lightmap;

		} u_lightmap;

		Program* m_lightmap;

		struct BakeEntry { Scene* scene; LightmapAtlas* atlas; };
		vector<BakeEntry> m_bake_queue;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT BlockGeometry : public DrawBlock
	{
	public:
		BlockGeometry(GfxSystem& gfx_system);
		~BlockGeometry();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const final;
		virtual void submit(Render& render, const Pass& render_pass) const final;

		Material* m_material = nullptr;
		Material* m_material_twosided = nullptr;
	};

	export_ class MUD_GFX_PBR_EXPORT PassOpaque : public DrawPass
	{
	public:
		PassOpaque(GfxSystem& gfx_system);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;

		size_t m_direct_light_index;
	};

	export_ class MUD_GFX_PBR_EXPORT PassAlpha : public DrawPass
	{
	public:
		PassAlpha(GfxSystem& gfx_system);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_PBR_EXPORT PassGeometry : public DrawPass
	{
	public:
		PassGeometry(GfxSystem& gfx_system, BlockGeometry& block_geometry);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;

		BlockGeometry& m_block_geometry;
	};

	export_ class MUD_GFX_PBR_EXPORT PassLights : public RenderPass
	{
	public:
		PassLights(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void submit_render_pass(Render& render) final;
		
		BlockFilter& m_filter;
		Program* m_program;
	};

	struct ReflectionRenderer : public Renderer
	{
		ReflectionRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct ForwardRenderer : public Renderer
	{
		ForwardRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct DeferredRenderer : public Renderer
	{
		DeferredRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ MUD_GFX_PBR_EXPORT void gather_gi_probes(Scene& scene, vector<GIProbe*>& gi_probes);
	export_ MUD_GFX_PBR_EXPORT void gather_lightmaps(Scene& scene, vector<LightmapAtlas*>& atlases);
	export_ MUD_GFX_PBR_EXPORT void gather_reflection_probes(Scene& scene, vector<ReflectionProbe*>& reflection_probes);

	export_ MUD_GFX_PBR_EXPORT void pipeline_pbr(GfxSystem& gfx_system, Pipeline& pipeline, bool deferred = false);
}


#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#include <stl/map.h>
#endif

namespace mud
{
	enum ShaderOptionRadiance : unsigned int
	{
		RADIANCE_ENVMAP,
		RADIANCE_ARRAY,
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockRadiance : public DrawBlock
	{
	public:
		BlockRadiance(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy);

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void prefilter_radiance(Radiance& radiance);

		struct RadianceUniform
		{
			void createUniforms()
			{
				s_radiance_map = bgfx::createUniform("s_radiance_map", bgfx::UniformType::Int1);
			}

			bgfx::UniformHandle s_radiance_map;

		} u_radiance;

		struct PrefilterUniform
		{
			void createUniforms()
			{
				u_prefilter_envmap_params = bgfx::createUniform("u_prefilter_envmap_params", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle u_prefilter_envmap_params;

		} u_prefilter;

		BlockFilter& m_filter;
		BlockCopy& m_copy;

		Program& m_prefilter_program;

		vector<Radiance*> m_prefilter_queue;
		map<uint16_t, uint16_t> m_prefiltered;
	};
}



#ifndef MUD_MODULES
#endif


#ifndef MUD_MODULES
#endif

#include <bgfx/bgfx.h>

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	struct ReflectionCubemap
	{
		ReflectionCubemap(uint16_t size);
		bgfx::FrameBufferHandle m_fbo[6];
		bgfx::TextureHandle m_cubemap;
		bgfx::TextureHandle m_depth;
		uint16_t m_size;
	};

	class ReflectionAtlas
	{
	public:
		ReflectionAtlas(uint16_t size, uint16_t subdiv);
		~ReflectionAtlas();

		uint16_t m_size = 0;
		uint16_t m_subdiv = 0;

		bgfx::TextureHandle m_color_tex = BGFX_INVALID_HANDLE;

		vec4 probe_rect(ReflectionProbe& probe);
		uvec4 render_update(Render& render, ReflectionProbe& probe);

		struct Slot
		{
			size_t m_index;
			ReflectionProbe* m_probe;
			uvec4 m_urect;
			vec4 m_rect;
			uint64_t m_last_update;
		};

		bgfx::FrameBufferHandle m_fbo[6];
		bgfx::TextureHandle m_color;

		vector<Slot> m_slots;
		vector<Slot*> m_free_slots;
	};
}

namespace mud
{
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

	export_ class refl_ MUD_GFX_PBR_EXPORT ReflectionProbe
	{
	public:
		ReflectionProbe(Node3& node);

		attr_ Node3& m_node;

		attr_ bool m_visible = true;
		attr_ float m_intensity = 1.f;
		attr_ vec3 m_extents = Zero3;
		attr_ bool m_shadows = false;

		ReflectionAtlas* m_atlas;
		int m_atlas_index = -1;

		attr_ bool m_dirty = true;
	};

	export_ class MUD_GFX_PBR_EXPORT PassProbes : public RenderPass
	{
	public:
		PassProbes(GfxSystem& gfx_system, BlockReflection& block_reflection);

		BlockReflection& m_block_reflection;

		virtual void submit_render_pass(Render& render) final;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockReflection : public DrawBlock
	{
	public:
		BlockReflection(GfxSystem& gfx_system);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const final;
		virtual void submit(Render& render, const Pass& render_pass) const final;

		void upload_reflection_probes(Render& render, Pass& render_pass, array<ReflectionProbe*> probes);
		void render_reflection_probe(Render& render, ReflectionProbe& reflection_probe);

		ReflectionCubemap& find_cubemap(uint16_t size);

		struct ReflectionUniform
		{
			static constexpr size_t max_reflection_probes = 16;

			void createUniforms(uint16_t max_probes)
			{
				u_extents_intensity		= bgfx::createUniform("u_reflection_extents_intensity",	bgfx::UniformType::Vec4, max_probes);
				u_ambient				= bgfx::createUniform("u_reflection_ambient",			bgfx::UniformType::Vec4, max_probes);
				u_atlas_rect			= bgfx::createUniform("u_reflection_atlas_rect",		bgfx::UniformType::Mat4, max_probes);
				u_matrix				= bgfx::createUniform("u_reflection_matrix",			bgfx::UniformType::Vec4, max_probes);

				u_indices		= bgfx::createUniform("u_reflection_indices",		bgfx::UniformType::Int1, max_probes);
				u_count			= bgfx::createUniform("u_reflection_count",			bgfx::UniformType::Int1);
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

		vector<ReflectionCubemap> m_cubemaps;

		ReflectionAtlas m_atlas;

		float m_reflection_multiplier;
	};
}



#ifndef MUD_MODULES
#endif


#ifndef MUD_MODULES
#endif

#include <bgfx/bgfx.h>

#ifndef MUD_CPP_20
#include <stl/vector.h>
#include <stl/map.h>
#endif

namespace mud
{
	struct ShadowCubemap
	{
		ShadowCubemap(uint16_t size);
		bgfx::FrameBufferHandle m_fbos[6];
		bgfx::TextureHandle m_cubemap;
		uint16_t m_size;
	};

	class ShadowAtlas
	{
	public:
		ShadowAtlas() {}
		ShadowAtlas(uint16_t size, vector<uint16_t> slices_subdiv);

		uint16_t m_size = 0;

		bgfx::TextureHandle m_depth = BGFX_INVALID_HANDLE;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;

		vector<ShadowCubemap> m_cubemaps;

		uvec4 light_rect(Light& light);

		uvec4 render_update(Render& render, Light& light);
		bool update_light(Light& light, uint64_t render, float coverage, uint64_t light_version);
		void remove_light(Light& light);

		ShadowCubemap& light_cubemap(Light& light, uint16_t shadow_size);

		struct Slice
		{
			Slice(uint32_t size, uint16_t subdiv, uvec4 rect);

			uint32_t m_size;
			uint16_t m_subdiv;
			uvec4 m_rect;

			struct Slot
			{
				Light* m_light;
				uvec4 m_rect;
			};

			void remove_light(Light& light);
			void add_light(Light& light);

			vector<Slot> m_slots;
			vector<Slot*> m_free_slots;
		};

		vector<Slice> m_slices;

		struct Index
		{
			uint8_t m_slice;
			uint16_t m_slot;
		};

		vector<Index> m_light_indices;
	};
}

namespace mud
{
	enum ShaderOptionShadow : unsigned int
	{
		CSM_SHADOW,
		CSM_BLEND,
	};

	enum ShaderModeShadow : unsigned int
	{
		CSM_NUM_CASCADES,
		CSM_PCF_LEVEL,
	};

	enum CSMFilterMode : unsigned int
	{
		CSM_NO_PCF = 0,
		CSM_HARD_PCF = 1,
		CSM_PCF5 = 2,
		CSM_PCF13 = 3
	};

	struct CSMShadow
	{
		CSMShadow() {}
		CSMShadow(uint16_t size);

		uint16_t m_size = 0;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_depth = BGFX_INVALID_HANDLE;
		CSMFilterMode m_filter_mode = CSM_PCF5;
	};

	export_ class MUD_GFX_PBR_EXPORT PassShadow : public PassDepth
	{
	public:
		PassShadow(GfxSystem& gfx_system, BlockDepth& block_depth, BlockShadow& block_shadow);

		BlockDepth& m_block_depth;
		BlockShadow& m_block_shadow;

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_PBR_EXPORT PassShadowmap : public RenderPass
	{
	public:
		PassShadowmap(GfxSystem& gfx_system, BlockShadow& block_shadow);

		BlockShadow& m_block_shadow;

		virtual void submit_render_pass(Render& render) final;
	};

	struct ShadowRenderer : public Renderer
	{
		ShadowRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ struct LightBounds
	{
		vec3 min = { 9000.0f,  9000.0f,  9000.0f };
		vec3 max = { -9000.0f, -9000.0f, -9000.0f };
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT LightShadow
	{
		struct Slice
		{
			vec4 m_viewport_rect;
			vec4 m_texture_rect;
			mat4 m_projection;
			mat4 m_transform;
			mat4 m_shadow_matrix;
			float m_bias_scale;

			FrustumSlice m_frustum_slice;
			LightBounds m_light_bounds;

			vector<Item*> m_items;
		};

		vector<FrustumSlice> m_frustum_slices;
		vector<Slice> m_slices;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockShadow : public DrawBlock
	{
	public:
		BlockShadow(GfxSystem& gfx_system, BlockDepth& block_depth);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void update_shadows(Render& render);
		void render_shadows(Render& render);

		void update_direct(Render& render, Light& light, size_t num_direct, size_t index);
		void render_direct(Render& render, Light& light, size_t index);

		BlockDepth& m_block_depth;

		DepthParams m_depth_params;

		Light* m_direct_light = nullptr;

		struct DirectionalShadowUniform
		{
			void createUniforms()
			{
				s_csm_atlas	 = bgfx::createUniform("s_csm_atlas",  bgfx::UniformType::Int1);
				u_csm_params = bgfx::createUniform("u_csm_params", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle s_csm_atlas;
			bgfx::UniformHandle u_csm_params;

		} u_direct_shadow;

		struct ShadowUniform
		{
			void createUniforms()
			{
				s_shadow_atlas = bgfx::createUniform("s_shadow_atlas", bgfx::UniformType::Int1);
				u_shadow_pixel_size = bgfx::createUniform("u_shadow_pixel_size", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle s_shadow_atlas;
			bgfx::UniformHandle u_shadow_pixel_size;

		} u_shadow;

		ShadowAtlas m_atlas;

		vector<LightShadow> m_shadows;

		CSMShadow m_csm;

#ifdef MUD_PLATFORM_EMSCRIPTEN
		CSMFilterMode m_pcf_level = CSM_HARD_PCF; // @todo can't get true pcf working on WebGL so far
#else
		CSMFilterMode m_pcf_level = CSM_PCF5;
#endif
	};
}



#ifndef MUD_MODULES
#endif

namespace mud
{
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>();
    
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::GIProbe>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Lightmap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapAtlas>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapItem>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGIBake>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGITrace>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGeometry>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLightmap>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>();
    export_ template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>();
    
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BCS*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::DofBlur*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::GIProbe*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::Glow*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::LightShadow*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::Lightmap*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::LightmapAtlas*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::LightmapItem*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::ReflectionProbe*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::Tonemap*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockBlur*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockDofBlur*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockGIBake*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockGITrace*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockGeometry*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockGlow*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockLight*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockLightmap*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockRadiance*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockReflection*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockShadow*>>;
    export_ template struct MUD_GFX_PBR_EXPORT Typed<vector<mud::BlockTonemap*>>;
}



#ifndef MUD_MODULES
#endif

namespace mud
{
namespace gfx
{
	export_ MUD_GFX_EXPORT func_ GIProbe& gi_probe(Gnode& parent, uint16_t subdiv, const vec3& extents);
	export_ MUD_GFX_EXPORT func_ LightmapAtlas& lightmap(Gnode& parent, uint32_t resolution, float density = 8.f, const string& save_path = "");
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

	export_ class refl_ MUD_GFX_PBR_EXPORT GIProbe
	{
	public:
		GIProbe(Node3& node);
		~GIProbe();

		void resize(uint16_t subdiv, const vec3& extents);
		void lightmap(uint32_t size, float density, const string& save_path = "");

		Node3& m_node;

		bgfx::TextureHandle m_raster = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_voxels_color = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_voxels_normals = BGFX_INVALID_HANDLE;
		bgfx::TextureHandle m_voxels_light = BGFX_INVALID_HANDLE;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;

		bgfx::TextureHandle m_voxels_light_rgba = BGFX_INVALID_HANDLE;

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

	export_ MUD_GFX_PBR_EXPORT void save_gi_probe(GfxSystem& gfx_system, GIProbe& gi_probe, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path);
	export_ MUD_GFX_PBR_EXPORT void load_gi_probe(GfxSystem& gfx_system, GIProbe& gi_probe, const string& path);

	struct VoxelRenderer : public Renderer
	{
		VoxelRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ class MUD_GFX_PBR_EXPORT PassGIBake : public DrawPass
	{
	public:
		PassGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake);

		BlockLight& m_block_light;
		BlockGIBake& m_block_gi_bake;

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_PBR_EXPORT PassGIProbes : public RenderPass
	{
	public:
		PassGIProbes(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake);

		BlockLight& m_block_light;
		BlockGIBake& m_block_gi_bake;

		virtual void submit_render_pass(Render& render) final;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGITrace : public DrawBlock
	{
	public:
		BlockGITrace(GfxSystem& gfx_system);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void upload_gi_probes(Render& render, const Pass& render_pass) const;

		struct GIProbeUniform
		{
			static const int max_gi_probes = 2;

			void createUniforms()
			{
				u_transform   = bgfx::createUniform("u_gi_probe_transform",    bgfx::UniformType::Mat4, max_gi_probes);
				u_bounds      = bgfx::createUniform("u_gi_probe_bounds4",      bgfx::UniformType::Vec4, max_gi_probes);
				// multiplier, bias, normal_bias, blend_ambient
				u_params      = bgfx::createUniform("u_gi_probe_params",       bgfx::UniformType::Vec4, max_gi_probes);
				u_inv_extents = bgfx::createUniform("u_gi_probe_inv_extents4", bgfx::UniformType::Vec4, max_gi_probes);
				u_cell_size   = bgfx::createUniform("u_gi_probe_cell_size4",   bgfx::UniformType::Vec4, max_gi_probes);

				s_gi_probe = bgfx::createUniform("s_gi_probe", bgfx::UniformType::Int1, max_gi_probes);
			}

			void setUniforms(bgfx::Encoder& encoder, GIProbe& gi_probe, const mat4& view) const
			{
				float diffuse = gi_probe.m_dynamic_range * gi_probe.m_diffuse;
				float specular = gi_probe.m_dynamic_range * gi_probe.m_specular;
				vec4 params = { diffuse, specular, gi_probe.m_bias, gi_probe.m_normal_bias };
				vec4 bounds = { gi_probe.m_extents * 2.f, 0.f };
				mat4 transform = gi_probe.m_transform * inverse(view);
				vec4 inv_extents = { Unit3 / gi_probe.m_extents, 1.f };
				vec4 cell_size = { gi_probe.m_extents * 2.f / float(gi_probe.m_subdiv), 1.f };

				encoder.setUniform(u_transform, &transform);
				encoder.setUniform(u_bounds, &bounds);
				encoder.setUniform(u_params, &params);
				encoder.setUniform(u_inv_extents, &inv_extents);
				encoder.setUniform(u_cell_size, &cell_size);
			}

			bgfx::UniformHandle u_transform;
			bgfx::UniformHandle u_bounds;
			bgfx::UniformHandle u_params;
			bgfx::UniformHandle u_inv_extents;
			bgfx::UniformHandle u_cell_size;

			bgfx::UniformHandle s_gi_probe;

		} u_gi_probe;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGIBake : public DrawBlock
	{
	public:
		BlockGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGITrace& block_trace);

		BlockLight& m_block_light;
		BlockGITrace& m_block_trace;

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void voxelize(Render& render, GIProbe& gi_probe);
		void compute(Render& render, GIProbe& gi_probe);
		void bounce(Render& render, GIProbe& gi_probe);
		void output(Render& render, GIProbe& gi_probe);

		struct VoxelGIUniform
		{
			void createUniforms()
			{
				s_voxels_albedo    = bgfx::createUniform("s_voxels_albedo",  bgfx::UniformType::Int1);
				s_voxels_normals   = bgfx::createUniform("s_voxels_normals", bgfx::UniformType::Int1);
				s_voxels_light     = bgfx::createUniform("s_voxels_light",   bgfx::UniformType::Int1);

				s_voxels_light_rgba  = bgfx::createUniform("s_voxels_light_rgba",   bgfx::UniformType::Int1);

				u_world  = bgfx::createUniform("u_voxelgi_world",  bgfx::UniformType::Mat4);
				u_normal = bgfx::createUniform("u_voxelgi_normal", bgfx::UniformType::Mat3);

				u_params_0 = bgfx::createUniform("u_voxelgi_params_0", bgfx::UniformType::Vec4);
				u_params_1 = bgfx::createUniform("u_voxelgi_params_1", bgfx::UniformType::Vec4);
			}

			void setUniforms(bgfx::Encoder& encoder, GIProbe& gi_probe) const
			{
				vec4 voxelgi_extents = { gi_probe.m_extents, 0.f };
				vec4 voxelgi_subdiv = { vec3(float(gi_probe.m_subdiv)), 0.f };

				mat4 voxelgi_world = gi_probe.m_transform;
				//mat3 voxelgi_normal = {};

				encoder.setUniform(u_params_0, &voxelgi_extents);
				encoder.setUniform(u_params_1, &voxelgi_subdiv);

				encoder.setUniform(u_world, &voxelgi_world);
				//encoder.setUniform(u_normal, &voxelgi_normal);
			}

			bgfx::UniformHandle s_voxels_albedo;
			bgfx::UniformHandle s_voxels_normals;
			bgfx::UniformHandle s_voxels_light;
			bgfx::UniformHandle s_voxels_light_rgba;

			bgfx::UniformHandle u_world;
			bgfx::UniformHandle u_normal;

			bgfx::UniformHandle u_params_0;
			bgfx::UniformHandle u_params_1;

		} u_voxelgi;

		Program* m_direct_light;
		Program* m_bounce_light;
		Program* m_output_light;
		Program* m_voxelize;

		GIProbe* m_bake_probe = nullptr;

		bool m_direct_light_compute = false;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
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
			u_blur_params = bgfx::createUniform("u_blur_params", bgfx::UniformType::Vec4);
			u_blur_kernel_0_3 = bgfx::createUniform("u_blur_kernel_0_3", bgfx::UniformType::Vec4);
			u_blur_kernel_4_7 = bgfx::createUniform("u_blur_kernel_4_7", bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle u_blur_params;
		bgfx::UniformHandle u_blur_kernel_0_3;
		bgfx::UniformHandle u_blur_kernel_4_7;
	};

	struct BlurKernel
	{
		float m_horizontal[7];
		float m_vertical[5];
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockBlur : public GfxBlock
	{
	public:
		BlockBlur(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;
		
		void blur(Render& render);

		void gaussian_pass(Render& render, uvec4& rect, uint8_t lod, bool horizontal, const BlurKernel& kernel);

		BlockFilter& m_filter;

		EffectBlurUniform u_uniform;
		Program& m_program;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	enum ShaderOptionDofBlur : unsigned int
	{
		DOF_FIRST_PASS,
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT DofBlur
	{
		attr_ bool m_enabled = false;
		attr_ float m_far_distance = 10.f;
		attr_ float m_far_transition = 5.f;
		attr_ float m_far_radius = 5.f;
		attr_ float m_near_distance = 2.f;
		attr_ float m_near_transition = 1.f;
		attr_ float m_near_radius = 5.f;
		attr_ float m_max_coc_radius = 8.f;
	};

	struct DofBlurUniform
	{
		void createUniforms()
		{
			u_dof_near_params = bgfx::createUniform("u_dof_near_params", bgfx::UniformType::Vec4);
			u_dof_far_params = bgfx::createUniform("u_dof_far_params", bgfx::UniformType::Vec4);
			u_dof_params = bgfx::createUniform("u_dof_params", bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle u_dof_near_params;
		bgfx::UniformHandle u_dof_far_params;
		bgfx::UniformHandle u_dof_params;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockDofBlur : public GfxBlock
	{
	public:
		BlockDofBlur(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;
		virtual void submit_pass(Render& render) final;

		void render(Render& render, const DofBlur& blur);

		void submit_blur_pass(Render& render, const DofBlur& blur, bool first, uint64_t bgfx_state = 0);

		BlockFilter& m_filter;

		DofBlurUniform u_uniform;

		Program& m_program;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	enum ShaderOptionGlow : unsigned int
	{
		GLOW_FILTER_BICUBIC,
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT Glow
	{
		attr_ bool m_enabled = false;
		attr_ vec4 m_levels_1_4 = { 1.f, 0.f, 0.f, 0.f };
		attr_ vec4 m_levels_5_8 = Zero4;
		attr_ float m_intensity = 0.4f;
		attr_ float m_bloom = 0.0f;
		attr_ float m_bleed_threshold = 1.0f;
		attr_ float m_bleed_scale = 2.0f;
		attr_ bool m_bicubic_filter = false;
	};

	struct GlowUniform
	{
		void createUniforms()
		{
			u_glow_params_0 = bgfx::createUniform("u_glow_params_0", bgfx::UniformType::Vec4);
			u_glow_params_1 = bgfx::createUniform("u_glow_params_1", bgfx::UniformType::Vec4);
			u_glow_levels_1_4 = bgfx::createUniform("u_glow_levels_1_4", bgfx::UniformType::Vec4);
			u_glow_levels_5_8 = bgfx::createUniform("u_glow_levels_5_8", bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle u_glow_params_0;
		bgfx::UniformHandle u_glow_params_1;
		bgfx::UniformHandle u_glow_levels_1_4;
		bgfx::UniformHandle u_glow_levels_5_8;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGlow : public GfxBlock
	{
	public:
		BlockGlow(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy, BlockBlur& blur);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;
		virtual void submit_pass(Render& render) final;

		void glow_bleed(Render& render, Glow& glow);
		void glow_blur(Render& render, Glow& glow);
		void glow_merge(Render& render, Glow& glow);

		void render(Render& render, Glow& glow);

		BlockFilter& m_filter;
		BlockCopy& m_copy;
		BlockBlur& m_blur;

		GlowUniform u_uniform;

		Program& m_bleed_program;
		Program& m_merge_program;
	};

}


#ifndef MUD_MODULES
#endif

namespace mud
{
	enum TonemapShaderOption : unsigned int
	{
		ADJUST_BCS,
		COLOR_CORRECTION,
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
		ACES
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT BCS
	{
		attr_ bool m_enabled = false;
		attr_ float m_brightness = 1.0f;
		attr_ float m_contrast = 1.0f;
		attr_ float m_saturation = 1.0f;
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT Tonemap
	{
		attr_ TonemapMode m_mode = TonemapMode::Linear;
		attr_ bool m_enabled = false;
		attr_ float m_exposure = 1.0f;
		attr_ float m_white_point = 1.0f;

		bgfx::TextureHandle m_color_correction = BGFX_INVALID_HANDLE;
	};

	struct TonemapUniform
	{
		void createUniforms()
		{
			u_bcs = bgfx::createUniform("u_tonemap_bcs", bgfx::UniformType::Vec4);
			u_exposure_params = bgfx::createUniform("u_exposure_params", bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle u_bcs;
		bgfx::UniformHandle u_exposure_params;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockTonemap : public GfxBlock
	{
	public:
		BlockTonemap(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;
		virtual void submit_pass(Render& render) final;

		void render(Render& render, Tonemap& tonemap, BCS& bcs);

		BlockFilter& m_filter;
		BlockCopy& m_copy;

		TonemapUniform u_uniform;
		Program& m_program;
	};
}



namespace mud
{
	template <> struct TypedBuffer<Tonemap> { static uint32_t index() { return 0; } };
	template <> struct TypedBuffer<BCS> { static uint32_t index() { return 1; } };
	template <> struct TypedBuffer<Glow> { static uint32_t index() { return 2; } };
	template <> struct TypedBuffer<DofBlur> { static uint32_t index() { return 3; } };
}

