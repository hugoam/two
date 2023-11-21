module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

static string vertex_shader =

	"$input a_position, a_color0\n"
	"$output v_position, v_color\n"
		
	"#include <common.sh>\n"
		
	"void main()\n"
	"{\n"
	"	v_position = vec4(a_position.xyz, 1.0);\n"
	"	v_color = a_color0;\n"
		
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string fragment_shader =

	"$input v_position, v_color\n"
		
	"#include <common.sh>\n"
		
	"void main()\n"
	"{\n"
	"	vec4 color = vec4(v_color);\n"
	"	color.r += sin(v_position.x * 10.0 + u_time) * 0.5;\n"
		
	"	gl_FragColor = color;\n"
	"}\n";

EX(xx_geom_rawshader)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	constexpr size_t triangles = 500;

	static Program& program = app.m_gfx.programs().create("rawshader");
	if(init)
	{
		program.set_block(MaterialBlock::Solid);
		program.set_source(ShaderType::Vertex, vertex_shader);
		program.set_source(ShaderType::Fragment, fragment_shader);
	}
	
	static Node3* node = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 10.f;
		camera.m_eye.z = 2.f;

		//scene.background = new THREE.Color(0x101010);
		
		Material& material = app.m_gfx.materials().create("rawshader", [](Material& m) {
			m.m_program = &program;
			m.m_base.m_cull_mode = CullMode::None;
			m.m_base.m_blend_mode = BlendMode::Alpha;
			m.m_alpha.m_is_alpha = true;
		});

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