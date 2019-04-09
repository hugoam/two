//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>
#include <xx_three/code/bloom_pass.h>

using namespace mud;

// @author alteredq / http://alteredqualia.com/
// Film grain & scanlines shader
//
// - ported from HLSL to WebGL / GLSL
// http://www.truevision3d.com/forums/showcase/staticnoise_sourceblackwhite_scanline_shaders-t18698.0.html
//
// Screen Space Static Postprocessor
//
// Produces an analogue noise overlay similar to a film grain / TV static
//
// Original implementation and noise algorithm
// Pat 'Hawthorne' Shearon
//
// Optimized scanlines + noise version with intensity scaling
// Georg 'Leviathan' Steinrohder
//
// This version is provided under a Creative Commons Attribution 3.0 License
// http://creativecommons.org/licenses/by/3.0/
//

struct Film
{
	float noise = 0.5f;
	float scanlines = 0.05f;
	int num_scanlines = 4096;
	bool grayscale = true;
};

static string film_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"

	"#include <filter.sh>\n"

	"void main() {\n"
		"v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
		"gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";


static string film_fragment =

	"$input v_uv0\n"

	"#include <filter.sh>\n"

	"uniform vec4 u_film_p0;\n"
	"#define u_noise     u_film_p0.x\n"
	"#define u_intensity u_film_p0.y\n"
	"#define u_count     int(u_film_p0.z)\n"
	"#define u_grayscale bool(u_film_p0.w)\n"
		
	"void main() {\n"

		"vec3 source = texture2D(s_source_0, v_uv0).rgb;\n"

		// noise
		"float dx = rand(v_uv0 + u_time);\n"
		"vec3 color = source + source * clamp(0.1 + dx, 0.0, 1.0);\n"

		// scanlines
		"vec2 sc = vec2(sin(v_uv0.y * u_count), cos(v_uv0.y * u_count));\n"
		"color += source * vec3(sc.x, sc.y, sc.x) * u_intensity;\n"

		// interpolate between source and result by intensity
		"color = source + clamp(u_noise, 0.0, 1.0) * (color - source);\n"

		// convert to grayscale if desired
		"if(u_grayscale) {\n"
			"color = vec3_splat(color.r * 0.3 + color.g * 0.59 + color.b * 0.11);\n"
		"}\n"

		"gl_FragColor = vec4(color, 1.0);\n"
	"}";


Program& film_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("film");
	program.set_source(ShaderType::Vertex, film_vertex);
	program.set_source(ShaderType::Fragment, film_fragment);
	return program;
}

// @author alteredq / http://alteredqualia.com/

void pass_film(GfxSystem& gfx, Render& render, const Film& film) //noiseIntensity, scanlinesIntensity, scanlineu_count, grayscale
{
	static Program& program = gfx.programs().fetch("film");

	Pass pass = render.next_pass("film", PassType::PostProcess);

	gfx.m_filter->uniform(pass, "u_film_p0", vec4(film.noise, film.scanlines, float(film.num_scanlines), float(film.grayscale)));
	gfx.m_filter->source0(render.m_target->m_post.last());
	gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);

	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, render.m_target->m_post.last());
}

static string lava_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_position, v_uv0\n"

	"#include <common.sh>\n"

	"void main()\n"
	"{\n"
	"	int material_index = int(u_state_material);\n"
	"	BaseMaterial basic = read_base_material(material_index);\n"

	"   v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;\n"
	"	vec4 view = mul(u_modelView, vec4(a_position.xyz, 1.0));\n"
	"	v_position = mul(u_proj, view);\n"
	"	gl_Position = v_position;\n"
	"}\n";

static string lava_fragment =

	"$input v_position, v_uv0\n"

	"#include <common.sh>\n"
	//"#include <fog.sh>\n"

	"#define fog_density p0.x\n"
	"#define fog_color   p0.yzw\n"

	"void main()\n"
	"{\n"
		"int material_index = int(u_state_material);\n"
		"UserMaterial mat = read_user_material(material_index);\n"

		"vec2 uv = v_uv0;\n"
		"vec2 position = - 1.0 + 2.0 * uv;\n"

		"vec4 noise = texture2D(s_user0, uv);\n"
		"vec2 T1 = uv + vec2(1.5, - 1.5) * u_time * 0.02;\n"
		"vec2 T2 = uv + vec2(- 0.5, 2.0) * u_time * 0.01;\n"

		"T1.x += noise.x * 2.0;\n"
		"T1.y += noise.y * 2.0;\n"
		"T2.x -= noise.y * 0.2;\n"
		"T2.y += noise.z * 0.2;\n"

		"float p = texture2D(s_user0, T1 * 2.0).a;\n"

		"vec4 lava = texture2D(s_user1, T2 * 2.0);\n"
		"vec4 source = lava * (vec4(p, p, p, p) * 2.0) + (lava * lava - 0.1);\n"

		"if(source.r > 1.0) { source.bg += clamp(source.r - 2.0, 0.0, 100.0); }\n"
		"if(source.g > 1.0) { source.rb += source.g - 1.0; }\n"
		"if(source.b > 1.0) { source.rg += source.b - 1.0; }\n"

		"gl_FragColor = source;\n"

	"#if BGFX_SHADER_LANGUAGE_HLSL\n"
	//"	float depth = v_position.z;\n"
		"float depth = gl_FragCoord.z * gl_FragCoord.w;\n"
	"#else\n"
	//"	float depth = (v_position.z + v_position.w) * 0.5;\n"
		"float depth = gl_FragCoord.z / gl_FragCoord.w;\n"
	"#endif\n"
		"float fogFactor = exp2(-mat.fog_density * mat.fog_density * depth * depth * LOG2);\n"
		"fogFactor = 1.0 - clamp(fogFactor, 0.0, 1.0);\n"

		//"gl_FragColor = mix(source, vec4(vec3(0.0, 0.0, 0.0), source.w), fogFactor);\n"
		"gl_FragColor = mix(source, vec4(mat.fog_color, source.w), fogFactor);\n"
	"}\n";


void xx_shader_lava(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);
	viewer.m_viewport.m_autorender = false;

	Scene& scene = viewer.m_scene;

	static vec3 angles = vec3(0.3f, 0.f, 0.f);
	static Node3* node = nullptr;
	
	static Program& program = app.m_gfx.programs().create("lava");
	if(init)
	{
		program.set_block(MaterialBlock::Solid);
		program.set_block(MaterialBlock::User);
		program.set_source(ShaderType::Vertex, lava_vertex);
		program.set_source(ShaderType::Fragment, lava_fragment);
	}

	static Texture& cloud = *app.m_gfx.textures().file("lava/cloud.png");
	static Texture& lava = *app.m_gfx.textures().file("lava/lavatile.png");

	static const float fog_density = 0.45f;
	static const Colour fog_source = Colour(0.f);

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 35.f; camera.m_near = 1.f; camera.m_far = 3000.f;
		camera.m_eye.z = 4.f;
		
		Material& material = app.m_gfx.materials().create("lava", [&](Material& m) {
			m.m_program = &program;
			m.m_base.m_uv0_scale = { 3.f, 1.f };
			m.m_user.m_attr0 = { fog_density, to_vec3(fog_source) };
			m.m_user.m_tex0 = &cloud;
			m.m_user.m_tex1 = &lava;
		});

		const float size = 0.65f;

		Model& model = app.m_gfx.shape(Torus(size, 0.3f));

		node = &gfx::nodes(scene).add(Node3(vec3(0.f), quat(angles)));
		Item& it = gfx::items(scene).add(Item(*node, model, 0U, &material));

		film_program(app.m_gfx);
	}

	const float delta = 5.f * app.m_gfx.m_frame_time;

	//uniforms["time"].value += 0.2 * delta;

	angles.y += 0.0125f * delta;
	angles.x += 0.05f * delta;

	node->apply(vec3(0.f), quat(angles));

	//renderer.clear();
	//composer.render(0.01);

	static Film film = { 0.35f, 0.95f, 2048, false };

	auto renderer = [](GfxSystem& gfx, Render& render) {

		begin_pbr_render(gfx, render);

		pass_clear(gfx, render);
		pass_solid(gfx, render);

		pass_begin_post(gfx, render);
		pass_bloom(gfx, render, render.m_target->m_diffuse, render.m_target->m_post.current(), false, 1.25f);
		pass_film(gfx, render, film);

		const Pass flip = render.composite_pass("flip");
		gfx.m_copy->quad(flip, *render.m_fbo, render.m_target->m_post.last());
	};

	Render render = { Shading::Shaded, viewer.m_viewport, app.m_gfx.main_target(), app.m_gfx.m_render_frame };
	app.m_gfx.m_renderer.gather(render);
	app.m_gfx.m_renderer.begin(render);

	renderer(app.m_gfx, render);

	app.m_gfx.m_renderer.end(render);
}
