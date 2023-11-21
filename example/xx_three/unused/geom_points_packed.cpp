module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

EX(xx_geom_points_packed)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	constexpr size_t particles = 500000;

	static Program& program = app.m_gfx.programs().fetch("solid");

	static Node3* node = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 27.f; camera.m_near = 5.f; camera.m_far = 3500.f;
		camera.m_eye.z = 2750.f;
		
		Material& material = app.m_gfx.materials().create("points", [](Material& m) {
			m.m_program = &program;
			m.m_base.m_shader_color = ShaderColor::Vertex;
			m.m_point.m_point_size = 15.f;
		});

		viewer.m_viewport.m_clear_colour = rgb(0x050505);
		scene.m_env.m_fog = { true, 1.f, rgb(0x050505), true, 2000.f, 3500.f };

		GpuMesh gpu_mesh = alloc_mesh(PrimitiveType::Points, VertexAttribute::Position | VertexAttribute::Colour, particles, 0);
		
		const float s = 1000.f; const float s2 = s / 2.f; // particles spread in the cube

		for(size_t i = 0; i < particles; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * s - s2;
			Colour c = to_colour(p / s + 0.5f);

			// 12 bytes = float3 position (xyz)
			// 4 bytes = uint32 color (rgba)

			gpu_mesh.m_writer.position(p);
			gpu_mesh.m_writer.colour(c);
		}

		Model& model = app.m_gfx.create_model_gpu("points", gpu_mesh);

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model, 0U, &material));
		node = &n;
		UNUSED(it);
	}

	const float time = app.m_gfx.m_time / 2.f;

	vec3 angles = vec3(time * 0.25f, time * 0.5f, 0.f);
	node->apply(vec3(0.f), quat(angles));

}