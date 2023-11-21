module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

EX(xx_hierarchy2)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
	ControlNode& input = viewer;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
	ControlNode& input = window;
#endif

	static Program& normal = app.m_gfx.programs().fetch("normal");

	struct Node { Node3* parent; Node3* node; vec3 position; };
	static vector<Node> nodes;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 15000.f;
		camera.m_eye.z = 500.f;

		scene.m_env.m_background.m_colour = rgb(0xffffff);
		viewer.m_viewport.m_clear_colour = rgb(0xffffff);

		Material& material = app.m_gfx.materials().create("hierarchy2", [&](Material& m) {
			m.m_program = &normal;
		});

		Model& geometry = app.m_gfx.shape(Cube(50.f));

		Node3& root = gfx::nodes(scene).add(Node3(vec3(1000.f, 0.f, 0.f)));
		gfx::items(scene).add(Item(root, geometry, 0U, &material));

		constexpr size_t amount = 200;

		const vec3 offsets[] = { x3 * 100.f, x3 * -100.f, y3 * -100.f, y3 * 100.f, z3 * -100.f, z3 * 100.f };

		nodes.clear();
		for(const vec3& offset : offsets)
		{
			Node3* parent = &root;

			for(size_t i = 0; i < amount; i++)
			{
				Node3& object = gfx::nodes(scene).add(Node3(offset));
				gfx::items(scene).add(Item(object, geometry, 0U, &material));

				nodes.push_back({ parent, &object, offset });
				parent = &object;
			}
		}
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = input.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_size / 2.f) * 10.f;
	}


	const float time = app.m_gfx.m_time;

	float rx = sin(time * 0.7f) * 0.2f;
	float ry = sin(time * 0.3f) * 0.1f;
	float rz = sin(time * 0.2f) * 0.1f;

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * 0.05f;
	camera.m_eye.y += (-mouse.y - camera.m_eye.y) * 0.05f;

	//camera.lookAt(scene.position);

	for(size_t i = 0; i < nodes.size(); ++i)
	{
		vec3 rotation = vec3(rx, ry, rz);
		nodes[i].node->derive(*nodes[i].parent, nodes[i].position, quat(rotation));
	}
}
