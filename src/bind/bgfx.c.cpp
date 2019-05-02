#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>
#include <bgfx/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// BgfxSystem
	two::Type* DECL two_BgfxSystem__type() {
		return &two::type<two::BgfxSystem>();
	}
	uint32_t DECL two_BgfxSystem__get_frame(two::BgfxSystem* self) {
		return self->m_frame;
	}
	void DECL two_BgfxSystem__set_frame(two::BgfxSystem* self, uint32_t value) {
		self->m_frame = value;
	}
	float DECL two_BgfxSystem__get_time(two::BgfxSystem* self) {
		return self->m_time;
	}
	void DECL two_BgfxSystem__set_time(two::BgfxSystem* self, float value) {
		self->m_time = value;
	}
	float DECL two_BgfxSystem__get_frame_time(two::BgfxSystem* self) {
		return self->m_frame_time;
	}
	void DECL two_BgfxSystem__set_frame_time(two::BgfxSystem* self, float value) {
		self->m_frame_time = value;
	}
	float DECL two_BgfxSystem__get_delta_time(two::BgfxSystem* self) {
		return self->m_delta_time;
	}
	void DECL two_BgfxSystem__set_delta_time(two::BgfxSystem* self, float value) {
		self->m_delta_time = value;
	}
	void DECL two_BgfxSystem__destroy(two::BgfxSystem* self) {
		delete self;
	}
	
}


