//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#include <ui/Structs/Widget.h>
#include <ui/Style/Style.h>
#include <gfx/Viewport.h>
#include <gfx/Picker.h>
#include <gfx/Camera.h>
#include <gfx/Scene.h>
#include <gfx/Graph.h>
#include <gfx-pbr/Filters/Tonemap.h>
#endif
#include <gfx-ui/Forward.h>

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

		std::vector<unique_ptr<Picker>> m_pickers;

		Ref m_selected;
		Ref m_hovered;

		RenderFilters m_filters;

		unique_ptr<ViewerController> m_controller;

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

	export_ MUD_GFX_UI_EXPORT func_ OrbitController& orbit_controller(Viewer& viewer, float yaw = 0.f, float pitch = 0.f, float distance = 1.f);
	export_ MUD_GFX_UI_EXPORT func_ FreeOrbitController& free_orbit_controller(Viewer& viewer);
	export_ MUD_GFX_UI_EXPORT func_ OrbitController& isometric_controller(Viewer& viewer, bool topdown = false);
	export_ MUD_GFX_UI_EXPORT func_ OrbitController& hybrid_controller(Viewer& viewer, OrbitMode mode, Transform& entity, bool& aiming, vec2& angles);

	export_ MUD_GFX_UI_EXPORT func_ void velocity_controller(Viewer& viewer, vec3& linear, vec3& angular, float speed = 1.f);
}
}
