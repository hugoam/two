//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_hierarchy(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Program& normal = app.m_gfx.programs().fetch("normal");

	static Material& material = app.m_gfx.materials().create("normal", [&](Material& m) {
		m.m_program = &normal;
	});

	static Node3* group = nullptr;
	static vector<Node3> nodes;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye.z = 500.f;

		//scene.background = new THREE.Color(0xffffff);
		//scene.fog = new THREE.Fog(0xffffff, 1, 10000);

		Model& geometry = app.m_gfx.shape(Cube(50.f));

		Node3& node = gfx::nodes(scene).add(Node3());
		group = &node;

		for(size_t i = 0; i < 1000; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * 2000.f - 1000.f;
			vec3 a = vec3(randf(), randf(), 0.f) * c_2pi;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a)));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
		}
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_frame.m_size / 2.f) * 10.f;
	}

	const float time = app.m_gfx.m_time;

	float rx = sin(time * 0.7f) * 0.5f;
	float ry = sin(time * 0.3f) * 0.5f;
	float rz = sin(time * 0.2f) * 0.5f;

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * 0.05f;
	camera.m_eye.y += (-mouse.y - camera.m_eye.y) * 0.05f;

	//camera.lookAt(scene.position);

	group->apply(vec3(0.f), quat(vec3(rx, ry, rz)));
}