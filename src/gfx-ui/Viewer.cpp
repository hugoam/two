//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.ui;
#else
#include <infra/Vector.h>
#include <math/Math.h>
#include <ctx/InputEvent.h>
#include <ui/Render/Renderer.h>
#include <ui/Frame/Frame.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Style/Styles.h>
#include <ui/Controller/Controller.h>
#include <ui/UiWindow.h>
#include <gfx/Item.h>
#include <gfx/Camera.h>
#include <gfx/GfxSystem.h>
#include <gfx/RenderTarget.h>
#include <gfx/Renderer.h>
#include <gfx/Pipeline.h>
#include <gfx/Filter.h>
#include <gfx-ui/Viewer.h>
#endif

namespace mud
{
	ViewerStyles::ViewerStyles()
		: viewer("Viewer", styles().wedge, [](Layout& l) { l.m_opacity = OPAQUE; l.m_space = SHEET; }, [](InkStyle& l) { l.m_empty = false; })
		, viewer_fixed("ViewerFixed", viewer, [](Layout& l) { l.m_space = BLOCK; l.m_align = { CENTER, CENTER }; l.m_padding = vec4(4.f); }, [](InkStyle& l) { l.m_empty = false; l.m_border_width = vec4(1.f); l.m_border_colour = Colour::MidGrey; })
		//, skin_definitions["Viewer:modal"].set({ &InkStyle::m_border_colour, Colour::White });
		//, skin_definitions["Viewer:modal"].set({ &InkStyle::m_border_width, vec4(1.f) });
		, space_sheet("SpaceSheet", styles().root_sheet, [](Layout& l) { l.m_opacity = OPAQUE; l.m_flow = FREE; l.m_size = vec2(600.f, 450.f); })
	{}

	ViewerStyles& viewer_styles() { static ViewerStyles styles; return styles; }

	Viewer::Viewer(Widget* parent, void* identity, Scene& scene)
		: Widget(parent, identity)
		, m_scene(&scene)
		, m_context(as<GfxContext>(parent->ui_window().m_context))
		, m_camera(&scene)
		, m_viewport(m_camera, scene)
		, m_pick_query()
	{
		this->init(viewer_styles().viewer);

#ifndef MUD_MODULES // @todo clang bug
		m_viewport.m_get_size = [&] { return uvec4(this->query_size()); };
		m_viewport.m_render = [&](Render& render) { this->render(render); };
		m_viewport.m_filters = &m_filters;

		m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			//renderer.draw_frame(frame, rect);
			this->blit(vg);
		};
#endif

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
		if(m_pick_query)
		{
			if(!m_picker)
				m_picker = make_unique<Picker>(m_scene->m_gfx_system, *m_context.m_target);

			m_picker->process(render, m_pick_query);
		}

//#define MUD_DEBUG_PICKER_TEXTURE
#ifdef MUD_DEBUG_PICKER_TEXTURE
		if(m_picker)
		{
			BlockCopy& copy = *m_scene->m_gfx_system.m_pipeline->block<BlockCopy>();
			vec4 source_rect = { Zero2, rect_size(vec4(m_pick_query.m_rect)) };
			vec4 target_rect = { vec2(0.f), vec2(render.m_target->m_size) * 0.33f };
			copy.submit_quad(*render.m_target, 251, BGFX_INVALID_HANDLE, m_picker->m_fbo_texture, { source_rect, target_rect, true });
		}
#endif
	}

	void Viewer::blit(Vg& vg)
	{
		vg.begin_target();
		vec4 image_rect = { vec2(0.f), vec2(m_context.m_target->m_size) };
		if(bgfx::getCaps()->originBottomLeft)
			image_rect.w = -image_rect.w;
		vg.draw_texture(m_context.m_vg_handle, { vec4(m_viewport.m_rect) }, image_rect);
		vg.end_target();
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
		vec2 pos = m_frame.local_position(this->root_sheet().m_mouse.m_pos);
		return m_viewport.ray(pos);
	}

	void Viewer::pick_point(vec2 position, std::function<void(Item*)> callback, uint32_t mask)
	{
		if(m_pick_query) return;
		Ray ray = m_viewport.ray(position);
		float fov = m_camera.m_fov / m_size.y;// / float(m_context.m_target->m_size.y);
		m_pick_query = { uvec4{ uvec2(position), uvec2(1U) }, ray, fov, m_camera.m_aspect, mask };
		m_pick_query.m_callback = callback;
	}

	void Viewer::pick_rectangle(vec4 rect, std::function<void(array<Item*>)> callback, uint32_t mask)
	{
		if(m_pick_query) return;
		Ray ray = m_viewport.ray(rect_center(rect));
		float fov = m_camera.m_fov * rect_h(rect) / m_size.y;
		float aspect = rect_w(rect) / rect_h(rect);
		m_pick_query = { uvec4(rect), ray, fov, aspect, mask };
		m_pick_query.m_multi_callback = callback;
	}

	SceneViewer::SceneViewer(Widget* parent, void* identity)
		: Scene(as<GfxContext>(parent->ui_window().m_context).m_gfx_system)
		, Viewer(parent, identity, *this)
	{}

	OrbitController::OrbitController(Viewer& viewer, float yaw, float pitch, float distance) : m_viewer(viewer), m_yaw(yaw), m_pitch(pitch), m_distance(distance) {}

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
			m_yaw = fmod(m_yaw - 0.02f * mouse_event.m_delta.x, 2.f * c_pi);
			m_pitch = fmod(m_pitch - 0.02f * mouse_event.m_delta.y, 2.f * c_pi);
		}

		this->update_position();
	}

	void OrbitController::update_position(const quat& rotation)
	{
		vec3 direction = rotate(rotation, -Z3);
		m_viewer.m_camera.m_node.m_position = m_position - direction * m_distance;
		m_viewer.m_camera.m_target.m_position = m_position;
	}

	void OrbitController::update_position()
	{
		quat rotation = quat(vec3{ m_pitch, m_yaw, 0.f });
		this->update_position(rotation);
	}

	void OrbitController::set_position(const vec3& position)
	{
		m_position = position;
		this->update_position();
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
			self.m_frame.solver(viewer_styles().viewer_fixed);
			//dummy(self, size);
		}
		return self;
	}

	OrbitController& orbit_controller(Viewer& viewer, float yaw, float pitch, float distance)
	{
		if(!viewer.m_controller)
			viewer.m_controller = make_unique<OrbitController>(viewer, yaw, pitch, distance);
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
			speed += -move.velocity;
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

	OrbitController& isometric_controller(Viewer& viewer, bool topdown)
	{
		OrbitController& orbit = orbit_controller(viewer);

		if(topdown)
		{
			orbit.m_yaw = c_pi / 2.f;
			orbit.m_pitch = -c_pi / 2.f;
		}
		else
		{
			orbit.m_yaw = c_pi / 4.f;
			orbit.m_pitch = -c_pi / 4.f;
		}

		orbit.update_position();
		return orbit;
	}
}
}
