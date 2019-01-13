#include <infra/Api.h>
#include <tree/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Object
	void EMSCRIPTEN_KEEPALIVE Object___destroy__(mud::Object* self) {
		delete self;
	}
	// ViewerController
	void EMSCRIPTEN_KEEPALIVE ViewerController___destroy__(mud::ViewerController* self) {
		delete self;
	}
	// OrbitController
	void EMSCRIPTEN_KEEPALIVE OrbitController_set_eye_1(mud::OrbitController* self, const mud::quat* rotation) {
		self->set_eye(*rotation);
	}
	void EMSCRIPTEN_KEEPALIVE OrbitController_set_target_1(mud::OrbitController* self, const mud::vec3* position) {
		self->set_target(*position);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE OrbitController_get_position(mud::OrbitController* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE OrbitController_set_position(mud::OrbitController* self, mud::vec3* value) {
		self->m_position = *value;
	}
	float EMSCRIPTEN_KEEPALIVE OrbitController_get_yaw(mud::OrbitController* self) {
		return self->m_yaw;
	}
	void EMSCRIPTEN_KEEPALIVE OrbitController_set_yaw(mud::OrbitController* self, float value) {
		self->m_yaw = value;
	}
	float EMSCRIPTEN_KEEPALIVE OrbitController_get_pitch(mud::OrbitController* self) {
		return self->m_pitch;
	}
	void EMSCRIPTEN_KEEPALIVE OrbitController_set_pitch(mud::OrbitController* self, float value) {
		self->m_pitch = value;
	}
	float EMSCRIPTEN_KEEPALIVE OrbitController_get_distance(mud::OrbitController* self) {
		return self->m_distance;
	}
	void EMSCRIPTEN_KEEPALIVE OrbitController_set_distance(mud::OrbitController* self, float value) {
		self->m_distance = value;
	}
	void EMSCRIPTEN_KEEPALIVE OrbitController___destroy__(mud::OrbitController* self) {
		delete self;
	}
	// FreeOrbitController
	void EMSCRIPTEN_KEEPALIVE FreeOrbitController___destroy__(mud::FreeOrbitController* self) {
		delete self;
	}
	// SpaceSheet
	void EMSCRIPTEN_KEEPALIVE SpaceSheet___destroy__(mud::SpaceSheet* self) {
		delete self;
	}
	// Viewer
	mud::Scene* EMSCRIPTEN_KEEPALIVE Viewer_get_scene(mud::Viewer* self) {
		return self->m_scene;
	}
	void EMSCRIPTEN_KEEPALIVE Viewer_set_scene(mud::Viewer* self, mud::Scene* value) {
		self->m_scene = value;
	}
	mud::Viewport* EMSCRIPTEN_KEEPALIVE Viewer_get_viewport(mud::Viewer* self) {
		return &self->m_viewport;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Viewer_get_position(mud::Viewer* self) {
		static mud::vec2 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Viewer_set_position(mud::Viewer* self, mud::vec2* value) {
		self->m_position = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Viewer_get_size(mud::Viewer* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Viewer_set_size(mud::Viewer* self, mud::vec2* value) {
		self->m_size = *value;
	}
	void EMSCRIPTEN_KEEPALIVE Viewer___destroy__(mud::Viewer* self) {
		delete self;
	}
	// SceneViewer
	void EMSCRIPTEN_KEEPALIVE SceneViewer___destroy__(mud::SceneViewer* self) {
		delete self;
	}
	// OrbitMode
	mud::ui::OrbitMode EMSCRIPTEN_KEEPALIVE OrbitMode_ThirdPerson() {
		return mud::ui::OrbitMode::ThirdPerson;
	}
	mud::ui::OrbitMode EMSCRIPTEN_KEEPALIVE OrbitMode_Isometric() {
		return mud::ui::OrbitMode::Isometric;
	}
	mud::ui::OrbitMode EMSCRIPTEN_KEEPALIVE OrbitMode_PseudoIsometric() {
		return mud::ui::OrbitMode::PseudoIsometric;
	}
	
}


