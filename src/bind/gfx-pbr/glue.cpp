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
	float EMSCRIPTEN_KEEPALIVE BCS_get_brightness(mud::BCS* self) {
		return self->m_brightness;
	}
	float EMSCRIPTEN_KEEPALIVE BCS_get_contrast(mud::BCS* self) {
		return self->m_contrast;
	}
	float EMSCRIPTEN_KEEPALIVE BCS_get_saturation(mud::BCS* self) {
		return self->m_saturation;
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
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_far_distance(mud::DofBlur* self) {
		return self->m_far_distance;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_far_transition(mud::DofBlur* self) {
		return self->m_far_transition;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_far_radius(mud::DofBlur* self) {
		return self->m_far_radius;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_near_distance(mud::DofBlur* self) {
		return self->m_near_distance;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_near_transition(mud::DofBlur* self) {
		return self->m_near_transition;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_near_radius(mud::DofBlur* self) {
		return self->m_near_radius;
	}
	float EMSCRIPTEN_KEEPALIVE DofBlur_get_max_coc_radius(mud::DofBlur* self) {
		return self->m_max_coc_radius;
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
	mud::vec4* EMSCRIPTEN_KEEPALIVE Glow_get_levels_1_4(mud::Glow* self) {
		static mud::vec4 temp;
		return (temp = &self->m_levels_1_4, &temp);
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE Glow_get_levels_5_8(mud::Glow* self) {
		static mud::vec4 temp;
		return (temp = &self->m_levels_5_8, &temp);
	}
	float EMSCRIPTEN_KEEPALIVE Glow_get_intensity(mud::Glow* self) {
		return self->m_intensity;
	}
	float EMSCRIPTEN_KEEPALIVE Glow_get_bloom(mud::Glow* self) {
		return self->m_bloom;
	}
	float EMSCRIPTEN_KEEPALIVE Glow_get_bleed_threshold(mud::Glow* self) {
		return self->m_bleed_threshold;
	}
	float EMSCRIPTEN_KEEPALIVE Glow_get_bleed_scale(mud::Glow* self) {
		return self->m_bleed_scale;
	}
	bool EMSCRIPTEN_KEEPALIVE Glow_get_bicubic_filter(mud::Glow* self) {
		return self->m_bicubic_filter;
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
		return &&self->m_node;
	}
	bool EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_visible(mud::ReflectionProbe* self) {
		return self->m_visible;
	}
	float EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_intensity(mud::ReflectionProbe* self) {
		return self->m_intensity;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_extents(mud::ReflectionProbe* self) {
		static mud::vec3 temp;
		return (temp = &self->m_extents, &temp);
	}
	bool EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_shadows(mud::ReflectionProbe* self) {
		return self->m_shadows;
	}
	bool EMSCRIPTEN_KEEPALIVE ReflectionProbe_get_dirty(mud::ReflectionProbe* self) {
		return self->m_dirty;
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
		return (temp = &self->m_dof_blur, &temp);
	}
	mud::Glow* EMSCRIPTEN_KEEPALIVE RenderFilters_get_glow(mud::RenderFilters* self) {
		static mud::Glow temp;
		return (temp = &self->m_glow, &temp);
	}
	mud::BCS* EMSCRIPTEN_KEEPALIVE RenderFilters_get_bcs(mud::RenderFilters* self) {
		static mud::BCS temp;
		return (temp = &self->m_bcs, &temp);
	}
	mud::Tonemap* EMSCRIPTEN_KEEPALIVE RenderFilters_get_tonemap(mud::RenderFilters* self) {
		static mud::Tonemap temp;
		return (temp = &self->m_tonemap, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE RenderFilters___destroy__(mud::RenderFilters* self) {
		delete self;
	}
	// Tonemap
	mud::Tonemap* EMSCRIPTEN_KEEPALIVE Tonemap_Tonemap_0() {
		return new mud::Tonemap();
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE Tonemap_get_mode(mud::Tonemap* self) {
		static mud::TonemapMode temp;
		return (temp = &self->m_mode, &temp);
	}
	bool EMSCRIPTEN_KEEPALIVE Tonemap_get_enabled(mud::Tonemap* self) {
		return self->m_enabled;
	}
	float EMSCRIPTEN_KEEPALIVE Tonemap_get_exposure(mud::Tonemap* self) {
		return self->m_exposure;
	}
	float EMSCRIPTEN_KEEPALIVE Tonemap_get_white_point(mud::Tonemap* self) {
		return self->m_white_point;
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
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE emscripten_enum_TonemapMode_Linear() {
		return mud::TonemapMode::Linear;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE emscripten_enum_TonemapMode_Reinhardt() {
		return mud::TonemapMode::Reinhardt;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE emscripten_enum_TonemapMode_Filmic() {
		return mud::TonemapMode::Filmic;
	}
	mud::TonemapMode EMSCRIPTEN_KEEPALIVE emscripten_enum_TonemapMode_ACES() {
		return mud::TonemapMode::ACES;
	}
	
}


