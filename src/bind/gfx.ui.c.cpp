#include <infra/Api.h>
#include <tree/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// SpaceSheet
	two::Type* DECL two_SpaceSheet__type() {
		return &two::type<two::SpaceSheet>();
	}
	void DECL two_SpaceSheet__destroy(two::SpaceSheet* self) {
		delete self;
	}
	// ViewerController
	two::Type* DECL two_ViewerController__type() {
		return &two::type<two::ViewerController>();
	}
	void DECL two_ViewerController__destroy(two::ViewerController* self) {
		delete self;
	}
	// Viewer
	two::Type* DECL two_Viewer__type() {
		return &two::type<two::Viewer>();
	}
	two::Scene* DECL two_Viewer__get_scene(two::Viewer* self) {
		return self->m_scene;
	}
	void DECL two_Viewer__set_scene(two::Viewer* self, two::Scene* value) {
		self->m_scene = value;
	}
	two::Camera* DECL two_Viewer__get_camera(two::Viewer* self) {
		return &self->m_camera;
	}
	two::Viewport* DECL two_Viewer__get_viewport(two::Viewer* self) {
		return &self->m_viewport;
	}
	two::vec2* DECL two_Viewer__get_position(two::Viewer* self) {
		return &self->m_position;
	}
	void DECL two_Viewer__set_position(two::Viewer* self, two::vec2* value) {
		self->m_position = *value;
	}
	two::vec2* DECL two_Viewer__get_size(two::Viewer* self) {
		return &self->m_size;
	}
	void DECL two_Viewer__set_size(two::Viewer* self, two::vec2* value) {
		self->m_size = *value;
	}
	void DECL two_Viewer__destroy(two::Viewer* self) {
		delete self;
	}
	// SceneViewer
	two::Type* DECL two_SceneViewer__type() {
		return &two::type<two::SceneViewer>();
	}
	void DECL two_SceneViewer__destroy(two::SceneViewer* self) {
		delete self;
	}
	// OrbitController
	two::Type* DECL two_OrbitController__type() {
		return &two::type<two::OrbitController>();
	}
	void DECL two_OrbitController_set_eye_1(two::OrbitController* self, const two::quat* rotation) {
		self->set_eye(*rotation);
	}
	void DECL two_OrbitController_set_target_1(two::OrbitController* self, const two::vec3* position) {
		self->set_target(*position);
	}
	two::vec3* DECL two_OrbitController__get_position(two::OrbitController* self) {
		return &self->m_position;
	}
	void DECL two_OrbitController__set_position(two::OrbitController* self, two::vec3* value) {
		self->m_position = *value;
	}
	float DECL two_OrbitController__get_yaw(two::OrbitController* self) {
		return self->m_yaw;
	}
	void DECL two_OrbitController__set_yaw(two::OrbitController* self, float value) {
		self->m_yaw = value;
	}
	float DECL two_OrbitController__get_pitch(two::OrbitController* self) {
		return self->m_pitch;
	}
	void DECL two_OrbitController__set_pitch(two::OrbitController* self, float value) {
		self->m_pitch = value;
	}
	float DECL two_OrbitController__get_distance(two::OrbitController* self) {
		return self->m_distance;
	}
	void DECL two_OrbitController__set_distance(two::OrbitController* self, float value) {
		self->m_distance = value;
	}
	void DECL two_OrbitController__destroy(two::OrbitController* self) {
		delete self;
	}
	// TrackballController
	two::Type* DECL two_TrackballController__type() {
		return &two::type<two::TrackballController>();
	}
	float DECL two_TrackballController__get_rotateSpeed(two::TrackballController* self) {
		return self->m_rotateSpeed;
	}
	void DECL two_TrackballController__set_rotateSpeed(two::TrackballController* self, float value) {
		self->m_rotateSpeed = value;
	}
	float DECL two_TrackballController__get_zoomSpeed(two::TrackballController* self) {
		return self->m_zoomSpeed;
	}
	void DECL two_TrackballController__set_zoomSpeed(two::TrackballController* self, float value) {
		self->m_zoomSpeed = value;
	}
	float DECL two_TrackballController__get_panSpeed(two::TrackballController* self) {
		return self->m_panSpeed;
	}
	void DECL two_TrackballController__set_panSpeed(two::TrackballController* self, float value) {
		self->m_panSpeed = value;
	}
	bool DECL two_TrackballController__get_staticMoving(two::TrackballController* self) {
		return self->m_staticMoving;
	}
	void DECL two_TrackballController__set_staticMoving(two::TrackballController* self, bool value) {
		self->m_staticMoving = value;
	}
	float DECL two_TrackballController__get_dynamicDampingFactor(two::TrackballController* self) {
		return self->m_dynamicDampingFactor;
	}
	void DECL two_TrackballController__set_dynamicDampingFactor(two::TrackballController* self, float value) {
		self->m_dynamicDampingFactor = value;
	}
	float DECL two_TrackballController__get_minDistance(two::TrackballController* self) {
		return self->m_minDistance;
	}
	void DECL two_TrackballController__set_minDistance(two::TrackballController* self, float value) {
		self->m_minDistance = value;
	}
	float DECL two_TrackballController__get_maxDistance(two::TrackballController* self) {
		return self->m_maxDistance;
	}
	void DECL two_TrackballController__set_maxDistance(two::TrackballController* self, float value) {
		self->m_maxDistance = value;
	}
	two::vec3* DECL two_TrackballController__get_target(two::TrackballController* self) {
		return &self->m_target;
	}
	void DECL two_TrackballController__set_target(two::TrackballController* self, two::vec3* value) {
		self->m_target = *value;
	}
	void DECL two_TrackballController__destroy(two::TrackballController* self) {
		delete self;
	}
	// OrbitControls
	two::Type* DECL two_OrbitControls__type() {
		return &two::type<two::OrbitControls>();
	}
	void DECL two_OrbitControls__destroy(two::OrbitControls* self) {
		delete self;
	}
	// FreeOrbitController
	two::Type* DECL two_FreeOrbitController__type() {
		return &two::type<two::FreeOrbitController>();
	}
	void DECL two_FreeOrbitController__destroy(two::FreeOrbitController* self) {
		delete self;
	}
	two::Viewer* DECL two_ui_viewer_2(two::Widget* parent, two::Scene* scene) {
		return &two::ui::viewer(*parent, *scene);
	}
	two::SceneViewer* DECL two_ui_scene_viewer_1(two::Widget* parent) {
		return &two::ui::scene_viewer(*parent);
	}
	two::SceneViewer* DECL two_ui_scene_viewer_2(two::Widget* parent, const two::vec2* size) {
		return &two::ui::scene_viewer(*parent, *size);
	}
	two::TrackballController* DECL two_ui_trackball_controller_1(two::Viewer* viewer) {
		return &two::ui::trackball_controller(*viewer);
	}
	two::OrbitControls* DECL two_ui_orbit_controls_1(two::Viewer* viewer) {
		return &two::ui::orbit_controls(*viewer);
	}
	two::OrbitController* DECL two_ui_orbit_controller_1(two::Viewer* viewer) {
		return &two::ui::orbit_controller(*viewer);
	}
	two::OrbitController* DECL two_ui_orbit_controller_2(two::Viewer* viewer, float yaw) {
		return &two::ui::orbit_controller(*viewer, yaw);
	}
	two::OrbitController* DECL two_ui_orbit_controller_3(two::Viewer* viewer, float yaw, float pitch) {
		return &two::ui::orbit_controller(*viewer, yaw, pitch);
	}
	two::OrbitController* DECL two_ui_orbit_controller_4(two::Viewer* viewer, float yaw, float pitch, float distance) {
		return &two::ui::orbit_controller(*viewer, yaw, pitch, distance);
	}
	two::FreeOrbitController* DECL two_ui_free_orbit_controller_1(two::Viewer* viewer) {
		return &two::ui::free_orbit_controller(*viewer);
	}
	two::OrbitController* DECL two_ui_isometric_controller_1(two::Viewer* viewer) {
		return &two::ui::isometric_controller(*viewer);
	}
	two::OrbitController* DECL two_ui_isometric_controller_2(two::Viewer* viewer, bool topdown) {
		return &two::ui::isometric_controller(*viewer, topdown);
	}
	two::OrbitController* DECL two_ui_hybrid_controller_5(two::Viewer* viewer, two::ui::OrbitMode mode, two::Transform* entity, bool aiming, two::vec2* angles) {
		return &two::ui::hybrid_controller(*viewer, mode, *entity, aiming, *angles);
	}
	two::OrbitController* DECL two_ui_hybrid_controller_6(two::Viewer* viewer, two::ui::OrbitMode mode, two::Transform* entity, bool aiming, two::vec2* angles, bool modal) {
		return &two::ui::hybrid_controller(*viewer, mode, *entity, aiming, *angles, modal);
	}
	void DECL two_ui_velocity_controller_3(two::Viewer* viewer, two::vec3* linear, two::vec3* angular) {
		two::ui::velocity_controller(*viewer, *linear, *angular);
	}
	void DECL two_ui_velocity_controller_4(two::Viewer* viewer, two::vec3* linear, two::vec3* angular, float speed) {
		two::ui::velocity_controller(*viewer, *linear, *angular, speed);
	}
	// OrbitMode
	two::ui::OrbitMode DECL two_ui_OrbitMode_ThirdPerson() {
		return two::ui::OrbitMode::ThirdPerson;
	}
	two::ui::OrbitMode DECL two_ui_OrbitMode_Isometric() {
		return two::ui::OrbitMode::Isometric;
	}
	two::ui::OrbitMode DECL two_ui_OrbitMode_PseudoIsometric() {
		return two::ui::OrbitMode::PseudoIsometric;
	}
	
}


