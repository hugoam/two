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
	mud::Circlifier* EMSCRIPTEN_KEEPALIVE Circlifier_Circlifier_1(mud::Image256* image) {
		return new mud::Circlifier(*image);
	}
	void EMSCRIPTEN_KEEPALIVE Circlifier___destroy__(mud::Circlifier* self) {
		delete self;
	}
	// Fract
	mud::Fract* EMSCRIPTEN_KEEPALIVE Fract_Fract_0() {
		return new mud::Fract();
	}
	mud::Fract* EMSCRIPTEN_KEEPALIVE Fract_Fract_1(size_t num_tabs) {
		return new mud::Fract(num_tabs);
	}
	void EMSCRIPTEN_KEEPALIVE Fract_generate_0(mud::Fract* self) {
		self->generate();
	}
	void EMSCRIPTEN_KEEPALIVE Fract_generate_1(mud::Fract* self, size_t num_tabs) {
		self->generate(num_tabs);
	}
	void EMSCRIPTEN_KEEPALIVE Fract_regen_0(mud::Fract* self) {
		self->regen();
	}
	void EMSCRIPTEN_KEEPALIVE Fract_render_4(mud::Fract* self, const mud::Rect* rect, const mud::Pattern* pattern, mud::uvec2* resolution, mud::Image256* output_image) {
		self->render(*rect, *pattern, resolution, *output_image);
	}
	void EMSCRIPTEN_KEEPALIVE Fract_render_whole_3(mud::Fract* self, const mud::Pattern* pattern, mud::uvec2* resolution, mud::Image256* output_image) {
		self->render_whole(*pattern, resolution, *output_image);
	}
	size_t EMSCRIPTEN_KEEPALIVE Fract_get_nutabs(mud::Fract* self) {
		return self->m_num_tabs;
	}
	void EMSCRIPTEN_KEEPALIVE Fract___destroy__(mud::Fract* self) {
		delete self;
	}
	// FractSample
	mud::FractSample* EMSCRIPTEN_KEEPALIVE FractSample_FractSample_3(mud::Fract* fract, const mud::Rect* rect, mud::uvec2* resolution) {
		return new mud::FractSample(*fract, *rect, resolution);
	}
	void EMSCRIPTEN_KEEPALIVE FractSample_render_2(mud::FractSample* self, const mud::Pattern* pattern, mud::Image256* outputImage) {
		self->render(*pattern, *outputImage);
	}
	mud::Fract* EMSCRIPTEN_KEEPALIVE FractSample_get_fract(mud::FractSample* self) {
		return &self->m_fract;
	}
	mud::Rect* EMSCRIPTEN_KEEPALIVE FractSample_get_rect(mud::FractSample* self) {
		static mud::Rect temp;
		return (temp = self->m_rect, &temp);
	}
	mud::uvec2* EMSCRIPTEN_KEEPALIVE FractSample_get_resolution(mud::FractSample* self) {
		static mud::uvec2 temp;
		return (temp = self->m_resolution, &temp);
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
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_2(mud::Palette* palette, mud::PatternSampling sampling) {
		return new mud::Pattern(palette, sampling);
	}
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_3(mud::Palette* palette, mud::PatternSampling sampling, float precision) {
		return new mud::Pattern(palette, sampling, precision);
	}
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_4(mud::Palette* palette, mud::PatternSampling sampling, float precision, size_t step) {
		return new mud::Pattern(palette, sampling, precision, step);
	}
	mud::Pattern* EMSCRIPTEN_KEEPALIVE Pattern_Pattern_0() {
		return new mud::Pattern();
	}
	void EMSCRIPTEN_KEEPALIVE Pattern___destroy__(mud::Pattern* self) {
		delete self;
	}
	// PatternSampling
	mud::PatternSampling EMSCRIPTEN_KEEPALIVE PatternSampling_X() {
		return mud::PatternSampling::X;
	}
	mud::PatternSampling EMSCRIPTEN_KEEPALIVE PatternSampling_XY() {
		return mud::PatternSampling::XY;
	}
	mud::PatternSampling EMSCRIPTEN_KEEPALIVE PatternSampling_Depth() {
		return mud::PatternSampling::Depth;
	}
	
}


