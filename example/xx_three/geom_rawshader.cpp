//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

static string vertex_shader()
{
	string shader =

		"$input a_position, a_color0\n"
		"$output v_position, v_color\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
		"{\n"
		"	v_position = vec4(a_position, 1.0);\n"
		"	v_color = a_color0;\n"
		"\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));\n"
		"}\n";

	return shader;
}

static string fragment_shader()
{
	string shader =

		"$input v_position, v_color\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec4 color = vec4(v_color);\n"
		"	color.r += sin(v_position.x * 10.0 + u_time) * 0.5;\n"
		"\n"
		"	gl_FragColor = color;\n"
		"}\n";

	return shader;
}

void xx_geom_rawshader(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	constexpr size_t triangles = 500;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Program program = { "shader" };
	program.m_blocks[MaterialBlock::Solid] = true;
	program.m_sources[ShaderType::Vertex] = vertex_shader();
	program.m_sources[ShaderType::Fragment] = fragment_shader();
	
	static Material& material = app.m_gfx.materials().create("material", [](Material& m) {
		m.m_program = &program;
		m.m_base.m_cull_mode = CullMode::None;
		m.m_base.m_blend_mode = BlendMode::Alpha;
		m.m_alpha.m_is_alpha = true;
	});

	static Node3* node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 10.f;
		camera.m_eye.z = 2.f;

		//scene.background = new THREE.Color(0x101010);

		MeshPacker geometry;

		for(size_t i = 0; i < triangles; i++)
		{
			const vec3 p = vec3(randf(), randf(), randf()) - 0.5f;
			const Colour c = Colour(randf(), randf(), randf(), randf()); // * 255
			geometry.position(p);
			geometry.colour(c);
		}

		Model& model = app.m_gfx.create_model_geo("model", geometry);
		
		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model, 0U, &material));
		UNUSED(it);
		node = &n;
	}

	const float time = app.m_gfx.m_time;

	vec3 angles = vec3(0.f, time * 0.2f, 0.f);
	node->apply(vec3(0.f), quat(angles));
}