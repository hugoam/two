#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gfx-pbr/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// BCS
	mud::Type* DECL mud_BCS__type() {
		return &mud::type<mud::BCS>();
	}
	mud::BCS* DECL mud_BCS__construct_0() {
		return new mud::BCS();
	}
	bool DECL mud_BCS__get_enabled(mud::BCS* self) {
		return self->m_enabled;
	}
	void DECL mud_BCS__set_enabled(mud::BCS* self, bool value) {
		self->m_enabled = value;
	}
	float DECL mud_BCS__get_brightness(mud::BCS* self) {
		return self->m_brightness;
	}
	void DECL mud_BCS__set_brightness(mud::BCS* self, float value) {
		self->m_brightness = value;
	}
	float DECL mud_BCS__get_contrast(mud::BCS* self) {
		return self->m_contrast;
	}
	void DECL mud_BCS__set_contrast(mud::BCS* self, float value) {
		self->m_contrast = value;
	}
	float DECL mud_BCS__get_saturation(mud::BCS* self) {
		return self->m_saturation;
	}
	void DECL mud_BCS__set_saturation(mud::BCS* self, float value) {
		self->m_saturation = value;
	}
	void DECL mud_BCS__destroy(mud::BCS* self) {
		delete self;
	}
	// CSMShadow
	mud::Type* DECL mud_CSMShadow__type() {
		return &mud::type<mud::CSMShadow>();
	}
	mud::CSMShadow* DECL mud_CSMShadow__construct_0() {
		return new mud::CSMShadow();
	}
	void DECL mud_CSMShadow__destroy(mud::CSMShadow* self) {
		delete self;
	}
	// CubeCamera
	mud::Type* DECL mud_CubeCamera__type() {
		return &mud::type<mud::CubeCamera>();
	}
	mud::CubeCamera* DECL mud_CubeCamera__construct_0() {
		return new mud::CubeCamera();
	}
	mud::CubeCamera* DECL mud_CubeCamera__construct_4(mud::Scene* scene, float near, float far, uint32_t size) {
		return new mud::CubeCamera(*scene, near, far, size);
	}
	mud::Render* DECL mud_CubeCamera_render_3(mud::CubeCamera* self, mud::GfxSystem* gfx, mud::Render* render, mud::SignedAxis axis) {
		static mud::Render temp;
		return (temp = self->render(*gfx, *render, axis), &temp);
	}
	mud::CubeTarget* DECL mud_CubeCamera__get_cubemap(mud::CubeCamera* self) {
		return &self->m_cubemap;
	}
	mud::uvec2* DECL mud_CubeCamera__get_size(mud::CubeCamera* self) {
		return &self->m_size;
	}
	void DECL mud_CubeCamera__set_size(mud::CubeCamera* self, mud::uvec2* value) {
		self->m_size = *value;
	}
	void DECL mud_CubeCamera__destroy(mud::CubeCamera* self) {
		delete self;
	}
	// CubeTarget
	mud::Type* DECL mud_CubeTarget__type() {
		return &mud::type<mud::CubeTarget>();
	}
	mud::CubeTarget* DECL mud_CubeTarget__construct_0() {
		return new mud::CubeTarget();
	}
	void DECL mud_CubeTarget_create_1(mud::CubeTarget* self, uint32_t size) {
		self->create(size);
	}
	mud::FrameBuffer* DECL mud_CubeTarget_side_1(mud::CubeTarget* self, size_t i) {
		return &self->side(i);
	}
	mud::Texture* DECL mud_CubeTarget__get_cubemap(mud::CubeTarget* self) {
		return &self->m_cubemap;
	}
	mud::Texture* DECL mud_CubeTarget__get_depth(mud::CubeTarget* self) {
		return &self->m_depth;
	}
	uint32_t DECL mud_CubeTarget__get_size(mud::CubeTarget* self) {
		return self->m_size;
	}
	void DECL mud_CubeTarget__set_size(mud::CubeTarget* self, uint32_t value) {
		self->m_size = value;
	}
	void DECL mud_CubeTarget__destroy(mud::CubeTarget* self) {
		delete self;
	}
	// DofBlur
	mud::Type* DECL mud_DofBlur__type() {
		return &mud::type<mud::DofBlur>();
	}
	mud::DofBlur* DECL mud_DofBlur__construct_0() {
		return new mud::DofBlur();
	}
	bool DECL mud_DofBlur__get_enabled(mud::DofBlur* self) {
		return self->m_enabled;
	}
	void DECL mud_DofBlur__set_enabled(mud::DofBlur* self, bool value) {
		self->m_enabled = value;
	}
	mud::DofParams* DECL mud_DofBlur__get_far(mud::DofBlur* self) {
		return &self->m_far;
	}
	void DECL mud_DofBlur__set_far(mud::DofBlur* self, mud::DofParams* value) {
		self->m_far = *value;
	}
	mud::DofParams* DECL mud_DofBlur__get_near(mud::DofBlur* self) {
		return &self->m_near;
	}
	void DECL mud_DofBlur__set_near(mud::DofBlur* self, mud::DofParams* value) {
		self->m_near = *value;
	}
	float DECL mud_DofBlur__get_max_coc_radius(mud::DofBlur* self) {
		return self->m_max_coc_radius;
	}
	void DECL mud_DofBlur__set_max_coc_radius(mud::DofBlur* self, float value) {
		self->m_max_coc_radius = value;
	}
	void DECL mud_DofBlur__destroy(mud::DofBlur* self) {
		delete self;
	}
	// DofParams
	mud::Type* DECL mud_DofParams__type() {
		return &mud::type<mud::DofParams>();
	}
	mud::DofParams* DECL mud_DofParams__construct_0() {
		return new mud::DofParams();
	}
	float DECL mud_DofParams__get_distance(mud::DofParams* self) {
		return self->m_distance;
	}
	void DECL mud_DofParams__set_distance(mud::DofParams* self, float value) {
		self->m_distance = value;
	}
	float DECL mud_DofParams__get_transition(mud::DofParams* self) {
		return self->m_transition;
	}
	void DECL mud_DofParams__set_transition(mud::DofParams* self, float value) {
		self->m_transition = value;
	}
	float DECL mud_DofParams__get_radius(mud::DofParams* self) {
		return self->m_radius;
	}
	void DECL mud_DofParams__set_radius(mud::DofParams* self, float value) {
		self->m_radius = value;
	}
	void DECL mud_DofParams__destroy(mud::DofParams* self) {
		delete self;
	}
	// GIProbe
	mud::Type* DECL mud_GIProbe__type() {
		return &mud::type<mud::GIProbe>();
	}
	void DECL mud_GIProbe__destroy(mud::GIProbe* self) {
		delete self;
	}
	// Glow
	mud::Type* DECL mud_Glow__type() {
		return &mud::type<mud::Glow>();
	}
	mud::Glow* DECL mud_Glow__construct_0() {
		return new mud::Glow();
	}
	bool DECL mud_Glow__get_enabled(mud::Glow* self) {
		return self->m_enabled;
	}
	void DECL mud_Glow__set_enabled(mud::Glow* self, bool value) {
		self->m_enabled = value;
	}
	mud::vec4* DECL mud_Glow__get_levels_1_4(mud::Glow* self) {
		return &self->m_levels_1_4;
	}
	void DECL mud_Glow__set_levels_1_4(mud::Glow* self, mud::vec4* value) {
		self->m_levels_1_4 = *value;
	}
	mud::vec4* DECL mud_Glow__get_levels_5_8(mud::Glow* self) {
		return &self->m_levels_5_8;
	}
	void DECL mud_Glow__set_levels_5_8(mud::Glow* self, mud::vec4* value) {
		self->m_levels_5_8 = *value;
	}
	float DECL mud_Glow__get_intensity(mud::Glow* self) {
		return self->m_intensity;
	}
	void DECL mud_Glow__set_intensity(mud::Glow* self, float value) {
		self->m_intensity = value;
	}
	float DECL mud_Glow__get_bloom(mud::Glow* self) {
		return self->m_bloom;
	}
	void DECL mud_Glow__set_bloom(mud::Glow* self, float value) {
		self->m_bloom = value;
	}
	float DECL mud_Glow__get_bleed_threshold(mud::Glow* self) {
		return self->m_bleed_threshold;
	}
	void DECL mud_Glow__set_bleed_threshold(mud::Glow* self, float value) {
		self->m_bleed_threshold = value;
	}
	float DECL mud_Glow__get_bleed_scale(mud::Glow* self) {
		return self->m_bleed_scale;
	}
	void DECL mud_Glow__set_bleed_scale(mud::Glow* self, float value) {
		self->m_bleed_scale = value;
	}
	bool DECL mud_Glow__get_bicubic_filter(mud::Glow* self) {
		return self->m_bicubic_filter;
	}
	void DECL mud_Glow__set_bicubic_filter(mud::Glow* self, bool value) {
		self->m_bicubic_filter = value;
	}
	void DECL mud_Glow__destroy(mud::Glow* self) {
		delete self;
	}
	// LightShadow
	mud::Type* DECL mud_LightShadow__type() {
		return &mud::type<mud::LightShadow>();
	}
	mud::LightShadow* DECL mud_LightShadow__construct_0() {
		return new mud::LightShadow();
	}
	void DECL mud_LightShadow__destroy(mud::LightShadow* self) {
		delete self;
	}
	// Lightmap
	mud::Type* DECL mud_Lightmap__type() {
		return &mud::type<mud::Lightmap>();
	}
	void DECL mud_Lightmap__destroy(mud::Lightmap* self) {
		delete self;
	}
	// LightmapAtlas
	mud::Type* DECL mud_LightmapAtlas__type() {
		return &mud::type<mud::LightmapAtlas>();
	}
	void DECL mud_LightmapAtlas__destroy(mud::LightmapAtlas* self) {
		delete self;
	}
	// LightmapItem
	mud::Type* DECL mud_LightmapItem__type() {
		return &mud::type<mud::LightmapItem>();
	}
	void DECL mud_LightmapItem__destroy(mud::LightmapItem* self) {
		delete self;
	}
	// ReflectionProbe
	mud::Type* DECL mud_ReflectionProbe__type() {
		return &mud::type<mud::ReflectionProbe>();
	}
	mud::Node3* DECL mud_ReflectionProbe__get_node(mud::ReflectionProbe* self) {
		return &self->m_node;
	}
	bool DECL mud_ReflectionProbe__get_visible(mud::ReflectionProbe* self) {
		return self->m_visible;
	}
	void DECL mud_ReflectionProbe__set_visible(mud::ReflectionProbe* self, bool value) {
		self->m_visible = value;
	}
	float DECL mud_ReflectionProbe__get_intensity(mud::ReflectionProbe* self) {
		return self->m_intensity;
	}
	void DECL mud_ReflectionProbe__set_intensity(mud::ReflectionProbe* self, float value) {
		self->m_intensity = value;
	}
	mud::vec3* DECL mud_ReflectionProbe__get_extents(mud::ReflectionProbe* self) {
		return &self->m_extents;
	}
	void DECL mud_ReflectionProbe__set_extents(mud::ReflectionProbe* self, mud::vec3* value) {
		self->m_extents = *value;
	}
	bool DECL mud_ReflectionProbe__get_shadows(mud::ReflectionProbe* self) {
		return self->m_shadows;
	}
	void DECL mud_ReflectionProbe__set_shadows(mud::ReflectionProbe* self, bool value) {
		self->m_shadows = value;
	}
	bool DECL mud_ReflectionProbe__get_dirty(mud::ReflectionProbe* self) {
		return self->m_dirty;
	}
	void DECL mud_ReflectionProbe__set_dirty(mud::ReflectionProbe* self, bool value) {
		self->m_dirty = value;
	}
	void DECL mud_ReflectionProbe__destroy(mud::ReflectionProbe* self) {
		delete self;
	}
	// Tonemap
	mud::Type* DECL mud_Tonemap__type() {
		return &mud::type<mud::Tonemap>();
	}
	mud::Tonemap* DECL mud_Tonemap__construct_0() {
		return new mud::Tonemap();
	}
	mud::TonemapMode DECL mud_Tonemap__get_mode(mud::Tonemap* self) {
		return self->m_mode;
	}
	void DECL mud_Tonemap__set_mode(mud::Tonemap* self, mud::TonemapMode value) {
		self->m_mode = value;
	}
	bool DECL mud_Tonemap__get_enabled(mud::Tonemap* self) {
		return self->m_enabled;
	}
	void DECL mud_Tonemap__set_enabled(mud::Tonemap* self, bool value) {
		self->m_enabled = value;
	}
	float DECL mud_Tonemap__get_exposure(mud::Tonemap* self) {
		return self->m_exposure;
	}
	void DECL mud_Tonemap__set_exposure(mud::Tonemap* self, float value) {
		self->m_exposure = value;
	}
	float DECL mud_Tonemap__get_white_point(mud::Tonemap* self) {
		return self->m_white_point;
	}
	void DECL mud_Tonemap__set_white_point(mud::Tonemap* self, float value) {
		self->m_white_point = value;
	}
	void DECL mud_Tonemap__destroy(mud::Tonemap* self) {
		delete self;
	}
	// BlockBlur
	mud::Type* DECL mud_BlockBlur__type() {
		return &mud::type<mud::BlockBlur>();
	}
	void DECL mud_BlockBlur__destroy(mud::BlockBlur* self) {
		delete self;
	}
	// BlockDofBlur
	mud::Type* DECL mud_BlockDofBlur__type() {
		return &mud::type<mud::BlockDofBlur>();
	}
	void DECL mud_BlockDofBlur__destroy(mud::BlockDofBlur* self) {
		delete self;
	}
	// BlockGIBake
	mud::Type* DECL mud_BlockGIBake__type() {
		return &mud::type<mud::BlockGIBake>();
	}
	void DECL mud_BlockGIBake__destroy(mud::BlockGIBake* self) {
		delete self;
	}
	// BlockGITrace
	mud::Type* DECL mud_BlockGITrace__type() {
		return &mud::type<mud::BlockGITrace>();
	}
	void DECL mud_BlockGITrace__destroy(mud::BlockGITrace* self) {
		delete self;
	}
	// BlockGeometry
	mud::Type* DECL mud_BlockGeometry__type() {
		return &mud::type<mud::BlockGeometry>();
	}
	void DECL mud_BlockGeometry__destroy(mud::BlockGeometry* self) {
		delete self;
	}
	// BlockGlow
	mud::Type* DECL mud_BlockGlow__type() {
		return &mud::type<mud::BlockGlow>();
	}
	void DECL mud_BlockGlow__destroy(mud::BlockGlow* self) {
		delete self;
	}
	// BlockLight
	mud::Type* DECL mud_BlockLight__type() {
		return &mud::type<mud::BlockLight>();
	}
	void DECL mud_BlockLight__destroy(mud::BlockLight* self) {
		delete self;
	}
	// BlockLightmap
	mud::Type* DECL mud_BlockLightmap__type() {
		return &mud::type<mud::BlockLightmap>();
	}
	void DECL mud_BlockLightmap__destroy(mud::BlockLightmap* self) {
		delete self;
	}
	// BlockRadiance
	mud::Type* DECL mud_BlockRadiance__type() {
		return &mud::type<mud::BlockRadiance>();
	}
	void DECL mud_BlockRadiance__destroy(mud::BlockRadiance* self) {
		delete self;
	}
	// BlockReflection
	mud::Type* DECL mud_BlockReflection__type() {
		return &mud::type<mud::BlockReflection>();
	}
	void DECL mud_BlockReflection__destroy(mud::BlockReflection* self) {
		delete self;
	}
	// BlockShadow
	mud::Type* DECL mud_BlockShadow__type() {
		return &mud::type<mud::BlockShadow>();
	}
	void DECL mud_BlockShadow__destroy(mud::BlockShadow* self) {
		delete self;
	}
	// BlockTonemap
	mud::Type* DECL mud_BlockTonemap__type() {
		return &mud::type<mud::BlockTonemap>();
	}
	void DECL mud_BlockTonemap__destroy(mud::BlockTonemap* self) {
		delete self;
	}
	void DECL mud_begin_pbr_render_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::begin_pbr_render(*gfx, *render);
	}
	void DECL mud_pass_gi_probes_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_gi_probes(*gfx, *render);
	}
	void DECL mud_pass_shadowmaps_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_shadowmaps(*gfx, *render);
	}
	void DECL mud_pass_shadow_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_shadow(*gfx, *render);
	}
	void DECL mud_pass_opaque_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_opaque(*gfx, *render);
	}
	void DECL mud_pass_alpha_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_alpha(*gfx, *render);
	}
	void DECL mud_pass_geometry_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_geometry(*gfx, *render);
	}
	void DECL mud_pass_lights_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_lights(*gfx, *render);
	}
	void DECL mud_pass_voxel_gi_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_voxel_gi(*gfx, *render);
	}
	void DECL mud_pass_lightmap_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::pass_lightmap(*gfx, *render);
	}
	void DECL mud_render_pbr_forward_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::render_pbr_forward(*gfx, *render);
	}
	void DECL mud_render_pbr_deferred_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::render_pbr_deferred(*gfx, *render);
	}
	void DECL mud_render_shadow_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::render_shadow(*gfx, *render);
	}
	void DECL mud_render_voxel_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::render_voxel(*gfx, *render);
	}
	void DECL mud_render_lightmap_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::render_lightmap(*gfx, *render);
	}
	void DECL mud_render_reflection_2(mud::GfxSystem* gfx, mud::Render* render) {
		mud::render_reflection(*gfx, *render);
	}
	void DECL mud_pipeline_pbr_2(mud::GfxSystem* gfx, mud::Renderer* pipeline) {
		mud::pipeline_pbr(*gfx, *pipeline);
	}
	void DECL mud_pipeline_pbr_3(mud::GfxSystem* gfx, mud::Renderer* pipeline, bool deferred) {
		mud::pipeline_pbr(*gfx, *pipeline, deferred);
	}
	void DECL mud_gfx_setup_pipeline_pbr_1(mud::GfxSystem* gfx) {
		mud::gfx::setup_pipeline_pbr(*gfx);
	}
	mud::GIProbe* DECL mud_gfx_gi_probe_3(mud::Gnode* parent, uint16_t subdiv, const mud::vec3* extents) {
		return &mud::gfx::gi_probe(*parent, subdiv, *extents);
	}
	mud::LightmapAtlas* DECL mud_gfx_lightmap_2(mud::Gnode* parent, uint32_t resolution) {
		return &mud::gfx::lightmap(*parent, resolution);
	}
	mud::LightmapAtlas* DECL mud_gfx_lightmap_3(mud::Gnode* parent, uint32_t resolution, float density) {
		return &mud::gfx::lightmap(*parent, resolution, density);
	}
	mud::LightmapAtlas* DECL mud_gfx_lightmap_4(mud::Gnode* parent, uint32_t resolution, float density, const char* save_path) {
		return &mud::gfx::lightmap(*parent, resolution, density, save_path);
	}
	// TonemapMode
	mud::TonemapMode DECL mud_TonemapMode_None() {
		return mud::TonemapMode::None;
	}
	mud::TonemapMode DECL mud_TonemapMode_Linear() {
		return mud::TonemapMode::Linear;
	}
	mud::TonemapMode DECL mud_TonemapMode_Reinhardt() {
		return mud::TonemapMode::Reinhardt;
	}
	mud::TonemapMode DECL mud_TonemapMode_Filmic() {
		return mud::TonemapMode::Filmic;
	}
	mud::TonemapMode DECL mud_TonemapMode_ACES() {
		return mud::TonemapMode::ACES;
	}
	mud::TonemapMode DECL mud_TonemapMode_Cineon() {
		return mud::TonemapMode::Cineon;
	}
	mud::TonemapMode DECL mud_TonemapMode_Uncharted2() {
		return mud::TonemapMode::Uncharted2;
	}
	
}


