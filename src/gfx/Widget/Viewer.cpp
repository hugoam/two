//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx/Widget/Viewer.h>

#include <ui/Render/Renderer.h>

#include <obj/Vector.h>

#include <gfx/Item.h>
#include <gfx/Camera.h>
#include <gfx/GfxSystem.h>
#include <gfx/RenderTarget.h>
#include <gfx/Renderer.h>
#include <gfx/Pipeline.h>
#include <gfx/Filter.h>

#include <ui/Frame/Frame.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Style/Styles.h>

#include <ui/Controller/Controller.h>
#include <ctx/InputEvent.h>
#include <ui/UiWindow.h>

#include <math/Math.h>

namespace mud
{
	ViewerStyles::ViewerStyles()
		: viewport("Viewer", styles().wedge, [](Layout& l) { l.m_opacity = OPAQUE; l.m_space = SHEET; } }, [](InkStyle& l) { l.m_empty = false; } })
		, viewport_fixed("ViewerFixed", viewport, [](Layout& l) { l.m_space = BLOCK; } }, [](InkStyle& l) { l.m_empty = false; } })
		//, skin_definitions["Viewer:modal"].set({ &InkStyle::m_border_colour, Colour::White });
		//, skin_definitions["Viewer:modal"].set({ &InkStyle::m_border_width, vec4(1.f) });
		, space_sheet("SpaceSheet", styles().root_sheet, [](Layout& l) { l.m_opacity = OPAQUE; l.m_flow = FREE; l.m_size = vec2(600.f, 450.f); } }, {})
	{}

	ViewerStyles& viewer_styles() { static ViewerStyles styles; return styles; }

	Viewer::Viewer(Widget* parent, void* identity, Scene& scene)
		: Widget(parent, identity)
		, m_scene(&scene)
		, m_context(as<GfxContext>(*parent->ui_window().m_context))
		, m_camera(&scene)
		, m_viewport(m_camera, scene)
		, m_pick_query()
	{
		this->init(viewer_styles().viewport);

		m_viewport.m_get_size = [&] { return uvec4(this->query_size()); };
		m_viewport.m_render = [&](Render& render) { this->render(render); };
		m_viewport.m_filters = &m_filters;

		m_custom_draw = [&](const Frame& frame, VgRenderer& renderer) { UNUSED(frame); this->blit(renderer); };

		m_context.m_viewports.push_back(&m_viewport);

		//this->take_focus();

		m_filters.m_tonemap.m_enabled = true;
	}

	Viewer::~Viewer()
	{
		vector_remove(m_context.m_viewports, &m_viewport);
	}

	void Viewer::update()
	{}

	void Viewer::render(Render& render)
	{
#ifndef MUD_PLATFORM_EMSCRIPTEN
		if(!m_picker)
			m_picker = make_unique<Picker>(m_scene->m_gfx_system, *m_context.m_target);

		m_picker->process(render, m_pick_query);

#if 0
		if(m_picker)
		{
			BlockCopy& copy = *m_scene->m_gfx_system.m_pipeline->block<BlockCopy>();
			vec4 source_rect = { Zero2, rect_size(vec4(m_pick_query.m_rect)) };
			vec4 target_rect = { vec2(0.f), vec2(render.m_target->m_size) * 0.33f };
			copy.submit_quad(*render.m_target, 251, BGFX_INVALID_HANDLE, m_picker->m_fbo_texture, { source_rect, target_rect, true });
		}
#endif
#endif
	}

	void Viewer::blit(VgRenderer& renderer)
	{
		renderer.begin_target();
		vec4 image_rect = { vec2(0.f), vec2(m_context.m_target->m_size) };
		if(bgfx::getCaps()->originBottomLeft)
			image_rect.w = -image_rect.w;
		renderer.draw_texture(m_context.m_vg_handle, { vec4(m_viewport.m_rect) }, image_rect);
		renderer.end_target();
	}

	vec4 Viewer::query_size()
	{
		m_position = m_frame.absolute_position();
		m_size = m_frame.m_size * m_frame.absolute_scale();
		return { m_position, m_size };
	}

    void Viewer::resize()
    {
		m_viewport.m_rect = uvec4(this->query_size());
    }

	Ray Viewer::mouse_ray()
	{
		return m_viewport.ray(this->root_sheet().m_mouse.m_last_pos);
	}

	void Viewer::pick_point(vec2 position, std::function<void(Item*)> callback, uint32_t mask)
	{
		Ray ray = m_viewport.ray(position);
		float fov = m_camera.m_fov / m_size.y;// / float(m_context.m_target->m_size.y);
		m_pick_query = { uvec4{ uvec2(position), uvec2(1U) }, ray, fov, m_camera.m_aspect, mask };
		m_pick_query.m_callback = callback;
	}

	void Viewer::pick_rectangle(vec4 rect, std::function<void(array<Item*>)> callback, uint32_t mask)
	{
		Ray ray = m_viewport.ray(rect_center(rect));
		float fov = m_camera.m_fov * rect_h(rect) / m_size.y;
		float aspect = rect_w(rect) / rect_h(rect);
		m_pick_query = { uvec4(rect), ray, fov, aspect, mask };
		m_pick_query.m_multi_callback = callback;
	}

	SceneViewer::SceneViewer(Widget* parent, void* identity)
		: Scene(as<GfxContext>(*parent->ui_window().m_context).m_gfx_system)
		, Viewer(parent, identity, *this)
	{}

	OrbitController::OrbitController(Viewer& viewer) : m_viewer(viewer) {}

	void OrbitController::process(Viewer& viewer)
	{
		//EventDispatch::process(viewer);

		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			if(mouse_event.m_deltaZ > 0)
				m_distance *= 0.75f;
			else
				m_distance *= 1.3f;
		}

		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseMiddle, EventType::Dragged))
		{
			m_yaw = fmod(m_yaw - 0.02f * mouse_event.m_delta.x, 2 * M_PI);
			m_pitch = fmod(m_pitch - 0.02f * mouse_event.m_delta.y, 2 * M_PI);
		}

		vec3 direction = rotate(quat(vec3{ m_pitch, m_yaw, 0.f }), -Z3);
		m_viewer.m_camera.m_node.m_position = m_position - direction * m_distance;
		m_viewer.m_camera.m_target.m_position = m_position;
	}

	FreeOrbitController::FreeOrbitController(Viewer& viewer) : OrbitController(viewer) {}

namespace ui
{
	Viewer& viewer(Widget& parent, Scene& scene)
	{
		return parent.child_args<Viewer, Scene&>(scene);
	}

	SceneViewer& scene_viewer(Widget& parent, const vec2& size)
	{
		SceneViewer& self = parent.sub<SceneViewer>(nullptr);
		if(self.once() && size != Zero2)
		{
			self.m_frame.m_content = size;
			self.m_frame.solver(viewer_styles().viewport_fixed);
			//dummy(self, size);
		}
		return self;
	}

	OrbitController& orbit_controller(Viewer& viewer)
	{
		if(!viewer.m_controller)
			viewer.m_controller = make_unique<OrbitController>(viewer);
		viewer.m_controller->process(viewer);
		return as<OrbitController>(*viewer.m_controller);
	}

namespace
{
	struct KeyMove
	{
		KeyCode key;
		vec3 velocity;
	};
}

	void free_orbit_control_key(Viewer& viewer, vec3& speed, const KeyMove& move)
	{
		if(viewer.key_event(move.key, EventType::Pressed))
			speed += move.velocity;
		if(viewer.key_event(move.key, EventType::Released))
			speed -= move.velocity;
	}

	FreeOrbitController& free_orbit_controller(Viewer& viewer)
	{
		if(!viewer.m_controller)
			viewer.m_controller = make_unique<FreeOrbitController>(viewer);

		FreeOrbitController& controller = as<FreeOrbitController>(*viewer.m_controller);
		controller.process(viewer);
		
		const KeyMove moves[8] =
		{
			{ KC_UP,   -Z3 * 2.f }, { KC_W,  -Z3 * 2.f },
			{ KC_DOWN,  Z3 * 2.f }, { KC_S,   Z3 * 2.f },
			{ KC_LEFT, -X3 * 1.f }, { KC_A,  -X3 * 1.f },
			{ KC_RIGHT, X3 * 1.f }, { KC_D,   X3 * 1.f },
		};

		for(const KeyMove& key_move : moves)
			free_orbit_control_key(viewer, controller.m_speed, key_move);

		vec3 velocity = rotate(quat(vec3{ controller.m_pitch, controller.m_yaw, 0.f }), controller.m_speed);
		controller.m_position += velocity;

		return controller;
	}
}
}
