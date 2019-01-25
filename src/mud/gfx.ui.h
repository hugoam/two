#pragma once

#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/ui.h>
#include <mud/tree.h>
#include <mud/ecs.h>
#include <mud/math.h>
#include <mud/ctx.h>
#include <mud/infra.h>
#include <mud/type.h>





#ifndef MUD_GFX_UI_EXPORT
#define MUD_GFX_UI_EXPORT MUD_IMPORT
#endif

namespace mud
{
namespace ui
{
    enum class OrbitMode : int;
    
}
}

namespace mud
{
	class Object;
    class SpaceSheet;
    struct ViewerStyles;
    class ViewerController;
    class Viewer;
    class SceneViewer;
    class OrbitController;
    class FreeOrbitController;
    class SpaceViewport;
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	class SpaceQuad;

	export_ class refl_ MUD_GFX_UI_EXPORT SpaceSheet : public Ui
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

		float m_width;
		float m_height;

		unique<SpaceQuad> m_quad;

		float m_size_ratio;
	};
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::ui::OrbitMode>();
    
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::ViewerController>();
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::OrbitController>();
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::FreeOrbitController>();
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::SpaceSheet>();
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::Viewer>();
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::SceneViewer>();
    
    export_ template struct MUD_GFX_UI_EXPORT Typed<vector<mud::ViewerController*>>;
    export_ template struct MUD_GFX_UI_EXPORT Typed<vector<mud::OrbitController*>>;
    export_ template struct MUD_GFX_UI_EXPORT Typed<vector<mud::FreeOrbitController*>>;
    export_ template struct MUD_GFX_UI_EXPORT Typed<vector<mud::SpaceSheet*>>;
    export_ template struct MUD_GFX_UI_EXPORT Typed<vector<mud::Viewer*>>;
    export_ template struct MUD_GFX_UI_EXPORT Typed<vector<mud::SceneViewer*>>;
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ struct ViewerStyles
	{
		ViewerStyles();
		Style viewer; Style viewer_fixed; Style space_sheet;
	};

	export_ MUD_GFX_UI_EXPORT ViewerStyles& viewer_styles();

	export_ class refl_ MUD_GFX_UI_EXPORT ViewerController
	{
	public:
		virtual ~ViewerController() {}

		virtual void process(Viewer& viewer) = 0;
	};

	export_ class refl_ MUD_GFX_UI_EXPORT Viewer : public Widget
	{
	public:
		Viewer(Widget* parent, void* identity, Scene& scene);
		//Viewer(UiWindow& ui_window, Scene& scene);
		~Viewer();

		attr_ Scene* m_scene;
		GfxContext& m_context;

		Camera m_camera;
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
		vec4 query_size();

		Ray mouse_ray();

		Picker& picker(size_t index);
	};

	export_ class refl_ MUD_GFX_UI_EXPORT SceneViewer : public Scene, public Viewer
	{
	public:
		SceneViewer(Widget* parent, void* identity);
	};

	export_ class refl_ MUD_GFX_UI_EXPORT OrbitController : public ViewerController//, public EventDispatch
	{
	public:
		OrbitController(Viewer& viewer, float yaw = 0.f, float pitch = 0.f, float distance = 1.f);

		Viewer& m_viewer;
		Camera& m_camera;

		attr_ vec3 m_position = Zero3;
		attr_ float m_yaw = 0.f;
		attr_ float m_pitch = 0.f;
		attr_ float m_distance = 1.f;

		virtual void process(Viewer& viewer);

		meth_ void set_eye(const quat& rotation);
		meth_ void set_target(const vec3& position);

		void update_eye();
	};

	export_ class refl_ MUD_GFX_UI_EXPORT FreeOrbitController : public OrbitController
	{
	public:
		FreeOrbitController(Viewer& viewer);

		vec3 m_speed = Zero3;
	};

namespace ui
{
	export_ MUD_GFX_UI_EXPORT func_ Viewer& viewer(Widget& parent, Scene& scene);
	export_ MUD_GFX_UI_EXPORT func_ SceneViewer& scene_viewer(Widget& parent, const vec2& size = Zero2);

	enum class refl_ OrbitMode
	{
		ThirdPerson,
		Isometric,
		PseudoIsometric,
	};

	export_ MUD_GFX_UI_EXPORT func_ OrbitController& orbit_controller(Viewer& viewer, float yaw = c_pi / 4.f, float pitch = -c_pi / 4.f, float distance = 10.f);
	export_ MUD_GFX_UI_EXPORT func_ FreeOrbitController& free_orbit_controller(Viewer& viewer);
	export_ MUD_GFX_UI_EXPORT func_ OrbitController& isometric_controller(Viewer& viewer, bool topdown = false);
	export_ MUD_GFX_UI_EXPORT func_ OrbitController& hybrid_controller(Viewer& viewer, OrbitMode mode, Transform& entity, bool& aiming, vec2& angles, bool modal = false);

	export_ MUD_GFX_UI_EXPORT func_ void velocity_controller(Viewer& viewer, vec3& linear, vec3& angular, float speed = 1.f);
}
}



namespace mud
{
	export_ class MUD_GFX_UI_EXPORT SpaceViewport : public Viewer
	{
	public:
		SpaceViewport(Widget* parent, void* identity, Scene& scene);

		virtual ControlNode* control_event(InputEvent& inputEvent);
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	MUD_GFX_UI_EXPORT void viewport_picker(Viewer& viewer, Widget& widget, vector<Ref>& selection);

	MUD_GFX_UI_EXPORT Viewer& scene_viewport(Widget& parent, Scene& scene, Camera& camera, vector<Ref>& selection);
}

