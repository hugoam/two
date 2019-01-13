#include <infra/Api.h>
#include <tree/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>
#include <gfx/Api.h>
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
	// Object
	void EMSCRIPTEN_KEEPALIVE Object___destroy__(mud::Object* self) {
		delete self;
	}
	// ViewerController
	void EMSCRIPTEN_KEEPALIVE ViewerController___destroy__(mud::ViewerController* self) {
		delete self;
	}
	// OrbitController
	void EMSCRIPTEN_KEEPALIVE OrbitController_set_eye_1(mud::OrbitController* self, const quat rotation) {
		self->set_eye(*rotation);
	}
	void EMSCRIPTEN_KEEPALIVE OrbitController_set_target_1(mud::OrbitController* self, const vec3 position) {
		self->set_target(*position);
	}
	vec3 EMSCRIPTEN_KEEPALIVE OrbitController_get_position(mud::OrbitController* self) {
		return self->m_position;
	}
	float EMSCRIPTEN_KEEPALIVE OrbitController_get_yaw(mud::OrbitController* self) {
		return self->m_yaw;
	}
	float EMSCRIPTEN_KEEPALIVE OrbitController_get_pitch(mud::OrbitController* self) {
		return self->m_pitch;
	}
	float EMSCRIPTEN_KEEPALIVE OrbitController_get_distance(mud::OrbitController* self) {
		return self->m_distance;
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
	Scene EMSCRIPTEN_KEEPALIVE Viewer_get_scene(mud::Viewer* self) {
		return self->m_scene;
	}
	Viewport EMSCRIPTEN_KEEPALIVE Viewer_get_viewport(mud::Viewer* self) {
		return self->m_viewport;
	}
	vec2 EMSCRIPTEN_KEEPALIVE Viewer_get_position(mud::Viewer* self) {
		return self->m_position;
	}
	vec2 EMSCRIPTEN_KEEPALIVE Viewer_get_size(mud::Viewer* self) {
		return self->m_size;
	}
	void EMSCRIPTEN_KEEPALIVE Viewer___destroy__(mud::Viewer* self) {
		delete self;
	}
	// SceneViewer
	void EMSCRIPTEN_KEEPALIVE SceneViewer___destroy__(mud::SceneViewer* self) {
		delete self;
	}
	
}


// 'OrbitMode'
OrbitMode EMSCRIPTEN_KEEPALIVE emscripten_enum_OrbitMode_ThirdPerson() {
	return mud::ui::OrbitMode::ThirdPerson;
}
OrbitMode EMSCRIPTEN_KEEPALIVE emscripten_enum_OrbitMode_Isometric() {
	return mud::ui::OrbitMode::Isometric;
}
OrbitMode EMSCRIPTEN_KEEPALIVE emscripten_enum_OrbitMode_PseudoIsometric() {
	return mud::ui::OrbitMode::PseudoIsometric;
}
