#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gfx-pbr/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// BlockLight
	two::Type* DECL two_BlockLight__type() {
		return &two::type<two::BlockLight>();
	}
	void DECL two_BlockLight__destroy(two::BlockLight* self) {
		delete self;
	}
	// LightmapItem
	two::Type* DECL two_LightmapItem__type() {
		return &two::type<two::LightmapItem>();
	}
	void DECL two_LightmapItem__destroy(two::LightmapItem* self) {
		delete self;
	}
	// Lightmap
	two::Type* DECL two_Lightmap__type() {
		return &two::type<two::Lightmap>();
	}
	void DECL two_Lightmap__destroy(two::Lightmap* self) {
		delete self;
	}
	// LightmapAtlas
	two::Type* DECL two_LightmapAtlas__type() {
		return &two::type<two::LightmapAtlas>();
	}
	void DECL two_LightmapAtlas__destroy(two::LightmapAtlas* self) {
		delete self;
	}
	// BlockLightmap
	two::Type* DECL two_BlockLightmap__type() {
		return &two::type<two::BlockLightmap>();
	}
	void DECL two_BlockLightmap__destroy(two::BlockLightmap* self) {
		delete self;
	}
	// PBRShot
	two::Type* DECL two_PBRShot__type() {
		return &two::type<two::PBRShot>();
	}
	void DECL two_PBRShot__destroy(two::PBRShot* self) {
		delete self;
	}
	// BlockGeometry
	two::Type* DECL two_BlockGeometry__type() {
		return &two::type<two::BlockGeometry>();
	}
	void DECL two_BlockGeometry__destroy(two::BlockGeometry* self) {
		delete self;
	}
	// BlockRadiance
	two::Type* DECL two_BlockRadiance__type() {
		return &two::type<two::BlockRadiance>();
	}
	void DECL two_BlockRadiance__destroy(two::BlockRadiance* self) {
		delete self;
	}
	// CubeTarget
	two::Type* DECL two_CubeTarget__type() {
		return &two::type<two::CubeTarget>();
	}
	two::CubeTarget* DECL two_CubeTarget__construct_0() {
		return new two::CubeTarget();
	}
	void DECL two_CubeTarget_create_1(two::CubeTarget* self, uint32_t size) {
		self->create(size);
	}
	two::FrameBuffer* DECL two_CubeTarget_side_1(two::CubeTarget* self, size_t i) {
		return &self->side(i);
	}
	two::Texture* DECL two_CubeTarget__get_cubemap(two::CubeTarget* self) {
		return &self->m_cubemap;
	}
	two::Texture* DECL two_CubeTarget__get_depth(two::CubeTarget* self) {
		return &self->m_depth;
	}
	uint32_t DECL two_CubeTarget__get_size(two::CubeTarget* self) {
		return self->m_size;
	}
	void DECL two_CubeTarget__set_size(two::CubeTarget* self, uint32_t value) {
		self->m_size = value;
	}
	void DECL two_CubeTarget__destroy(two::CubeTarget* self) {
		delete self;
	}
	// CubeCamera
	two::Type* DECL two_CubeCamera__type() {
		return &two::type<two::CubeCamera>();
	}
	two::CubeCamera* DECL two_CubeCamera__construct_0() {
		return new two::CubeCamera();
	}
	two::CubeCamera* DECL two_CubeCamera__construct_4(two::Scene* scene, float near, float far, uint32_t size) {
		return new two::CubeCamera(*scene, near, far, size);
	}
	two::Render* DECL two_CubeCamera_render_3(two::CubeCamera* self, two::GfxSystem* gfx, two::Render* render, two::SignedAxis axis) {
		static two::Render temp;
		return (temp = self->render(*gfx, *render, axis), &temp);
	}
	two::CubeTarget* DECL two_CubeCamera__get_cubemap(two::CubeCamera* self) {
		return &self->m_cubemap;
	}
	two::uvec2* DECL two_CubeCamera__get_size(two::CubeCamera* self) {
		return &self->m_size;
	}
	void DECL two_CubeCamera__set_size(two::CubeCamera* self, two::uvec2* value) {
		self->m_size = *value;
	}
	void DECL two_CubeCamera__destroy(two::CubeCamera* self) {
		delete self;
	}
	// ReflectionProbe
	two::Type* DECL two_ReflectionProbe__type() {
		return &two::type<two::ReflectionProbe>();
	}
	two::Node3* DECL two_ReflectionProbe__get_node(two::ReflectionProbe* self) {
		return &self->m_node;
	}
	bool DECL two_ReflectionProbe__get_visible(two::ReflectionProbe* self) {
		return self->m_visible;
	}
	void DECL two_ReflectionProbe__set_visible(two::ReflectionProbe* self, bool value) {
		self->m_visible = value;
	}
	float DECL two_ReflectionProbe__get_intensity(two::ReflectionProbe* self) {
		return self->m_intensity;
	}
	void DECL two_ReflectionProbe__set_intensity(two::ReflectionProbe* self, float value) {
		self->m_intensity = value;
	}
	two::vec3* DECL two_ReflectionProbe__get_extents(two::ReflectionProbe* self) {
		return &self->m_extents;
	}
	void DECL two_ReflectionProbe__set_extents(two::ReflectionProbe* self, two::vec3* value) {
		self->m_extents = *value;
	}
	bool DECL two_ReflectionProbe__get_shadows(two::ReflectionProbe* self) {
		return self->m_shadows;
	}
	void DECL two_ReflectionProbe__set_shadows(two::ReflectionProbe* self, bool value) {
		self->m_shadows = value;
	}
	bool DECL two_ReflectionProbe__get_dirty(two::ReflectionProbe* self) {
		return self->m_dirty;
	}
	void DECL two_ReflectionProbe__set_dirty(two::ReflectionProbe* self, bool value) {
		self->m_dirty = value;
	}
	void DECL two_ReflectionProbe__destroy(two::ReflectionProbe* self) {
		delete self;
	}
	// BlockReflection
	two::Type* DECL two_BlockReflection__type() {
		return &two::type<two::BlockReflection>();
	}
	void DECL two_BlockReflection__destroy(two::BlockReflection* self) {
		delete self;
	}
	// LightShadow
	two::Type* DECL two_LightShadow__type() {
		return &two::type<two::LightShadow>();
	}
	two::LightShadow* DECL two_LightShadow__construct_0() {
		return new two::LightShadow();
	}
	void DECL two_LightShadow__destroy(two::LightShadow* self) {
		delete self;
	}
	// CSMSlice
	two::Type* DECL two_CSMSlice__type() {
		return &two::type<two::CSMSlice>();
	}
	two::CSMSlice* DECL two_CSMSlice__construct_0() {
		return new two::CSMSlice();
	}
	void DECL two_CSMSlice__destroy(two::CSMSlice* self) {
		delete self;
	}
	// CSMShadow
	two::Type* DECL two_CSMShadow__type() {
		return &two::type<two::CSMShadow>();
	}
	two::CSMShadow* DECL two_CSMShadow__construct_0() {
		return new two::CSMShadow();
	}
	void DECL two_CSMShadow__destroy(two::CSMShadow* self) {
		delete self;
	}
	// BlockShadow
	two::Type* DECL two_BlockShadow__type() {
		return &two::type<two::BlockShadow>();
	}
	void DECL two_BlockShadow__destroy(two::BlockShadow* self) {
		delete self;
	}
	// GIProbe
	two::Type* DECL two_GIProbe__type() {
		return &two::type<two::GIProbe>();
	}
	void DECL two_GIProbe__destroy(two::GIProbe* self) {
		delete self;
	}
	// BlockGITrace
	two::Type* DECL two_BlockGITrace__type() {
		return &two::type<two::BlockGITrace>();
	}
	void DECL two_BlockGITrace__destroy(two::BlockGITrace* self) {
		delete self;
	}
	// BlockGIBake
	two::Type* DECL two_BlockGIBake__type() {
		return &two::type<two::BlockGIBake>();
	}
	void DECL two_BlockGIBake__destroy(two::BlockGIBake* self) {
		delete self;
	}
	// BlockBlur
	two::Type* DECL two_BlockBlur__type() {
		return &two::type<two::BlockBlur>();
	}
	void DECL two_BlockBlur__destroy(two::BlockBlur* self) {
		delete self;
	}
	// DofParams
	two::Type* DECL two_DofParams__type() {
		return &two::type<two::DofParams>();
	}
	two::DofParams* DECL two_DofParams__construct_0() {
		return new two::DofParams();
	}
	float DECL two_DofParams__get_distance(two::DofParams* self) {
		return self->m_distance;
	}
	void DECL two_DofParams__set_distance(two::DofParams* self, float value) {
		self->m_distance = value;
	}
	float DECL two_DofParams__get_transition(two::DofParams* self) {
		return self->m_transition;
	}
	void DECL two_DofParams__set_transition(two::DofParams* self, float value) {
		self->m_transition = value;
	}
	float DECL two_DofParams__get_radius(two::DofParams* self) {
		return self->m_radius;
	}
	void DECL two_DofParams__set_radius(two::DofParams* self, float value) {
		self->m_radius = value;
	}
	void DECL two_DofParams__destroy(two::DofParams* self) {
		delete self;
	}
	// DofBlur
	two::Type* DECL two_DofBlur__type() {
		return &two::type<two::DofBlur>();
	}
	two::DofBlur* DECL two_DofBlur__construct_0() {
		return new two::DofBlur();
	}
	bool DECL two_DofBlur__get_enabled(two::DofBlur* self) {
		return self->m_enabled;
	}
	void DECL two_DofBlur__set_enabled(two::DofBlur* self, bool value) {
		self->m_enabled = value;
	}
	two::DofParams* DECL two_DofBlur__get_far(two::DofBlur* self) {
		return &self->m_far;
	}
	void DECL two_DofBlur__set_far(two::DofBlur* self, two::DofParams* value) {
		self->m_far = *value;
	}
	two::DofParams* DECL two_DofBlur__get_near(two::DofBlur* self) {
		return &self->m_near;
	}
	void DECL two_DofBlur__set_near(two::DofBlur* self, two::DofParams* value) {
		self->m_near = *value;
	}
	float DECL two_DofBlur__get_max_coc_radius(two::DofBlur* self) {
		return self->m_max_coc_radius;
	}
	void DECL two_DofBlur__set_max_coc_radius(two::DofBlur* self, float value) {
		self->m_max_coc_radius = value;
	}
	void DECL two_DofBlur__destroy(two::DofBlur* self) {
		delete self;
	}
	// BlockDofBlur
	two::Type* DECL two_BlockDofBlur__type() {
		return &two::type<two::BlockDofBlur>();
	}
	void DECL two_BlockDofBlur__destroy(two::BlockDofBlur* self) {
		delete self;
	}
	// Glow
	two::Type* DECL two_Glow__type() {
		return &two::type<two::Glow>();
	}
	two::Glow* DECL two_Glow__construct_0() {
		return new two::Glow();
	}
	bool DECL two_Glow__get_enabled(two::Glow* self) {
		return self->m_enabled;
	}
	void DECL two_Glow__set_enabled(two::Glow* self, bool value) {
		self->m_enabled = value;
	}
	two::vec4* DECL two_Glow__get_levels_1_4(two::Glow* self) {
		return &self->m_levels_1_4;
	}
	void DECL two_Glow__set_levels_1_4(two::Glow* self, two::vec4* value) {
		self->m_levels_1_4 = *value;
	}
	two::vec4* DECL two_Glow__get_levels_5_8(two::Glow* self) {
		return &self->m_levels_5_8;
	}
	void DECL two_Glow__set_levels_5_8(two::Glow* self, two::vec4* value) {
		self->m_levels_5_8 = *value;
	}
	float DECL two_Glow__get_intensity(two::Glow* self) {
		return self->m_intensity;
	}
	void DECL two_Glow__set_intensity(two::Glow* self, float value) {
		self->m_intensity = value;
	}
	float DECL two_Glow__get_bloom(two::Glow* self) {
		return self->m_bloom;
	}
	void DECL two_Glow__set_bloom(two::Glow* self, float value) {
		self->m_bloom = value;
	}
	float DECL two_Glow__get_bleed_threshold(two::Glow* self) {
		return self->m_bleed_threshold;
	}
	void DECL two_Glow__set_bleed_threshold(two::Glow* self, float value) {
		self->m_bleed_threshold = value;
	}
	float DECL two_Glow__get_bleed_scale(two::Glow* self) {
		return self->m_bleed_scale;
	}
	void DECL two_Glow__set_bleed_scale(two::Glow* self, float value) {
		self->m_bleed_scale = value;
	}
	bool DECL two_Glow__get_bicubic_filter(two::Glow* self) {
		return self->m_bicubic_filter;
	}
	void DECL two_Glow__set_bicubic_filter(two::Glow* self, bool value) {
		self->m_bicubic_filter = value;
	}
	void DECL two_Glow__destroy(two::Glow* self) {
		delete self;
	}
	// BlockGlow
	two::Type* DECL two_BlockGlow__type() {
		return &two::type<two::BlockGlow>();
	}
	void DECL two_BlockGlow__destroy(two::BlockGlow* self) {
		delete self;
	}
	// BCS
	two::Type* DECL two_BCS__type() {
		return &two::type<two::BCS>();
	}
	two::BCS* DECL two_BCS__construct_0() {
		return new two::BCS();
	}
	bool DECL two_BCS__get_enabled(two::BCS* self) {
		return self->m_enabled;
	}
	void DECL two_BCS__set_enabled(two::BCS* self, bool value) {
		self->m_enabled = value;
	}
	float DECL two_BCS__get_brightness(two::BCS* self) {
		return self->m_brightness;
	}
	void DECL two_BCS__set_brightness(two::BCS* self, float value) {
		self->m_brightness = value;
	}
	float DECL two_BCS__get_contrast(two::BCS* self) {
		return self->m_contrast;
	}
	void DECL two_BCS__set_contrast(two::BCS* self, float value) {
		self->m_contrast = value;
	}
	float DECL two_BCS__get_saturation(two::BCS* self) {
		return self->m_saturation;
	}
	void DECL two_BCS__set_saturation(two::BCS* self, float value) {
		self->m_saturation = value;
	}
	void DECL two_BCS__destroy(two::BCS* self) {
		delete self;
	}
	// Tonemap
	two::Type* DECL two_Tonemap__type() {
		return &two::type<two::Tonemap>();
	}
	two::Tonemap* DECL two_Tonemap__construct_0() {
		return new two::Tonemap();
	}
	two::TonemapMode DECL two_Tonemap__get_mode(two::Tonemap* self) {
		return self->m_mode;
	}
	void DECL two_Tonemap__set_mode(two::Tonemap* self, two::TonemapMode value) {
		self->m_mode = value;
	}
	bool DECL two_Tonemap__get_enabled(two::Tonemap* self) {
		return self->m_enabled;
	}
	void DECL two_Tonemap__set_enabled(two::Tonemap* self, bool value) {
		self->m_enabled = value;
	}
	float DECL two_Tonemap__get_exposure(two::Tonemap* self) {
		return self->m_exposure;
	}
	void DECL two_Tonemap__set_exposure(two::Tonemap* self, float value) {
		self->m_exposure = value;
	}
	float DECL two_Tonemap__get_white_point(two::Tonemap* self) {
		return self->m_white_point;
	}
	void DECL two_Tonemap__set_white_point(two::Tonemap* self, float value) {
		self->m_white_point = value;
	}
	void DECL two_Tonemap__destroy(two::Tonemap* self) {
		delete self;
	}
	// BlockTonemap
	two::Type* DECL two_BlockTonemap__type() {
		return &two::type<two::BlockTonemap>();
	}
	void DECL two_BlockTonemap__destroy(two::BlockTonemap* self) {
		delete self;
	}
	void DECL two_begin_pbr_render_2(two::GfxSystem* gfx, two::Render* render) {
		two::begin_pbr_render(*gfx, *render);
	}
	void DECL two_pass_gi_probes_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_gi_probes(*gfx, *render);
	}
	void DECL two_pass_shadowmaps_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_shadowmaps(*gfx, *render);
	}
	void DECL two_pass_shadow_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_shadow(*gfx, *render);
	}
	void DECL two_pass_opaque_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_opaque(*gfx, *render);
	}
	void DECL two_pass_alpha_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_alpha(*gfx, *render);
	}
	void DECL two_pass_geometry_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_geometry(*gfx, *render);
	}
	void DECL two_pass_lights_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_lights(*gfx, *render);
	}
	void DECL two_pass_voxel_gi_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_voxel_gi(*gfx, *render);
	}
	void DECL two_pass_lightmap_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_lightmap(*gfx, *render);
	}
	void DECL two_pass_begin_post_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_begin_post(*gfx, *render);
	}
	void DECL two_pass_post_auto_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_post_auto(*gfx, *render);
	}
	void DECL two_pass_post_effects_6(two::GfxSystem* gfx, two::Render* render, two::DofBlur* dof, two::Glow* glow, two::Tonemap* tonemap, two::BCS* bcs) {
		two::pass_post_effects(*gfx, *render, *dof, *glow, *tonemap, *bcs);
	}
	void DECL two_render_pbr_forward_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_pbr_forward(*gfx, *render);
	}
	void DECL two_render_pbr_deferred_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_pbr_deferred(*gfx, *render);
	}
	void DECL two_render_shadow_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_shadow(*gfx, *render);
	}
	void DECL two_render_voxel_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_voxel(*gfx, *render);
	}
	void DECL two_render_lightmap_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_lightmap(*gfx, *render);
	}
	void DECL two_render_reflection_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_reflection(*gfx, *render);
	}
	void DECL two_pipeline_pbr_2(two::GfxSystem* gfx, two::Renderer* pipeline) {
		two::pipeline_pbr(*gfx, *pipeline);
	}
	void DECL two_pipeline_pbr_3(two::GfxSystem* gfx, two::Renderer* pipeline, bool deferred) {
		two::pipeline_pbr(*gfx, *pipeline, deferred);
	}
	void DECL two_gfx_setup_pipeline_pbr_1(two::GfxSystem* gfx) {
		two::gfx::setup_pipeline_pbr(*gfx);
	}
	two::GIProbe* DECL two_gfx_gi_probe_3(two::Gnode* parent, uint16_t subdiv, const two::vec3* extents) {
		return &two::gfx::gi_probe(*parent, subdiv, *extents);
	}
	two::LightmapAtlas* DECL two_gfx_lightmap_2(two::Gnode* parent, uint32_t resolution) {
		return &two::gfx::lightmap(*parent, resolution);
	}
	two::LightmapAtlas* DECL two_gfx_lightmap_3(two::Gnode* parent, uint32_t resolution, float density) {
		return &two::gfx::lightmap(*parent, resolution, density);
	}
	two::LightmapAtlas* DECL two_gfx_lightmap_4(two::Gnode* parent, uint32_t resolution, float density, const char* save_path) {
		return &two::gfx::lightmap(*parent, resolution, density, save_path);
	}
	void DECL two_pass_dofblur_3(two::GfxSystem* gfx, two::Render* render, const two::DofBlur* blur) {
		two::pass_dofblur(*gfx, *render, *blur);
	}
	void DECL two_pass_glow_3(two::GfxSystem* gfx, two::Render* render, two::Glow* glow) {
		two::pass_glow(*gfx, *render, *glow);
	}
	void DECL two_pass_tonemap_4(two::GfxSystem* gfx, two::Render* render, two::Tonemap* tonemap, two::BCS* bcs) {
		two::pass_tonemap(*gfx, *render, *tonemap, *bcs);
	}
	// TonemapMode
	two::TonemapMode DECL two_TonemapMode_Linear() {
		return two::TonemapMode::Linear;
	}
	two::TonemapMode DECL two_TonemapMode_Reinhardt() {
		return two::TonemapMode::Reinhardt;
	}
	two::TonemapMode DECL two_TonemapMode_Filmic() {
		return two::TonemapMode::Filmic;
	}
	two::TonemapMode DECL two_TonemapMode_ACES() {
		return two::TonemapMode::ACES;
	}
	two::TonemapMode DECL two_TonemapMode_Cineon() {
		return two::TonemapMode::Cineon;
	}
	two::TonemapMode DECL two_TonemapMode_Uncharted2() {
		return two::TonemapMode::Uncharted2;
	}
	
}


