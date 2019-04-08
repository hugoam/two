//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>
#include <ecs/ECS.hpp>

#include <xx_three/xx_three.h>

// This Bloom Pass is inspired by the bloom pass of the Unreal Engine. It creates a mip map chain of bloom textures and blur them
// with different radii. Because of the weigted combination of mips, and since larger blurs are done on higher mips, this bloom
// is better in quality and performance.

struct HighPass
{
	float smoothWidth = 1.f;
	Colour defaultColor = Colour::None;
	// float defaultOpacity = 0.f;
};

static string filter_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"

	"#include <filter.sh>\n"

	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";
	
static string luminosity_fragment =

	"$input v_uv0\n"

	"#include <filter.sh>\n"

	"uniform vec4 u_glow_lum_p0;\n"
	"#define u_threshold    u_glow_lum_p0.x\n"
	"#define u_smooth_width u_glow_lum_p0.y\n"

	//"uniform vec3 defaultColor;\n"
	//"uniform float defaultOpacity;\n"
	
	"void main() {\n"

		"vec4 texel = texture2D(s_source_0, v_uv0);\n"

		"vec3 luma = vec3(0.299, 0.587, 0.114);\n"
		"float v = dot(texel.xyz, luma);\n"

		"vec4 outputColor = vec4_splat(0.0);\n" //vec4(defaultColor.rgb, defaultOpacity);\n"

		"float alpha = smoothstep(u_threshold, u_threshold + u_smooth_width, v);\n"

		"gl_FragColor = mix(outputColor, texel, alpha);\n"
	"}\n";

static Program& highpass_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("bloom_lum");
	program.set_source(ShaderType::Vertex, filter_vertex);
	program.set_source(ShaderType::Fragment, luminosity_fragment);
	return program;
}

// @author spidersharma / http://eduperiment.com/
// Inspired from Unreal Engine
// https://docs.unrealengine.com/latest/INT/Engine/Rendering/PostProcessEffects/Bloom/

static string blur_fragment =

	"$input v_uv0\n"

	"#include <filter.sh>\n"
	"#include <convert.sh>\n"

	"#define SIGMA KERNEL_RADIUS\n"

	"uniform vec4 u_glow_blur_p0;\n"
	"#define u_direction u_glow_blur_p0.xy\n"
	"#define u_level_size u_glow_blur_p0.zw\n"

	"float gaussianPdf(float x, float sigma) {\n"
	"	return 0.39894 * exp(-0.5 * x * x / (sigma * sigma)) / sigma;\n"
	"}\n"

	"void main() {\n"
	"	vec2 invSize = 1.0 / u_level_size;\n"
	"	float fSigma = float(SIGMA);\n"
	"	float weightSum = gaussianPdf(0.0, fSigma);\n"
	"	vec3 diffuseSum = texture2DLod(s_source_0, v_uv0, float(u_source_0_level)).rgb * weightSum;\n"

	"	for(int i = 1; i < KERNEL_RADIUS; i++) {\n"
	"		float x = float(i);\n"
	"		float w = gaussianPdf(x, fSigma);\n"
	"		vec2 uvOffset = u_direction * invSize * x;\n"
	"		vec3 sample1 = texture2DLod(s_source_0, v_uv0 + uvOffset, float(u_source_0_level)).rgb;\n"
	"		vec3 sample2 = texture2DLod(s_source_0, v_uv0 - uvOffset, float(u_source_0_level)).rgb;\n"
	"		diffuseSum += (sample1 + sample2) * w;\n"
	"		weightSum += 2.0 * w;\n"
	"	}\n"

	"	gl_FragColor = vec4(diffuseSum / weightSum, 1.0);\n"
	//"	gl_FragColor = vec4(hsl_to_rgb(vec3(u_source_0_level / 5.0, 1.0, 0.5)), 1.0);\n"
	//"	gl_FragColor = vec4(vec3_splat(float(u_source_0_level) / 5.0), 1.0);\n"
	"}\n";

static Program& blur_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("bloom_blur");
	program.set_source(ShaderType::Vertex, filter_vertex);
	program.set_source(ShaderType::Fragment, blur_fragment);
	program.register_block(*gfx.m_filter);
	program.register_modes(0, { "KERNEL_RADIUS" });
	return program;
}

static string merge_fragment =

	"$input v_uv0\n"

	"#include <filter.sh>\n"

	"uniform vec4 u_glow_merge_p0;\n"
	"#define u_glow_strength u_glow_merge_p0.x\n"
	"#define u_glow_radius u_glow_merge_p0.y\n"

	"uniform vec4 u_glow_levels[2];\n"
	"uniform vec4 u_glow_colors[5];\n"

	"float bloomFactor(float factor) { \n"
	"	float mirrorFactor = 1.2 - factor;\n"
	"	return mix(factor, mirrorFactor, u_glow_radius);\n"
	"}\n"

	"void main() {\n"
	"	vec4 bloom = u_glow_strength * (bloomFactor(u_glow_levels[0].x) * u_glow_colors[0] * texture2DLod(s_source_1, v_uv0, 1.0) + \n"
	"									bloomFactor(u_glow_levels[0].y) * u_glow_colors[1] * texture2DLod(s_source_1, v_uv0, 2.0) + \n"
	"									bloomFactor(u_glow_levels[0].z) * u_glow_colors[2] * texture2DLod(s_source_1, v_uv0, 3.0) + \n"
	"									bloomFactor(u_glow_levels[0].w) * u_glow_colors[3] * texture2DLod(s_source_1, v_uv0, 4.0) + \n"
	"									bloomFactor(u_glow_levels[1].x) * u_glow_colors[4] * texture2DLod(s_source_1, v_uv0, 5.0));\n"
	"	gl_FragColor = texture2DLod(s_source_0, v_uv0, 0.0) + bloom;"
	"}\n";

static Program& merge_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("bloom_merge");
	program.set_source(ShaderType::Vertex, filter_vertex);
	program.set_source(ShaderType::Fragment, merge_fragment);
	return program;
}

struct Bloom
{
	float exposure = 1.f;
	float strength = 1.5f;
	float radius = 0.4f;
	float threshold = 0.85f;
	float levels[5] = { 1.0, 0.8, 0.6, 0.4, 0.2 };
	uvec2 resolution = uvec2(256U);
};

void pass_unreal_bloom(GfxSystem& gfx, Render& render, const Bloom& bloom)
{
	auto pass_lum = [](GfxSystem& gfx, Render& render, const Bloom& bloom, FrameBuffer& fbo)
	{
		static Program& program = highpass_program(gfx);

		// luminosity high pass

		Pass pass = render.next_pass("bloom_lum", PassType::PostProcess);

		gfx.m_filter->uniform(pass, "u_glow_lum_p0", vec4(bloom.threshold, 0.01f, 0.f, 0.f));

		gfx.m_filter->source0(render.m_target->m_diffuse);

		gfx.m_filter->quad(pass, fbo, program);
	};

	enum BlurPass { BlurH, BlurV };
	enum BlurOptions { KERNEL_SIZE };

	auto pass_blur = [](GfxSystem& gfx, Render& render, BlurPass d, Texture& source, int source_level, FrameBuffer& dest, uint8_t kernel_size)
	{
		static Program& program_blur = blur_program(gfx);
		ProgramVersion program = { program_blur };

		Pass pass = render.next_pass("bloom_blur", PassType::PostProcess);

		constexpr vec2 dirs[] = { vec2(1.f, 0.f), vec2(0.f, 1.f) };

		gfx.m_filter->uniform(pass, "u_glow_blur_p0", vec4(dirs[d], vec2(dest.m_size)));

		gfx.m_filter->source0p(source, program, source_level);

		program.set_mode(0, KERNEL_SIZE, kernel_size);

		gfx.m_filter->quad(pass, dest, program);
	};

	auto pass_merge = [](GfxSystem& gfx, Render& render, const Bloom& bloom, Texture& source)
	{
		static Program& program = merge_program(gfx);

		Pass pass = render.next_pass("bloom_merge", PassType::PostProcess);

		static const vec4 white = to_vec4(Colour(1.f));
		static const float glow_levels[5] = { 1.0f, 0.8f, 0.6f, 0.4f, 0.2f };
		static const vec4 glow_tint[5] = { white, white, white, white };

		gfx.m_filter->uniform(pass, "u_glow_merge_p0", vec4(bloom.strength, bloom.radius, 0.f, 0.f));
		gfx.m_filter->uniforms(pass, "u_glow_levels", glow_levels);
		gfx.m_filter->uniforms4(pass, "u_glow_colors", glow_tint);

		gfx.m_filter->source0(render.m_target->m_diffuse);
		gfx.m_filter->source1(source);

		gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);

		gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, render.m_target->m_post.last());
	};

	// 1. Extract bright areas
	pass_lum(gfx, render, bloom, render.m_target->m_post.swap());

	//copy.debug_show_texture(render, render.m_target->m_ping_pong.last(), vec4(0.f));

	// 2. Blur all the mips progressively
	//SwapCascade& swap = render.m_target->m_swap_cascade;
	static SwapCascade swap;
	if(!swap.m_one.m_texture.valid())
		//swap.create(bloom.resolution, TextureFormat::RGBA8);
		swap.create(bloom.resolution, TextureFormat::RGBA16F);

	Texture* source = &render.m_target->m_post.last();

	constexpr size_t kernel_sizes[] = { 0, 3, 5, 7, 9, 11 };

	for(size_t i = 1; i < 6; i++)
	{
		Cascade& h = swap.swap();
		pass_blur(gfx, render, BlurH, *source, i - 1, *h.m_fbos[i], kernel_sizes[i]);

		Cascade& v = swap.swap();
		pass_blur(gfx, render, BlurV, h.m_texture, i, *v.m_fbos[i], kernel_sizes[i]);

		source = &v.m_texture;
	}

	//gfx.m_copy->debug_show_texture(render, swap.last().m_texture, vec4(0.f), 3);
	//gfx.m_copy->debug_show_texture(render, *source, vec4(0.f));

	// Composite all the mips
	pass_merge(gfx, render, bloom, *source);

}

void xx_effect_bloom(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterGltf gltf_importer(app.m_gfx);

	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);
	//controls.maxPolarAngle = c_pi * 0.5;
	//controls.minDistance = 1;
	//controls.maxDistance = 10;

	static Tonemap tonemap;
	tonemap.m_mode = TonemapMode::Reinhardt;
	//tonemap.m_exposure = 3.f;

	static BCS bcs;

	Scene& scene = viewer.m_scene;

	static Bloom bloom = { 1.f, 1.5, 0.f, 0.f };
	bloom.exposure = 1.f;
	bloom.strength = 1.5f;
	bloom.threshold = 0.f;
	bloom.radius = 0.f;

	bloom.resolution = app.m_gfx.main_target().m_size;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 100.f;
		camera.m_eye = vec3(-5.f, 2.5f, -3.5f);

		Zone& env = scene.m_env;
		env.m_radiance.m_colour = rgb(0x404040);

		Node3& ln = gfx::nodes(scene).add(Node3());
		gfx::lights(scene).add(Light(ln, LightType::Point, false, rgb(0xffffff), 1.f, 0.f));

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);

			pass_begin_post(gfx, render);
			pass_tonemap(gfx, render, tonemap, bcs);

			pass_unreal_bloom(gfx, render, bloom);
			pass_flip(gfx, render);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);

		Model& model = *app.m_gfx.models().file("PrimaryIonDrive"); // .glb

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model));
		Mime& mi = gfx::mimes(scene).add(Mime(n));
		mi.add_item(it);

		string anim = mi.m_rig.m_skeleton.m_animations[0]->m_name;
		mi.start(anim, true, 0.f, 1.f);

		// Mesh contains self-intersecting semi-transparent faces, which display
		// z-fighting unless depthWrite is disabled.
		//var core = model.getObjectByName('geo1_HoloFillDark_0');
		//core.material.depthWrite = false;
	}

	scene.update();

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::sheet(*dock);

		float exposure = pow(tonemap.m_exposure, 1.0 / 4.0);

		Widget& controls = ui::stack(sheet);
		ui::slider_field<float>(controls, "threshold", { bloom.threshold, { 0.f, 1.f, 0.01f } });
		ui::slider_field<float>(controls, "strength",  { bloom.strength,  { 0.f, 3.f, 0.1f } });
		ui::slider_field<float>(controls, "radius",    { bloom.radius,    { 0.f, 1.f, 0.01f } });


		ui::slider_field<float>(controls, "exposure", { exposure, { 0.1f, 2.f, 0.01f } });

		tonemap.m_exposure = pow(exposure, 4.0);
	}

	//const float delta = clock.getDelta();

	//mixer.update(delta);
}
