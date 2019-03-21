//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_geom_lines(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	constexpr size_t segments = 10000;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	//static Program& program = app.m_gfx.programs().fetch("line");
	static Program& program = app.m_gfx.programs().fetch("solid");

	static Node3* node = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 27.f; camera.m_near = 1.f; camera.m_far = 4000.f;
		camera.m_eye.z = 2750.f;
		
		Material& material = app.m_gfx.materials().create("lines", [](Material& m) {
			m.m_program = &program;
			m.m_base.m_shader_color = ShaderColor::Vertex;
		});

		MeshPacker geometry;
		geometry.m_primitive = PrimitiveType::Lines;

		float r = 800.f;

		for(size_t i = 0; i < segments; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * r - r / 2.f;
			Colour c = to_colour(p / r + 0.5f);

			geometry.position(p);
			geometry.colour(c);
		}

		Model& model = app.m_gfx.create_model_geo("lines", geometry);

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model, 0U, &material));
		UNUSED(it);
		node = &n;
	}

	const float time = app.m_gfx.m_time / 2.f; // * 0.001;

	vec3 angles = vec3(time * 0.25f, time * 0.5f, 0.f);
	node->apply(vec3(0.f), quat(angles));
}
