module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
#include <bgfx/bgfx.h>
module two.xxthree;

using namespace two;

// @author felixturner / http://airtight.cc/
//
// RGB Shift Shader
// Shifts red and blue channels from center in opposite directions
// Ported from http://kriss.cx/tom/2009/05/rgb-shift/
// by Tom Butterworth / http://kriss.cx/tom/

static string glitch_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string glitch_fragment =

	"$input v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"uniform vec4 u_glitch_p0;\n"
	"#define u_amount u_glitch_p0.x\n"
	"#define u_angle u_glitch_p0.y\n"
	"#define u_seed u_glitch_p0.y\n"

	"uniform vec4 u_glitch_p1;\n"
	"#define u_scale u_glitch_p1.xy\n"
	"#define u_distort u_glitch_p1.zw\n"
		
	//"uniform float col_s;\n"
		
	"float rand2(vec2 co){\n"
	"	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);\n"
	"}\n"
		
	"void main() {\n"
	"	const float col_s = 0.5;\n"
	"	vec2 p = v_uv0;\n"
	"	float xs = floor(gl_FragCoord.x / 0.5);\n"
	"	float ys = floor(gl_FragCoord.y / 0.5);\n"
	"	//based on staffantans glitch shader for unity https://github.com/staffantan/unityglitch \n"
	"	vec4 normal = texture2D(s_source_1, p * u_seed * u_seed);\n"
	"	if(p.y < u_distort.x + col_s && p.y > u_distort.x - col_s * u_seed) {\n"
	"		if(u_scale.x > 0.0) {\n"
	"			p.y = 1.0 - (p.y + u_distort.y);\n"
	"		}\n"
	"		else {\n"
	"			p.y = u_distort.y;\n"
	"		}\n"
	"	}\n"
	"	if(p.x < u_distort.y + col_s && p.x > u_distort.y - col_s * u_seed) {\n"
	"		if(u_scale.y > 0.0){\n"
	"			p.x = u_distort.x;\n"
	"		}\n"
	"		else {\n"
	"			p.x = 1.0 - (p.x + u_distort.x);\n"
	"		}\n"
	"	}\n"
	"	p.x += normal.x * u_scale.x * (u_seed / 5.0);\n"
	"	p.y += normal.y * u_scale.y * (u_seed / 5.0);\n"
	"	//base from RGB shift shader\n"
	"	vec2 offset = u_amount * vec2(cos(u_angle), sin(u_angle));\n"
	"	vec4 cr = texture2D(s_source_0, p + offset);\n"
	"	vec4 cga = texture2D(s_source_0, p);\n"
	"	vec4 cb = texture2D(s_source_0, p - offset);\n"
	"	gl_FragColor = vec4(cr.r, cga.g, cb.b, cga.a);\n"
	"	//add noise\n"
	"	vec4 snow = 200.0 * u_amount * vec4_splat(rand2(vec2(xs * u_seed, ys * u_seed * 50.0)) * 0.2);\n"
	"	gl_FragColor = gl_FragColor + snow;\n"
	"}\n";

constexpr int speed = 2;

struct Glitch
{
	float seed = randf();
	int randX = randi(120, 240) * speed;
	bool gowild = false;
	int bypass = 0;
	int frame = 0;
};

Texture& glitch_heightmap(GfxSystem& gfx, uint size)
{
	Texture& texture = gfx.textures().create("glitch");

	const bgfx::Memory* memory = bgfx::alloc(size * size * 4 * sizeof(float));
	//var array = new Float32Array(size * size * 3);

	float* data = (float*)memory->data;

	const size_t count = size * size;
	for(size_t i = 0; i < count; i++)
	{
		float val = randf(0.f, 1.f);
		data[i * 4 + 0] = val;
		data[i * 4 + 1] = val;
		data[i * 4 + 2] = val;
		data[i * 4 + 3] = 0.f;
	}

	texture.load_float(uvec2(size), *memory);
	return texture;
}

void pass_glitch(GfxSystem& gfx, Render& render, Glitch& glitch, uint dt_size = 64)
{
	static Program& program = gfx.programs().create("glitch");
	program.set_source(ShaderType::Vertex, glitch_vertex);
	program.set_source(ShaderType::Fragment, glitch_fragment);

	static Texture& disp = glitch_heightmap(gfx, dt_size);

	float amount = 0.f;
	float angle = 0.f;
	vec2 scale = vec2(0.f);
	vec2 distort = vec2(0.f);

	int frame = glitch.frame % glitch.randX;
	if(frame == 0 || glitch.gowild == true)
	{
		amount = randf() / 30.f;
		angle = randf(-c_pi, c_pi);
		scale = vec2(randf(-1.f, 1.f), randf(-1.f, 1.f));
		distort = vec2(randf(0.f, 1.f), randf(0.f, 1.f));
		glitch.frame = 0;
		glitch.randX = randi(120, 240) * speed;

	}
	else if(frame < glitch.randX / 5)
	{
		amount = randf() / 90.f;
		angle = randf(-c_pi, c_pi);
		scale = vec2(randf(-0.3f, 0.3f), randf(-0.3f, 0.3f));
		distort = vec2(randf(0.f, 1.f), randf(0.f, 1.f));

	}
	else if(glitch.gowild == false)
	{
		glitch.frame++;
		return;
	}

	glitch.frame++;

	Pass pass = render.next_pass("glitch", PassType::PostProcess);

	gfx.m_filter->uniform(pass, "u_glitch_p0", vec4(amount, angle, glitch.seed, 0.f));
	gfx.m_filter->uniform(pass, "u_glitch_p1", vec4(scale, distort));

	gfx.m_filter->source0(render.m_target->m_diffuse);
	gfx.m_filter->sourcedepth(disp);

	RenderTarget& target = *render.m_target;
	gfx.m_filter->quad(pass, target.m_post.swap(), program);

	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, target.m_post.last());
}

EX(xx_effect_glitch)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	static Node3* object = nullptr;
	struct Node { vec3 p; vec3 a; vec3 s; Node3* n; };
	static vector<Node> nodes;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye.z = 400.f;

		scene.m_env.m_radiance.m_ambient = rgb(0x222222);

		scene.m_env.m_fog = { true, 1.f, rgb(0x000000), true, 1.f, 1000.f };

		Symbol symbol; symbol.m_subdiv = uvec2(4U);
		Model& geometry = app.m_gfx.shape(Sphere(1.f), symbol);

		Program& phong = app.m_gfx.programs().fetch("pbr/phong");

		Node3& group = gfx::nodes(scene).add(Node3());
		object = &group;

		for(size_t i = 0; i < 100; i++)
		{
			const string name = "object" + to_string(i);
			Material& material = app.m_gfx.materials().create(name, [&](Material& m) {
				m.m_program = &phong;
				m.m_base.m_flat_shaded = true;
				m.m_phong.m_diffuse = rgb(randi<uint32_t>());
			});

			const vec3 p = normalize(vec3(randf(), randf(), randf()) - 0.5f) * randf() * 400.f;
			const vec3 a = vec3(randf(), randf(), randf()) * 2.f;
			const vec3 s = vec3(randf() * 50.f);

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
			nodes.push_back({ p, a, s, &n });
		}

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f), facing(vec3(-1.f, -1.f, -1.f))));
		Light& light = gfx::lights(scene).add(Light(n, LightType::Direct, false));

		static Glitch glitch = {};

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);
			pass_glitch(gfx, render, glitch);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

	const float delta = app.m_gfx.m_frame_time;

	static vec3 angles = vec3(0.f);
	angles.x += 0.2f * delta;
	angles.y += 0.4f * delta;

	object->apply(vec3(0.f), quat(angles));

	for(const Node& node : nodes)
		node.n->derive(*object, node.p, quat(node.a), node.s);
}