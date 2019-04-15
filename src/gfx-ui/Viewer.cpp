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
		, m_context(as<GfxWindow>(parent->ui_window().m_context))
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
			vec4 source_rect = { vec2(0.f), vec2(m_pick_query.m_rect.size) };
			vec4 target_rect = { vec2(0.f), vec2(render.m_target->m_size) * 0.33f };
			m_gfx.m_copy->quad(*render.m_target, 251, BGFX_INVALID_HANDLE, m_picker->m_fbo_texture, { source_rect, target_rect, true });
		}
#endif
	}

	void Viewer::blit(Vg& vg)
	{
		vg.begin_target();
		const vec2 target_size = vec2(m_context.m_size);
		vec4 image_rect = { vec2(0.f), target_size };
		if(bgfx::getCaps()->originBottomLeft)
			image_rect.w = -image_rect.w;
		vg.draw_texture(m_context.m_vg_handle, m_viewport.m_rect * target_size, image_rect);
		vg.end_target();
	}

	vec4 Viewer::query_rect()
	{
		m_position = m_frame.absolute_position();
		m_size = m_frame.m_size * m_frame.absolute_scale();
		const vec4 absolute = vec4(m_position, m_size);
		return absolute / vec2(m_context.m_size);
	}

    void Viewer::resize()
    {
		m_viewport.m_rect = this->query_rect();
    }

	Ray Viewer::mouse_ray(const vec2& pos)
	{
		float xNDC = (pos.x / m_size.x) * 2.0f - 1.0f;
		float yNDC = ((m_size.y - pos.y) / m_size.y) * 2.0f - 1.0f;
		return m_camera.ray(vec2(xNDC, yNDC));
	}

	Ray Viewer::mouse_ray()
	{
		vec2 pos = m_frame.local_position(this->ui().m_mouse.m_pos);
		//return m_viewport.ray(pos);
		return this->mouse_ray(pos);
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
		, m_scene(as<GfxWindow>(parent->ui_window().m_context).m_gfx)
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
	
	void make_safe(Polar& p)
	{
		float EPS = 0.000001f;
		p.phi = max(EPS, min(c_pi - EPS, p.phi));
	}

	Polar to_polar(const vec3& p)
	{
		const float radius = sqrt(sq(p.x) + sq(p.y) + sq(p.z));

		if(radius == 0.f)
			return { 0.f, 0.f, 0.f };
		else
		{
			const float theta = atan2(p.x, p.z);
			const float phi = acos(clamp(p.y / radius, -1.f, 1.f));
			return { theta, phi, radius };
		}
	}

	vec3 to_vec3(const Polar& p)
	{
		const float t = sin(p.phi) * p.radius;

		const float x = t * sin(p.theta);
		const float y = cos(p.phi) * p.radius;
		const float z = t * cos(p.theta);

		return vec3(x, y, z);
	}

	void OrbitControls::process(Viewer& viewer)
	{
		Camera& camera = viewer.m_camera;
		this->update(viewer, camera.m_fov, camera.m_eye, camera.m_target, camera.m_up, camera.m_view);
	}

	void OrbitControls::update(Widget& widget, float fov, vec3& eye, vec3& target, vec3& up, mat4& mat)
	{
		auto getAutoRotationAngle = [&]() -> float { return 2.f * c_pi / 60.f / 60.f * autoRotateSpeed; };

		auto getZoomScale = [&]() -> float { return pow(0.95f, zoomSpeed); };

		auto rotateLeft = [&](float angle) { sphericalDelta.theta -= angle; };
		auto rotateUp = [&](float angle) { sphericalDelta.phi -= angle; };

		auto panLeft = [&](float distance)
		{
			vec3 v = vec3(mat[0]); // get X column of objectMatrix
			v *= -distance;
			panOffset += v;
		};

		auto panUp = [&](float distance)
		{
			vec3 v = screenSpacePanning ?
				vec3(mat[1]) : cross(up, vec3(mat[0])); // get X column of objectMatrix
			v *= -distance;
			panOffset += v;
		};

		// deltaX and deltaY are in pixels; right and down are positive
		auto pan = [&](const vec2& delta) {

			bool perspective = true;
			if(perspective) {

				// perspective
				vec3 offset = eye - target;
				float targetDistance = length(offset);

				// half of the fov is center to top of screen
				targetDistance *= tan((fov / 2.f) * c_pi / 180.0);

				// we use only clientHeight here so aspect ratio does not distort speed
				panLeft(2 * delta.x * targetDistance / widget.m_frame.m_size.y); // , object.matrix);
				panUp(2 * delta.y * targetDistance / widget.m_frame.m_size.y); // , object.matrix);

			}
			else {

				// orthographic
				//panLeft(deltaX * (object.right - object.left) / object.zoom / element.clientWidth, object.matrix);
				//panUp(deltaY * (object.top - object.bottom) / object.zoom / element.clientHeight, object.matrix);

			}
		};

#if 1
		auto dollyIn = [&](float dollyScale) {

			bool perspective = true;
			if(perspective) {
				scale /= dollyScale;
			}
			else {
				//object.zoom = max(minZoom, min(maxZoom, object.zoom * dollyScale));
				//object.updateProjectionMatrix();
				zoomChanged = true;
			}
		};

		auto dollyOut = [&](float dollyScale) {

			bool perspective = true;
			if(perspective) {
				scale *= dollyScale;
			}
			else {
				//object.zoom = max(minZoom, min(maxZoom, object.zoom / dollyScale));
				//object.updateProjectionMatrix();
				zoomChanged = true;
			}
		};
#endif

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
		{
			bool mod = event.m_modifiers != InputMod::None;
			state = mod ? State::Pan : State::Rotate;
			if(enableRotate && state == State::Rotate)
				rotateStart = event.m_relative;
			else if(enablePan && state == State::Pan)
				panStart = event.m_relative;
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseMiddle, EventType::Pressed))
		{
			state = State::Dolly;
			if(enableZoom)
				dollyStart = event.m_relative;
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseRight, EventType::Pressed))
		{
			state = State::Pan;
			if(enablePan)
				panStart = event.m_relative;
		}

		auto handleMouseMoveRotate = [&](const MouseEvent& event) {

			rotateEnd = event.m_relative;
			rotateDelta = (rotateEnd - rotateStart) * rotateSpeed;

			rotateLeft(2 * c_pi * rotateDelta.x / widget.m_frame.m_size.y); // yes, height
			rotateUp(2 * c_pi * rotateDelta.y / widget.m_frame.m_size.y);

			rotateStart = rotateEnd;
		};

		auto handleMouseMoveDolly = [&](const MouseEvent& event) {

			dollyEnd = event.m_relative;

			dollyDelta = dollyEnd - dollyStart;

			if(dollyDelta.y > 0.f)
				dollyIn(getZoomScale());
			else if(dollyDelta.y < 0.f)
				dollyOut(getZoomScale());

			dollyStart = dollyEnd;
		};

		auto handleMouseMovePan = [&](const MouseEvent& event) {

			panEnd = event.m_relative;

			panDelta = (panEnd - panStart) * panSpeed;

			pan(panDelta);

			panStart = panEnd;
		};

		if(MouseEvent event = widget.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			if(state == State::Rotate && enableRotate)
			{
				handleMouseMoveRotate(event);
			}
			else if(state == State::Dolly && enableZoom)
			{
				handleMouseMoveDolly(event);
			}
			else if(state == State::Pan && enablePan)
			{
				handleMouseMovePan(event);
			}
		}

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseLeft, EventType::Released))
			state = State::None;
		if(MouseEvent event = widget.mouse_event(DeviceType::MouseMiddle, EventType::Released))
			state = State::None;
		if(MouseEvent event = widget.mouse_event(DeviceType::MouseRight, EventType::Released))
			state = State::None;

		if(MouseEvent event = widget.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
		{
			if(enabled == false || enableZoom == false || (state != State::None && state != State::Rotate)) return;

			//dispatchEvent(startEvent);

			if(event.m_deltaZ < 0.f)
				dollyOut(getZoomScale() * abs(event.m_deltaZ));
			else if(event.m_deltaZ > 0)
				dollyIn(getZoomScale() * abs(event.m_deltaZ));

			//dispatchEvent(endEvent);
		}

			
		//var offset = vec3(0.f);
		//
		//// so camera.up is the orbit axis
		quat rotation = ZeroQuat;// new THREE.Quaternion().setFromUnitVectors(object.up, new vec3(0, 1, 0));
		quat invrotation = inverse(rotation); // quat.clone().inverse();

		//var position = object.position;

		vec3 offset = eye - target;

		// rotate offset to "y-axis-is-up" space
		offset = rotation * offset;

		// angle from z-axis around y-axis
		spherical = to_polar(offset);

		if(autoRotate && state == State::None)
			rotateLeft(getAutoRotationAngle());

		spherical.theta += sphericalDelta.theta;
		spherical.phi += sphericalDelta.phi;

		spherical.theta = max(minAzimuthAngle, min(maxAzimuthAngle, spherical.theta));
		spherical.phi = max(minPolarAngle, min(maxPolarAngle, spherical.phi));

		make_safe(spherical);

		spherical.radius *= scale;

		// restrict radius to be between desired limits
		spherical.radius = max(minDistance, min(maxDistance, spherical.radius));

		// move target to panned location
		target +=  panOffset;

		offset = to_vec3(spherical);

		// rotate offset back to "camera-up-vector-is-up" space
		offset = invrotation * offset;

		eye = target + offset;

		//object.lookAt(target);

		if(enableDamping == true) {

			sphericalDelta.theta *= (1.f - dampingFactor);
			sphericalDelta.phi *= (1.f - dampingFactor);

			panOffset *= 1.f - dampingFactor;

		}
		else {

			sphericalDelta = {};//vec3(0.f);

			panOffset = vec3(0.f);

		}

		scale = 1.f;
	}

#if 0
		
		function handleKeyDown( event ) {

			// console.log( 'handleKeyDown' );

			var needsUpdate = false;

			switch ( event.keyCode ) {

				case keys.UP:
					pan( 0, keyPanSpeed );
					needsUpdate = true;
					break;

				case keys.BOTTOM:
					pan( 0, - keyPanSpeed );
					needsUpdate = true;
					break;

				case keys.LEFT:
					pan( keyPanSpeed, 0 );
					needsUpdate = true;
					break;

				case keys.RIGHT:
					pan( - keyPanSpeed, 0 );
					needsUpdate = true;
					break;

			}

			if ( needsUpdate ) {

				// prevent the browser from scrolling on cursor keys
				event.preventDefault();

				update();

			}


		}

		function handleTouchStartRotate( event ) {

			//console.log( 'handleTouchStartRotate' );

			rotateStart.set( event.touches[ 0 ].pageX, event.touches[ 0 ].pageY );

		}

		function handleTouchStartDollyPan( event ) {

			//console.log( 'handleTouchStartDollyPan' );

			if ( enableZoom ) {

				var dx = event.touches[ 0 ].pageX - event.touches[ 1 ].pageX;
				var dy = event.touches[ 0 ].pageY - event.touches[ 1 ].pageY;

				var distance = sqrt( dx * dx + dy * dy );

				dollyStart.set( 0, distance );

			}

			if ( enablePan ) {

				var x = 0.5 * ( event.touches[ 0 ].pageX + event.touches[ 1 ].pageX );
				var y = 0.5 * ( event.touches[ 0 ].pageY + event.touches[ 1 ].pageY );

				panStart.set( x, y );

			}

		}

		function handleTouchMoveRotate( event ) {

			//console.log( 'handleTouchMoveRotate' );

			rotateEnd.set( event.touches[ 0 ].pageX, event.touches[ 0 ].pageY );

			rotateDelta.subVectors( rotateEnd, rotateStart ).multiplyScalar( rotateSpeed );

			var element = domElement === document ? domElement.body : domElement;

			rotateLeft( 2 * c_pi * rotateDelta.x / element.clientHeight ); // yes, height

			rotateUp( 2 * c_pi * rotateDelta.y / element.clientHeight );

			rotateStart.copy( rotateEnd );

			update();

		}

		function handleTouchMoveDollyPan( event ) {

			//console.log( 'handleTouchMoveDollyPan' );

			if ( enableZoom ) {

				var dx = event.touches[ 0 ].pageX - event.touches[ 1 ].pageX;
				var dy = event.touches[ 0 ].pageY - event.touches[ 1 ].pageY;

				var distance = sqrt( dx * dx + dy * dy );

				dollyEnd.set( 0, distance );

				dollyDelta.set( 0, pow( dollyEnd.y / dollyStart.y, zoomSpeed ) );

				dollyIn( dollyDelta.y );

				dollyStart.copy( dollyEnd );

			}

			if ( enablePan ) {

				var x = 0.5 * ( event.touches[ 0 ].pageX + event.touches[ 1 ].pageX );
				var y = 0.5 * ( event.touches[ 0 ].pageY + event.touches[ 1 ].pageY );

				panEnd.set( x, y );

				panDelta.subVectors( panEnd, panStart ).multiplyScalar( panSpeed );

				pan( panDelta.x, panDelta.y );

				panStart.copy( panEnd );

			}

			update();

		}

		function handleTouchEnd( event ) {

			//console.log( 'handleTouchEnd' );

		}

		function onKeyDown( event ) {

			if ( enabled === false || enableKeys === false || enablePan === false ) return;

			handleKeyDown( event );

		}

		function onTouchStart( event ) {

			if ( enabled === false ) return;

			event.preventDefault();

			switch ( event.touches.length ) {

				case 1:	// one-fingered touch: rotate

					if ( enableRotate === false ) return;

					handleTouchStartRotate( event );

					state = State::TOUCH_ROTATE;

					break;

				case 2:	// two-fingered touch: dolly-pan

					if ( enableZoom === false && enablePan === false ) return;

					handleTouchStartDollyPan( event );

					state = State::TOUCH_DOLLY_PAN;

					break;

				default:

					state = State::None;

			}

			if ( state !== State::None ) {

				dispatchEvent( startEvent );

			}

		}

		function onTouchMove( event ) {

			if ( enabled === false ) return;

			event.preventDefault();
			event.stopPropagation();

			switch ( event.touches.length ) {

				case 1: // one-fingered touch: rotate

					if ( enableRotate === false ) return;
					if ( state !== State::TOUCH_ROTATE ) return; // is this needed?

					handleTouchMoveRotate( event );

					break;

				case 2: // two-fingered touch: dolly-pan

					if ( enableZoom === false && enablePan === false ) return;
					if ( state !== State::TOUCH_DOLLY_PAN ) return; // is this needed?

					handleTouchMoveDollyPan( event );

					break;

				default:

					state = State::None;

			}

		}

		function onTouchEnd( event ) {

			if ( enabled === false ) return;

			handleTouchEnd( event );

			dispatchEvent( endEvent );

			state = State::None;

		}

		function onContextMenu( event ) {

			if ( enabled === false ) return;

			event.preventDefault();

		}

		// force an update at start

		this.update();
#endif

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
		vec3 moveDirection = vec3(m_moveCurr - m_movePrev, 0.f);
		float angle = length(moveDirection);

		if(angle)
		{
			m_to_eye = eye - m_target;

			vec3 upward = normalize(up);
			vec3 sideward = normalize(cross(upward, normalize(m_to_eye)));

			upward *= m_moveCurr.y - m_movePrev.y;
			sideward *= m_moveCurr.x - m_movePrev.x;

			moveDirection = upward + sideward;

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

		if(m_enabled == false) return;

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

		if(m_enabled == false) return;

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

		if(m_enabled == false) return;

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
		viewer.resize();
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
		self.resize();
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
			//if(viewer.m_hovered)
			//	select(selection, viewer.m_hovered->m_node->m_object);
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

	OrbitControls& orbit_controls(Viewer& viewer)
	{
		if(!viewer.m_controller)
			viewer.m_controller = make_unique<OrbitControls>();
		viewer.m_controller->process(viewer);
		return as<OrbitControls>(*viewer.m_controller);
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
			orbit.m_yaw = c_pi2;
			orbit.m_pitch = -c_pi2;
		}
		else
		{
			orbit.m_yaw = c_pi4;
			orbit.m_pitch = -c_pi4;
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
				angles.y = min(c_pi2 - 0.01f, max(-c_pi2 + 0.01f, angles.y));
			}
		}

		if(mode == Mode::ThirdPerson)
		{
			orbit.set_eye(aiming ? rotate(entity.m_rotation, X3, angles.y) : entity.m_rotation);
			aiming = true;
		}

		if(mode == Mode::PseudoIsometric)
		{
			orbit.m_pitch = -c_pi4;
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
