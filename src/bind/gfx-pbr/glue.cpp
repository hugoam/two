#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gfx-pbr/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// BCS
	mud::BCS* EMSCRIPTEN_KEEPALIVE mud_BCS_BCS_0() {
		return new mud::BCS();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_BCS_get_enabled(mud::BCS* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BCS_set_enabled(mud::BCS* self, bool value) {
		self->m_enabled = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_BCS_get_brightness(mud::BCS* self) {
		return self->m_brightness;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BCS_set_brightness(mud::BCS* self, float value) {
		self->m_brightness = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_BCS_get_contrast(mud::BCS* self) {
		return self->m_contrast;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BCS_set_contrast(mud::BCS* self, float value) {
		self->m_contrast = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_BCS_get_saturation(mud::BCS* self) {
		return self->m_saturation;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BCS_set_saturation(mud::BCS* self, float value) {
		self->m_saturation = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BCS___destroy__(mud::BCS* self) {
		delete self;
	}
	// DofBlur
	mud::DofBlur* EMSCRIPTEN_KEEPALIVE mud_DofBlur_DofBlur_0() {
		return new mud::DofBlur();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_DofBlur_get_enabled(mud::DofBlur* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur_set_enabled(mud::DofBlur* self, bool value) {
		self->m_enabled = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_DofBlur_get_far_distance(mud::DofBlur* self) {
		return self->m_far_distance;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur_set_far_distance(mud::DofBlur* self, float value) {
		self->m_far_distance = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_DofBlur_get_far_transition(mud::DofBlur* self) {
		return self->m_far_transition;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur_set_far_transition(mud::DofBlur* self, float value) {
		self->m_far_transition = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_DofBlur_get_far_radius(mud::DofBlur* self) {
		return self->m_far_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur_set_far_radius(mud::DofBlur* self, float value) {
		self->m_far_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_DofBlur_get_near_distance(mud::DofBlur* self) {
		return self->m_near_distance;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur_set_near_distance(mud::DofBlur* self, float value) {
		self->m_near_distance = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_DofBlur_get_near_transition(mud::DofBlur* self) {
		return self->m_near_transition;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur_set_near_transition(mud::DofBlur* self, float value) {
		self->m_near_transition = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_DofBlur_get_near_radius(mud::DofBlur* self) {
		return self->m_near_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur_set_near_radius(mud::DofBlur* self, float value) {
		self->m_near_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_DofBlur_get_max_coc_radius(mud::DofBlur* self) {
		return self->m_max_coc_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur_set_max_coc_radius(mud::DofBlur* self, float value) {
		self->m_max_coc_radius = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_DofBlur___destroy__(mud::DofBlur* self) {
		delete self;
	}
	// GIProbe
	void EMSCRIPTEN_KEEPALIVE mud_GIProbe___destroy__(mud::GIProbe* self) {
		delete self;
	}
	// Glow
	mud::Glow* EMSCRIPTEN_KEEPALIVE mud_Glow_Glow_0() {
		return new mud::Glow();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Glow_get_enabled(mud::Glow* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow_set_enabled(mud::Glow* self, bool value) {
		self->m_enabled = value;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE mud_Glow_get_levels_1_4(mud::Glow* self) {
		static mud::vec4 temp;
		return (temp = self->m_levels_1_4, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow_set_levels_1_4(mud::Glow* self, mud::vec4* value) {
		self->m_levels_1_4 = *value;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE mud_Glow_get_levels_5_8(mud::Glow* self) {
		static mud::vec4 temp;
		return (temp = self->m_levels_5_8, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow_set_levels_5_8(mud::Glow* self, mud::vec4* value) {
		self->m_levels_5_8 = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Glow_get_intensity(mud::Glow* self) {
		return self->m_intensity;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow_set_intensity(mud::Glow* self, float value) {
		self->m_intensity = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Glow_get_bloom(mud::Glow* self) {
		return self->m_bloom;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow_set_bloom(mud::Glow* self, float value) {
		self->m_bloom = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Glow_get_bleed_threshold(mud::Glow* self) {
		return self->m_bleed_threshold;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow_set_bleed_threshold(mud::Glow* self, float value) {
		self->m_bleed_threshold = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Glow_get_bleed_scale(mud::Glow* self) {
		return self->m_bleed_scale;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow_set_bleed_scale(mud::Glow* self, float value) {
		self->m_bleed_scale = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Glow_get_bicubic_filter(mud::Glow* self) {
		return self->m_bicubic_filter;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow_set_bicubic_filter(mud::Glow* self, bool value) {
		self->m_bicubic_filter = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Glow___destroy__(mud::Glow* self) {
		delete self;
	}
	// LightShadow
	mud::LightShadow* EMSCRIPTEN_KEEPALIVE mud_LightShadow_LightShadow_0() {
		return new mud::LightShadow();
	}
	void EMSCRIPTEN_KEEPALIVE mud_LightShadow___destroy__(mud::LightShadow* self) {
		delete self;
	}
	// Lightmap
	void EMSCRIPTEN_KEEPALIVE mud_Lightmap___destroy__(mud::Lightmap* self) {
		delete self;
	}
	// LightmapAtlas
	void EMSCRIPTEN_KEEPALIVE mud_LightmapAtlas___destroy__(mud::LightmapAtlas* self) {
		delete self;
	}
	// LightmapItem
	void EMSCRIPTEN_KEEPALIVE mud_LightmapItem___destroy__(mud::LightmapItem* self) {
		delete self;
	}
	// ReflectionProbe
	mud::Node3* EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_get_node(mud::ReflectionProbe* self) {
		return &self->m_node;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_get_visible(mud::ReflectionProbe* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_set_visible(mud::ReflectionProbe* self, bool value) {
		self->m_visible = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_get_intensity(mud::ReflectionProbe* self) {
		return self->m_intensity;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_set_intensity(mud::ReflectionProbe* self, float value) {
		self->m_intensity = value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_get_extents(mud::ReflectionProbe* self) {
		static mud::vec3 temp;
		return (temp = self->m_extents, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_set_extents(mud::ReflectionProbe* self, mud::vec3* value) {
		self->m_extents = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_get_shadows(mud::ReflectionProbe* self) {
		return self->m_shadows;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_set_shadows(mud::ReflectionProbe* self, bool value) {
		self->m_shadows = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_get_dirty(mud::ReflectionProbe* self) {
		return self->m_dirty;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe_set_dirty(mud::ReflectionProbe* self, bool value) {
		self->m_dirty = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ReflectionProbe___destroy__(mud::ReflectionProbe* self) {
		delete self;
	}
	// RenderFilters
	mud::RenderFilters* EMSCRIPTEN_KEEPALIVE mud_RenderFilters_RenderFilters_0() {
		return new mud::RenderFilters();
	}
	mud::DofBlur* EMSCRIPTEN_KEEPALIVE mud_RenderFilters_get_dof_blur(mud::RenderFilters* self) {
		static mud::DofBlur temp;
		return (temp = self->m_dof_blur, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_RenderFilters_set_dof_blur(mud::RenderFilters* self, mud::DofBlur* value) {
		self->m_dof_blur = *value;
	}
	mud::Glow* EMSCRIPTEN_KEEPALIVE mud_RenderFilters_get_glow(mud::RenderFilters* self) {
		static mud::Glow temp;
		return (temp = self->m_glow, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_RenderFilters_set_glow(mud::RenderFilters* self, mud::Glow* value) {
		self->m_glow = *value;
	}
	mud::BCS* EMSCRIPTEN_KEEPALIVE mud_RenderFilters_get_bcs(mud::RenderFilters* self) {
		static mud::BCS temp;
		return (temp = self->m_bcs, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_RenderFilters_set_bcs(mud::RenderFilters* self, mud::BCS* value) {
		self->m_bcs = *value;
	}
	mud::Tonemap* EMSCRIPTEN_KEEPALIVE mud_RenderFilters_get_tonemap(mud::RenderFilters* self) {
		static mud::Tonemap temp;
		return (temp = self->m_tonemap, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_RenderFilters_set_tonemap(mud::RenderFilters* self, mud::Tonemap* value) {
		self->m_tonemap = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_RenderFilters___destroy__(mud::RenderFilters* self) {
		delete self;
	}
	// Tonemap
	mud::Tonemap* EMSCRIPTEN_KEEPALIVE mud_Tonemap_Tonemap_0() {
		return new mud::Tonemap();
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE mud_Tonemap_get_mode(mud::Tonemap* self) {
		return self->m_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Tonemap_set_mode(mud::Tonemap* self, mud::TonemapMode value) {
		self->m_mode = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Tonemap_get_enabled(mud::Tonemap* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Tonemap_set_enabled(mud::Tonemap* self, bool value) {
		self->m_enabled = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Tonemap_get_exposure(mud::Tonemap* self) {
		return self->m_exposure;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Tonemap_set_exposure(mud::Tonemap* self, float value) {
		self->m_exposure = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Tonemap_get_white_point(mud::Tonemap* self) {
		return self->m_white_point;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Tonemap_set_white_point(mud::Tonemap* self, float value) {
		self->m_white_point = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Tonemap___destroy__(mud::Tonemap* self) {
		delete self;
	}
	// BlockBlur
	void EMSCRIPTEN_KEEPALIVE mud_BlockBlur___destroy__(mud::BlockBlur* self) {
		delete self;
	}
	// BlockDofBlur
	void EMSCRIPTEN_KEEPALIVE mud_BlockDofBlur___destroy__(mud::BlockDofBlur* self) {
		delete self;
	}
	// BlockGIBake
	void EMSCRIPTEN_KEEPALIVE mud_BlockGIBake___destroy__(mud::BlockGIBake* self) {
		delete self;
	}
	// BlockGITrace
	void EMSCRIPTEN_KEEPALIVE mud_BlockGITrace___destroy__(mud::BlockGITrace* self) {
		delete self;
	}
	// BlockGeometry
	void EMSCRIPTEN_KEEPALIVE mud_BlockGeometry___destroy__(mud::BlockGeometry* self) {
		delete self;
	}
	// BlockGlow
	void EMSCRIPTEN_KEEPALIVE mud_BlockGlow___destroy__(mud::BlockGlow* self) {
		delete self;
	}
	// BlockLight
	void EMSCRIPTEN_KEEPALIVE mud_BlockLight___destroy__(mud::BlockLight* self) {
		delete self;
	}
	// BlockLightmap
	void EMSCRIPTEN_KEEPALIVE mud_BlockLightmap___destroy__(mud::BlockLightmap* self) {
		delete self;
	}
	// BlockRadiance
	void EMSCRIPTEN_KEEPALIVE mud_BlockRadiance___destroy__(mud::BlockRadiance* self) {
		delete self;
	}
	// BlockReflection
	void EMSCRIPTEN_KEEPALIVE mud_BlockReflection___destroy__(mud::BlockReflection* self) {
		delete self;
	}
	// BlockShadow
	void EMSCRIPTEN_KEEPALIVE mud_BlockShadow___destroy__(mud::BlockShadow* self) {
		delete self;
	}
	// BlockTonemap
	void EMSCRIPTEN_KEEPALIVE mud_BlockTonemap___destroy__(mud::BlockTonemap* self) {
		delete self;
	}
	// TonemapMode
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE mud_TonemapMode_Linear() {
		return mud::TonemapMode::Linear;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE mud_TonemapMode_Reinhardt() {
		return mud::TonemapMode::Reinhardt;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE mud_TonemapMode_Filmic() {
		return mud::TonemapMode::Filmic;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE mud_TonemapMode_ACES() {
		return mud::TonemapMode::ACES;
	}
	
}


