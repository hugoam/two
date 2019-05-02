#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <fract/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Circlifier
	two::Type* DECL two_Circlifier__type() {
		return &two::type<two::Circlifier>();
	}
	two::Circlifier* DECL two_Circlifier__construct_1(two::Image256* image) {
		return new two::Circlifier(*image);
	}
	void DECL two_Circlifier__destroy(two::Circlifier* self) {
		delete self;
	}
	// Pattern
	two::Type* DECL two_Pattern__type() {
		return &two::type<two::Pattern>();
	}
	two::Pattern* DECL two_Pattern__construct_0() {
		return new two::Pattern();
	}
	two::Pattern* DECL two_Pattern__construct_2(two::Palette* palette, two::PatternSampling sampling) {
		return new two::Pattern(*palette, sampling);
	}
	two::Pattern* DECL two_Pattern__construct_3(two::Palette* palette, two::PatternSampling sampling, float precision) {
		return new two::Pattern(*palette, sampling, precision);
	}
	two::Pattern* DECL two_Pattern__construct_4(two::Palette* palette, two::PatternSampling sampling, float precision, size_t step) {
		return new two::Pattern(*palette, sampling, precision, step);
	}
	void DECL two_Pattern__destroy(two::Pattern* self) {
		delete self;
	}
	// FractTab
	two::Type* DECL two_FractTab__type() {
		return &two::type<two::FractTab>();
	}
	two::FractTab* DECL two_FractTab__construct_0() {
		return new two::FractTab();
	}
	void DECL two_FractTab__destroy(two::FractTab* self) {
		delete self;
	}
	// Fract
	two::Type* DECL two_Fract__type() {
		return &two::type<two::Fract>();
	}
	two::Fract* DECL two_Fract__construct_0() {
		return new two::Fract();
	}
	two::Fract* DECL two_Fract__construct_1(size_t num_tabs) {
		return new two::Fract(num_tabs);
	}
	void DECL two_Fract_generate_0(two::Fract* self) {
		self->generate();
	}
	void DECL two_Fract_generate_1(two::Fract* self, size_t num_tabs) {
		self->generate(num_tabs);
	}
	void DECL two_Fract_regen_0(two::Fract* self) {
		self->regen();
	}
	void DECL two_Fract_render_4(two::Fract* self, const two::Rect* rect, const two::Pattern* pattern, const two::uvec2* resolution, two::Image256* output_image) {
		self->render(*rect, *pattern, *resolution, *output_image);
	}
	void DECL two_Fract_render_whole_3(two::Fract* self, const two::Pattern* pattern, const two::uvec2* resolution, two::Image256* output_image) {
		self->render_whole(*pattern, *resolution, *output_image);
	}
	size_t DECL two_Fract__get_nutabs(two::Fract* self) {
		return self->m_num_tabs;
	}
	void DECL two_Fract__set_nutabs(two::Fract* self, size_t value) {
		self->m_num_tabs = value;
	}
	void DECL two_Fract__destroy(two::Fract* self) {
		delete self;
	}
	// FractSample
	two::Type* DECL two_FractSample__type() {
		return &two::type<two::FractSample>();
	}
	two::FractSample* DECL two_FractSample__construct_3(two::Fract* fract, const two::Rect* rect, two::uvec2* resolution) {
		return new two::FractSample(*fract, *rect, *resolution);
	}
	void DECL two_FractSample_render_2(two::FractSample* self, const two::Pattern* pattern, two::Image256* outputImage) {
		self->render(*pattern, *outputImage);
	}
	two::Fract* DECL two_FractSample__get_fract(two::FractSample* self) {
		return &self->m_fract;
	}
	two::Rect* DECL two_FractSample__get_rect(two::FractSample* self) {
		return &self->m_rect;
	}
	void DECL two_FractSample__set_rect(two::FractSample* self, two::Rect* value) {
		self->m_rect = *value;
	}
	two::uvec2* DECL two_FractSample__get_resolution(two::FractSample* self) {
		return &self->m_resolution;
	}
	void DECL two_FractSample__set_resolution(two::FractSample* self, two::uvec2* value) {
		self->m_resolution = *value;
	}
	void DECL two_FractSample__destroy(two::FractSample* self) {
		delete self;
	}
	void DECL two_generate_fract_3(two::uvec2* resolution, const two::Pattern* pattern, two::Image256* output_image) {
		two::generate_fract(*resolution, *pattern, *output_image);
	}
	// PatternSampling
	two::PatternSampling DECL two_PatternSampling_X() {
		return two::PatternSampling::X;
	}
	two::PatternSampling DECL two_PatternSampling_XY() {
		return two::PatternSampling::XY;
	}
	two::PatternSampling DECL two_PatternSampling_Depth() {
		return two::PatternSampling::Depth;
	}
	
}


