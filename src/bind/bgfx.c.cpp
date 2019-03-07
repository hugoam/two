#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>
#include <bgfx/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// BgfxSystem
	mud::Type* DECL mud_BgfxSystem__type() {
		return &mud::type<mud::BgfxSystem>();
	}
	uint32_t DECL mud_BgfxSystem__get_frame(mud::BgfxSystem* self) {
		return self->m_frame;
	}
	void DECL mud_BgfxSystem__set_frame(mud::BgfxSystem* self, uint32_t value) {
		self->m_frame = value;
	}
	float DECL mud_BgfxSystem__get_time(mud::BgfxSystem* self) {
		return self->m_time;
	}
	void DECL mud_BgfxSystem__set_time(mud::BgfxSystem* self, float value) {
		self->m_time = value;
	}
	float DECL mud_BgfxSystem__get_frame_time(mud::BgfxSystem* self) {
		return self->m_frame_time;
	}
	void DECL mud_BgfxSystem__set_frame_time(mud::BgfxSystem* self, float value) {
		self->m_frame_time = value;
	}
	float DECL mud_BgfxSystem__get_delta_time(mud::BgfxSystem* self) {
		return self->m_delta_time;
	}
	void DECL mud_BgfxSystem__set_delta_time(mud::BgfxSystem* self, float value) {
		self->m_delta_time = value;
	}
	void DECL mud_BgfxSystem__destroy(mud::BgfxSystem* self) {
		delete self;
	}
	
}


