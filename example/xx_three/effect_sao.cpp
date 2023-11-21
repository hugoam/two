module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
#include <bgfx/bgfx.h>
module two.xxthree;

using namespace two;

#define GL_CORRUPTION_BUG 0

static string sao_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string sao_fragment =

	"$input v_uv0\n"
		
	"#include <filter.sh>\n"

	"#define NUM_SAMPLES 7\n"
	"#define NUM_RINGS 4\n"

	"#define s_normal  s_source_0\n"

	"uniform vec4 u_sao_p0;\n"
	"#define u_scale     u_sao_p0.x\n"
	"#define u_intensity u_sao_p0.y\n"
	"#define u_bias      u_sao_p0.z\n"
	"#define u_seed      u_sao_p0.w\n"
		
	"uniform vec4 u_sao_p1;\n"
	"#define u_kernelRadius  u_sao_p1.x\n"
	"#define u_minResolution u_sao_p1.y\n"
	"#define u_size          u_sao_p1.zw\n"

	"uniform mat4 u_sao_invproj;\n"

	"float toClipSpaceDepth(float depth)\n"
	"{\n"
	"#if BGFX_SHADER_LANGUAGE_GLSL\n"
	"	return depth * 2.0 - 1.0;\n"
	"#else\n"
	"	return depth;\n"
	"#endif\n"
	"}\n"

	"vec3 toClipSpace(vec2 uv, float depth)\n"
	"{\n"
	"	vec3 clip = vec3(uv * 2.0 - 1.0, toClipSpaceDepth(depth));\n"
	"#if !BGFX_SHADER_LANGUAGE_GLSL\n"
	"	clip.y = -clip.y;\n"
	"#endif\n"
	"	return clip;\n"
	"}\n"
	
	"vec3 clipToView(vec3 clip)\n"
	"{\n"
	"	vec4 wpos = mul(u_sao_invproj, vec4(clip, 1.0) );\n"
	"	return wpos.xyz / wpos.w;\n"
	"}\n"

	"vec3 getViewPosition(vec2 uv, float depth) {\n"
	"	vec3 clip = toClipSpace(uv, depth);\n"
	"	return clipToView(clip);\n"
	"}\n"

	"vec3 unpackRGBToNormal(vec3 rgb) {\n"
	"	return 2.0 * rgb.xyz - 1.0;\n"
	"}\n"

	"vec3 getViewNormal(vec3 viewPosition, vec2 uv) {\n"
	"	return unpackRGBToNormal(texture2D(s_normal, uv).xyz);\n"
	"}\n"

	"float getOcclusion(vec3 position, vec3 normal, vec3 samplePosition, float scale, float offset) {\n"
	"	vec3 delta = samplePosition - position;\n"
	"	float distance = length(delta);\n"
	"	distance = scale * distance;\n"
	"	return max(0.0, (dot(normal, delta) - offset) / distance - u_bias) / (1.0 + pow2(distance));\n"
	"}\n"

	"CONST(float) ANGLE_STEP = PI2 * float(NUM_RINGS) / float(NUM_SAMPLES);\n"
	"CONST(float) INV_NUM_SAMPLES = 1.0 / float(NUM_SAMPLES);\n"

	"void main() {\n"
	"	float depth = texture2D(s_source_depth, v_uv0).x;\n"
	"	if(depth >= (1.0 - EPSILON)) {\n"
	"		discard;\n"
	"	}\n"

	"	vec3 position = getViewPosition(v_uv0, depth);\n"

	"	// precompute some variables require in getOcclusion.\n"
	"	float scaleDividedByCameraFar = u_scale / u_z_far;\n"
	"	float minResolutionMultipliedByCameraFar = u_minResolution * u_z_far;\n"
	"	vec3 normal = getViewNormal(position, v_uv0);\n"

	"	// jsfiddle that shows sample pattern: https://jsfiddle.net/a16ff1p7/\n"
	"	float angle = rand(v_uv0 + u_seed) * PI2;\n"
	"	vec2 radius = vec2_splat(u_kernelRadius * INV_NUM_SAMPLES) / u_size;\n"
	"	vec2 step = radius;\n"

	"	float occlusionSum = 0.0;\n"
	"	float weightSum = 0.0;\n"

	"	for(int i = 0; i < NUM_SAMPLES; i ++) {\n"
	"		vec2 uv = v_uv0 + vec2(cos(angle), sin(angle)) * radius;\n"
	"		radius += step;\n"
	"		angle += ANGLE_STEP;\n"

	"		float sampleDepth = texture2D(s_source_depth, uv).x;\n"
	"		if(sampleDepth >= (1.0 - EPSILON)) {\n"
	"			continue;\n"
	"		}\n"

	"		vec3 samplePosition = getViewPosition(uv, sampleDepth);\n"
	"		occlusionSum += getOcclusion(position, normal, samplePosition, scaleDividedByCameraFar, minResolutionMultipliedByCameraFar);\n"
	"		weightSum += 1.0;\n"
	"	}\n"

	"	if(weightSum == 0.0) discard;\n"

	"	float ambientOcclusion = occlusionSum * (u_intensity / weightSum);\n"

	"	gl_FragColor = vec4(vec3_splat(1.0 - ambientOcclusion), 1.0);\n"
	"}\n";


static string depth_blur_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"
		
	"#include <filter.sh>\n"
		
	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string depth_blur_fragment =

	"$input v_uv0\n"
		
	"#define PERSPECTIVE_CAMERA 1\n"

	"#include <filter.sh>\n"
		
	"#define s_diffuse s_source_0\n"
	"#define s_depth s_source_depth\n"
		
	"uniform vec4 u_sao_blur_p0;\n"
	"#define u_inv_size     u_sao_blur_p0.xy\n"
	"#define u_depth_cutoff u_sao_blur_p0.z\n"

	"uniform vec4 u_sao_blur_samples[16];\n"
	//"uniform vec4 u_sao_blur_samples[KERNEL_RADIUS + 1];\n"

	"float getViewZ(float depth) {\n"
	"#if PERSPECTIVE_CAMERA == 1\n"
	"	return perspectiveDepthToViewZ(depth);\n"
	"#else\n"
	"	return orthographicDepthToViewZ(depth);\n"
	"#endif\n"
	"}\n"

	"void main() {\n"
	"	float depth = texture2D(s_source_depth, v_uv0).x;\n"
	"	if(depth >= (1.0 - EPSILON)) {\n"
	"		discard;\n"
	"	}\n"

	"	float centerViewZ = -getViewZ(depth);\n"
	"	bool rBreak = false, lBreak = false;\n"

	"	float weightSum = u_sao_blur_samples[0].z;\n"
	"	vec4 diffuseSum = texture2D(s_diffuse, v_uv0) * weightSum;\n"

	"	for(int i = 1; i <= KERNEL_RADIUS; i ++) {\n"

	"		float weight = u_sao_blur_samples[i].z;\n"
	"		vec2 offset = u_sao_blur_samples[i].xy * u_inv_size;\n"

	"		vec2 uv = v_uv0 + offset;\n"
	"		float viewZ = -getViewZ(texture2D(s_source_depth, uv).x);\n"

	"		if(abs(viewZ - centerViewZ) > u_depth_cutoff) rBreak = true;\n"

	"		if(!rBreak) {\n"
	"			diffuseSum += texture2D(s_diffuse, uv) * weight;\n"
	"			weightSum += weight;\n"
	"		}\n"

	"		uv = v_uv0 - offset;\n"
	"		viewZ = -getViewZ(texture2D(s_source_depth, uv).x);\n"

	"		if(abs(viewZ - centerViewZ) > u_depth_cutoff) lBreak = true;\n"

	"		if(!lBreak) {\n"
	"			diffuseSum += texture2D(s_diffuse, uv) * weight;\n"
	"			weightSum += weight;\n"
	"		}\n"

	"	}\n"

	"	gl_FragColor = diffuseSum / weightSum;\n"
	"}\n";

enum class OutputSAO
{
	Default,
	Beauty,
	SAO,
	Depth,
	Normal
};

struct SAO
{
	OutputSAO output = OutputSAO::Default;

	float bias = 0.5f;
	float intensity = 0.18f; // 0.1f
	float scale = 1.f;
	size_t kernelRadius = 100;
	float minResolution = 0;
	bool blur = true;
	size_t blurRadius = 8;
	float blurStdDev = 4.f;
	float blurDepthCutoff = 0.01f;
};

float gaussian(float x, float dev)
{
	return exp(-(x * x) / (2.f * (dev * dev))) / (sqrt(2.f * c_pi) * dev);
}

void pass_sao(GfxSystem& gfx, Render& render, const SAO& sao, uvec2 resolution = uvec2(256U))
{
	static FrameBuffer target = { resolution, TextureFormat::RGBA8 };
	static FrameBuffer pong = { resolution, TextureFormat::RGBA8 };
	//static FrameBuffer normals = { resolution, TextureFormat::RGBA8, TEXTURE_POINT };

	static Texture ndepth = { resolution, false, TextureFormat::D24S8, BGFX_TEXTURE_RT | TEXTURE_CLAMP | TEXTURE_DEPTH };
	static Texture normal = { resolution, false, TextureFormat::RGBA8, BGFX_TEXTURE_RT | TEXTURE_CLAMP };
	static FrameBuffer normalfbo =  { resolution, { &ndepth, &normal } };

	auto pass_normal = [](GfxSystem& gfx, Render& render, FrameBuffer& fbo)
	{
		static Program& program = gfx.programs().fetch("normal");

		Pass pass = render.next_pass("normals", PassType::Normals);
		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;
		pass.m_fbo = &fbo;

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			element.set_program(program);
			return true;
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	};

	auto pass_sao = [&](GfxSystem& gfx, Render& render, const SAO& sao, FrameBuffer& fbo, Texture& normals, Texture& depth)
	{
		static Program& program = gfx.programs().fetch("sao");

		Pass pass = render.next_pass("sao", PassType::PostProcess);

		gfx.m_filter->source0(normals);
		gfx.m_filter->sourcedepth(depth);

		static float seed = randf();

		gfx.m_filter->uniform(pass, "u_sao_p0", vec4(sao.scale, sao.intensity, sao.bias, seed));
		gfx.m_filter->uniform(pass, "u_sao_p1", vec4(sao.kernelRadius, sao.minResolution, vec2(resolution)));

		gfx.m_filter->uniform(pass, "u_sao_invproj", inverse(render.m_camera->m_proj));

		gfx.m_filter->quad(pass, fbo, program);
	};

	enum BlurPass { BlurV, BlurH };
	enum BlurOptions { KERNEL_RADIUS };

	auto pass_blur = [](GfxSystem& gfx, Render& render, const SAO& sao, BlurPass d, Texture& source, Texture& depth, FrameBuffer& dest)
	{
		static float dev = 0.f;
		static size_t radius = 0;

		constexpr size_t max_blur_radius = 16;
		static vec2 dirs[2] = { vec2(0.f, 1.f), vec2(1.f, 0.f) };
		static vec4 samples[2][max_blur_radius] = {};

		if(dev != sao.blurStdDev || radius != sao.blurRadius)
		{
			for(size_t dd = 0; dd < 2; ++dd)
				for(size_t i = 0; i <= sao.blurRadius; i++)
				{
					vec2 offset = dirs[dd] * float(i);
					float weight = gaussian(i, sao.blurStdDev);
					samples[dd][i] = { offset, vec2(weight, 0.f) };
				}

			dev = sao.blurStdDev;
			radius = sao.blurRadius;
		}

		ProgramVersion program = ProgramVersion(gfx.programs().fetch("depth_blur"));

		Pass pass = render.next_pass("blur", PassType::PostProcess);

		const float depth_cutoff = sao.blurDepthCutoff * (render.m_camera->m_far - render.m_camera->m_near);
		gfx.m_filter->uniform(pass, "u_sao_blur_p0", vec4(1.f / vec2(dest.m_size), depth_cutoff, 0.f));
		gfx.m_filter->uniforms4(pass, "u_sao_blur_samples", samples[d]);

		gfx.m_filter->source0(source);
		gfx.m_filter->sourcedepth(depth);

		program.set_mode(0, KERNEL_RADIUS, radius);

		gfx.m_filter->quad(pass, dest, program);
	};

	auto pass_merge = [](GfxSystem& gfx, Render& render, const SAO& sao, Texture& source)
	{

#define BLEND_OP (0                                                                     \
	| BGFX_STATE_BLEND_FUNC_SEPARATE(BGFX_STATE_BLEND_DST_COLOR, BGFX_STATE_BLEND_ZERO, \
									 BGFX_STATE_BLEND_DST_ALPHA, BGFX_STATE_BLEND_ZERO) \
	| BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_ADD)                          \
	)

#if GL_CORRUPTION_BUG
		FrameBuffer& fbo = render.m_target->m_post.swap();

		Pass blit = render.next_pass("blit", PassType::PostProcess);
		gfx.m_copy->quad(blit, fbo, render.m_target->m_diffuse);
#else
		FrameBuffer& fbo = *render.m_fbo;
#endif
		Pass pass = render.next_pass("sao merge", PassType::PostProcess);
		gfx.m_copy->quad(pass, fbo, source, BLEND_OP);
	};

	//if (this.params.output === 1)
	//	return;

	Texture& depth = render.m_target->m_depth;
	//Texture& depth = ndepth;

	// Clear rule : default normal is facing the camera
	pass_clear_fbo(gfx, render, normalfbo, rgb(0x7777ff), 1.f);
	pass_normal(gfx, render, normalfbo);

	// Rendering SAO texture
	pass_clear_fbo(gfx, render, target, rgb(0xffffff)); // , 1.f);
	pass_sao(gfx, render, sao, target, normal, depth);

	// Blurring SAO texture
	if(sao.blur)
	{
		pass_blur(gfx, render, sao, BlurV, target.m_tex, depth, pong);
		pass_blur(gfx, render, sao, BlurH, pong.m_tex, depth, target);
	}

	if(sao.output == OutputSAO::Default)
	{
		pass_merge(gfx, render, sao, target.m_tex);
	}
	else
	{
		Pass pass = render.next_pass("blit", PassType::PostProcess);
		if(sao.output == OutputSAO::SAO)
			gfx.m_copy->quad(pass, render.m_target->m_post.swap(), target.m_tex);
		else if(sao.output == OutputSAO::Normal)
			gfx.m_copy->quad(pass, render.m_target->m_post.swap(), normal);
		else if(sao.output == OutputSAO::Depth)
			gfx.m_copy->quad(pass, render.m_target->m_post.swap(), render.m_target->m_depth);
		else if(sao.output == OutputSAO::Beauty)
			gfx.m_copy->quad(pass, render.m_target->m_post.swap(), render.m_target->m_diffuse);

#if !GL_CORRUPTION_BUG
		gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, render.m_target->m_post.last());
#endif
	}

#if GL_CORRUPTION_BUG
	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, render.m_target->m_post.last());
#endif
}

EX(xx_effect_sao)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	static Node3* node = nullptr;
	struct Node { vec3 p; vec3 a; vec3 s; Node3* node; };
	static vector<Node> nodes;

	static SAO sao = {};

	auto render = [](GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		pass_clear(gfx, render);
		pass_opaque(gfx, render);
		pass_sao(gfx, render, sao, render.m_target->m_size);
	};

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 65.f; camera.m_near = 3.f; camera.m_far = 10.f;
		camera.m_eye.z = 7.f;

		sao.blur = false;
		sao.output = OutputSAO::SAO;

		static Program& depth_blur = app.m_gfx.programs().create("depth_blur");
		depth_blur.set_source(ShaderType::Vertex, depth_blur_vertex);
		depth_blur.set_source(ShaderType::Fragment, depth_blur_fragment);
		depth_blur.register_modes(0, { "KERNEL_RADIUS" });

		static Program& sao = app.m_gfx.programs().create("sao");
		sao.set_source(ShaderType::Vertex, sao_vertex);
		sao.set_source(ShaderType::Fragment, sao_fragment);

		Node3& group = gfx::nodes(scene).add(Node3());
		node = &group;

		Node3& l0 = gfx::nodes(scene).add(Node3(vec3(-70.f, -70.f, 70.f)));
		gfx::lights(scene).add(Light(l0, LightType::Point, false, rgb(0xddffdd), 0.8f, 0.f));

		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(-70.f, 70.f, 70.f)));
		gfx::lights(scene).add(Light(l1, LightType::Point, false, rgb(0xffdddd), 0.8f, 0.f));

		Node3& l2 = gfx::nodes(scene).add(Node3(vec3(70.f, -70.f, 70.f)));
		gfx::lights(scene).add(Light(l2, LightType::Point, false, rgb(0xddddff), 0.8f, 0.f));

		scene.m_env.m_radiance.m_ambient = rgb(0xffffff) * 0.05f;

		Symbol symbol; symbol.m_subdiv = uvec2(48, 24);
		Model& geometry = app.m_gfx.shape(Sphere(3.f), symbol);

		Program& pbr = app.m_gfx.programs().fetch("pbr/pbr");
		Program& three = app.m_gfx.programs().fetch("pbr/three");

		nodes.clear();
		for(size_t i = 0; i < 120; i++)
		{
			const string name = "sao" + to_string(i);
			Material& material = app.m_gfx.materials().create(name, [&](Material& m) {
				m.m_program = &three;
				m.m_pbr.m_albedo = hsl(randf(), 1.0, 0.3);
				m.m_pbr.m_roughness = 0.5f * randf() + 0.25f;
				m.m_pbr.m_metallic = 0.f;
			});

			const vec3 p = vec3(randf(), randf(), randf()) * 4.f - 2.f;
			const vec3 a = vec3(randf(), randf(), randf());
			const vec3 s = vec3(randf()) * 0.2f + 0.05f;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
			nodes.push_back({ p, a, s, &n });
		}

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

#if UI
	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::sheet(*dock);

		auto panel = [&](const string& name) -> Widget&
		{
			Widget& s = ui::expandbox(sheet, name.c_str());
			return ui::columns(s, { 0.3f, 0.7f });
		};

		Widget& a = panel("Material");

		ui::dropdown_field(a, "shape", { "Beauty+SAO", "Beauty", "SAO", "Depth", "Normal" }, (uint32_t&)sao.output);

		ui::slider_field(a, "bias",           sao.bias,         { -1.f, 1.f, 0.1f });
		ui::slider_field(a, "intensity",      sao.intensity,    { 0.f, 1.f, 0.01f });
		ui::slider_field(a, "scale",          sao.scale,        { 0.f, 10.f, 0.1f });
		ui::slider_field(a, "kernel radius", sao.kernelRadius, { 1, 100, 1 });

		ui::field(a,    "blur", sao.blur);
		ui::slider_field(a, "blur radius",       sao.blurRadius,      { 0, 200, 1 });
		ui::slider_field(a,  "blur std dev",      sao.blurStdDev,      { 0.5f, 150.f, 0.1f });
		ui::slider_field(a,  "blur depth cutoff", sao.blurDepthCutoff, { 0.0f, 0.1f, 0.01f });
	}
#endif

	const float time = app.m_gfx.m_time;

	vec3 angles = vec3(time * 0.2f, time * 0.1f, 0.f);

	node->apply(vec3(0.f), quat(angles));
	for(Node& n : nodes)
		n.node->derive(*node, n.p, quat(n.a), n.s);
}