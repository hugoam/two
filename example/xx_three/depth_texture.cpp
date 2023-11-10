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

static string vertex_shader =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string fragment_shader =

	"$input v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"float readDepth(sampler2D depthSampler, vec2 coord)\n"
	"{\n"
	"	float depth = texture2D(depthSampler, coord).x;\n"
	"	float viewZ = perspectiveDepthToViewZ(depth);\n"
	"	return viewZToOrthographicDepth(viewZ);\n"
	//"	return linearize_depth(depth);\n"
	"}\n"
		
	"void main() {\n"
	//"	vec3 diffuse = texture2D(s_source_0, v_uv0).rgb;\n"
	"	float depth = readDepth(s_source_depth, v_uv0);\n"
	//"	float depth = texture2D(s_source_depth, v_uv0).x;\n"
		
	"	gl_FragColor = vec4(1.0 - vec3_splat(depth), 1.0);\n"
	"}\n";

void pass_to_depth(GfxSystem& gfx, Render& render)
{
	static Program& program = gfx.programs().fetch("todepth");

	RenderTarget& target = *render.m_target;

	Pass pass = render.next_pass("todepth", PassType::PostProcess);

	gfx.m_filter->sourcedepth(render.m_target->m_depth);

	gfx.m_filter->quad(pass, target.m_post.swap(), program);

	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, target.m_post.last());
};

EX(xx_depth_texture)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif
	viewer.m_viewport.m_autorender = false;

#if UI
	OrbitControls& controls = ui::orbit_controls(viewer);
	//TrackballController& controls = ui::trackball_controller(viewer);
	//controls.m_dynamicDampingFactor = 0.05f;
	controls.enableDamping = true;
	controls.dampingFactor = 0.15f;
	controls.rotateSpeed = 0.35f;

#endif

	static Program& program = app.m_gfx.programs().create("todepth");
	if(init)
	{
		program.set_source(ShaderType::Vertex, vertex_shader);
		program.set_source(ShaderType::Fragment, fragment_shader);
	}

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 0.01f; camera.m_far = 50.f;
		camera.m_eye.z = 4.f;

		Symbol symbol; symbol.m_subdiv = uvec2(128, 64);
		Model& geometry = app.m_gfx.shape(TorusKnot(1.f, 0.3f), symbol);

		Material& material = app.m_gfx.materials().create("material", [&](Material& m) {
			m.m_program = &app.m_gfx.programs().fetch("solid");
			m.m_solid.m_colour = Colour::Blue;
		});

		const size_t count = 50U;
		const float scale = 5.f;

		for(size_t i = 0; i < count; i++)
		{
			const float r = randf() * c_2pi;
			const float z = (randf() * 2.f) - 1.f;
			const float distscale = sqrt(1.f - z * z) * scale;

			const vec3 p = vec3(cos(r) * distscale, sin(r) * distscale, z * scale);
			const vec3 a = vec3(randf(), randf(), randf());
			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a)));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
		}
	}

	auto renderer = [](GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		render.m_is_mrt = false;
		pass_clear(gfx, render);
		pass_opaque(gfx, render);
		pass_solid(gfx, render);
		pass_to_depth(gfx, render);
	};

	Render render = { Shading::Shaded, viewer.m_viewport, app.m_gfx.main_target(), app.m_gfx.m_render_frame };
	app.m_gfx.m_renderer.gather(render);
	app.m_gfx.m_renderer.begin(render);
	renderer(app.m_gfx, render);
	app.m_gfx.m_renderer.end(render);
}