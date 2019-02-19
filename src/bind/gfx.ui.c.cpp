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
	
	// SpaceSheet
	mud::Type* DECL mud_SpaceSheet__type() {
		return &mud::type<mud::SpaceSheet>();
	}
	void DECL mud_SpaceSheet__destroy(mud::SpaceSheet* self) {
		delete self;
	}
	// Viewer
	mud::Type* DECL mud_Viewer__type() {
		return &mud::type<mud::Viewer>();
	}
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
		return &self->m_position;
	}
	void DECL mud_Viewer__set_position(mud::Viewer* self, mud::vec2* value) {
		self->m_position = *value;
	}
	mud::vec2* DECL mud_Viewer__get_size(mud::Viewer* self) {
		return &self->m_size;
	}
	void DECL mud_Viewer__set_size(mud::Viewer* self, mud::vec2* value) {
		self->m_size = *value;
	}
	void DECL mud_Viewer__destroy(mud::Viewer* self) {
		delete self;
	}
	// ViewerController
	mud::Type* DECL mud_ViewerController__type() {
		return &mud::type<mud::ViewerController>();
	}
	void DECL mud_ViewerController__destroy(mud::ViewerController* self) {
		delete self;
	}
	// OrbitController
	mud::Type* DECL mud_OrbitController__type() {
		return &mud::type<mud::OrbitController>();
	}
	void DECL mud_OrbitController_set_eye_1(mud::OrbitController* self, const mud::quat* rotation) {
		self->set_eye(*rotation);
	}
	void DECL mud_OrbitController_set_target_1(mud::OrbitController* self, const mud::vec3* position) {
		self->set_target(*position);
	}
	mud::vec3* DECL mud_OrbitController__get_position(mud::OrbitController* self) {
		return &self->m_position;
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
	mud::Type* DECL mud_FreeOrbitController__type() {
		return &mud::type<mud::FreeOrbitController>();
	}
	void DECL mud_FreeOrbitController__destroy(mud::FreeOrbitController* self) {
		delete self;
	}
	// SceneViewer
	mud::Type* DECL mud_SceneViewer__type() {
		return &mud::type<mud::SceneViewer>();
	}
	void DECL mud_SceneViewer__destroy(mud::SceneViewer* self) {
		delete self;
	}
	// TrackballController
	mud::Type* DECL mud_TrackballController__type() {
		return &mud::type<mud::TrackballController>();
	}
	void DECL mud_TrackballController__destroy(mud::TrackballController* self) {
		delete self;
	}
	mud::Viewer* DECL mud_ui_viewer_2(mud::Widget* parent, mud::Scene* scene) {
		return &mud::ui::viewer(*parent, *scene);
	}
	mud::SceneViewer* DECL mud_ui_scene_viewer_1(mud::Widget* parent) {
		return &mud::ui::scene_viewer(*parent);
	}
	mud::SceneViewer* DECL mud_ui_scene_viewer_2(mud::Widget* parent, const mud::vec2* size) {
		return &mud::ui::scene_viewer(*parent, *size);
	}
	mud::TrackballController* DECL mud_ui_trackball_controller_1(mud::Viewer* viewer) {
		return &mud::ui::trackball_controller(*viewer);
	}
	mud::OrbitController* DECL mud_ui_orbit_controller_1(mud::Viewer* viewer) {
		return &mud::ui::orbit_controller(*viewer);
	}
	mud::OrbitController* DECL mud_ui_orbit_controller_2(mud::Viewer* viewer, float yaw) {
		return &mud::ui::orbit_controller(*viewer, yaw);
	}
	mud::OrbitController* DECL mud_ui_orbit_controller_3(mud::Viewer* viewer, float yaw, float pitch) {
		return &mud::ui::orbit_controller(*viewer, yaw, pitch);
	}
	mud::OrbitController* DECL mud_ui_orbit_controller_4(mud::Viewer* viewer, float yaw, float pitch, float distance) {
		return &mud::ui::orbit_controller(*viewer, yaw, pitch, distance);
	}
	mud::FreeOrbitController* DECL mud_ui_free_orbit_controller_1(mud::Viewer* viewer) {
		return &mud::ui::free_orbit_controller(*viewer);
	}
	mud::OrbitController* DECL mud_ui_isometric_controller_1(mud::Viewer* viewer) {
		return &mud::ui::isometric_controller(*viewer);
	}
	mud::OrbitController* DECL mud_ui_isometric_controller_2(mud::Viewer* viewer, bool topdown) {
		return &mud::ui::isometric_controller(*viewer, topdown);
	}
	mud::OrbitController* DECL mud_ui_hybrid_controller_5(mud::Viewer* viewer, mud::ui::OrbitMode mode, mud::Transform* entity, bool aiming, mud::vec2* angles) {
		return &mud::ui::hybrid_controller(*viewer, mode, *entity, aiming, *angles);
	}
	mud::OrbitController* DECL mud_ui_hybrid_controller_6(mud::Viewer* viewer, mud::ui::OrbitMode mode, mud::Transform* entity, bool aiming, mud::vec2* angles, bool modal) {
		return &mud::ui::hybrid_controller(*viewer, mode, *entity, aiming, *angles, modal);
	}
	void DECL mud_ui_velocity_controller_3(mud::Viewer* viewer, mud::vec3* linear, mud::vec3* angular) {
		mud::ui::velocity_controller(*viewer, *linear, *angular);
	}
	void DECL mud_ui_velocity_controller_4(mud::Viewer* viewer, mud::vec3* linear, mud::vec3* angular, float speed) {
		mud::ui::velocity_controller(*viewer, *linear, *angular, speed);
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


