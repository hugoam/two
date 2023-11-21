module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

#define GLITCH 0

static string vertex_shader =

	"$input a_position, a_texcoord0, i_data0\n"
	"$output v_uv0, v_scale\n"
		
	"#include <common.sh>\n"
		
	"void main()\n"
	"{\n"
	"   vec3 i_position = i_data0.xyz;"
	"	vec3 timexyz = i_position + vec3_splat(u_time / 2.0);\n"
	"	float scale =  sin(timexyz.x * 2.1) + sin(timexyz.y * 3.2) + sin(timexyz.z * 4.3);\n"
	"	v_scale = scale;\n"
	"	float size = scale * 10.0 + 10.0;\n"
	"	vec3 view = mul(u_modelView, vec4(i_position, 1.0)).xyz;\n"
	"	view += a_position.xyz * size;\n"
	"	v_uv0 = a_texcoord0;\n"
	"	gl_Position = mul(u_proj, vec4(view, 1.0));\n"
		
	"}\n";

static string fragment_shader =

	"$input v_uv0, v_scale\n"
		
	"#include <common.sh>\n"
	"#include <convert.sh>\n"
		
	"void main()\n"
	"{\n"
	"	vec4 color = texture2D(s_color, v_uv0);\n"
	"   vec3 hsl = hsl_to_rgb(vec3(v_scale / 5.0, 1.0, 0.5));\n"
	"	gl_FragColor = vec4(color.rgb * hsl.rgb, color.a);\n"
	"	if (color.a < 0.5) discard;\n"
	"}\n";

EX(xx_geom_sprites)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	constexpr size_t particles = 75000;

#if UI && GLITCH
	ui::orbit_controls(viewer);
#endif

	static Program& program = app.m_gfx.programs().create("sprites");
	if(init)
	{
		program.set_block(MaterialBlock::Solid);
		program.set_source(ShaderType::Vertex, vertex_shader);
		program.set_source(ShaderType::Fragment, fragment_shader);
	}

	static Texture& texture = *app.m_gfx.textures().file("sprites/circle.png");

	struct Instance { vec3 position; float distance; };
	static vector<Instance> instances(particles);

	static Node3* node = nullptr;
	static Batch* batch = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 5000.f;
		camera.m_eye.z = 1400.f;
		
		Material& material = app.m_gfx.materials().create("sprites", [](Material& m) {
			m.m_program = &program;
			m.m_base.m_depth_test = DepthTest::Enabled;
			m.m_base.m_depth_draw = DepthDraw::Enabled;
	#if !GLITCH
			m.m_solid.m_colour = &texture;
	#endif
		});

		// cool glitch
		Symbol symbol; symbol.m_subdiv = uvec2(6U);
#if GLITCH
		Model& circle = app.m_gfx.shape(Circle(), symbol);
#else
		Model& circle = app.m_gfx.shape(Circle(1.f, Axis::Z), symbol);
#endif

		for(size_t i = 0; i < particles; ++i)
		{
			instances[i] = { vec3(randf(), randf(), randf()) * 2.f - 1.f };
		}

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, circle, 0U, &material));
		node = &n;

		batch = &gfx::batches(scene).add(Batch(it, sizeof(Instance)));
		it.m_batch = batch;

		span<float> data = { &instances[0].position.x, instances.size() * sizeof(Instance) / sizeof(float) };
		batch->cache(data);
	}

	const float time = app.m_gfx.m_time / 2.f;

	vec3 scale = vec3(500.f);
	vec3 angles = vec3(time * 0.2f, time * 0.4f, 0.f);
	node->apply(vec3(0.f), quat(angles), scale);
}