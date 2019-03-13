//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#if 0
THREE.SAOShader = {
	defines: {
		'NUM_SAMPLES': 7,
		'NUM_RINGS': 4,
		'DIFFUSE_TEXTURE': 0,
		'PERSPECTIVE_CAMERA': 1
	},
	uniforms: {

		'size': { type: 'v2', value: new THREE.Vector2(512, 512) },

		'scale': { type: 'f', value: 1.0 },
		'intensity': { type: 'f', value: 0.1 },
		'bias': { type: 'f', value: 0.5 },

		'minResolution': { type: 'f', value: 0.0 },
		'kernelRadius': { type: 'f', value: 100.0 },
		'randomSeed': { type: 'f', value: 0.0 }
	},
#endif

static string sao_vertex()
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

static string sao_fragment()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"uniform vec4 u_sao_p0;\n"
		"#define u_scale;\n"
		"#define u_intensity;\n"
		"#define u_bias;\n"
		"\n"
		"uniform vec4 u_sao_p1;\n"
		"#define u_kernelRadius;\n"
		"#define u_minResolution;\n"
		"#define u_size;\n"
		//"uniform float randomSeed;\n"
		"\n"
		"// RGBA depth\n"
		"\n"
		"#include <packing>\n"
		"\n"
		"vec4 getDefaultColor(vec2 screenPosition) {\n"
		"	#if DIFFUSE_TEXTURE == 1\n"
		"	return texture2D(s_diffuse, v_uv0);\n"
		"	#else\n"
		"	return vec4(1.0);\n"
		"	#endif\n"
		"}\n"

		"float getDepth(vec2 screenPosition) {\n"
		"	return texture2D(tDepth, screenPosition).x;\n"
		"}\n"

		"float getViewZ(float depth) {\n"
		"	#if PERSPECTIVE_CAMERA == 1\n"
		"	return perspectiveDepthToViewZ(depth);\n"
		"	#else\n"
		"	return orthographicDepthToViewZ(depth);\n"
		"	#endif\n"
		"}\n"

		"vec3 getViewPosition(vec2 screenPosition, float depth, float viewZ) {\n"
		"	float clipW = cameraProjectionMatrix[2][3] * viewZ + cameraProjectionMatrix[3][3];\n"
		"	vec4 clipPosition = vec4((vec3(screenPosition, depth) - 0.5) * 2.0, 1.0);\n"
		"	clipPosition *= clipW; // unprojection.\n"

		"	return (cameraInverseProjectionMatrix * clipPosition).xyz;\n"
		"}\n"

		"vec3 getViewNormal(vec3 viewPosition, vec2 screenPosition) {\n"
		"	return unpackRGBToNormal(texture2D(tNormal, screenPosition).xyz);\n"
		"}\n"

		"float scaleDividedByCameraFar;\n"
		"float minResolutionMultipliedByCameraFar;\n"

		"float getOcclusion(vec3 centerViewPosition, vec3 centerViewNormal, vec3 sampleViewPosition) {\n"
		"	vec3 viewDelta = sampleViewPosition - centerViewPosition;\n"
		"	float viewDistance = length(viewDelta);\n"
		"	float scaledScreenDistance = scaleDividedByCameraFar * viewDistance;\n"

		"	return max(0.0, (dot(centerViewNormal, viewDelta) - minResolutionMultipliedByCameraFar) / scaledScreenDistance - bias) / (1.0 + pow2(scaledScreenDistance));\n"
		"}\n"

		"// moving costly divides into consts\n"
		"const float ANGLE_STEP = PI2 * float(NUM_RINGS) / float(NUM_SAMPLES);\n"
		"const float INV_NUM_SAMPLES = 1.0 / float(NUM_SAMPLES);\n"

		"float getAmbientOcclusion(vec3 centerViewPosition) {\n"
		"	// precompute some variables require in getOcclusion.\n"
		"	scaleDividedByCameraFar = u_scale / u_z_far;\n"
		"	minResolutionMultipliedByCameraFar = u_minResolution * u_z_far;\n"
		"	vec3 centerViewNormal = getViewNormal(centerViewPosition, v_uv0);\n"

		"	// jsfiddle that shows sample pattern: https://jsfiddle.net/a16ff1p7/\n"
		"	float angle = rand(v_uv0 + randomSeed) * PI2;\n"
		"	vec2 radius = vec2(kernelRadius * INV_NUM_SAMPLES) / size;\n"
		"	vec2 radiusStep = radius;\n"

		"	float occlusionSum = 0.0;\n"
		"	float weightSum = 0.0;\n"

		"	for(int i = 0; i < NUM_SAMPLES; i ++) {\n"
		"		vec2 sampleUv = v_uv0 + vec2(cos(angle), sin(angle)) * radius;\n"
		"		radius += radiusStep;\n"
		"		angle += ANGLE_STEP;\n"

		"		float sampleDepth = getDepth(sampleUv);\n"
		"		if(sampleDepth >= (1.0 - EPSILON)) {\n"
		"			continue;\n"
		"		}\n"

		"		float sampleViewZ = getViewZ(sampleDepth);\n"
		"		vec3 sampleViewPosition = getViewPosition(sampleUv, sampleDepth, sampleViewZ);\n"
		"		occlusionSum += getOcclusion(centerViewPosition, centerViewNormal, sampleViewPosition);\n"
		"		weightSum += 1.0;\n"
		"	}\n"

		"	if(weightSum == 0.0) discard;\n"

		"	return occlusionSum * (intensity / weightSum);\n"
		"}\n"


		"void main() {\n"
		"	float centerDepth = getDepth(v_uv0);\n"
		"	if(centerDepth >= (1.0 - EPSILON)) {\n"
		"		discard;\n"
		"	}\n"

		"	float centerViewZ = getViewZ(centerDepth);\n"
		"	vec3 viewPosition = getViewPosition(v_uv0, centerDepth, centerViewZ);\n"

		"	float ambientOcclusion = getAmbientOcclusion(viewPosition);\n"

		"	gl_FragColor = getDefaultColor(v_uv0);\n"
		"	gl_FragColor.xyz *=  1.0 - ambientOcclusion;\n"
		"}";

	return shader;
}

#if 0
THREE.DepthLimitedBlurShader = {
	defines: {
		'KERNEL_RADIUS': 4,
		'PERSPECTIVE_CAMERA': 1
	},
	uniforms: {
		'size': { type: 'v2', value: new THREE.Vector2(512, 512) },
		'depthCutoff': { type: 'f', value: 10 },
	},
#endif

static string depth_blur_vertex()
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
static string depth_blur_fragment()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"#define s_diffuse s_source_0\n"
		"#define s_depth s_source_depth\n"
		"\n"
		"#include <packing>\n"
		"\n"
		"uniform vec4 u_sao_blur_p0\n"
		"#define u_inv_size u_depth_blur_p0.xy\n"
		"#define u_depth_cutoff u_depth_blur_p0.z\n"
		"\n"
		"uniform vec4 u_sao_blur_samples[KERNEL_RADIUS + 1];\n"

		"float getDepth(vec2 screenPosition) {\n"
		"	return texture2D(tDepth, screenPosition).x;\n"
		"}\n"

		"float getViewZ(float depth) {\n"
		"	#if PERSPECTIVE_CAMERA == 1\n"
		"	return perspectiveDepthToViewZ(depth);\n"
		"	#else\n"
		"	return orthographicDepthToViewZ(depth);\n"
		"	#endif\n"
		"}\n"

		"void main() {\n"
		"	float depth = getDepth(v_uv0);\n"
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
		"		float viewZ = -getViewZ(getDepth(uv));\n"

		"		if(abs(viewZ - centerViewZ) > depthCutoff) rBreak = true;\n"

		"		if(!rBreak) {\n"
		"			diffuseSum += texture2D(s_diffuse, uv) * weight;\n"
		"			weightSum += sampleWeight;\n"
		"		}\n"

		"		uv = v_uv0 - offset;\n"
		"		viewZ = -getViewZ(getDepth(uv));\n"

		"		if(abs(viewZ - centerViewZ) > u_depth_cutoff) lBreak = true;\n"

		"		if(!lBreak) {\n"
		"			diffuseSum += texture2D(s_diffuse, uv) * weight;\n"
		"			weightSum += weight;\n"
		"		}\n"

		"	}\n"

		"	gl_FragColor = diffuseSum / weightSum;\n"
		"}";

	return shader;
}

enum class OutputSAO {
	Default,
	Beauty,
	SAO,
	Depth,
	Normal
};

struct SAO
{
	int output = 0;

	float bias = 0.5f;
	float intensity = 0.18f;
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
	OutputSAO output = OutputSAO::Default;

	static BlockCopy& copy = *gfx.m_renderer.block<BlockCopy>();
	static BlockFilter& filter = *gfx.m_renderer.block<BlockFilter>();

	static FrameBuffer target = FrameBuffer(resolution, bgfx::TextureFormat::RGBA8);
	static FrameBuffer pong = FrameBuffer(resolution, bgfx::TextureFormat::RGBA8);
	static FrameBuffer normals = FrameBuffer(resolution, bgfx::TextureFormat::RGBA8, BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_MIN_POINT);

	auto pass_normal = [](GfxSystem& gfx, Render& render, FrameBuffer& fbo)
	{
		static Program& program = gfx.programs().fetch("normal");

		Pass render_pass = render.next_pass("normals", PassType::Normals);
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;
		render_pass.m_fbo = &fbo;

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement element)
		{
			element.m_program = &program;
			element.m_shader_version = element.m_material->shader_version(*element.m_program);

			gfx.m_renderer.add_element(render, pass, element);
		};

		gfx.m_renderer.pass(render, render_pass, queue_draw_element);
	};

	auto pass_sao = [&](GfxSystem& gfx, Render& render, const SAO& sao, FrameBuffer& fbo, Texture& normals)
	{
		static Program& program = gfx.programs().create("sao");
		program.set_source(ShaderType::Vertex, sao_vertex());
		program.set_source(ShaderType::Fragment, sao_fragment());

		Pass pass = render.next_pass("normals", PassType::Normals);

		//this.saoMaterial.extensions.derivatives = true;

		filter.source0(normals);
		filter.sourcedepth(render.m_target->m_depth);

		filter.uniform(pass.m_index, "u_sao_p0", vec4(sao.bias, sao.intensity, sao.scale, 0.f));
		filter.uniform(pass.m_index, "u_sao_p1", vec4(vec2(sao.kernelRadius, sao.minResolution), vec2(resolution)));

		// this.saoMaterial.uniforms['randomSeed'].value = Math.random();
	};

	enum BlurPass { BlurV, BlurH };

	auto pass_blur = [](GfxSystem& gfx, Render& render, const SAO& sao, BlurPass d, Texture& source, FrameBuffer& dest)
	{
		static Program& program = gfx.programs().create("depth_blur");
		program.m_sources[ShaderType::Vertex] = depth_blur_vertex();
		program.m_sources[ShaderType::Fragment] = depth_blur_fragment();

		static float dev = 0.f;
		static size_t radius = 0;

		static vec2 dirs[2] = { vec2(0.f, 1.f), vec2(1.f, 0.f) };
		static float weights[8][2] = {};
		static vec2 offsets[8][2] = {};
		static vec4 samples[8][2] = {};

		if(dev != sao.blurStdDev || radius != sao.blurRadius)
		{
			for(size_t i = 0; i <= sao.blurRadius; i++)
				offsets[d][i] = dirs[d] * float(i);

			for(size_t i = 0; i <= sao.blurRadius; i++)
				weights[d][i] = gaussian(i, sao.blurStdDev);

			for(size_t i = 0; i <= sao.blurRadius; i++)
				samples[d][i] = { offsets[d][i], vec2(weights[d][i], 0.f) };

			dev = sao.blurStdDev;
			radius = sao.blurRadius;
		}

		Pass pass = render.next_pass("blur", PassType::PostProcess);

		const float depth_cutoff = sao.blurDepthCutoff * (render.m_camera.m_far - render.m_camera.m_near);
		filter.uniform(pass.m_index, "u_sao_blur_p0", vec4(vec2(dest.m_size), vec2(depth_cutoff, 0.f)));
		filter.uniforms(pass.m_index, "u_sao_blur_samples", samples[d], 8U);

		filter.source0(source);
		filter.sourcedepth(render.m_target->m_depth);
	};

	auto pass_merge = [](GfxSystem& gfx, Render& render, const SAO& sao)
	{
		static Program& program = gfx.programs().fetch("sao");

		//static bgfx::UniformHandle u_bokeh_p0 = bgfx::createUniform("u_sao_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);

		Pass pass = render.next_pass("sao", PassType::PostProcess);

		filter.source0(render.m_target->m_diffuse);
		filter.sourcedepth(render.m_target->m_depth);

		RenderTarget& target = *render.m_target;
		filter.quad(pass.m_index, target.m_post_process.swap(), program, pass.m_viewport->m_rect);

		//this.materialCopy.blending = THREE.CustomBlending;
		//this.materialCopy.blendSrc = THREE.DstColorFactor;
		//this.materialCopy.blendDst = THREE.ZeroFactor;
		//this.materialCopy.blendEquation = THREE.AddEquation;
		//this.materialCopy.blendSrcAlpha = THREE.DstAlphaFactor;
		//this.materialCopy.blendDstAlpha = THREE.ZeroFactor;
		//this.materialCopy.blendEquationAlpha = THREE.AddEquation;

		copy.quad(render.composite_pass(), *render.m_target_fbo, target.m_post_process.last(), pass.m_viewport->m_rect);
	};

	//if (this.params.output === 1)
	//	return;

	// Clear rule : default normal is facing the camera
	//pass_clear(gfx, render, normals.m_fbo, 0x7777ff, 1.f);
	pass_normal(gfx, render, normals);

	// Rendering SAO texture
	//pass_clear(gfx, render, target.m_fbo, 0xffffff, 1.f);
	pass_sao(gfx, render, sao, target, normals);

	// Blurring SAO texture
	if(sao.blur)
	{
		pass_blur(gfx, render, sao, BlurV, target, pong);
		pass_blur(gfx, render, sao, BlurH, pong, target);
	}

	if(output == OutputSAO::Default)
	{
		pass_merge(gfx, render, sao);
	}
}

void xx_effect_sao(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Node3* node = nullptr;

	static SAO sao = {};

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 65.f; camera.m_near = 3.f; camera.m_far = 10.f;
		camera.m_eye.z = 7.f;

		Node3& group = gfx::nodes(scene).add(Node3());
		node = &group;

		Node3& l0 = gfx::nodes(scene).add(Node3(vec3(-70.f, -70.f, 70.f)));
		gfx::lights(scene).add(Light(l0, LightType::Point, false, rgb(0xddffdd), 0.8f));

		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(-70.f, 70.f, 70.f)));
		gfx::lights(scene).add(Light(l1, LightType::Point, false, rgb(0xffdddd), 0.8f));

		Node3& l2 = gfx::nodes(scene).add(Node3(vec3(70.f, -70.f, 70.f)));
		gfx::lights(scene).add(Light(l2, LightType::Point, false, rgb(0xddddff), 0.8f));

		//var light3 = new THREE.AmbientLight(0xffffff, 0.05);
		//scene.add(light3);

		static Model& geometry = app.m_gfx.shape(Sphere(1.f));

		static Program& pbr = app.m_gfx.programs().fetch("pbr/pbr");

		for(size_t i = 0; i < 120; i++)
		{
			const string name = "object" + to_string(i);
			Material& material = app.m_gfx.materials().create(name, [&](Material& m) {
				m.m_program = &pbr;
				m.m_pbr.m_albedo = hsl(randf(), 1.0, 0.3);
				m.m_pbr.m_roughness = 0.5f * randf() + 0.25f;
				m.m_pbr.m_metallic = 0.f;
			});

			vec3 p = vec3(randf(), randf(), randf()) * 4.f - 2.f;
			vec3 a = vec3(randf(), randf(), randf());
			vec3 s = vec3(randf()) * 0.2f + 0.05f;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
		}

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);
			pass_sao(gfx, render, sao);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

	// Init gui
	//var gui = new dat.GUI();
	//gui.add(saoPass.params, 'output', {
	//	'Beauty': THREE.SAOPass.OUTPUT.Beauty,
	//	'Beauty+SAO': THREE.SAOPass.OUTPUT.Default,
	//	'SAO': THREE.SAOPass.OUTPUT.SAO,
	//	'Depth': THREE.SAOPass.OUTPUT.Depth,
	//	'Normal': THREE.SAOPass.OUTPUT.Normal
	//}).onChange(function (value) {
	//
	//	saoPass.params.output = parseInt(value);
	//
	//});
	//gui.add(saoPass.params, 'saoBias', - 1, 1);
	//gui.add(saoPass.params, 'saoIntensity', 0, 1);
	//gui.add(saoPass.params, 'saoScale', 0, 10);
	//gui.add(saoPass.params, 'saoKernelRadius', 1, 100);
	//gui.add(saoPass.params, 'saoMinResolution', 0, 1);
	//gui.add(saoPass.params, 'saoBlur');
	//gui.add(saoPass.params, 'saoBlurRadius', 0, 200);
	//gui.add(saoPass.params, 'saoBlurStdDev', 0.5, 150);
	//gui.add(saoPass.params, 'saoBlurDepthCutoff', 0.0, 0.1);

	const float time = app.m_gfx.m_time;

	static vec3 angles = vec3(time * 0.0002, time * 0.0001, 0.f);

	node->apply(vec3(0.f), quat(angles));
}