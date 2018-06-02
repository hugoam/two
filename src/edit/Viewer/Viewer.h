//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <ui/Structs/Widget.h>
#include <ui/Style/Style.h>
#include <edit/Generated/Types.h>
#include <gfx/Viewport.h>
#include <gfx/Picker.h>
#include <gfx/Camera.h>
#include <gfx/Scene.h>
#include <gfx/Graph.h>
#include <gfx-pbr/Filters/Tonemap.h>

namespace mud
{
	struct ViewerStyles
	{
		ViewerStyles();
		Style viewer; Style viewer_fixed; Style space_sheet;
	};

	MUD_GFX_EXPORT ViewerStyles& viewer_styles();

	export_ class _refl_ MUD_GFX_EXPORT ViewerController
	{
	public:
		virtual ~ViewerController() {}

		virtual void process(Viewer& viewer) = 0;
	};

	export_ class _refl_ MUD_GFX_EXPORT Viewer : public Widget
	{
	public:
		Viewer(Widget* parent, void* identity, Scene& scene);
		//Viewer(UiWindow& ui_window, Scene& scene);
		~Viewer();

		_attr_ Scene* m_scene;
		GfxContext& m_context;

		Camera m_camera;
		_attr_ Viewport m_viewport;
		unique_ptr<Picker> m_picker;

		_attr_ vec2 m_position;
		_attr_ vec2 m_size;

		PickQuery m_pick_query;

		RenderFilters m_filters;

		unique_ptr<ViewerController> m_controller;

		void update();

		void render(Render& render);
		void blit(VgRenderer& renderer);

		void resize();
		vec4 query_size();

		Ray mouse_ray();

		void pick_point(vec2 position, std::function<void(Item*)> callback, uint32_t mask = UINT32_MAX);
		void pick_rectangle(vec4 rect, std::function<void(array<Item*>)> callback, uint32_t mask = UINT32_MAX);
	};

	export_ class _refl_ MUD_GFX_EXPORT SceneViewer : public Scene, public Viewer
	{
	public:
		SceneViewer(Widget* parent, void* identity);
	};

	class OrbitController : public ViewerController//, public EventDispatch
	{
	public:
		OrbitController(Viewer& viewer);

		Viewer& m_viewer;

		vec3 m_position = Zero3;
		float m_yaw = 0.f;
		float m_pitch = 0.f;
		float m_distance = 1.f;

		virtual void process(Viewer& viewer);
	};

	class FreeOrbitController : public OrbitController
	{
	public:
		FreeOrbitController(Viewer& viewer);

		vec3 m_speed = Zero3;
	};

namespace ui
{
	MUD_GFX_EXPORT _func_ Viewer& viewer(Widget& parent, Scene& scene);
	MUD_GFX_EXPORT _func_ SceneViewer& scene_viewer(Widget& parent, const vec2& size = Zero2);

	MUD_GFX_EXPORT OrbitController& orbit_controller(Viewer& viewer);
	MUD_GFX_EXPORT FreeOrbitController& free_orbit_controller(Viewer& viewer);
}
}
