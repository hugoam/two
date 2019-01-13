#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gfx-pbr/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// BCS
	mud::BCS* EMSCRIPTEN_KEEPALIVE BCS_BCS_0() {
		return new mud::BCS();
	}
	bool EMSCRIPTEN_KEEPALIVE BCS_get_enabled(mud::BCS* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE BCS_set_enabled(mud::BCS* self, bool enabled) {
		self->m_enabled = enabled;
	}
	float EMSCRIPTEN_KEEPALIVE BCS_get_brightness(mud::BCS* self) {
		return self->m_brightness;
	}
	void EMSCRIPTEN_KEEPALIVE BCS_set_brightness(mud::BCS* self, float brightness) {
		self->m_brightness = brightness;
	}
	float EMSCRIPTEN_KEEPALIVE BCS_get_contrast(mud::BCS* self) {
		return self->m_contrast;
	}
	void EMSCRIPTEN_KEEPALIVE BCS_set_contrast(mud::BCS* self, float contrast) {
		self->m_contrast = contrast;
	}
	float EMSCRIPTEN_KEEPALIVE BCS_get_saturation(mud::BCS* self) {
		return self->m_saturation;
	}
	void EMSCRIPTEN_KEEPALIVE BCS_set_saturation(mud::BCS* self, float saturation) {
		self->m_saturation = saturation;
	}
	void EMSCRIPTEN_KEEPALIVE BCS___destroy__(mud::BCS* self) {
		delete self;
	}
	// DofBlur
	mud::DofBlur* EMSCRIPTEN_KEEPALIVE DofBlur_DofBlur_0() {
		return new mud::DofBlur();
	}
	bool EMSCRIPTEN_KEEPALIVE DofBlur_get_enabled(mud::DofBlur* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur_set_enabled(mud::DofBlur* self, bool enabled) {
		self->m_enabled = enabled;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_far_distance(mud::DofBlur* self) {
		return self->m_far_distance;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur_set_far_distance(mud::DofBlur* self, float far_distance) {
		self->m_far_distance = far_distance;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_far_transition(mud::DofBlur* self) {
		return self->m_far_transition;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur_set_far_transition(mud::DofBlur* self, float far_transition) {
		self->m_far_transition = far_transition;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_far_radius(mud::DofBlur* self) {
		return self->m_far_radius;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur_set_far_radius(mud::DofBlur* self, float far_radius) {
		self->m_far_radius = far_radius;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_near_distance(mud::DofBlur* self) {
		return self->m_near_distance;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur_set_near_distance(mud::DofBlur* self, float near_distance) {
		self->m_near_distance = near_distance;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_near_transition(mud::DofBlur* self) {
		return self->m_near_transition;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur_set_near_transition(mud::DofBlur* self, float near_transition) {
		self->m_near_transition = near_transition;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_near_radius(mud::DofBlur* self) {
		return self->m_near_radius;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur_set_near_radius(mud::DofBlur* self, float near_radius) {
		self->m_near_radius = near_radius;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_max_coc_radius(mud::DofBlur* self) {
		return self->m_max_coc_radius;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur_set_max_coc_radius(mud::DofBlur* self, float max_coc_radius) {
		self->m_max_coc_radius = max_coc_radius;
	}
	void EMSCRIPTEN_KEEPALIVE DofBlur___destroy__(mud::DofBlur* self) {
		delete self;
	}
	// GIProbe
	void EMSCRIPTEN_KEEPALIVE GIProbe___destroy__(mud::GIProbe* self) {
		delete self;
	}
	// Glow
	mud::Glow* EMSCRIPTEN_KEEPALIVE Glow_Glow_0() {
		return new mud::Glow();
	}
	bool EMSCRIPTEN_KEEPALIVE Glow_get_enabled(mud::Glow* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE Glow_set_enabled(mud::Glow* self, bool enabled) {
		self->m_enabled = enabled;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE Glow_get_levels_1_4(mud::Glow* self) {
		static mud::vec4 temp;
		return (temp = self->m_levels_1_4, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Glow_set_levels_1_4(mud::Glow* self, mud::vec4* levels_1_4) {
		self->m_levels_1_4 = *levels_1_4;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE Glow_get_levels_5_8(mud::Glow* self) {
		static mud::vec4 temp;
		return (temp = self->m_levels_5_8, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Glow_set_levels_5_8(mud::Glow* self, mud::vec4* levels_5_8) {
		self->m_levels_5_8 = *levels_5_8;
	}
	float EMSCRIPTEN_KEEPALIVE Glow_get_intensity(mud::Glow* self) {
		return self->m_intensity;
	}
	void EMSCRIPTEN_KEEPALIVE Glow_set_intensity(mud::Glow* self, float intensity) {
		self->m_intensity = intensity;
	}
	float EMSCRIPTEN_KEEPALIVE Glow_get_bloom(mud::Glow* self) {
		return self->m_bloom;
	}
	void EMSCRIPTEN_KEEPALIVE Glow_set_bloom(mud::Glow* self, float bloom) {
		self->m_bloom = bloom;
	}
	float EMSCRIPTEN_KEEPALIVE Glow_get_bleed_threshold(mud::Glow* self) {
		return self->m_bleed_threshold;
	}
	void EMSCRIPTEN_KEEPALIVE Glow_set_bleed_threshold(mud::Glow* self, float bleed_threshold) {
		self->m_bleed_threshold = bleed_threshold;
	}
	float EMSCRIPTEN_KEEPALIVE Glow_get_bleed_scale(mud::Glow* self) {
		return self->m_bleed_scale;
	}
	void EMSCRIPTEN_KEEPALIVE Glow_set_bleed_scale(mud::Glow* self, float bleed_scale) {
		self->m_bleed_scale = bleed_scale;
	}
	bool EMSCRIPTEN_KEEPALIVE Glow_get_bicubic_filter(mud::Glow* self) {
		return self->m_bicubic_filter;
	}
	void EMSCRIPTEN_KEEPALIVE Glow_set_bicubic_filter(mud::Glow* self, bool bicubic_filter) {
		self->m_bicubic_filter = bicubic_filter;
	}
	void EMSCRIPTEN_KEEPALIVE Glow___destroy__(mud::Glow* self) {
		delete self;
	}
	// LightShadow
	mud::LightShadow* EMSCRIPTEN_KEEPALIVE LightShadow_LightShadow_0() {
		return new mud::LightShadow();
	}
	void EMSCRIPTEN_KEEPALIVE LightShadow___destroy__(mud::LightShadow* self) {
		delete self;
	}
	// Lightmap
	void EMSCRIPTEN_KEEPALIVE Lightmap___destroy__(mud::Lightmap* self) {
		delete self;
	}
	// LightmapAtlas
	void EMSCRIPTEN_KEEPALIVE LightmapAtlas___destroy__(mud::LightmapAtlas* self) {
		delete self;
	}
	// LightmapItem
	void EMSCRIPTEN_KEEPALIVE LightmapItem___destroy__(mud::LightmapItem* self) {
		delete self;
	}
	// ReflectionProbe
	mud::Node3* EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_node(mud::ReflectionProbe* self) {
		return &self->m_node;
	}
	bool EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_visible(mud::ReflectionProbe* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE ReflectionProbe_set_visible(mud::ReflectionProbe* self, bool visible) {
		self->m_visible = visible;
	}
	float EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_intensity(mud::ReflectionProbe* self) {
		return self->m_intensity;
	}
	void EMSCRIPTEN_KEEPALIVE ReflectionProbe_set_intensity(mud::ReflectionProbe* self, float intensity) {
		self->m_intensity = intensity;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_extents(mud::ReflectionProbe* self) {
		static mud::vec3 temp;
		return (temp = self->m_extents, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ReflectionProbe_set_extents(mud::ReflectionProbe* self, mud::vec3* extents) {
		self->m_extents = *extents;
	}
	bool EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_shadows(mud::ReflectionProbe* self) {
		return self->m_shadows;
	}
	void EMSCRIPTEN_KEEPALIVE ReflectionProbe_set_shadows(mud::ReflectionProbe* self, bool shadows) {
		self->m_shadows = shadows;
	}
	bool EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_dirty(mud::ReflectionProbe* self) {
		return self->m_dirty;
	}
	void EMSCRIPTEN_KEEPALIVE ReflectionProbe_set_dirty(mud::ReflectionProbe* self, bool dirty) {
		self->m_dirty = dirty;
	}
	void EMSCRIPTEN_KEEPALIVE ReflectionProbe___destroy__(mud::ReflectionProbe* self) {
		delete self;
	}
	// RenderFilters
	mud::RenderFilters* EMSCRIPTEN_KEEPALIVE RenderFilters_RenderFilters_0() {
		return new mud::RenderFilters();
	}
	mud::DofBlur* EMSCRIPTEN_KEEPALIVE RenderFilters_get_dof_blur(mud::RenderFilters* self) {
		static mud::DofBlur temp;
		return (temp = self->m_dof_blur, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE RenderFilters_set_dof_blur(mud::RenderFilters* self, mud::DofBlur* dof_blur) {
		self->m_dof_blur = *dof_blur;
	}
	mud::Glow* EMSCRIPTEN_KEEPALIVE RenderFilters_get_glow(mud::RenderFilters* self) {
		static mud::Glow temp;
		return (temp = self->m_glow, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE RenderFilters_set_glow(mud::RenderFilters* self, mud::Glow* glow) {
		self->m_glow = *glow;
	}
	mud::BCS* EMSCRIPTEN_KEEPALIVE RenderFilters_get_bcs(mud::RenderFilters* self) {
		static mud::BCS temp;
		return (temp = self->m_bcs, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE RenderFilters_set_bcs(mud::RenderFilters* self, mud::BCS* bcs) {
		self->m_bcs = *bcs;
	}
	mud::Tonemap* EMSCRIPTEN_KEEPALIVE RenderFilters_get_tonemap(mud::RenderFilters* self) {
		static mud::Tonemap temp;
		return (temp = self->m_tonemap, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE RenderFilters_set_tonemap(mud::RenderFilters* self, mud::Tonemap* tonemap) {
		self->m_tonemap = *tonemap;
	}
	void EMSCRIPTEN_KEEPALIVE RenderFilters___destroy__(mud::RenderFilters* self) {
		delete self;
	}
	// Tonemap
	mud::Tonemap* EMSCRIPTEN_KEEPALIVE Tonemap_Tonemap_0() {
		return new mud::Tonemap();
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE Tonemap_get_mode(mud::Tonemap* self) {
		return self->m_mode;
	}
	void EMSCRIPTEN_KEEPALIVE Tonemap_set_mode(mud::Tonemap* self, mud::TonemapMode mode) {
		self->m_mode = mode;
	}
	bool EMSCRIPTEN_KEEPALIVE Tonemap_get_enabled(mud::Tonemap* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE Tonemap_set_enabled(mud::Tonemap* self, bool enabled) {
		self->m_enabled = enabled;
	}
	float EMSCRIPTEN_KEEPALIVE Tonemap_get_exposure(mud::Tonemap* self) {
		return self->m_exposure;
	}
	void EMSCRIPTEN_KEEPALIVE Tonemap_set_exposure(mud::Tonemap* self, float exposure) {
		self->m_exposure = exposure;
	}
	float EMSCRIPTEN_KEEPALIVE Tonemap_get_white_point(mud::Tonemap* self) {
		return self->m_white_point;
	}
	void EMSCRIPTEN_KEEPALIVE Tonemap_set_white_point(mud::Tonemap* self, float white_point) {
		self->m_white_point = white_point;
	}
	void EMSCRIPTEN_KEEPALIVE Tonemap___destroy__(mud::Tonemap* self) {
		delete self;
	}
	// BlockBlur
	void EMSCRIPTEN_KEEPALIVE BlockBlur___destroy__(mud::BlockBlur* self) {
		delete self;
	}
	// BlockDofBlur
	void EMSCRIPTEN_KEEPALIVE BlockDofBlur___destroy__(mud::BlockDofBlur* self) {
		delete self;
	}
	// BlockGIBake
	void EMSCRIPTEN_KEEPALIVE BlockGIBake___destroy__(mud::BlockGIBake* self) {
		delete self;
	}
	// BlockGITrace
	void EMSCRIPTEN_KEEPALIVE BlockGITrace___destroy__(mud::BlockGITrace* self) {
		delete self;
	}
	// BlockGeometry
	void EMSCRIPTEN_KEEPALIVE BlockGeometry___destroy__(mud::BlockGeometry* self) {
		delete self;
	}
	// BlockGlow
	void EMSCRIPTEN_KEEPALIVE BlockGlow___destroy__(mud::BlockGlow* self) {
		delete self;
	}
	// BlockLight
	void EMSCRIPTEN_KEEPALIVE BlockLight___destroy__(mud::BlockLight* self) {
		delete self;
	}
	// BlockLightmap
	void EMSCRIPTEN_KEEPALIVE BlockLightmap___destroy__(mud::BlockLightmap* self) {
		delete self;
	}
	// BlockRadiance
	void EMSCRIPTEN_KEEPALIVE BlockRadiance___destroy__(mud::BlockRadiance* self) {
		delete self;
	}
	// BlockReflection
	void EMSCRIPTEN_KEEPALIVE BlockReflection___destroy__(mud::BlockReflection* self) {
		delete self;
	}
	// BlockShadow
	void EMSCRIPTEN_KEEPALIVE BlockShadow___destroy__(mud::BlockShadow* self) {
		delete self;
	}
	// BlockTonemap
	void EMSCRIPTEN_KEEPALIVE BlockTonemap___destroy__(mud::BlockTonemap* self) {
		delete self;
	}
	// TonemapMode
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE TonemapMode_Linear() {
		return mud::TonemapMode::Linear;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE TonemapMode_Reinhardt() {
		return mud::TonemapMode::Reinhardt;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE TonemapMode_Filmic() {
		return mud::TonemapMode::Filmic;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE TonemapMode_ACES() {
		return mud::TonemapMode::ACES;
	}
	
}


