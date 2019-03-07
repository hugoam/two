//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.ui;
#else
#include <stl/algorithm.h>
#include <tree/Graph.hpp>
#include <math/Math.h>
#include <geom/Geom.hpp>
#include <geom/Intersect.h>
#include <ctx/InputEvent.h>
#include <ui/UiRenderer.h>
#include <ui/Frame/Frame.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/UiRoot.h>
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
#include <gfx-ui/Types.h>
#endif

namespace mud
{
	ViewerStyles::ViewerStyles()
		: viewer("Viewer", styles().wedge, [](Layout& l) { l.m_opacity = Opacity::Opaque; l.m_space = Preset::Sheet; }, [](InkStyle& l) { l.m_empty = false; })
		, viewer_fixed("ViewerFixed", viewer, [](Layout& l) { l.m_space = Preset::Block; l.m_align = { Align::Center, Align::Center }; l.m_padding = vec4(4.f); }, [](InkStyle& l) { l.m_empty = false; l.m_border_width = vec4(1.f); l.m_border_colour = Colour::MidGrey; })
		//, skin_definitions["Viewer:modal"].set({ &InkStyle::m_border_colour, Colour::White });
		//, skin_definitions["Viewer:modal"].set({ &InkStyle::m_border_width, vec4(1.f) });
		, space_sheet("SpaceSheet", styles().ui, [](Layout& l) { l.m_opacity = Opacity::Opaque; l.m_flow = LayoutFlow::Free; l.m_size = vec2(600.f, 450.f); })
	{}

	ViewerStyles& viewer_styles() { static ViewerStyles styles; return styles; }

	Viewer::Viewer(Widget* parent, void* identity, Scene& scene)
		: Widget(parent, identity)
		, m_scene(&scene)
		, m_context(as<GfxContext>(parent->ui_window().m_context))
		, m_camera()
		, m_viewport(m_camera, scene)
	{
		this->init(viewer_styles().viewer);

		m_viewport.m_tasks.push_back([&](Render& render) { this->render(render); });

		m_custom_draw = [&](const Frame& frame, const vec4& rect, Vg& vg)
		{
			UNUSED(frame); UNUSED(rect);
			//renderer.draw_frame(frame, rect);
			this->blit(vg);
		};

		m_context.m_viewports.push_back(&m_viewport);

		//this->take_focus();
	}

	Viewer::~Viewer()
	{
		remove(m_context.m_viewports, &m_viewport);
	}

	void Viewer::update()
	{}

	void Viewer::render(Render& render)
	{
		for(auto& picker : m_pickers)
		{
			picker->process(render, picker->m_query);
		}

//#define MUD_DEBUG_PICKER_TEXTURE
#ifdef MUD_DEBUG_PICKER_TEXTURE
		if(m_picker)
		{
			BlockCopy& copy = *m_scene->m_gfx.m_pipeline->block<BlockCopy>();
			vec4 source_rect = { vec2(0.f), rect_size(vec4(m_pick_query.m_rect)) };
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
		vec2 pos = m_frame.local_position(this->ui().m_mouse.m_pos);
		return m_viewport.ray(pos);
	}

	Picker& Viewer::picker(size_t index)
	{
		if(m_pickers.size() <= index)
			m_pickers.resize(index + 1);
		if(!m_pickers[index])
			m_pickers[index] = make_unique<Picker>(m_scene->m_gfx, *m_context.m_target);
		return *m_pickers[index];
	}

	SceneViewer::SceneViewer(Widget* parent, void* identity)
		: Viewer(parent, identity, m_scene)
		, m_scene(as<GfxContext>(parent->ui_window().m_context).m_gfx)
	{}

	OrbitController::OrbitController(Viewer& viewer, float yaw, float pitch, float distance) : m_viewer(viewer), m_camera(viewer.m_camera), m_yaw(yaw), m_pitch(pitch), m_distance(distance) {}

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
			m_yaw = fmod(m_yaw - 0.02f * mouse_event.m_delta.x, c_2pi);
			m_pitch = fmod(m_pitch - 0.02f * mouse_event.m_delta.y, c_2pi);
		}

		this->update_eye();
	}

	void OrbitController::set_eye(const quat& rotation)
	{
		vec3 direction = rotate(rotation, -Z3);
		m_camera.m_eye = m_camera.m_target - direction * m_distance;
		//m_camera.m_target = m_position;
	}

	void OrbitController::set_target(const vec3& position)
	{
		m_camera.m_target = position;
		this->update_eye();
	}

	void OrbitController::update_eye()
	{
		quat rotation = quat({ m_pitch, m_yaw, 0.f });
		this->set_eye(rotation);
	}

	FreeOrbitController::FreeOrbitController(Viewer& viewer) : OrbitController(viewer) {}
	
	vec3 set_length(const vec3& vec, float length)
	{
		return normalize(vec) * length;
	}

	TrackballController::TrackballController(Viewer& viewer)
		: m_target0(viewer.m_camera.m_target)
		, m_eye0(viewer.m_camera.m_eye)
		, m_up0(viewer.m_camera.m_up)
	{}

	TrackballController::TrackballController(const vec3& eye, const vec3& target, const vec3& up)
	{
		// force an update at start
		//this->update(eye, target, up);

		m_target0 = target;
		m_eye0 = eye;
		m_up0 = up;
	}

	void TrackballController::rotateCamera(vec3& eye, vec3& up)
	{
		vec3 moveDirection = { m_moveCurr.x - m_movePrev.x, m_moveCurr.y - m_movePrev.y, 0 };
		float angle = length(moveDirection);

		if(angle)
		{
			m_to_eye = eye - m_target;

			vec3 eyeDirection = normalize(m_to_eye);
			vec3 objectUpDirection = normalize(up);
			vec3 objectSidewaysDirection = normalize(cross(objectUpDirection, eyeDirection));

			objectUpDirection = set_length(objectUpDirection, m_moveCurr.y - m_movePrev.y);
			objectSidewaysDirection = set_length(objectSidewaysDirection, m_moveCurr.x - m_movePrev.x);

			moveDirection = objectUpDirection + objectSidewaysDirection;

			vec3 axis = normalize(cross(moveDirection, m_to_eye));

			angle *= m_rotateSpeed;
			quat quaternion = axis_angle(axis, angle);

			m_to_eye = quaternion * m_to_eye;
			up = quaternion * up;

			m_lastAxis = axis;
			m_lastAngle = angle;
		}
		else if(!m_staticMoving && m_lastAngle)
		{
			m_lastAngle *= sqrt(1.f - m_dynamicDampingFactor);
			m_to_eye = eye - m_target;
			quat quaternion = axis_angle(m_lastAxis, m_lastAngle);
			m_to_eye = quaternion * m_to_eye;
			up = quaternion * up;
		}

		m_movePrev = m_moveCurr;
	}

	void TrackballController::zoomCamera()
	{
		if(m_state == State::TouchZoomPan)
		{
			float factor = m_touchZoomDistanceStart / m_touchZoomDistanceEnd;
			m_touchZoomDistanceStart = m_touchZoomDistanceEnd;
			m_to_eye *= factor;
		}
		else
		{
			float factor = 1.0f + (m_zoomEnd.y - m_zoomStart.y) * m_zoomSpeed;

			if(factor != 1.0f && factor > 0.0f)
				m_to_eye *= factor;

			if(m_staticMoving)
				m_zoomStart = m_zoomEnd;
			else
				m_zoomStart.y += (m_zoomEnd.y - m_zoomStart.y) * m_dynamicDampingFactor;
		}
	}

	void TrackballController::panCamera(vec3& position, const vec3& up)
	{
		vec2 mouseChange = m_panEnd - m_panStart;

		if(length2(mouseChange))
		{
			mouseChange *= length(m_to_eye) * m_panSpeed;

			vec3 pan = set_length(cross(m_to_eye, up), mouseChange.x);
			pan += set_length(up, mouseChange.y);

			position += pan;
			m_target += pan;

			if(m_staticMoving)
				m_panStart = m_panEnd;
			else
				m_panStart += (m_panEnd - m_panStart) * m_dynamicDampingFactor;
		}
	}

	void TrackballController::checkDistances(vec3& position)
	{
		if(!m_noZoom || !m_noPan)
		{
			if(length2(m_to_eye) > sq(m_maxDistance))
			{
				position = m_target + set_length(m_to_eye, m_maxDistance);
				m_zoomStart = m_zoomEnd;
			}

			if(length2(m_to_eye) < sq(m_minDistance))
			{
				position = m_target + set_length(m_to_eye, m_minDistance);
				m_zoomStart = m_zoomEnd;
			}
		}
	}

	void TrackballController::process(Viewer& viewer)
	{
		Camera& camera = viewer.m_camera;
		this->update(viewer, camera.m_eye, camera.m_target, camera.m_up); // , camera.m_up);
	}

	void TrackballController::update(Widget& widget, vec3& eye, vec3& target, vec3& up)
	{
		m_to_eye = eye - m_target;

		if(!m_noRotate) this->rotateCamera(eye, up);
		if(!m_noZoom) this->zoomCamera();
		if(!m_noPan) this->panCamera(eye, up);

		eye = m_target + m_to_eye;

		this->checkDistances(eye);

		if(m_enabled == false) return;

		auto getMouseOnScreen = [](const vec2& rect, const vec2& pos) -> vec2
		{
			return pos / rect;
		};

		auto getMouseOnCircle = [](const vec2& rect, const vec2& pos) -> vec2
		{
			return {
				(pos.x - rect.x * 0.5f) / (rect.x * 0.5f),
				(rect.y + 2 * -pos.y / rect.x) // screen.width intentional
			};
		};

		if(m_state == State::None)
		{
			for(State state : { State::Rotate, State::Zoom, State::Pan })
			{
				if(KeyEvent event = widget.key_event(m_keys[state], EventType::Pressed))
				{
					m_state = state;
					m_prevState = m_state;
				}

				if(KeyEvent event = widget.key_event(m_keys[state], EventType::Released))
				{
					m_state = m_prevState;
				}
			}
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
		{
			m_state = State::Rotate;
			if(!m_noRotate)
			{
				m_moveCurr = getMouseOnCircle(widget.m_frame.m_size, event.m_relative);
				m_movePrev = m_moveCurr;
			}
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseMiddle, EventType::Pressed))
		{
			m_state = State::Zoom;
			if(!m_noZoom)
			{
				m_zoomStart = getMouseOnScreen(widget.m_frame.m_size, event.m_relative);
				m_zoomEnd = m_zoomStart;
			}
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseRight, EventType::Pressed))
		{
			m_state = State::Pan;
			if(!m_noPan)
			{
				m_panStart = getMouseOnScreen(widget.m_frame.m_size, event.m_relative);
				m_panEnd = m_panStart;
			}
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			if(m_state == State::Rotate && !m_noRotate)
			{
				m_movePrev = m_moveCurr;
				m_moveCurr = getMouseOnCircle(widget.m_frame.m_size, event.m_relative);
			}
			else if(m_state == State::Zoom && !m_noZoom)
			{
				m_zoomEnd = getMouseOnScreen(widget.m_frame.m_size, event.m_relative);
			}
			else if(m_state == State::Pan && !m_noPan)
			{
				m_panEnd = getMouseOnScreen(widget.m_frame.m_size, event.m_relative);
			}
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Released))
			m_state = State::None;
		if(MouseEvent event = widget.mouse_event(DeviceType::MouseMiddle, EventType::Released))
			m_state = State::None;
		if(MouseEvent event = widget.mouse_event(DeviceType::MouseRight, EventType::Released))
			m_state = State::None;

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			if(m_noZoom != true)
			{
				m_zoomStart.y += event.m_deltaZ * 0.025f;
			}

		}

		target = m_target;

		if(distance2(m_lastEye, eye) > c_cmp_epsilon) // FLT_EPSILON) // EPS)
		{
			//this->dispatchEvent(changeEvent);
			m_lastEye = eye;
		}

	}

	void TrackballController::reset(vec3& eye, vec3& target, vec3& up)
	{
		m_state = State::None;
		m_prevState = State::None;

		m_target = m_target0;
		eye = m_eye0;
		up = m_up0;

		m_to_eye = eye - m_target;

		target = m_target;

		m_lastEye = eye;
	}

	/*
	function touchstart(event) {

		if(m_enabled == = false) return;

		event.preventDefault();

		switch(event.touches.length) {

		case 1:
			m_state = State::TouchRotate;
			m_moveCurr = getMouseOnCircle(event.touches[0].pageX, event.touches[0].pageY));
			m_movePrev = m_moveCurr);
			break;

		default: // 2 or more
			m_state = State::TouchZoomPan;
			var dx = event.touches[0].pageX - event.touches[1].pageX;
			var dy = event.touches[0].pageY - event.touches[1].pageY;
			m_touchZoomDistanceEnd = m_touchZoomDistanceStart = sqrt(dx * dx + dy * dy);

			var x = (event.touches[0].pageX + event.touches[1].pageX) / 2;
			var y = (event.touches[0].pageY + event.touches[1].pageY) / 2;
			m_panStart = getMouseOnScreen(x, y));
			m_panEnd = m_panStart);
			break;

		}

		_m_dispatchEvent(startEvent);

	}

	function touchmove(event) {

		if(m_enabled == = false) return;

		event.preventDefault();
		event.stopPropagation();

		switch(event.touches.length) {

		case 1:
			m_movePrev = m_moveCurr);
			m_moveCurr = getMouseOnCircle(event.touches[0].pageX, event.touches[0].pageY));
			break;

		default: // 2 or more
			var dx = event.touches[0].pageX - event.touches[1].pageX;
			var dy = event.touches[0].pageY - event.touches[1].pageY;
			m_touchZoomDistanceEnd = sqrt(dx * dx + dy * dy);

			var x = (event.touches[0].pageX + event.touches[1].pageX) / 2;
			var y = (event.touches[0].pageY + event.touches[1].pageY) / 2;
			m_panEnd = getMouseOnScreen(x, y));
			break;

		}

	}

	function touchend(event) {

		if(m_enabled == = false) return;

		switch(event.touches.length) {

		case 0:
			m_state = State::None;
			break;

		case 1:
			m_state = State::TouchRotate;
			m_moveCurr = getMouseOnCircle(event.touches[0].pageX, event.touches[0].pageY));
			m_movePrev = m_moveCurr);
			break;

		}

		_m_dispatchEvent(endEvent);

	}
	*/

namespace ui
{
	Viewer& viewer(Widget& parent, Scene& scene)
	{
		Viewer& viewer = parent.subi<Viewer, Scene&>(&type<Viewer>(), scene);
		viewer.m_scene = viewer.m_viewport.m_scene = &scene;;
		viewer.m_viewport.m_rect = uvec4(viewer.query_size());
		//if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::None, false))
		//	viewer.take_focus();
		return viewer;
	}

#if 0
	Viewer& pbr_viewer(Widget& parent, Scene& scene)
	{
		viewer.m_filters = make_unique<RenderFilters>();
		viewer.m_viewport.m_filters = &viewer.m_filters;
		viewer.m_viewport.comp<Tonemap>().m_enabled = true;
	}
#endif

	SceneViewer& scene_viewer(Widget& parent, const vec2& size)
	{
		SceneViewer& self = parent.subi<SceneViewer>(&type<SceneViewer>());
		self.m_viewport.m_rect = uvec4(self.query_size());
		if(self.once() && size != vec2(0.f))
		{
			self.m_frame.m_content = size;
			self.m_frame.solver(viewer_styles().viewer_fixed);
			//dummy(self, size);
		}
		return self;
	}

	void viewport_picker(Viewer& viewer, Widget& widget, vector<Ref>& selection)
	{
		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::Mouse, EventType::Moved, InputMod::None, false))
		{
			auto callback = [&](Item* item) { viewer.m_hovered = item; };
			viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, callback, ItemFlag::Selectable);
		}

		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
		{
			if(viewer.m_hovered)
				select(selection, viewer.m_hovered->m_node->m_object);
		}

		if(MouseEvent mouse_event = widget.mouse_event(DeviceType::MouseRight, EventType::Stroked))
		{
			//Entity* entity = pick_entity(viewer, mouse_event.m_relative, ItemFlag::Selectable | ItemFlag::Static);
			//context_menu(viewer.m_vision.m_user.m_selector, *entity);
		}
	}

	Viewer& scene_viewport(Widget& parent, Scene& scene, Camera& camera, vector<Ref>& selection)
	{
		Viewer& viewer = parent.suba<Viewer, Scene&>(scene);
		if(viewer.once())
		{
			UNUSED(camera);
			//scene.m_cameras.push_back({ &camera, &viewer.m_camera });
			//viewer.m_controller = make_unique<RTSCameraController>(viewer, camera);
		}

		//viewer.m_controller->process(viewer);
		viewport_picker(viewer, viewer, selection);
		return viewer;
	}

	OrbitController& orbit_controller(Viewer& viewer, float yaw, float pitch, float distance)
	{
		if(!viewer.m_controller)
			viewer.m_controller = make_unique<OrbitController>(viewer, yaw, pitch, distance);
		viewer.m_controller->process(viewer);
		return as<OrbitController>(*viewer.m_controller);
	}

	TrackballController& trackball_controller(Viewer& viewer)
	{
		if(!viewer.m_controller)
			viewer.m_controller = make_unique<TrackballController>(viewer);
		viewer.m_controller->process(viewer);
		return as<TrackballController>(*viewer.m_controller);
	}

	FreeOrbitController& free_orbit_controller(Viewer& viewer)
	{
		if(!viewer.m_controller)
			viewer.m_controller = make_unique<FreeOrbitController>(viewer);

		FreeOrbitController& controller = as<FreeOrbitController>(*viewer.m_controller);
		controller.process(viewer);
		
		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::None, false))
			viewer.take_focus();

		struct KeyMove { Key key; vec3 velocity; };

		auto move_key = [](Viewer& viewer, vec3& speed, const KeyMove& move)
		{
			if(viewer.key_event(move.key, EventType::Pressed))
				speed += move.velocity;
			if(viewer.key_event(move.key, EventType::Released))
				speed += -move.velocity;
		};

		const KeyMove moves[12] =
		{
			{ Key::Up,   -Z3 * 2.f }, { Key::W,  -Z3 * 2.f },
			{ Key::Down,  Z3 * 2.f }, { Key::S,   Z3 * 2.f },
			{ Key::Left, -X3 * 1.f }, { Key::A,  -X3 * 1.f },
			{ Key::Right, X3 * 1.f }, { Key::D,   X3 * 1.f },
			{ Key::T,	  Y3 * 1.f }, { Key::Z,  -Y3 * 1.f },
			{ Key::G,	 -Y3 * 1.f }, { Key::X,   Y3 * 1.f },
		};

		for(const KeyMove& key_move : moves)
			move_key(viewer, controller.m_speed, key_move);

		vec3 velocity = rotate(quat({ controller.m_pitch, controller.m_yaw, 0.f }), controller.m_speed);
		controller.set_target(viewer.m_camera.m_target + velocity);

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

		orbit.update_eye();
		return orbit;
	}

	OrbitController& hybrid_controller(Viewer& viewer, OrbitMode mode, Transform& entity, bool& aiming, vec2& angles, bool modal)
	{
		UNUSED(modal);
		using Mode = OrbitMode;
		OrbitController& orbit = mode == Mode::Isometric ? ui::isometric_controller(viewer)
														 : ui::orbit_controller(viewer);

		orbit.set_target(entity.m_position + Y3 * 2.f);

		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked, InputMod::None, false))
		{
			if(!viewer.modal())
			{
				viewer.take_modal();

				if(mode == Mode::ThirdPerson || mode == Mode::PseudoIsometric)
				{
					if(!viewer.ui_window().m_context.m_mouse_lock)
						viewer.ui_window().m_context.lock_mouse(true);
				}
			}
		}

		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			const float rotation_speed = 1.f;
			vec2 angle = -mouse_event.m_delta / 250.f * rotation_speed;

			if(mode != Mode::ThirdPerson)
			{
				Ray ray = viewer.m_viewport.ray(mouse_event.m_relative);
				vec3 target = plane_segment_intersection(Plane(Y3, entity.m_position.y), to_segment(ray));
				if(mode == Mode::Isometric)
				{
					entity.m_rotation = look_at(entity.m_position, target);
				}
				else if(mode == Mode::PseudoIsometric)
				{
					entity.m_rotation = quat(vec3(0.f, orbit.m_yaw, 0.f));
					orbit.m_yaw += angle.x;
				}
			}
			else
			{
				entity.m_rotation = rotate(entity.m_rotation, Y3, angle.x);
				angles.y += angle.y;
				angles.y = min(c_pi / 2.f - 0.01f, max(-c_pi / 2.f + 0.01f, angles.y));
			}
		}

		if(mode == Mode::ThirdPerson)
		{
			orbit.set_eye(aiming ? rotate(entity.m_rotation, X3, angles.y) : entity.m_rotation);
			aiming = true;
		}

		if(mode == Mode::PseudoIsometric)
		{
			orbit.m_pitch = -c_pi / 4.f;
			orbit.update_eye();
		}

		if(viewer.key_event(Key::Escape, EventType::Stroked))
		{
			viewer.yield_modal();
			if(mode == Mode::ThirdPerson || mode == Mode::PseudoIsometric)
			{
				if(viewer.ui_window().m_context.m_mouse_lock)
					viewer.ui_window().m_context.lock_mouse(false);
			}
		}

		return orbit;
	}

	void velocity_controller(Viewer& viewer, vec3& linear, vec3& angular, float speed)
	{
		struct KeyMove { Key key; vec3 velocity; };

		auto velocity_key = [](Widget& widget, vec3& linear, vec3& angular, const KeyMove& move, float speed)
		{
			UNUSED(angular);
			if(widget.key_event(move.key, EventType::Pressed))
				linear += move.velocity * speed;
			if(widget.key_event(move.key, EventType::Released))
				linear -= move.velocity * speed;
		};

		//bool shift = viewer.ui().m_keyboard.m_shift;

		const KeyMove moves[8] =
		{
			{ Key::Up,    -Z3 }, { Key::W, -Z3 },
			{ Key::Down,   Z3 }, { Key::S,  Z3 },
			{ Key::Left,  -X3 }, { Key::A, -X3 },
			{ Key::Right,  X3 }, { Key::D,  X3 },
		};

		for(const KeyMove& key_move : moves)
			velocity_key(viewer, linear, angular, key_move, speed);
	}
}
}
