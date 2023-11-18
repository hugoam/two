#pragma once

#include <two/gfx.h>
#include <two/geom.h>
#include <two/ui.h>
#include <two/tree.h>
#include <two/ecs.h>
#include <two/math.h>
#include <two/ctx.h>
#include <two/infra.h>
#include <two/type.h>




#ifndef TWO_GFX_UI_EXPORT
#define TWO_GFX_UI_EXPORT TWO_IMPORT
#endif

namespace two
{
namespace ui
{
    enum class OrbitMode : int;
    
}
}

namespace two
{
	class Object;
    class SpaceSheet;
    struct ViewerStyles;
    class ViewerController;
    class Viewer;
    class SceneViewer;
    class OrbitController;
    class TrackballController;
    class FreeOrbitController;
	class OrbitControls;
    class SpaceViewport;
}



namespace two
{
	class SpaceQuad;

	export_ class refl_ TWO_GFX_UI_EXPORT SpaceSheet : public Ui
	{
	public:
		SpaceSheet(Widget& parent, SpaceViewport& viewport);
		~SpaceSheet();

		void next_frame();

		void updateSize();

		void transformCoordinates(MouseEvent& mouse_event);

		virtual void receive_event(InputEvent& inputEvent);

	private:
		SpaceViewport& m_viewer;
		//GfxDynamicTexture& m_texture;

		vec2 m_size;

		unique<SpaceQuad> m_quad;

		float m_size_ratio;
	};
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif



namespace two
{
    // Exported types
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::ui::OrbitMode>();
    
    
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::SpaceSheet>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::ViewerController>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::Viewer>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::SceneViewer>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::OrbitController>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::TrackballController>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::OrbitControls>();
    export_ template <> TWO_GFX_UI_EXPORT Type& type<two::FreeOrbitController>();
}


namespace two
{
	export_ struct ViewerStyles
	{
		ViewerStyles();
		Style viewer; Style viewer_fixed; Style space_sheet;
	};

	export_ TWO_GFX_UI_EXPORT ViewerStyles& viewer_styles();

	export_ class refl_ TWO_GFX_UI_EXPORT ViewerController
	{
	public:
		virtual ~ViewerController() {}

		virtual void process(Viewer& viewer) = 0;
	};

	export_ class refl_ TWO_GFX_UI_EXPORT Viewer : public Widget
	{
	public:
		Viewer(Widget* parent, void* identity, Scene& scene);
		~Viewer();

		attr_ Scene* m_scene;
		GfxWindow& m_context;

		attr_ Camera m_camera;
		attr_ Viewport m_viewport;
		attr_ vec2 m_position;
		attr_ vec2 m_size;

		vector<unique<Picker>> m_pickers;

		Item* m_hovered = nullptr;

		unique<ViewerController> m_controller;

		void update();

		void render(Render& render);
		void blit(Vg& vg);

		void resize();
		vec4 query_rect();

		Ray mouse_ray();
		Ray mouse_ray(const vec2& pos);

		Picker& picker(size_t index);
	};

	export_ class refl_ TWO_GFX_UI_EXPORT SceneViewer : public Viewer
	{
	public:
		SceneViewer(Widget* parent, void* identity);

		Scene m_scene;
	};

	export_ class refl_ TWO_GFX_UI_EXPORT OrbitController : public ViewerController//, public EventDispatch
	{
	public:
		OrbitController(Viewer& viewer, float yaw = 0.f, float pitch = 0.f, float distance = 1.f);

		Viewer& m_viewer;
		Camera& m_camera;

		attr_ vec3 m_position = vec3(0.f);
		attr_ float m_yaw = 0.f;
		attr_ float m_pitch = 0.f;
		attr_ float m_distance = 1.f;

		virtual void process(Viewer& viewer);

		meth_ void set_eye(const quat& rotation);
		meth_ void set_target(const vec3& position);

		void update_eye();
	};

	export_ class refl_ TWO_GFX_UI_EXPORT TrackballController : public ViewerController
	{
	public:
		TrackballController(const vec3& eye, const vec3& target, const vec3& up);
		TrackballController(Viewer& viewer);

		enum State { None = -1, Rotate = 0, Zoom = 1, Pan = 2, TouchRotate = 3, TouchZoomPan = 4 };

		bool m_enabled = true;

		attr_ float m_rotateSpeed = 1.0f;
		attr_ float m_zoomSpeed = 1.2f;
		attr_ float m_panSpeed = 0.3f; // 0.8f

		bool m_noRotate = false;
		bool m_noZoom = false;
		bool m_noPan = false;

		attr_ bool m_staticMoving = false;
		attr_ float m_dynamicDampingFactor = 0.2f;

		attr_ float m_minDistance = 0.f;
		attr_ float m_maxDistance = FLT_MAX;// Infinity;

		Key m_keys[3] = { Key::A, Key::S, Key::D };
		//m_keys = [65 /*A*/, 83 /*S*/, 68 /*D*/];

		attr_ vec3 m_target = vec3(0.f);

	private:
		vec3 m_lastEye = vec3(0.f);

		State m_state = State::None;
		State m_prevState = State::None;

		vec3 m_to_eye = vec3(0.f);

		vec2 m_movePrev = vec2(0.f);
		vec2 m_moveCurr = vec2(0.f);

		vec3 m_lastAxis = vec3(0.f);
		float m_lastAngle = 0.f;

		vec2 m_zoomStart = vec2(0.f);
		vec2 m_zoomEnd = vec2(0.f);

		float m_touchZoomDistanceStart = 0.f;
		float m_touchZoomDistanceEnd = 0.f;

		vec2 m_panStart = vec2(0.f);
		vec2 m_panEnd = vec2(0.f);

		// for reset
		vec3 m_target0;
		vec3 m_eye0;
		vec3 m_up0;

	public:
		void rotateCamera(vec3& eye, vec3& up);
		void zoomCamera();
		void panCamera(vec3& position, const vec3& up);

		void checkDistances(vec3& position);

		void reset(vec3& eye, vec3& target, vec3& up);

		virtual void process(Viewer& viewer) override;
		void update(Widget& widget, vec3& eye, vec3& target, vec3& up);

	};

	// This set of controls performs orbiting, dollying (zooming), and panning.
	// Unlike TrackballControls, it maintains the "up" direction object.up (+Y by default).
	//
	//    Orbit - left mouse / touch: one-finger move
	//    Zoom - middle mouse, or mousewheel / touch: two-finger spread or squish
	//    Pan - right mouse, or left mouse + ctrl/meta/shiftKey, or arrow keys / touch: two-finger move

	struct Polar { float theta; float phi; float radius; };

	export_ class refl_ TWO_GFX_UI_EXPORT OrbitControls : public ViewerController
	{
	public:
		// Set to false to disable this control
		bool enabled = true;

		// "target" sets the location of focus, where the object orbits around
		//vec3 target = vec3(0.f);

		// How far you can dolly in and out ( PerspectiveCamera only )
		float minDistance = 0;
		float maxDistance = FLT_MAX; // Infinity;

		// How far you can zoom in and out ( OrthographicCamera only )
		float minZoom = 0;
		float maxZoom = FLT_MAX; // Infinity;

		// How far you can orbit vertically, upper and lower limits.
		// Range is 0 to c_pi radians.
		float minPolarAngle = 0; // radians
		float maxPolarAngle = c_pi; // radians

		// How far you can orbit horizontally, upper and lower limits.
		// If set, must be a sub-interval of the interval [ - c_pi, c_pi ].
		float minAzimuthAngle = -FLT_MAX; // -Infinity; // radians
		float maxAzimuthAngle = FLT_MAX; // Infinity; // radians

		// Set to true to enable damping (inertia)
		// If damping is enabled, you must call controls.update() in your animation loop
		bool enableDamping = false;
		float dampingFactor = 0.25;

		// This option actually enables dollying in and out; left as "zoom" for backwards compatibility.
		// Set to false to disable zooming
		bool enableZoom = true;
		float zoomSpeed = 1.0;

		// Set to false to disable rotating
		bool enableRotate = true;
		float rotateSpeed = 1.0;

		// Set to false to disable panning
		bool enablePan = true;
		float panSpeed = 1.0;
		bool screenSpacePanning = false; // if true, pan in screen-space
		float keyPanSpeed = 7.0;	// pixels moved per arrow key push

		// Set to true to automatically rotate around the target
		// If auto-rotate is enabled, you must call controls.update() in your animation loop
		bool autoRotate = false;
		float autoRotateSpeed = 2.0; // 30 seconds per round when fps is 60

		// Set to false to disable use of the keys
		bool enableKeys = true;

		// The four arrow keys
		//this.keys = { LEFT: 37, UP: 38, RIGHT: 39, BOTTOM: 40 };

		// Mouse buttons
		//this.mouseButtons = { LEFT: THREE.MOUSE.LEFT, MIDDLE: THREE.MOUSE.MIDDLE, RIGHT: THREE.MOUSE.RIGHT };

		virtual void process(Viewer& viewer) override;

		void update(Widget& widget, float fov, vec3& eye, vec3& target, vec3& up, mat4& mat);

	private:
		enum class State { None = -1, Rotate = 0, Dolly = 1, Pan = 2, TouchRotate = 3, TouchDollyPan = 4 };

		State state = State::None;

		float EPS = 0.000001f;

		// current position in spherical coordinates
		Polar spherical = {};
		Polar sphericalDelta = {};

		float scale = 1.f;
		vec3 panOffset = vec3(0.f);
		bool zoomChanged = false;

		vec2 rotateStart = vec2(0.f);
		vec2 rotateEnd = vec2(0.f);
		vec2 rotateDelta = vec2(0.f);

		vec2 panStart = vec2(0.f);
		vec2 panEnd = vec2(0.f);
		vec2 panDelta = vec2(0.f);

		vec2 dollyStart = vec2(0.f);
		vec2 dollyEnd = vec2(0.f);
		vec2 dollyDelta = vec2(0.f);
	};

	export_ class refl_ TWO_GFX_UI_EXPORT FreeOrbitController : public OrbitController
	{
	public:
		FreeOrbitController(Viewer& viewer);

		vec3 m_speed = vec3(0.f);
	};

namespace ui
{
	export_ TWO_GFX_UI_EXPORT func_ Viewer& viewer(Widget& parent, Scene& scene);
	export_ TWO_GFX_UI_EXPORT func_ SceneViewer& scene_viewer(Widget& parent, const vec2& size = vec2(0.f));

	export_ TWO_GFX_UI_EXPORT void viewport_picker(Viewer& viewer, Widget& widget, vector<Ref>& selection);
	export_ TWO_GFX_UI_EXPORT Viewer& scene_viewport(Widget& parent, Scene& scene, Camera& camera, vector<Ref>& selection);

	enum class refl_ OrbitMode
	{
		ThirdPerson,
		Isometric,
		PseudoIsometric,
	};

	export_ TWO_GFX_UI_EXPORT func_ TrackballController& trackball_controller(Viewer& viewer);
	export_ TWO_GFX_UI_EXPORT func_ OrbitControls& orbit_controls(Viewer& viewer);
	export_ TWO_GFX_UI_EXPORT func_ OrbitController& orbit_controller(Viewer& viewer, float yaw = c_pi4, float pitch = -c_pi4, float distance = 10.f);
	export_ TWO_GFX_UI_EXPORT func_ FreeOrbitController& free_orbit_controller(Viewer& viewer);
	export_ TWO_GFX_UI_EXPORT func_ OrbitController& isometric_controller(Viewer& viewer, bool topdown = false);
	export_ TWO_GFX_UI_EXPORT func_ OrbitController& hybrid_controller(Viewer& viewer, OrbitMode mode, Transform& entity, bool& aiming, vec2& angles, bool modal = false);

	export_ TWO_GFX_UI_EXPORT func_ void velocity_controller(Viewer& viewer, vec3& linear, vec3& angular, float speed = 1.f);
}
}



namespace two
{
	export_ class TWO_GFX_UI_EXPORT SpaceViewport : public Viewer
	{
	public:
		SpaceViewport(Widget* parent, void* identity, Scene& scene);

		virtual ControlNode* control_event(InputEvent& inputEvent);
	};
}

