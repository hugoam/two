#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;
#else
#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>
#include <stl/vector.hpp>
#endif

using namespace two;

// @author meatbags / xavierburrow.com, github/meatbags
// RGB Halftone shader for three.js.

enum class HalftoneShape { None, Dot, Ellipse, Line, Square };
enum class HalftoneBlend { None, Linear, Multiply, Add, Lighter, Darker };

struct Halftone
{
	HalftoneShape m_shape = HalftoneShape::Dot;
	HalftoneBlend m_blend_mode = HalftoneBlend::Linear;
	float m_radius = 4.f;
	vec3 m_rotate = vec3(c_pi / 12.f) * vec3(1.f, 2.f, 3.f);
	float m_scatter = 0.f;
	float m_blending = 1.f;
	bool m_grayscale = false;
	bool m_disable = false;
};

static string halftone_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"

	"#include <filter.sh>\n"

	"void main()\n"
	"{\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string halftone_fragment =

	"$input v_uv0\n"

	"#include <filter.sh>\n"

	"#define SQRT2_MINUS_ONE 0.41421356\n"
	"#define SQRT2_HALF_MINUS_ONE 0.20710678\n"

	"#define SHAPE_DOT 1\n"
	"#define SHAPE_ELLIPSE 2\n"
	"#define SHAPE_LINE 3\n"
	"#define SHAPE_SQUARE 4\n"

	"#define BLENDING_LINEAR 1\n"
	"#define BLENDING_MULTIPLY 2\n"
	"#define BLENDING_ADD 3\n"
	"#define BLENDING_LIGHTER 4\n"
	"#define BLENDING_DARKER 5\n"

	"uniform vec4 u_halftone_p0;\n"
	"#define u_radius u_halftone_p0.x\n"
	"#define u_rotateR u_halftone_p0.y\n"
	"#define u_rotateG u_halftone_p0.z\n"
	"#define u_rotateB u_halftone_p0.w\n"

	"uniform vec4 u_halftone_p1;\n"
	"#define u_shape int(u_halftone_p1.x)\n"
	"#define u_scatter u_halftone_p1.y\n"
	"#define u_blending u_halftone_p1.z\n"
	"#define u_blend_mode int(u_halftone_p1.w)\n"

	"uniform vec4 u_halftone_p2;\n"
	"#define u_disable bool(u_halftone_p2.x)\n"
	"#define u_greyscale bool(u_halftone_p2.y)\n"

	"CONST(int) samples = 8;\n"

	"float blend(float a, float b, float t) {\n"
		// linear blend
		"return a * (1.0 - t) + b * t;\n"
	"}\n"

	"float hypot(float x, float y) {\n"
		// vector magnitude
		"return sqrt(x * x + y * y);\n"
	"}\n"

	"float randf(vec2 seed){\n"
		// get pseudo-random number
		"return fract(sin(dot(seed.xy, vec2(12.9898, 78.233))) * 43758.5453);\n"
	"}\n"

	"float distanceToDotRadius(float channel, vec2 coord, vec2 normal, vec2 p, float angle, float rad_max) {\n"

		// apply shape-specific transforms
		"float dist = hypot(coord.x - p.x, coord.y - p.y);\n"
		"float rad = channel;\n"

		"if (u_shape == SHAPE_DOT) {\n"
			"rad = pow(abs(rad), 1.125) * rad_max;\n"
		"} else if (u_shape == SHAPE_ELLIPSE) {\n"
			"rad = pow(abs(rad), 1.125) * rad_max;\n"
			"if (dist != 0.0) {\n"
				"float dot_p = abs((p.x - coord.x) / dist * normal.x + (p.y - coord.y) / dist * normal.y);\n"
				"dist = (dist * (1.0 - SQRT2_HALF_MINUS_ONE)) + dot_p * dist * SQRT2_MINUS_ONE;\n"
			"}\n"
		"} else if (u_shape == SHAPE_LINE) {\n"
			"rad = pow(abs(rad), 1.5) * rad_max;\n"
			"float dot_p = (p.x - coord.x) * normal.x + (p.y - coord.y) * normal.y;\n"
			"dist = hypot(normal.x * dot_p, normal.y * dot_p);\n"
		"} else if (u_shape == SHAPE_SQUARE) {\n"
			"float theta = atan2(p.y - coord.y, p.x - coord.x) - angle;\n"
			"float sin_t = abs(sin(theta));\n"
			"float cos_t = abs(cos(theta));\n"
			"rad = pow(abs(rad), 1.4);\n"
			"rad = rad_max * (rad + ((sin_t > cos_t) ? rad - sin_t * rad : rad - cos_t * rad));\n"
		"}\n"

		"return rad - dist;\n"
	"}\n"

	"struct Cell {\n"
		// grid sample positions
		"vec2 normal;\n"
		"vec2 p1;\n"
		"vec2 p2;\n"
		"vec2 p3;\n"
		"vec2 p4;\n"
		"float samp2;\n"
		"float samp1;\n"
		"float samp3;\n"
		"float samp4;\n"
	"};\n"

	"vec4 getSample(vec2 uv) {\n"
		// multi-sampled point
		"vec4 tex = texture2D(s_source_0, uv * u_pixel_size);\n"
		"float base = randf(vec2(floor(uv.x), floor(uv.y))) * PI2;\n"
		"float step = PI2 / float(samples);\n"
		"float dist = u_radius * 0.66;\n"

		"for (int i = 0; i < samples; ++i) {\n"
			"float r = base + step * float(i);\n"
			"vec2 coord = uv + vec2(cos(r) * dist, sin(r) * dist);\n"
			"tex += texture2D(s_source_0, coord * u_pixel_size);\n"
		"}\n"

		"tex /= float(samples) + 1.0;\n"
		"return tex;\n"
	"}\n"

	"float getDotColour(Cell c, vec2 p, int channel, float angle, float aa) {\n"

		// get colour for given point
		"float dist_c_1, dist_c_2, dist_c_3, dist_c_4, res;\n"

		"if (channel == 0) {\n"
			"c.samp1 = getSample(c.p1).r;\n"
			"c.samp2 = getSample(c.p2).r;\n"
			"c.samp3 = getSample(c.p3).r;\n"
			"c.samp4 = getSample(c.p4).r;\n"
		"} else if (channel == 1) {\n"
			"c.samp1 = getSample(c.p1).g;\n"
			"c.samp2 = getSample(c.p2).g;\n"
			"c.samp3 = getSample(c.p3).g;\n"
			"c.samp4 = getSample(c.p4).g;\n"
		"} else {\n"
			"c.samp1 = getSample(c.p1).b;\n"
			"c.samp3 = getSample(c.p3).b;\n"
			"c.samp2 = getSample(c.p2).b;\n"
			"c.samp4 = getSample(c.p4).b;\n"
		"}\n"

		"dist_c_1 = distanceToDotRadius(c.samp1, c.p1, c.normal, p, angle, u_radius);\n"
		"dist_c_2 = distanceToDotRadius(c.samp2, c.p2, c.normal, p, angle, u_radius);\n"
		"dist_c_3 = distanceToDotRadius(c.samp3, c.p3, c.normal, p, angle, u_radius);\n"
		"dist_c_4 = distanceToDotRadius(c.samp4, c.p4, c.normal, p, angle, u_radius);\n"
		"res = (dist_c_1 > 0.0) ? clamp(dist_c_1 / aa, 0.0, 1.0) : 0.0;\n"
		"res += (dist_c_2 > 0.0) ? clamp(dist_c_2 / aa, 0.0, 1.0) : 0.0;\n"
		"res += (dist_c_3 > 0.0) ? clamp(dist_c_3 / aa, 0.0, 1.0) : 0.0;\n"
		"res += (dist_c_4 > 0.0) ? clamp(dist_c_4 / aa, 0.0, 1.0) : 0.0;\n"
		"res = clamp(res, 0.0, 1.0);\n"

		"return res;\n"
	"}\n"

	"Cell getReferenceCell(vec2 p, vec2 origin, float grid_angle, float step) {\n"

		// get containing cell
		"Cell c;\n"

		// calc grid
		"vec2 n = vec2(cos(grid_angle), sin(grid_angle));\n"
		"float threshold = step * 0.5;\n"
		"float dot_normal = n.x * (p.x - origin.x) + n.y * (p.y - origin.y);\n"
		"float dot_line = -n.y * (p.x - origin.x) + n.x * (p.y - origin.y);\n"
		"vec2 offset = vec2(n.x * dot_normal, n.y * dot_normal);\n"
		"float offset_normal = mod(hypot(offset.x, offset.y), step);\n"
		"float normal_dir = (dot_normal < 0.0) ? 1.0 : -1.0;\n"
		"float normal_scale = ((offset_normal < threshold) ? -offset_normal : step - offset_normal) * normal_dir;\n"
		"float offset_line = mod(hypot((p.x - offset.x) - origin.x, (p.y - offset.y) - origin.y), step);\n"
		"float line_dir = (dot_line < 0.0) ? 1.0 : -1.0;\n"
		"float line_scale = ((offset_line < threshold) ? -offset_line : step - offset_line) * line_dir;\n"

		// get closest corner
		"c.normal = n;\n"
		"c.p1.x = p.x - n.x * normal_scale + n.y * line_scale;\n"
		"c.p1.y = p.y - n.y * normal_scale - n.x * line_scale;\n"

		// scatter
		"if (u_scatter != 0.0) {\n"

			"float off_mag = u_scatter * threshold * 0.5;\n"
			"float off_angle = randf(vec2(floor(c.p1.x), floor(c.p1.y))) * PI2;\n"
			"c.p1.x += cos(off_angle) * off_mag;\n"
			"c.p1.y += sin(off_angle) * off_mag;\n"
		"}\n"

		// find corners
		"float normal_step = normal_dir * ((offset_normal < threshold) ? step : -step);\n"
		"float line_step = line_dir * ((offset_line < threshold) ? step : -step);\n"
		"c.p2.x = c.p1.x - n.x * normal_step;\n"
		"c.p2.y = c.p1.y - n.y * normal_step;\n"
		"c.p3.x = c.p1.x + n.y * line_step;\n"
		"c.p3.y = c.p1.y - n.x * line_step;\n"
		"c.p4.x = c.p1.x - n.x * normal_step + n.y * line_step;\n"
		"c.p4.y = c.p1.y - n.y * normal_step - n.x * line_step;\n"

		"return c;\n"
	"}\n"

	"float blendColour(float a, float b, float t) {\n"

		// blend colours
		"if (u_blend_mode == BLENDING_LINEAR) {\n"
			"return blend(a, b, 1.0 - t);\n"
		"} else if (u_blend_mode == BLENDING_ADD) {\n"
			"return blend(a, min(1.0, a + b), t);\n"
		"} else if (u_blend_mode == BLENDING_MULTIPLY) {\n"
			"return blend(a, max(0.0, a * b), t);\n"
		"} else if (u_blend_mode == BLENDING_LIGHTER) {\n"
			"return blend(a, max(a, b), t);\n"
		"} else if (u_blend_mode == BLENDING_DARKER) {\n"
			"return blend(a, min(a, b), t);\n"
		"} else {\n"
			"return blend(a, b, 1.0 - t);\n"
		"}\n"
	"}\n"

	"void main() {\n"

		"if (!u_disable) {\n"
			// setup
			"vec2 p = v_uv0 * u_screen_size;\n"
			"vec2 origin = vec2(0, 0);\n"
			"float aa = (u_radius < 2.5) ? u_radius * 0.5 : 1.25;\n"

			// get channel samples
			"Cell cell_r = getReferenceCell(p, origin, u_rotateR, u_radius);\n"
			"Cell cell_g = getReferenceCell(p, origin, u_rotateG, u_radius);\n"
			"Cell cell_b = getReferenceCell(p, origin, u_rotateB, u_radius);\n"
			"float r = getDotColour(cell_r, p, 0, u_rotateR, aa);\n"
			"float g = getDotColour(cell_g, p, 1, u_rotateG, aa);\n"
			"float b = getDotColour(cell_b, p, 2, u_rotateB, aa);\n"

			// blend with original
			"vec4 colour = texture2D(s_source_0, v_uv0);\n"
			"r = blendColour(r, colour.r, u_blending);\n"
			"g = blendColour(g, colour.g, u_blending);\n"
			"b = blendColour(b, colour.b, u_blending);\n"

			"if (u_greyscale) {\n"
				"r = g = b = (r + b + g) / 3.0;\n"
			"}\n"

			"gl_FragColor = vec4(r, g, b, 1.0);\n"

		"} else {\n"

			"gl_FragColor = texture2D(s_source_0, v_uv0);\n"

		"}\n"

	"}";

// @author meatbags / xavierburrow.com, github/meatbags
// RGB Halftone pass for three.js effects composer. Requires THREE.HalftoneShader.

void pass_halftone(GfxSystem& gfx, Render& render, Halftone& halftone) // renderer, writeBuffer, readBuffer, deltaTime, maskActive
{
	Program& program = gfx.programs().fetch("halftone");

	Pass pass = render.next_pass("halftone", PassType::PostProcess);

	gfx.m_filter->uniform(pass, "u_halftone_p0", vec4(halftone.m_radius, halftone.m_rotate));
	gfx.m_filter->uniform(pass, "u_halftone_p1", vec4(float(halftone.m_shape), halftone.m_scatter, halftone.m_blending, float(halftone.m_blend_mode)));
	gfx.m_filter->uniform(pass, "u_halftone_p2", vec4(float(halftone.m_disable), float(halftone.m_grayscale), 0.f, 0.f));

	gfx.m_filter->source0(render.m_target->m_diffuse);

	gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);

	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, render.m_target->m_post.last());
}

static string basic_vertex =

	"$input a_position, a_normal, a_texcoord0\n"
	"$output v_normal, v_uv0\n"

	"#include <common.sh>\n"

	"void main()\n"
	"{\n"
		"v_uv0 = a_texcoord0;\n"
		"v_normal = vec3(a_normal);\n"
		"gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}";

static string basic_fragment =

	"$input v_normal, v_uv0\n"

	"#include <common.sh>\n"

	"void main()\n"
	"{\n"
		"vec4 c = vec4(abs(v_normal) + vec3(v_uv0, 0.0), 0.0);\n"
		"gl_FragColor = c;\n"
	"}";

EX(xx_effect_halftone)
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

	static const float rotationSpeed = c_pi / 64.f;

	static Halftone halftone;

	static Node3* node = nullptr;
	struct Node { vec3 p; vec3 a; Node3* node; };
	static vector<Node> nodes;
	
	static vec3 angles = vec3(0.f);

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 75.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye.z = 12.f;

		viewer.m_viewport.m_clear_colour = rgb(0x444444);
		scene.m_env.m_background.m_colour = rgb(0x444444);

		Program& program = app.m_gfx.programs().create("halftone");
		program.set_source(ShaderType::Vertex, halftone_vertex);
		program.set_source(ShaderType::Fragment, halftone_fragment);

		Model& quad = app.m_gfx.shape(Cube(vec3(100.f, 1.f, 100.f)));
		Model& cube = app.m_gfx.shape(Cube(vec3(1.f)));

		Node3& group = gfx::nodes(scene).add(Node3());
		node = &group;

		Node3& ln = gfx::nodes(scene).add(Node3(vec3(0.f, 2.f, 0.f)));
		Light& l = gfx::lights(scene).add(Light(ln, LightType::Point, false, rgb(0xffffff), 1.f, 50.f)); // 2

		Node3& fn = gfx::nodes(scene).add(Node3(vec3(0.f, -10.f, 0.f)));
		Item& g = gfx::items(scene).add(Item(fn, quad));
		
		Program& basic = app.m_gfx.programs().create("halftonebasic");
		basic.set_pass(PassType::Opaque);
		basic.set_source(ShaderType::Vertex, basic_vertex);
		basic.set_source(ShaderType::Fragment, basic_fragment);

		Material& mat = app.m_gfx.materials().create("halftonebasic", [&](Material& m) {
			m.m_program = &basic;
		});

		nodes.clear();
		for (size_t i = 0; i < 50; ++i)
		{
			// fill scene with coloured cubes
			const vec3 p = vec3(randf(), randf(), randf()) * 16.f - 8.f;
			const vec3 a = vec3(randf(), randf(), randf()) * c_2pi;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a)));
			Item& g = gfx::items(scene).add(Item(n, cube, 0U, &mat));
			nodes.push_back({ p, a, &n });
		}

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);
			pass_halftone(gfx, render, halftone);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}
	
#if UI
	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::sheet(*dock);

		vec3 rotate = halftone.m_rotate / (c_pi / 180.f);

		Widget& controls = ui::stack(sheet);

		ui::dropdown_field(controls, "shape", { "None", "Dot", "Ellipse", "Line", "Square" }, (uint32_t&)halftone.m_shape);

		ui::slider_field(controls, "radius",   halftone.m_radius, { 1.f, 25.f, 0.1f });
		ui::slider_field(controls, "rotateR",  rotate.r, { 0.f, 90.f, 0.1f });
		ui::slider_field(controls, "rotateG",  rotate.g, { 0.f, 90.f, 0.1f });
		ui::slider_field(controls, "rotateB",  rotate.b, { 0.f, 90.f, 0.1f });
		ui::slider_field(controls, "scatter",  halftone.m_scatter, { 0.f, 1.f, 0.01f });
		ui::field<bool>  (controls, "grayscale", halftone.m_grayscale);

		ui::slider_field(controls, "blending", halftone.m_blending, { 0.f, 1.f, 0.01f });
		ui::dropdown_field(controls, "blend mode", { "None", "Linear", "Multiply", "Add", "Lighter", "Darker" }, (uint32_t&)halftone.m_blend_mode);

		ui::field<bool>  (controls, "disable", halftone.m_disable);

		halftone.m_rotate = rotate * (c_pi / 180.f);
	}
#endif

	const float delta = app.m_gfx.m_frame_time;
	angles.y += delta * rotationSpeed;

	node->apply(vec3(0.f), quat(angles));
	for(Node& n : nodes)
		n.node->derive(*node, n.p, quat(n.a));
}
