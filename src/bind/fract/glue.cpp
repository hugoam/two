#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <fract/Api.h>
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
	// Circlifier
	mud::Circlifier* EMSCRIPTEN_KEEPALIVE Circlifier_Circlifier_0() {
		return new mud::Circlifier();
	}
	mud::Circlifier* EMSCRIPTEN_KEEPALIVE Circlifier_Circlifier_1(Image256 image) {
		return new mud::Circlifier(*image);
	}
	std::vector<mud::Circle> EMSCRIPTEN_KEEPALIVE Circlifier_compute_1(mud::Circlifier* self, const Colour colour) {
		return self->compute(*colour, scale);
	}
	std::vector<mud::Circle> EMSCRIPTEN_KEEPALIVE Circlifier_compute_2(mud::Circlifier* self, const Colour colour, float scale) {
		return self->compute(*colour, scale);
	}
	void EMSCRIPTEN_KEEPALIVE Circlifier___destroy__(mud::Circlifier* self) {
		delete self;
	}
	// Fract
	mud::Fract* EMSCRIPTEN_KEEPALIVE Fract_Fract_0() {
		return new mud::Fract(num_tabs);
	}
	mud::Fract* EMSCRIPTEN_KEEPALIVE Fract_Fract_1(size_t num_tabs) {
		return new mud::Fract(num_tabs);
	}
	void EMSCRIPTEN_KEEPALIVE Fract_generate_0(mud::Fract* self) {
		self->generate(num_tabs);
	}
	void EMSCRIPTEN_KEEPALIVE Fract_generate_1(mud::Fract* self, size_t num_tabs) {
		self->generate(num_tabs);
	}
	void EMSCRIPTEN_KEEPALIVE Fract_regen_0(mud::Fract* self) {
		self->regen();
	}
	void EMSCRIPTEN_KEEPALIVE Fract_render_4(mud::Fract* self, const Rect rect, const Pattern pattern, uvec2 resolution, Image256 output_image) {
		self->render(*rect, *pattern, resolution, *output_image);
	}
	void EMSCRIPTEN_KEEPALIVE Fract_render_whole_3(mud::Fract* self, const Pattern pattern, uvec2 resolution, Image256 output_image) {
		self->render_whole(*pattern, resolution, *output_image);
	}
	void EMSCRIPTEN_KEEPALIVE Fract_render_grid_4(mud::Fract* self, uvec2 size, const Pattern pattern, uvec2 resolution, std::vector<mud::Image256> output_images) {
		self->render_grid(size, *pattern, resolution, *output_images);
	}
	size_t EMSCRIPTEN_KEEPALIVE Fract_get_nutabs(mud::Fract* self) {
		return self->m_num_tabs;
	}
	void EMSCRIPTEN_KEEPALIVE Fract___destroy__(mud::Fract* self) {
		delete self;
	}
	// FractSample
	mud::FractSample* EMSCRIPTEN_KEEPALIVE FractSample_FractSample_3(Fract fract, const Rect rect, uvec2 resolution) {
		return new mud::FractSample(*fract, *rect, resolution);
	}
	void EMSCRIPTEN_KEEPALIVE FractSample_render_2(mud::FractSample* self, const Pattern pattern, Image256 outputImage) {
		self->render(*pattern, *outputImage);
	}
	Fract EMSCRIPTEN_KEEPALIVE FractSample_get_fract(mud::FractSample* self) {
		return self->m_fract;
	}
	Rect EMSCRIPTEN_KEEPALIVE FractSample_get_rect(mud::FractSample* self) {
		return self->m_rect;
	}
	uvec2 EMSCRIPTEN_KEEPALIVE FractSample_get_resolution(mud::FractSample* self) {
		return self->m_resolution;
	}
	void EMSCRIPTEN_KEEPALIVE FractSample___destroy__(mud::FractSample* self) {
		delete self;
	}
	// FractTab
	mud::FractTab* EMSCRIPTEN_KEEPALIVE FractTab_FractTab_0() {
		return new mud::FractTab();
	}
	void EMSCRIPTEN_KEEPALIVE FractTab___destroy__(mud::FractTab* self) {
		delete self;
	}
	// Pattern
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_0() {
		return new mud::Pattern();
	}
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_2(Palette palette, PatternSampling sampling) {
		return new mud::Pattern(palette, sampling, precision, step);
	}
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_3(Palette palette, PatternSampling sampling, float precision) {
		return new mud::Pattern(palette, sampling, precision, step);
	}
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_4(Palette palette, PatternSampling sampling, float precision, size_t step) {
		return new mud::Pattern(palette, sampling, precision, step);
	}
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_0() {
		return new mud::Pattern();
	}
	void EMSCRIPTEN_KEEPALIVE Pattern___destroy__(mud::Pattern* self) {
		delete self;
	}
	// PatternSampling
	mud::PatternSampling EMSCRIPTEN_KEEPALIVE emscripten_enum_PatternSampling_X() {
		return mud::PatternSampling::X;
	}
	mud::PatternSampling EMSCRIPTEN_KEEPALIVE emscripten_enum_PatternSampling_XY() {
		return mud::PatternSampling::XY;
	}
	mud::PatternSampling EMSCRIPTEN_KEEPALIVE emscripten_enum_PatternSampling_Depth() {
		return mud::PatternSampling::Depth;
	}
	
}


