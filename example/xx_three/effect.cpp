module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

// @author alteredq / http://alteredqualia.com/
// dot screen shader
// based on glfx.js sepia shader
// https://github.com/evanw/glfx.js

static string dotscreen_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"

	"#include <filter.sh>\n"

	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string dotscreen_fragment =

	"$input v_uv0\n"

	"#include <filter.sh>\n"

	"uniform vec4 u_dotscreen_p0;\n"
	"#define u_center u_dotscreen_p0.xy\n"
	"#define u_angle  u_dotscreen_p0.z\n"
	"#define u_scale  u_dotscreen_p0.w\n"

	"uniform vec4 u_dotscreen_p1;\n"
	"#define u_size u_dotscreen_p1.xy\n"

	"#define s_diffuse s_source_0\n"

	"float pattern(vec2 uv) {\n"
		"float s = sin(u_angle), c = cos(u_angle);\n"

		"vec2 tex = uv * u_size - u_center;\n"
		"vec2 p = vec2(c * tex.x - s * tex.y, s * tex.x + c * tex.y) * u_scale;\n"

		"return (sin(p.x) * sin(p.y)) * 4.0;\n"
	"}\n"

	"void main() {\n"

		"vec4 color = texture2D(s_diffuse, v_uv0);\n"

		"float average = (color.r + color.g + color.b) / 3.0;\n"

		"gl_FragColor = vec4(vec3_splat(average * 10.0 - 5.0 + pattern(v_uv0)), color.a);\n"

	"}\n";

// @author felixturner / http://airtight.cc/
// RGB Shift Shader
// Shifts red and blue channels from center in opposite directions
// Ported from http://kriss.cx/tom/2009/05/rgb-shift/
// by Tom Butterworth / http://kriss.cx/tom/

static string rgbshift_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"

	"#include <filter.sh>\n"

	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";
	
static string rgbshift_fragment =

	"$input v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"uniform vec4 u_rgbshift_p0;\n"
	"#define u_amount u_rgbshift_p0.xy\n"
	"#define u_angle  u_rgbshift_p0.z\n"
		
	"#define s_diffuse s_source_0\n"
		
	"void main() {\n"

		"vec2 offset = u_amount * vec2(cos(u_angle), sin(u_angle));\n"
		"vec4 cr = texture2D(s_diffuse, v_uv0 + offset);\n"
		"vec4 cga = texture2D(s_diffuse, v_uv0);\n"
		"vec4 cb = texture2D(s_diffuse, v_uv0 - offset);\n"
		"gl_FragColor = vec4(cr.r, cga.g, cb.b, cga.a);\n"
	"}\n";


struct DotScreen
{
	vec2 size = vec2(256.f);
	vec2 center = vec2(0.5f);
	float angle = 1.57f;
	float scale = 1.f;
};

struct RgbShift
{
	float amount = 0.005f;
	float angle = 0.f;
};

void pass_dotscreen(GfxSystem& gfx, Render& render, DotScreen& p)
{
	Program& program = gfx.programs().fetch("dotscreen");

	Pass pass = render.next_pass("dotscreen", PassType::PostProcess);

	gfx.m_filter->uniform(pass, "u_dotscreen_p0", vec4(p.center, p.angle, p.scale));
	gfx.m_filter->uniform(pass, "u_dotscreen_p1", vec4(p.size, 0.f, 0.f));

	gfx.m_filter->source0(render.m_target->m_diffuse);

	gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);

	//gfx.m_copy->quad(render.composite_pass(), *render.m_fbo, render.m_target->m_post.last(), pass.m_viewport->m_rect);
}

void pass_rgbshift(GfxSystem& gfx, Render& render, RgbShift& p)
{
	Program& program = gfx.programs().fetch("rgbshift");

	Pass pass = render.next_pass("rgbshift", PassType::PostProcess);

	gfx.m_filter->uniform(pass, "u_rgbshift_p0", vec4(p.amount, p.angle, 0.f, 0.f));

	//gfx.m_filter->source0(render.m_target->m_diffuse);
	gfx.m_filter->source0(render.m_target->m_post.last());

	gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);

	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, render.m_target->m_post.last());
}

EX(xx_effect)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

#if UI
	ui::orbit_controls(viewer);
#endif

	static Node3* node = nullptr;
	struct Node { vec3 p; quat r; vec3 s; Node3* node; };
	static vector<Node> nodes;

	static RgbShift rgbshift;
	static DotScreen dotscreen;

	dotscreen.scale = 4.f;
	rgbshift.amount = 0.0015f;

	auto render = [](GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		pass_clear(gfx, render);
		pass_opaque(gfx, render);
		pass_dotscreen(gfx, render, dotscreen);
		pass_rgbshift(gfx, render, rgbshift);
	};

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye.z = 400.f;

		static Program& prog_rgbshift = app.m_gfx.programs().create("rgbshift");
		prog_rgbshift.set_source(ShaderType::Vertex, rgbshift_vertex);
		prog_rgbshift.set_source(ShaderType::Fragment, rgbshift_fragment);

		static Program& prog_dotscreen = app.m_gfx.programs().create("dotscreen");
		prog_dotscreen.set_source(ShaderType::Vertex, dotscreen_vertex);
		prog_dotscreen.set_source(ShaderType::Fragment, dotscreen_fragment);

		scene.m_env.m_radiance.m_ambient = rgb(0x222222);

		scene.m_env.m_fog = { true, 1.f, rgb(0x000000), true, 1.f, 1000.f };

		Node3& object = gfx::nodes(scene).add(Node3());
		node = &object;

		Symbol symbol; symbol.m_subdiv = uvec2(4U);
		Model& geometry = app.m_gfx.shape(Sphere(1.f), symbol);

		Program& phong = app.m_gfx.programs().fetch("pbr/phong");

		Material& material = app.m_gfx.materials().create("effect", [&](Material& m) {
			m.m_program = &phong;
			m.m_base.m_flat_shaded = true;
			m.m_phong.m_diffuse = rgb(0xffffff);
		});

		nodes.clear();
		for(size_t i = 0; i < 100; i++)
		{
			const vec3 p = normalize(vec3(randf(), randf(), randf()) - 0.5f) * randf() * 400.f;
			const vec3 a = vec3(randf(), randf(), randf()) * 2.f;
			const vec3 s = vec3(randf()) * 50.f;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
			nodes.push_back({ p, quat(a), s, &n });
		}

		Node3& ln = gfx::nodes(scene).add(Node3(vec3(0.f), look_dir(vec3(-1.f))));
		Light& l = gfx::lights(scene).add(Light(ln, LightType::Direct, false, rgb(0xffffff)));

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

	static vec3 angles = vec3(0.f);
	angles.x += 0.005f;
	angles.y += 0.01f;

	node->apply(vec3(0.f), quat(angles));

	for(Node& n : nodes)
		n.node->derive(*node, n.p, n.r, n.s);
}