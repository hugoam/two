//#include <two/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#include <cstdio>

using namespace two;

void xx_hierarchy(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	static Program& normal = app.m_gfx.programs().fetch("normal");

	static Node3* group = nullptr;
	struct Node { vec3 p; vec3 a; Node3* node; };
	static vector<Node> nodes;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye.z = 500.f;

		viewer.m_viewport.m_clear_colour = rgb(0xffffff);
		scene.m_env.m_fog = { true, 1.f, rgb(0xffffff), true, 1.f, 10000.f };

		Material& material = app.m_gfx.materials().create("hierarchy", [&](Material& m) {
			m.m_program = &normal;
		});

		Model& geometry = app.m_gfx.shape(Cube(50.f));

		Node3& node = gfx::nodes(scene).add(Node3());
		group = &node;

		nodes.clear();
		for(size_t i = 0; i < 1000; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * 2000.f - 1000.f;
			vec3 a = vec3(randf(), randf(), 0.f) * c_2pi;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a)));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
			nodes.push_back({ p, a, &n });
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

	for(Node& n : nodes)
	{
		n.node->derive(*group, n.p, quat(n.a));
	}
}