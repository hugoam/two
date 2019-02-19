//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <02_camera/02_camera.h>
#include <03_materials/03_materials.h>

using namespace mud;

vec3 set_length(const vec3& vec, float length)
{
	return normalize(vec) * length;
}

class TrackballControls : public ViewerController
{
public:
	TrackballControls(Viewer& viewer)
		: m_target0(viewer.m_camera.m_target)
		, m_eye0(viewer.m_camera.m_eye)
		, m_up0(viewer.m_camera.m_up)
	{}

	TrackballControls(const vec3& eye, const vec3& target, const vec3& up)
	{
		// force an update at start
		//this->update(eye, target, up);

		m_target0 = target;
		m_eye0 = eye;
		m_up0 = up;
	}

	enum State { None = -1, Rotate = 0, Zoom = 1, Pan = 2, TouchRotate = 3, TouchZoomPan = 4 };

	bool m_enabled = true;

	float m_rotateSpeed = 1.0f;
	float m_zoomSpeed = 1.2f;
	float m_panSpeed = 0.3f;

	bool m_noRotate = false;
	bool m_noZoom = false;
	bool m_noPan = false;

	bool m_staticMoving = false;
	float m_dynamicDampingFactor = 0.2f;

	float m_minDistance = 0.f;
	float m_maxDistance = FLT_MAX;// Infinity;

	Key m_keys[3] = { Key::A, Key::S, Key::D };
	//m_keys = [65 /*A*/, 83 /*S*/, 68 /*D*/];

private:
	vec3 m_target = vec3(0.f);

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
	vec2 getMouseOnScreen(const vec2& rect, const vec2& pos)
	{
		return pos / rect;
	}

	vec2 getMouseOnCircle(const vec2& rect, const vec2& pos)
	{
		return {
			(pos.x - rect.x * 0.5f) / (rect.x * 0.5f),
			(rect.y + 2 * -pos.y / rect.x) // screen.width intentional
		};
	}

	void rotateCamera(vec3& eye, vec3& up)
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


	void zoomCamera()
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

	void panCamera(vec3& position, const vec3& up)
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
				m_panStart += mouseChange = m_panEnd - m_panStart;
			//*= m_dynamicDampingFactor));
		}
	}

	void checkDistances(vec3& position)
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
	};

	void process(Viewer& viewer)
	{
		Camera& camera = viewer.m_camera;
		this->update(viewer, camera.m_eye, camera.m_target, camera.m_up); // , camera.m_up);
	}

	void update(Widget& widget, vec3& eye, vec3& target, vec3& up)
	{
		m_to_eye = eye - m_target;

		if(!m_noRotate) this->rotateCamera(eye, up);
		if(!m_noZoom) this->zoomCamera();
		if(!m_noPan) this->panCamera(eye, up);

		eye = m_target + m_to_eye;

		this->checkDistances(eye);

		if(m_enabled == false) return;

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

		if(distance2(m_lastEye, eye) > FLT_EPSILON) // EPS)
		{
			//this->dispatchEvent(changeEvent);
			m_lastEye = eye;
		}

	};

	void reset(vec3& eye, vec3& target, vec3& up)
	{
		m_state = State::None;
		m_prevState = State::None;

		m_target = m_target0;
		eye = m_eye0;
		up = m_up0;

		m_to_eye = eye - m_target;

		target = m_target;

		m_lastEye = eye;
	};

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

};

namespace mud
{
namespace ui
{
	TrackballControls& trackball_control(Viewer& viewer)
	{
		if(!viewer.m_controller)
			viewer.m_controller = make_unique<TrackballControls>(viewer);
		viewer.m_controller->process(viewer);
		return as<TrackballControls>(*viewer.m_controller);
	}
}
}

void ex_02_camera(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);

#if 1
	Viewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);
	TrackballControls& controls = ui::trackball_control(viewer);

	controls.m_rotateSpeed = 1.0f;
	controls.m_zoomSpeed = 1.2f;
	controls.m_panSpeed = 0.8f;
	
	controls.m_noZoom = false;
	controls.m_noPan = false;
	
	controls.m_staticMoving = false;
	controls.m_dynamicDampingFactor = 0.15f;
	
	//controls.keys = [65, 83, 68];

	Scene& scene = *viewer.m_scene;

	static vector<Node3*> lights;

	static bool once = false;
	if(!once)
	{
		once = true;

		// MATERIALS

#if 0
		Texture* texture = app.m_gfx_system.textures().file("disturb.jpg");
		//texture.repeat.set( 20, 10 );
		//texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
		//texture.format = THREE.RGBFormat;

		Material& ground_material = app.m_gfx_system.materials().fetch("ground"); //new THREE.MeshPhongMaterial( { color: 0xffffff, map: texture } );
		Material& material = gfx::pbr_material(app.m_gfx_system, "object", from_rgba(0xffffff), 0.5f, 1.0f); //new THREE.MeshStandardMaterial( { color: 0xffffff, roughness: 0.5f, metalness: 1.0f } );

		// GROUND

		Model& model = app.m_gfx_system.fetch_symbol(Symbol(), Rect(), DrawMode::PLAIN); //new THREE.Mesh( new THREE.PlaneBufferGeometry( 800, 400, 2, 2 ), groundMaterial );
		Node3& node = gfx::nodes(scene) += Node3(vec3(0, -5, 0), quat(-c_pi / 2.f, 0, 0, 1)));
		gfx::items(scene) += Item(node, model, 0, &ground_material));
#endif

		// OBJECTS
		Material& material = gfx::pbr_material(app.m_gfx_system, "object", Colour(1.f));//, 0.5f, 1.0f); //new THREE.MeshStandardMaterial( { color: 0xffffff, roughness: 0.5f, metalness: 1.0f } );

		//var torus = Torus();
		Model& torus_model = app.m_gfx_system.fetch_symbol(Symbol(), Torus(1.f, 0.1f), DrawMode::PLAIN); //new THREE.TorusBufferGeometry( 1.5, 0.4, 8, 16 );

		for(int i = 0; i < 5000; i++) {

			float x = 400.f * (0.5f - random_scalar<float>());
			float y = 50.f * (0.5f - random_scalar<float>()) + 25;
			float z = 200.f * (0.5f - random_scalar<float>());

			float a = 3.14f * (0.5f - random_scalar<float>());
			float b = 3.14f * (0.5f - random_scalar<float>());

			uint32_t flags = ItemFlag::Default;// | ItemFlag::NoCull;
			Node3& n = gfx::nodes(scene).add(Node3(vec3(x, y, z), quat(a, b, 0, 1)));
			Item& it = gfx::items(scene).add(Item(n, torus_model, flags, &material));

			gfx::update_item_aabb(it);

			//Gnode& n = gfx::node(root, {}, vec3(x, y, z));
			//gfx::item(n, torus_model, 0, &material);
		}

		// LIGHTS

		float intensity = 2.5;
		float distance = 100;
		float decay = 2.0;

		uint32_t colours[] = { 0xff0040, 0x0040ff, 0x80ff80, 0xffaa00, 0x00ffaa, 0xff1100 };

		Sphere sphere = Sphere(0.25); //THREE.SphereBufferGeometry( 0.25, 16, 8 );
		Model& sphere_model = app.m_gfx_system.fetch_symbol(Symbol(), sphere, DrawMode::PLAIN);

		for(int i = 0; i < 6; ++i)
		{
			Material& m = gfx::unshaded_material(app.m_gfx_system, ("light" + to_string(i)).c_str(), from_rgba(colours[i])); //Material({ color: colours[i] }) );
			Node3& n = gfx::nodes(scene).add(Node3());
			Light& l = gfx::lights(scene).add(Light(n, LightType::Point, false));
			l.m_colour = from_rgba(colours[i]);
			l.m_energy = intensity;
			l.m_range = distance;
			//l.decay = decay;
			Item& it = gfx::items(scene).add(Item(n, sphere_model, 0, &m));
			UNUSED(it);

			lights.push_back(&n);
		}

		//Node3& direct_node = gfx::nodes(scene) += Node3());
		//Light& direct_light = gfx::lights(scene) += Light(direct_node, LightType::Direct)); //THREE.DirectionalLight( 0xffffff, 0.05 );
		//dlight.position.set( 0.5f, 1, 0 ).normalize();
	}

	//var scene = viewer.scene.begin();

	Gnode& root = viewer.m_scene->begin();

	Material& material = milky_white(app.m_gfx_system);

	//gfx::direct_light_node(root);
	gfx::radiance(root, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
	gfx::shape(root, Sphere(), Symbol(), 0U, &material);
	gfx::shape(root, Torus(1.f, 0.1f), Symbol(), 0U, &material);

	return;

	float coef0[] = { 0.7f, 0.3f, 0.7f, 0.3f, 0.3f, 0.7f };
	float coef1[] = { 0.3f, 0.7f, 0.5f, 0.5f, 0.5f, 0.5f };

	//var time = Date.now() * 0.00025;
	float d = 150;

	static float time = 0.f;
	time += 0.01f;

	for(int i = 0; i < 6; ++i)
	{
		vec2 pos = { sin(time * coef0[i]) * d, cos(time * coef1[i]) * d };
		lights[i]->m_transform = bxtranslation({ pos.x, 0.f, pos.y });
	}

#elif 1
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	static bool once = false;
	if(!once)
	{
		once = true;

		Program* pbr = app.m_gfx_system.programs().file("pbr/pbr");

		Material& c = app.m_gfx_system.materials().fetch("cube");
		c.m_program = pbr;
		c.m_pbr_block = MaterialPbr(Colour(1.f, 0.f, 1.f));
		c.m_base_block.m_cull_mode = CullMode::Front;

		Material& s = app.m_gfx_system.materials().fetch("sphere");
		s.m_program = pbr;
		s.m_pbr_block.m_enabled = true;
		//s.m_pbr_block = MaterialPbr(from_rgba(0xa0adaf));
	}

	Material& cube_material = app.m_gfx_system.materials().fetch("cube");
	Material& sphere_material = app.m_gfx_system.materials().fetch("sphere");

	auto light_source = [&](Gnode& parent, Colour color, vec3 pos, quat rot) -> Gnode&
	{
		float intensity = 1.5;
		float range = 20.f;

		Gnode& node = gfx::node(parent, {}, pos, rot);
		Light& light = gfx::light(node, LightType::Point, false, color, range, 0.4f);// intensity);
		Item& inner = gfx::shape(node, Sphere(0.3f), Symbol::plain(color * intensity));
		Item& outer = gfx::shape(node, Sphere(2.0f), Symbol::plain(Colour::White), 0U, &sphere_material);
		return node;
	};

	auto light_pos = [](float time) -> vec3
	{
		return vec3(sin(time * 0.6) * 9, sin(time * 0.7) * 9 + 5, sin(time * 0.8) * 9);
	};

	auto light_rot = [](float time) -> quat
	{
		return quat(vec3(time, 0.f, time));
	};

	Gnode& scene = viewer.m_scene.begin();

	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	double time = app.m_gfx_system.m_frame_time;//performance.now() * 0.001;
	vec3 pos0 = light_pos(time);
	quat rot0 = light_rot(time);
	Gnode& light0 = light_source(scene, from_rgba(0x0088ff), pos0, rot0);

	time += 10000;
	vec3 pos1 = light_pos(time);
	quat rot1 = light_rot(time);
	Gnode& light1 = light_source(scene, from_rgba(0xff8888), pos1, rot1);

	Box box = Cube(vec3(30.f));
	Gnode& node = gfx::node(scene, {}, Y3 * 10.f);
	gfx::shape(node, box, Symbol::plain(Colour::White), 0, &cube_material);

#else
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Material& material = milky_white(app.m_gfx_system);

	Gnode& scene = viewer.m_scene.begin();
	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
	gfx::shape(scene, Sphere(), Symbol(), 0U, &material);
#endif
}

#ifdef _02_CAMERA_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_02_camera(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif

