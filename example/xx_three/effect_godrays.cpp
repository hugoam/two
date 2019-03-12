//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>

#include <xx_three/xx_three.h>

//<script src="js/loaders/OBJLoader.js"></script>
//<script src="js/ShaderGodRays.js"></script>

/**
 * @author huwb / http://huwbowles.com/
 *
 * God-rays (crepuscular rays)
 *
 * Similar implementation to the one used by Crytek for CryEngine 2 [Sousa2008].
 * Blurs a mask generated from the depth map along radial lines emanating from the light
 * source. The blur repeatedly applies a blur filter of increasing support but constant
 * sample count to produce a blur filter with large support.
 *
 * My implementation performs 3 passes, similar to the implementation from Sousa. I found
 * just 6 samples per pass produced acceptible results. The blur is applied three times,
 * with decreasing filter support. The result is equivalent to a single pass with
 * 6*6*6 = 216 samples.
 *
 * References:
 *
 * Sousa2008 - Crysis Next Gen Effects, GDC2008, http://www.crytek.com/sites/default/files/GDC08_SousaT_CrysisEffects.ppt
 */


static string filter_vertex()
{
	string shader =

		"$input a_position, a_texcoord0\n"
		"$output v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"void main() {\n"
		"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		"}\n";

	return shader;
}

static string godrays_mask_vertex()
{
	return filter_vertex();
}

static string godrays_mask_fragment()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"void main() {\n"
		"	float depth = texture2D(s_source_depth, v_uv0).x;\n"
		"	depth = -perspectiveDepthToViewZ(depth) / u_z_far;\n"
		"	depth = clamp(depth, 0.0, 1.0);\n"
		"	gl_FragColor = vec4(1.0 - depth, 0.0, 0.0, 0.0);\n"
		//"	gl_FragColor = vec4(1.0) - texture2D(s_source_0, v_uv0);\n"
		"}";

	return shader;
}


	/**
	 * The god-ray generation shader.
	 *
	 * First pass:
	 *
	 * The depth map is blurred along radial lines towards the "sun". The
	 * output is written to a temporary render target (I used a 1/4 sized
	 * target).
	 *
	 * Pass two & three:
	 *
	 * The results of the previous pass are re-blurred, each time with a
	 * decreased distance between samples.
	 */

static string godrays_vertex()
{
	return filter_vertex();
}

static string godrays_fragment()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"#define TAPS_PER_PASS 6.0\n"
		"\n"
		"uniform vec4 u_godrays_p0;\n"
		"#define u_sun u_godrays_p0.xy\n"
		"#define u_step_size u_godrays_p0.z\n"
		"\n"
		"void main() {\n"

			// delta from current pixel to "sun" position
			"vec2 delta = u_sun - v_uv0;\n"
			"float dist = length(delta);\n"

			// Step vector (uv space)
			"vec2 stepv = u_step_size * delta / dist;\n"

			// Number of iterations between pixel and sun
			"float iters = dist / u_step_size;\n"

			"vec2 uv = v_uv0;\n"
			"float col = 0.0;\n"

			// This breaks ANGLE in Chrome 22
			//	- see http://code.google.com/p/chromium/issues/detail?id=153105

			/*
			// Unrolling didnt do much on my hardware (ATI Mobility Radeon 3450),
			// so i've just left the loop

			"for (float i = 0.0; i < TAPS_PER_PASS; i += 1.0) {\n"

				// Accumulate samples, making sure we dont walk past the light source.

				// The check for uv.y < 1 would not be necessary with "border" UV wrap
				// mode, with a black border color. I don't think this is currently
				// exposed by three.js. As a result there might be artifacts when the
				// sun is to the left, right or bottom of screen as these cases are
				// not specifically handled.

				"col += (i <= iters && uv.y < 1.0 ? texture2D(s_source_0, uv).r : 0.0);\n"
				"uv += stepv;\n"

			"}\n"
			*/

			// Unrolling loop manually makes it work in ANGLE

			"if (0.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;\n"
			"uv += stepv;\n"

			"if (1.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;\n"
			"uv += stepv;\n"

			"if (2.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;\n"
			"uv += stepv;\n"

			"if (3.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;\n"
			"uv += stepv;\n"

			"if (4.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;\n"
			"uv += stepv;\n"

			"if (5.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;\n"
			"uv += stepv;\n"

			// Should technically be dividing by 'iters', but 'TAPS_PER_PASS' smooths out
			// objectionable artifacts, in particular near the sun position. The side
			// effect is that the result is darker than it should be around the sun, as
			// TAPS_PER_PASS is greater than the number of samples actually accumulated.
			// When the result is inverted (in the shader 'godrays_combine', this produces
			// a slight bright spot at the position of the sun, even when it is occluded.

			"gl_FragColor = vec4(col/TAPS_PER_PASS);\n"
			"gl_FragColor.a = 1.0;\n"

		"}\n";

	return shader;
}

	/**
	 * Additively applies god rays from texture tGodRays to a background (tColors).
	 * fGodRayIntensity attenuates the god rays.
	 */

static string godrays_combine_vertex()
{
	return filter_vertex();
}

static string godrays_combine_fragment()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"uniform vec4 u_godrays_combine_p0;\n"
		"#define u_intensity u_godrays_combine_p0.x\n"
		"\n"
		"void main() {\n"
		"\n"
		// Since THREE.MeshDepthMaterial renders foreground objects white and background
		// objects black, the god-rays will be white streaks. Therefore value is inverted
		// before being combined with tColors
		"\n"
		"	gl_FragColor = texture2D(s_source_0, v_uv0) + u_intensity * vec4(1.0 - texture2D(s_source_1, v_uv0).r);\n"
		"	gl_FragColor.a = 1.0;\n"
		//"	gl_FragColor = texture2D(s_source_0, v_uv0);\n"
		"\n"
		"}";

	return shader;
}


	/**
	 * A dodgy sun/sky shader. Makes a bright spot at the sun location. Would be
	 * cheaper/faster/simpler to implement this as a simple sun sprite.
	 */

static string godrays_sun_vertex()
{
	return filter_vertex();
}

static string godrays_sun_fragment()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"uniform vec4 u_godrays_sun_p0;\n"
		"#define u_bg_color u_godrays_sun_p0.xyz\n"
		"\n"
		"uniform vec4 u_godrays_sun_p1;\n"
		"#define u_sun_color u_godrays_sun_p1.xyz\n"
		"\n"
		"uniform vec4 u_godrays_sun_p2;\n"
		"#define u_sun_xy u_godrays_sun_p2.xy\n"
		"\n"
		"void main() {\n"
		"\n"
		"	vec2 diff = v_uv0 - u_sun_xy;\n"
		// Correct for aspect ratio
		"	diff.x *= u_aspect;\n"
		"\n"
		"	float prop = clamp(length(diff) / 0.5, 0.0, 1.0);\n"
		"	prop = 0.35 * pow(1.0 - prop, 3.0);\n"
		"\n"
		"	gl_FragColor.xyz = mix(u_sun_color, u_bg_color, 1.0 - prop);\n"
		"	gl_FragColor.w = 1.0;\n"
		"	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}";

	return shader;
}

struct Godrays
{
	float m_intensity = 0.75f; // 0.69f
	Colour m_bg_colour = rgb(0x000511);
	Colour m_sun_colour = rgb(0xffee00);

	vec3 m_sun_position = vec3(0, 1000.f, -1000.f);
	vec2 m_sun_screen = vec2(0.f);

	float m_orbit_radius;
};

void pass_fake_sun(GfxSystem& gfx, Render& render, const Godrays& godrays)
{
	static BlockCopy& copy = *gfx.m_renderer.block<BlockCopy>();
	static BlockFilter& filter = *gfx.m_renderer.block<BlockFilter>();

	static Program& program = gfx.programs().create("godrays_fake_sun");
	program.m_sources[ShaderType::Vertex] = godrays_sun_vertex();
	program.m_sources[ShaderType::Fragment] = godrays_sun_fragment();

	Pass pass = render.next_pass("godrays_fake_sun", PassType::PostProcess);

	filter.uniform(pass.m_index, "u_godrays_sun_p0", vec4(to_vec3(godrays.m_bg_colour), 0.f));
	filter.uniform(pass.m_index, "u_godrays_sun_p1", vec4(to_vec3(godrays.m_sun_colour), 0.f));
	filter.uniform(pass.m_index, "u_godrays_sun_p2", vec4(godrays.m_sun_screen, vec2(0.f)));

	// Draw sky and sun

	// Clear colors and depths, will clear to sky color
	//renderer.setRenderTarget(postprocessing.rtTextureColors);
	//renderer.clear(true, true, false);

	// Sun render. Runs a shader that gives a brightness based on the screen
	// space distance to the sun. Not very efficient, so i make a scissor
	// rectangle around the suns position to avoid rendering surrounding pixels.

	const float sunsqH = 0.74f * float(render.m_rect.height); // 0.74 depends on extent of sun from shader
	const float sunsqW = sunsqH; // both depend on height because sun is aspect-corrected

	const vec2 sun = godrays.m_sun_screen * vec2(rect_size(render.m_rect));

	bgfx::setViewScissor(pass.m_index, sun.x - sunsqW / 2.f, sun.y - sunsqH / 2.f, sunsqW, sunsqH);

	filter.quad(pass.m_index, *render.m_target_fbo, program, pass.m_viewport->m_rect);
}

void pass_godrays(GfxSystem& gfx, Render& render, const Godrays& godrays)
{
	static BlockCopy& copy = *gfx.m_renderer.block<BlockCopy>();
	static BlockFilter& filter = *gfx.m_renderer.block<BlockFilter>();

	//// Use a smaller size for some of the god-ray render targets for better performance.
	constexpr float downscale = 1.0 / 4.0;
	const uvec2 size = rect_size(render.m_rect) / 4U;

	// The ping-pong render targets can use an adjusted resolution to minimize cost
	static FrameBuffer ping = { render.m_target->m_size / 4U, bgfx::TextureFormat::R32F, 0U };
	static FrameBuffer pong = { render.m_target->m_size / 4U, bgfx::TextureFormat::R32F, 0U };
	
	// I would have this quarter size and use it as one of the ping-pong render
	// targets but the aliasing causes some temporal flickering
	static FrameBuffer depth = { render.m_target->m_size, bgfx::TextureFormat::R32F, 0U };

	//postprocessing.scene = new THREE.Scene();

	//postprocessing.camera = new THREE.OrthographicCamera(-0.5, 0.5, 0.5, -0.5, -10000, 10000);
	//postprocessing.camera.position.z = 100;

	//postprocessing.quad = new THREE.Mesh(
	//	new THREE.PlaneBufferGeometry(1.0, 1.0),
	//	postprocessing.materialGodraysGenerate
	//);
	//postprocessing.quad.position.z = -9900;
	//postprocessing.scene.add(postprocessing.quad);

	auto pass_mask_depth = [](GfxSystem& gfx, Render& render, const Godrays& godrays, FrameBuffer& fbo)
	{
		static Program& program = gfx.programs().create("godrays_depth_mask");
		program.m_sources[ShaderType::Vertex] = godrays_mask_vertex();
		program.m_sources[ShaderType::Fragment] = godrays_mask_fragment();

		Pass pass = render.next_pass("godrays_depth_mask", PassType::PostProcess);

		filter.sourcedepth(render.m_target->m_depth);

		filter.quad(pass.m_index, fbo, program, pass.m_viewport->m_rect);
	};

	auto pass_blur = [](GfxSystem& gfx, Render& render, const Godrays& godrays, FrameBuffer& fbo, Texture& source, float step_size, RenderQuad quad)
	{
		static Program& program = gfx.programs().create("godrays_generate");
		program.m_sources[ShaderType::Vertex] = godrays_vertex();
		program.m_sources[ShaderType::Fragment] = godrays_fragment();

		Pass pass = render.next_pass("godrays", PassType::PostProcess);

		filter.uniform(pass.m_index, "u_godrays_p0", vec4(godrays.m_sun_screen, vec2(step_size, 0.f)));
		filter.source0(source);

		filter.quad(pass.m_index, fbo, program, quad);
	};

	auto pass_combine = [](GfxSystem& gfx, Render& render, const Godrays& godrays, Texture& source)
	{
		static Program& program = gfx.programs().create("godrays_combine");
		program.m_sources[ShaderType::Vertex] = godrays_combine_vertex();
		program.m_sources[ShaderType::Fragment] = godrays_combine_fragment();

		Pass pass = render.next_pass("godrays_combine", PassType::PostProcess);

		filter.source0(render.m_target->m_diffuse);
		filter.source1(source);

		filter.uniform(pass.m_index, "u_godrays_combine_p0", vec4(godrays.m_intensity, 0.f, 0.f, 0.f));

		filter.quad(pass.m_index, *render.m_target_fbo, program, pass.m_viewport->m_rect);
	};

	pass_mask_depth(gfx, render, godrays, depth);

	// Render god-rays

	// Maximum length of god-rays (in texture space [0,1]X[0,1])
	const float filter_length = 1.f;
	//const float filter_length = 0.5f;

	// Samples taken by filter
	const float taps = 6.0;

	// Pass order could equivalently be 3,2,1 (instead of 1,2,3), which
	// would start with a small filter support and grow to large. however
	// the large-to-small order produces less objectionable aliasing artifacts that
	// appear as a glimmer along the length of the beams

	auto step_size = [](float filter_length, float taps, int pass)
	{
		return filter_length * pow(taps, -pass);
	};

	const vec4 rect = vec4(render.m_rect);
	const vec4 rect4 = rect / 4.f;

	// pass 1 - render into first ping-pong target
	const RenderQuad quad0 = { depth.source_quad(rect, true), pong.dest_quad(rect4, true), true };
	pass_blur(gfx, render, godrays, pong, depth, step_size(filter_length, taps, 1.0), quad0);

	// pass 2 - render into second ping-pong target
	const RenderQuad quad1 = { pong.source_quad(rect4, true), ping.dest_quad(rect4, true), true };
	pass_blur(gfx, render, godrays, ping, pong, step_size(filter_length, taps, 2.0), quad1);

	// pass 3 - 1st RT
	const RenderQuad quad2 = { ping.source_quad(rect4, true), pong.dest_quad(rect4, true), true };
	pass_blur(gfx, render, godrays, pong, ping, step_size(filter_length, taps, 3.0), quad2);

	// final pass - composite god-rays onto colors
	pass_combine(gfx, render, godrays, pong);

	//copy.debug_show_texture(render, depth, vec4(0.f));
	copy.debug_show_texture(render, pong, vec4(0.f));
}

void xx_effect_godrays(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	static ImporterOBJ obj_importer(app.m_gfx);

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	constexpr float orbit_radius = 200.f;

	static Godrays godrays = {};

	static Node3* node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 3000.f;
		camera.m_eye.z = 200.f;

		static Program& solid = app.m_gfx.programs().fetch("solid");

		Material& material = app.m_gfx.materials().create("material", [&](Material& m) {
			m.m_program = &solid;
			m.m_base.m_depth_draw = DepthDraw::Enabled;
			m.m_solid.m_colour = rgb(0x000000);
			//m.m_solid.m_colour = rgb(0xffffff);
		});

		Model& model = *app.m_gfx.models().file("tree"); // tree.obj
		model.m_items[0].m_material = &material;

		Node3& ntree = gfx::nodes(scene).add(Node3(vec3(0.f, -150.f, -150.f), ZeroQuat, vec3(400.f)));
		gfx::items(scene).add(Item(ntree, model, 0U, &material));

		Model& sphere = app.m_gfx.shape(Sphere(1.f));
		Node3& nsphere = gfx::nodes(scene).add(Node3(vec3(0.f), ZeroQuat, vec3(20.f)));
		gfx::items(scene).add(Item(nsphere, sphere, 0U, &material));
		node = &nsphere;

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			//pass_fake_sun(gfx, render, godrays);
			//pass_opaque(gfx, render);
			pass_background(gfx, render);
			pass_solid(gfx, render);
			//renderer.render(scene, camera, postprocessing.rtTextureColors);
			//renderer.render(scene, camera, postprocessing.rtTextureDepth, true);
			pass_godrays(gfx, render, godrays);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

	Gnode& root = viewer.m_scene.begin();
	gfx::radiance(root, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_frame.m_size / 2.f);
	}

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * 0.036f;
	camera.m_eye.y += (-(mouse.y) - camera.m_eye.y) * 0.036f;

	const float time = app.m_gfx.m_time * 0.5f;

	static vec3 position = vec3(0.f);
	position.x = orbit_radius * cos(time);
	position.z = orbit_radius * sin(time) - 100.f;

	node->apply(position);

	// Find the screenspace position of the sun
	const mat4 viewproj = camera.m_projection * camera.m_transform;
	vec3 sun = mulp(viewproj, godrays.m_sun_position);
	sun = (sun + 1.f) / 2.f;

	godrays.m_sun_screen = vec2(sun.x, sun.y);
}