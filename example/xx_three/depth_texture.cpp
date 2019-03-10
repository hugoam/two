//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

static string vertex_shader()
{
	string shader =

		"$input a_position, a_texcoord0\n"
		"$output v_uv0\n"
		"\n"
		"#include <filter/filter.sh>\n"
		"\n"
		"void main() {\n"
		"	v_uv0 = u_source_0_crop.xy + a_texcoord0 * u_source_0_crop.zw;\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		"}\n";

	return shader;
}

static string fragment_shader()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <filter/filter.sh>\n"
		"\n"
		"float readDepth(sampler2D depthSampler, vec2 coord)\n"
		"{\n"
		"	float depth = texture2D(depthSampler, coord).x;\n"
		"	float viewZ = perspectiveDepthToViewZ(depth);\n"
		"	return viewZToOrthographicDepth(viewZ);\n"
		//"	return linearize_depth(depth);\n"
		"}\n"
		"\n"
		"void main() {\n"
		//"	vec3 diffuse = texture2D(s_source_0, v_uv0).rgb;\n"
		"	float depth = readDepth(s_source_depth, v_uv0);\n"
		//"	float depth = texture2D(s_source_depth, v_uv0).x;\n"
		"\n"
		"	gl_FragColor = vec4(1.0 - vec3(depth), 1.0);\n"
		"}\n";

	return shader;
}

void pass_to_depth(GfxSystem& gfx, Render& render)
{
	static BlockCopy& block_copy = *gfx.m_renderer.block<BlockCopy>();
	static BlockFilter& block_filter = *gfx.m_renderer.block<BlockFilter>();

	static Program& program = gfx.programs().fetch("todepth");

	Pass pass = render.next_pass("todepth", PassType::PostProcess);

	bgfx::setTexture(uint8_t(TextureSampler::SourceDepth), block_filter.u_uniform.s_source_depth, render.m_target->m_depth);

	RenderTarget& target = *render.m_target;
	block_filter.submit_quad(target, pass.m_index, target.m_post_process.swap(), program.default_version(), pass.m_viewport->m_rect);

	block_copy.submit_quad(target, render.composite_pass(), render.m_target_fbo, target.m_post_process.last(), pass.m_viewport->m_rect);
};

void xx_depth_texture(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	//controls.enableDamping = true;
	//controls.dampingFactor = 0.25;
	//controls.rotateSpeed = 0.35;

	Scene& scene = viewer.m_scene;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 0.01f; camera.m_far = 50.f;
		camera.m_eye.z = 4.f;

		Model& geometry = app.m_gfx.shape(TorusKnot(1.f, 0.3f));

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

		static BlockFilter& block_filter = *app.m_gfx.m_renderer.block<BlockFilter>();

		Program& program = app.m_gfx.programs().create("todepth");
		program.m_sources[ShaderType::Vertex] = vertex_shader();
		program.m_sources[ShaderType::Fragment] = fragment_shader();

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			render.m_is_mrt = false;
			pass_clear(gfx, render);
			pass_solid(gfx, render);
			pass_to_depth(gfx, render);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}
}