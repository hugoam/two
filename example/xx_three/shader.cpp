//#include <two/frame.h>
#include <frame/Api.h>
#include <ui/Edit/Lang.h>

#include <09_live_shader/09_live_shader.h>

using namespace two;

#define GEOMETRY 1

static string vertex_shader =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"void main()\n"
	"{\n"
#if GEOMETRY
	"	int material_index = int(u_state_material_vertex);\n"
	"	BaseMaterial basic = read_base_material(material_index);\n"
	"	\n"
	"   v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;\n"
#else
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
#endif
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";


static string fragment_shader =

	"$input v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"void main() {\n"
		
	"	vec2 p = - 1.0 + 2.0 * v_uv0;\n"
	"	float a = u_time * 40.0;\n"
	"	float d, e, f, g = 1.0 / 40.0 ,h ,i ,r ,q;\n"
		
	"	e = 400.0 * (p.x * 0.5 + 0.5);\n"
	"	f = 400.0 * (p.y * 0.5 + 0.5);\n"
	"	i = 200.0 + sin(e * g + a / 150.0) * 20.0;\n"
	"	d = 200.0 + cos(f * g / 2.0) * 18.0 + cos(e * g) * 7.0;\n"
	"	r = sqrt(pow(abs(i - e), 2.0) + pow(abs(d - f), 2.0));\n"
	"	q = f / r;\n"
	"	e = (r * cos(q)) - a / 2.0;\n"
	"	f = (r * sin(q)) - a / 2.0;\n"
	"	d = sin(e * g) * 176.0 + sin(e * g) * 164.0 + r;\n"
	"	h = ((f + d) + a / 2.0) * g;\n"
	"	i = cos(h + r * p.x / 1.3) * (e + e + a) + cos(q * g * 6.0) * (r + h / 3.0);\n"
	"	h = sin(f * g) * 144.0 - sin(e * g) * 212.0 * p.x;\n"
	"	h = (h + (f - e) * q + sin(r - (a + h) / 7.0) * 10.0 + i / 4.0) * g;\n"
	"	i += cos(h * 2.3 * sin(a / 350.0 - q)) * 184.0 * sin(q - (r * 4.3 + a / 12.0) * g) + tan(r * g + h) * 184.0 * cos(r * g + h);\n"
	"	i = mod(i / 5.6, 256.0) / 64.0;\n"
	"	if (i < 0.0) i += 4.0;\n"
	"	if (i >= 2.0) i = 4.0 - i;\n"
	"	d = r / 350.0;\n"
	"	d += sin(d * d * 8.0) * 0.52;\n"
	"	f = (sin(a * g) + 1.0) / 2.0;\n"
	"	gl_FragColor = vec4(vec3(f * i / 1.6, i / 2.0 + d / 13.0, i) * d * p.x + vec3(i / 1.3 + d / 8.0, i / 2.0 + d / 18.0, i) * d * (1.0 - p.x), 1.0);\n"
		
	"}\n";

void xx_shader(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar); UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);

	static Program program = { "custom" };
	if(init)
	{
		program.set_block(MaterialBlock::Solid);
		program.set_source(ShaderType::Vertex, vertex_shader);
		program.set_source(ShaderType::Fragment, fragment_shader);
	}

#if GEOMETRY
	if(init)
	{
		Material& material = app.m_gfx.materials().create("custom", [&](Material& m) {
			m.m_program = &program;
			m.m_base.m_cull_mode = CullMode::None;
		});

		Model& model = app.m_gfx.shape(Quad(1.f));

		Scene& scene = viewer.m_scene;
		Node3& node = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(node, model, 0U, &material));
	}
#else
	Gnode& scene = viewer.m_scene.begin();

	auto draw_quad = [](GfxSystem& gfx, Render& render, const Pass& pass)
	{
		gfx.m_filter->quad(pass, *render.m_fbo, program.default_version(), pass.m_viewport->m_rect);
	};

	gfx::manual_job(scene, PassType::Solid, draw_quad);
#endif
}