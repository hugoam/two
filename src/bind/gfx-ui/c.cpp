#include <infra/Api.h>
#include <tree/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Object
	void DECL mud_Object__destroy(mud::Object* self) {
		delete self;
	}
	// ViewerController
	void DECL mud_ViewerController__destroy(mud::ViewerController* self) {
		delete self;
	}
	// OrbitController
	void DECL mud_OrbitController_set_eye_1(mud::OrbitController* self, const mud::quat* rotation) {
		self->set_eye(*rotation);
	}
	void DECL mud_OrbitController_set_target_1(mud::OrbitController* self, const mud::vec3* position) {
		self->set_target(*position);
	}
	mud::vec3* DECL mud_OrbitController__get_position(mud::OrbitController* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void DECL mud_OrbitController__set_position(mud::OrbitController* self, mud::vec3* value) {
		self->m_position = *value;
	}
	float DECL mud_OrbitController__get_yaw(mud::OrbitController* self) {
		return self->m_yaw;
	}
	void DECL mud_OrbitController__set_yaw(mud::OrbitController* self, float value) {
		self->m_yaw = value;
	}
	float DECL mud_OrbitController__get_pitch(mud::OrbitController* self) {
		return self->m_pitch;
	}
	void DECL mud_OrbitController__set_pitch(mud::OrbitController* self, float value) {
		self->m_pitch = value;
	}
	float DECL mud_OrbitController__get_distance(mud::OrbitController* self) {
		return self->m_distance;
	}
	void DECL mud_OrbitController__set_distance(mud::OrbitController* self, float value) {
		self->m_distance = value;
	}
	void DECL mud_OrbitController__destroy(mud::OrbitController* self) {
		delete self;
	}
	// FreeOrbitController
	void DECL mud_FreeOrbitController__destroy(mud::FreeOrbitController* self) {
		delete self;
	}
	// SpaceSheet
	void DECL mud_SpaceSheet__destroy(mud::SpaceSheet* self) {
		delete self;
	}
	// Viewer
	mud::Scene* DECL mud_Viewer__get_scene(mud::Viewer* self) {
		return self->m_scene;
	}
	void DECL mud_Viewer__set_scene(mud::Viewer* self, mud::Scene* value) {
		self->m_scene = value;
	}
	mud::Viewport* DECL mud_Viewer__get_viewport(mud::Viewer* self) {
		return &self->m_viewport;
	}
	mud::vec2* DECL mud_Viewer__get_position(mud::Viewer* self) {
		static mud::vec2 temp;
		return (temp = self->m_position, &temp);
	}
	void DECL mud_Viewer__set_position(mud::Viewer* self, mud::vec2* value) {
		self->m_position = *value;
	}
	mud::vec2* DECL mud_Viewer__get_size(mud::Viewer* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void DECL mud_Viewer__set_size(mud::Viewer* self, mud::vec2* value) {
		self->m_size = *value;
	}
	void DECL mud_Viewer__destroy(mud::Viewer* self) {
		delete self;
	}
	// SceneViewer
	void DECL mud_SceneViewer__destroy(mud::SceneViewer* self) {
		delete self;
	}
	// OrbitMode
	mud::ui::OrbitMode DECL mud_ui_OrbitMode_ThirdPerson() {
		return mud::ui::OrbitMode::ThirdPerson;
	}
	mud::ui::OrbitMode DECL mud_ui_OrbitMode_Isometric() {
		return mud::ui::OrbitMode::Isometric;
	}
	mud::ui::OrbitMode DECL mud_ui_OrbitMode_PseudoIsometric() {
		return mud::ui::OrbitMode::PseudoIsometric;
	}
	
}


