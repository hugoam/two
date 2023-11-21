module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

EX(xx_geom_lines)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	constexpr size_t segments = 10000;

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
		geometry.m_primitive = PrimitiveType::LineStrip;

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
