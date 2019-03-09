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
		"#include <common.sh>\n"
		"\n"
		"void main() {\n"
		"	v_uv0 = a_texcoord0;\n"
		"	gl_Position = u_modelViewProj * vec4(a_position.xyz, 1.0);\n"
		"}\n";

	return shader;
}

static string fragment_shader()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <common.sh>\n"
		"#include <filter/filter.sh>\n"
		"\n"
		"float readDepth(sampler2D depthSampler, vec2 coord) {\n"
		"	float depth = texture2D(depthSampler, coord).x;\n"
		"	float viewZ = perspectiveDepthToViewZ(depth);\n"
		"	return viewZToOrthographicDepth(viewZ);\n"
		"}\n"
		"\n"
		"void main() {\n"
		"	//vec3 diffuse = texture2D(tDiffuse, vUv).rgb;\n"
		"	float depth = readDepth(tDepth, vUv);\n"
		"\n"
		"	gl_FragColor = vec4(1.0 - vec3(depth), 1.0);\n"
		"}\n";

	return shader;
}

void xx_depth_texture(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	//var controls = new THREE.OrbitControls(camera, renderer.domElement);
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

		//var diffuse = new THREE.TextureLoader().load('textures/brick_diffuse.jpg');
		//diffuse.wrapS = diffuse.wrapT = THREE.RepeatWrapping;

		Model& geometry = app.m_gfx.shape(TorusKnot());
		//var geometry = new THREE.TorusKnotBufferGeometry(1, 0.3, 128, 64);

		// Setup some geometries
		Material material = app.m_gfx.materials().create("material", [](Material& m) {
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
			Node3& n = gfx::nodes(scene).add(Node3(p));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
		}

		static BlockFilter& block_filter = *app.m_gfx.m_renderer.block<BlockFilter>();

		Program& program = app.m_gfx.programs().create("todepth");
		program.m_sources[ShaderType::Vertex] = vertex_shader();
		program.m_sources[ShaderType::Fragment] = fragment_shader();
		// tDiffuse : { value: target.texture },
		// tDepth : { value: target.depthTexture }
		
		auto pass_to_depth = [](GfxSystem& gfx, Render& render)
		{
			Pass pass = render.next_pass("todepth", PassType::PostProcess);
			Program& program = gfx.programs().fetch("todepth");
			block_filter.submit_quad(*pass.m_target, pass.m_index, program.default_version(), pass.m_viewport->m_rect);
		};

		auto render = [](GfxSystem& gfx, Render& render)
		{
			render.m_is_mrt = false;
			pass_clear(gfx, render);
			pass_opaque(gfx, render);
			pass_resolve(gfx, render);
			pass_post_process(gfx, render);
			//pass_to_depth(gfx, render);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);

		// Create a multi render target with Float buffers
		//target = new THREE.WebGLRenderTarget(window.innerWidth, window.innerHeight);
		//target.texture.format = THREE.RGBFormat;
		//target.texture.minFilter = THREE.NearestFilter;
		//target.texture.magFilter = THREE.NearestFilter;
		//target.texture.generateMipmaps = false;
		//target.stencilBuffer = false;
		//target.depthBuffer = true;
		//target.depthTexture = new THREE.DepthTexture();
		//target.depthTexture.type = THREE.UnsignedShortType;
		//
	}
}