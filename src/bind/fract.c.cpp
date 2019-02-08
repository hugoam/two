#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <fract/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Circlifier
	mud::Type* DECL mud_Circlifier__type() {
		return &mud::type<mud::Circlifier>();
	}
	mud::Circlifier* DECL mud_Circlifier__construct_1(mud::Image256* image) {
		return new mud::Circlifier(*image);
	}
	void DECL mud_Circlifier__destroy(mud::Circlifier* self) {
		delete self;
	}
	// Fract
	mud::Type* DECL mud_Fract__type() {
		return &mud::type<mud::Fract>();
	}
	mud::Fract* DECL mud_Fract__construct_0() {
		return new mud::Fract();
	}
	mud::Fract* DECL mud_Fract__construct_1(size_t num_tabs) {
		return new mud::Fract(num_tabs);
	}
	void DECL mud_Fract_generate_0(mud::Fract* self) {
		self->generate();
	}
	void DECL mud_Fract_generate_1(mud::Fract* self, size_t num_tabs) {
		self->generate(num_tabs);
	}
	void DECL mud_Fract_regen_0(mud::Fract* self) {
		self->regen();
	}
	void DECL mud_Fract_render_4(mud::Fract* self, const mud::Rect* rect, const mud::Pattern* pattern, mud::uvec2* resolution, mud::Image256* output_image) {
		self->render(*rect, *pattern, *resolution, *output_image);
	}
	void DECL mud_Fract_render_whole_3(mud::Fract* self, const mud::Pattern* pattern, mud::uvec2* resolution, mud::Image256* output_image) {
		self->render_whole(*pattern, *resolution, *output_image);
	}
	size_t DECL mud_Fract__get_nutabs(mud::Fract* self) {
		return self->m_num_tabs;
	}
	void DECL mud_Fract__set_nutabs(mud::Fract* self, size_t value) {
		self->m_num_tabs = value;
	}
	void DECL mud_Fract__destroy(mud::Fract* self) {
		delete self;
	}
	// FractSample
	mud::Type* DECL mud_FractSample__type() {
		return &mud::type<mud::FractSample>();
	}
	mud::FractSample* DECL mud_FractSample__construct_3(mud::Fract* fract, const mud::Rect* rect, mud::uvec2* resolution) {
		return new mud::FractSample(*fract, *rect, *resolution);
	}
	void DECL mud_FractSample_render_2(mud::FractSample* self, const mud::Pattern* pattern, mud::Image256* outputImage) {
		self->render(*pattern, *outputImage);
	}
	mud::Fract* DECL mud_FractSample__get_fract(mud::FractSample* self) {
		return &self->m_fract;
	}
	mud::Rect* DECL mud_FractSample__get_rect(mud::FractSample* self) {
		static mud::Rect temp;
		return (temp = self->m_rect, &temp);
	}
	void DECL mud_FractSample__set_rect(mud::FractSample* self, mud::Rect* value) {
		self->m_rect = *value;
	}
	mud::uvec2* DECL mud_FractSample__get_resolution(mud::FractSample* self) {
		static mud::uvec2 temp;
		return (temp = self->m_resolution, &temp);
	}
	void DECL mud_FractSample__set_resolution(mud::FractSample* self, mud::uvec2* value) {
		self->m_resolution = *value;
	}
	void DECL mud_FractSample__destroy(mud::FractSample* self) {
		delete self;
	}
	// FractTab
	mud::Type* DECL mud_FractTab__type() {
		return &mud::type<mud::FractTab>();
	}
	mud::FractTab* DECL mud_FractTab__construct_0() {
		return new mud::FractTab();
	}
	void DECL mud_FractTab__destroy(mud::FractTab* self) {
		delete self;
	}
	// Pattern
	mud::Type* DECL mud_Pattern__type() {
		return &mud::type<mud::Pattern>();
	}
	mud::Pattern* DECL mud_Pattern__construct_2(mud::Palette* palette, mud::PatternSampling sampling) {
		return new mud::Pattern(*palette, sampling);
	}
	mud::Pattern* DECL mud_Pattern__construct_3(mud::Palette* palette, mud::PatternSampling sampling, float precision) {
		return new mud::Pattern(*palette, sampling, precision);
	}
	mud::Pattern* DECL mud_Pattern__construct_4(mud::Palette* palette, mud::PatternSampling sampling, float precision, size_t step) {
		return new mud::Pattern(*palette, sampling, precision, step);
	}
	void DECL mud_Pattern__destroy(mud::Pattern* self) {
		delete self;
	}
	void DECL mud_generate_fract_3(mud::uvec2* resolution, const mud::Pattern* pattern, mud::Image256* output_image) {
		mud::generate_fract(*resolution, *pattern, *output_image);
	}
	// PatternSampling
	mud::PatternSampling DECL mud_PatternSampling_X() {
		return mud::PatternSampling::X;
	}
	mud::PatternSampling DECL mud_PatternSampling_XY() {
		return mud::PatternSampling::XY;
	}
	mud::PatternSampling DECL mud_PatternSampling_Depth() {
		return mud::PatternSampling::Depth;
	}
	
}


