//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

// This Bloom Pass is inspired by the bloom pass of the Unreal Engine. It creates a mip map chain of bloom textures and blur them
// with different radii. Because of the weigted combination of mips, and since larger blurs are done on higher mips, this bloom
// is better in quality and performance.

#if 0
	uniforms: {

		"tDiffuse": { type: "t", value: null },
		"luminosityThreshold": { type: "f", value: 1.0 },
		"smoothWidth": { type: "f", value: 1.0 },
		"defaultColor": { type: "c", value: new THREE.Color(0x000000) },
		"defaultOpacity":  { type: "f", value: 0.0 }

	},
#endif

static string luminosity_vertex()
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
	
static string luminosity_fragment()
{
	string shader =

		"uniform sampler2D tDiffuse;\n"
		"uniform vec3 defaultColor;\n"
		"uniform float defaultOpacity;\n"
		"uniform float luminosityThreshold;\n"
		"uniform float smoothWidth;\n"

		"varying vec2 vUv;\n"

		"void main() {\n"

			"vec4 texel = texture2D(tDiffuse, vUv);\n"

			"vec3 luma = vec3(0.299, 0.587, 0.114);\n"

			"float v = dot(texel.xyz, luma);\n"

			"vec4 outputColor = vec4(defaultColor.rgb, defaultOpacity);\n"

			"float alpha = smoothstep(luminosityThreshold, luminosityThreshold + smoothWidth, v);\n"

			"gl_FragColor = mix(outputColor, texel, alpha);\n"

		"}";

	return shader;
}

/**
 * @author spidersharma / http://eduperiment.com/
 *
 * Inspired from Unreal Engine
 * https://docs.unrealengine.com/latest/INT/Engine/Rendering/PostProcessEffects/Bloom/
 */

#if 0
	defines: {
		"KERNEL_RADIUS": kernelRadius,
		"SIGMA": kernelRadius
	},

	uniforms: {
		"colorTexture": { value: null },
		"texSize": { value: new THREE.Vector2(0.5, 0.5) },
		"direction": { value: new THREE.Vector2(0.5, 0.5) }
	},
#endif

static string blur_vertex()
{
	string shader =

		"varying vec2 vUv;\n\
		void main() {\n\
			vUv = uv;\n\
			gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0);\n\
		}";

	return shader;
}
	
static string blur_fragment()
{
	string shader =

		"#include <common>\n"
		"varying vec2 vUv;\n"
		"uniform sampler2D colorTexture;\n"
		"uniform vec2 texSize;\n"
		"uniform vec2 direction;\n"
		"\n"
		"float gaussianPdf(in float x, in float sigma) {\n"
		"	return 0.39894 * exp(-0.5 * x * x/(sigma * sigma))/sigma;\n"
		"}\n"
		"void main() {\n"
		"	vec2 invSize = 1.0 / texSize;\n"
		"	float fSigma = float(SIGMA);\n"
		"	float weightSum = gaussianPdf(0.0, fSigma);\n"
		"	vec3 diffuseSum = texture2D(colorTexture, vUv).rgb * weightSum;\n"
		"	for(int i = 1; i < KERNEL_RADIUS; i ++) {\n"
		"		float x = float(i);\n"
		"		float w = gaussianPdf(x, fSigma);\n"
		"		vec2 uvOffset = direction * invSize * x;\n"
		"		vec3 sample1 = texture2D(colorTexture, vUv + uvOffset).rgb;\n"
		"		vec3 sample2 = texture2D(colorTexture, vUv - uvOffset).rgb;\n"
		"		diffuseSum += (sample1 + sample2) * w;\n"
		"		weightSum += 2.0 * w;\n"
		"	}\n"
		"	gl_FragColor = vec4(diffuseSum/weightSum, 1.0);\n"
		"}";

	return shader;
}

#if 0
			defines: {
				"NUM_MIPS": nMips
			},

			uniforms: {
				"blurTexture1": { value: null },
				"blurTexture2": { value: null },
				"blurTexture3": { value: null },
				"blurTexture4": { value: null },
				"blurTexture5": { value: null },
				"dirtTexture": { value: null },
				"bloomStrength": { value: 1.0 },
				"bloomFactors": { value: null },
				"bloomTintColors": { value: null },
				"bloomRadius": { value: 0.0 }
			},
#endif

static string merge_vertex()
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

static string merge_fragment()
{
	string shader =
		"varying vec2 vUv;\
		uniform sampler2D blurTexture1;\
		uniform sampler2D blurTexture2;\
		uniform sampler2D blurTexture3;\
		uniform sampler2D blurTexture4;\
		uniform sampler2D blurTexture5;\
		uniform sampler2D dirtTexture;\
		uniform float bloomStrength;\
		uniform float bloomRadius;\
		uniform float bloomFactors[NUM_MIPS];\
		uniform vec3 bloomTintColors[NUM_MIPS];\
		\
		float lerpBloomFactor(const in float factor) { \
			float mirrorFactor = 1.2 - factor;\
			return mix(factor, mirrorFactor, bloomRadius);\
		}\
		\
		void main() {\
			gl_FragColor = bloomStrength * (lerpBloomFactor(bloomFactors[0]) * vec4(bloomTintColors[0], 1.0) * texture2D(blurTexture1, vUv) + \
												lerpBloomFactor(bloomFactors[1]) * vec4(bloomTintColors[1], 1.0) * texture2D(blurTexture2, vUv) + \
												lerpBloomFactor(bloomFactors[2]) * vec4(bloomTintColors[2], 1.0) * texture2D(blurTexture3, vUv) + \
												lerpBloomFactor(bloomFactors[3]) * vec4(bloomTintColors[3], 1.0) * texture2D(blurTexture4, vUv) + \
												lerpBloomFactor(bloomFactors[4]) * vec4(bloomTintColors[4], 1.0) * texture2D(blurTexture5, vUv));\
		}";
	return shader;
}

struct Bloom
{
	float exposure = 1.f;
	float strength = 1.f;
	float radius;
	float threshold;
	float levels[5] = { 1.0, 0.8, 0.6, 0.4, 0.2 };
	uvec2 resolution = uvec2(256U);
};

void pass_unreal_bloom(GfxSystem& gfx, Render& render, const Bloom& bloom)
{
	//var bloomPass = new THREE.UnrealBloomPass(new THREE.Vector2(window.innerWidth, window.innerHeight), 1.5, 0.4, 0.85);
	//bloomPass.renderToScreen = true;
	//bloomPass.threshold = params.bloomThreshold;
	//bloomPass.strength = params.bloomStrength;
	//bloomPass.radius = params.bloomRadius;

	static BlockCopy& copy = *gfx.m_renderer.block<BlockCopy>();
	static BlockFilter& filter = *gfx.m_renderer.block<BlockFilter>();

	auto pass_lum = [](GfxSystem& gfx, Render& render, const Bloom& bloom, FrameBuffer& fbo)
	{
		static Program& program = gfx.programs().create("bloom_lum");
		program.m_sources[ShaderType::Vertex] = luminosity_vertex();
		program.m_sources[ShaderType::Fragment] = luminosity_fragment();

		// create color only once here, reuse it later inside the render function
		Colour clearColor = Colour(0.f);

		// luminosity high pass material

		Pass pass = render.next_pass("bloom_lum", PassType::PostProcess);

		filter.uniform(pass.m_index, "u_glow_lum_p0", vec4(bloom.threshold, 0.01f, 0.f, 0.f));

		filter.source0(render.m_target->m_diffuse);

		filter.quad(pass.m_index, fbo, program);
	};

	enum BlurPass { BlurH, BlurV };
	enum BlurOptions { BLUR_KERNEL_SIZE };

	auto pass_blur = [](GfxSystem& gfx, Render& render, BlurPass d, Texture& source, FrameBuffer& dest, uint8_t kernel_size)
	{
		static Program& program = gfx.programs().create("bloom_blur");
		program.m_sources[ShaderType::Vertex] = blur_vertex();
		program.m_sources[ShaderType::Fragment] = blur_fragment();

		Pass pass = render.next_pass("bloom_blur", PassType::PostProcess);

		constexpr vec2 dirs[] = { vec2(1.f, 0.f), vec2(0.f, 1.f) };

		filter.uniform(pass.m_index, "u_bloom_blur_p0", vec4(dirs[d], vec2(0.f, 0.f)));
		filter.source0(source);

		ProgramVersion version = { &program };
		version.set_mode(0, BLUR_KERNEL_SIZE, kernel_size);

		filter.quad(pass.m_index, dest, version);
	};

	auto pass_merge = [](GfxSystem& gfx, Render& render, const Bloom& bloom)//, FrameBuffer& fbo)
	{
		static Program& program = gfx.programs().create("bloom_merge");
		program.m_sources[ShaderType::Vertex] = blur_vertex();
		program.m_sources[ShaderType::Fragment] = blur_fragment();

		Pass pass = render.next_pass("bloom_merge", PassType::PostProcess);

		const Colour white = Colour(1.f);
		const vec4 glow_levels[2] = { vec4(1.0f, 0.8f, 0.6f, 0.4f), vec4(0.2f, 0.0f, 0.0f, 0.0f) };
		const vec4 glow_tint[5] = { to_vec4(white), to_vec4(white), to_vec4(white), to_vec4(white), to_vec4(white) };

		filter.uniform(pass.m_index, "u_glow_p0", vec4(bloom.strength, bloom.radius, 0.f, 0.f));
		filter.uniforms(pass.m_index, "u_glow_levels", glow_levels, 2U);
		filter.uniforms(pass.m_index, "u_glow_colors", glow_tint, 5U);

		filter.source0(render.m_target->m_diffuse);
		filter.source1(render.m_target->m_swap_cascade.last().m_texture);

		RenderTarget& target = *render.m_target;
		filter.quad(pass.m_index, target.m_post_process.swap(), program, pass.m_viewport->m_rect);

		// additive blend bloom over target
		copy.quad(render.composite_pass(), *render.m_target_fbo, target.m_post_process.last(), pass.m_viewport->m_rect);
	};

	// 1. Extract Bright Areas
	pass_lum(gfx, render, bloom, render.m_target->m_ping_pong.swap());

	// 2. Blur All the mips progressively
	//SwapCascade& swap = render.m_target->m_swap_cascade;
	static SwapCascade swap;
	if(!swap.m_one.m_texture.valid())
		swap.create(bloom.resolution, bgfx::TextureFormat::RGBA8);

	Texture* source = &render.m_target->m_ping_pong.last();

	constexpr size_t kernel_sizes[] = { 3, 5, 7, 9, 11 };
	
	for(size_t i = 0; i < 5; i++)
	{
		Cascade& h = swap.swap();
		pass_blur(gfx, render, BlurH, *source, *h.m_fbos[i], kernel_sizes[i]);

		Cascade& v = swap.swap();
		pass_blur(gfx, render, BlurV, h.m_texture, *v.m_fbos[i], kernel_sizes[i]);

		source = &v.m_texture;
	}

	// Composite All the mips
	pass_merge(gfx, render, bloom);

}

//<script src="js/loaders/GLTFLoader.js"></script>

void xx_effect_unreal_bloom(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);
	//controls.maxPolarAngle = c_pi * 0.5;
	//controls.minDistance = 1;
	//controls.maxDistance = 10;

	//renderer.toneMapping = THREE.ReinhardToneMapping;

	Scene& scene = viewer.m_scene;

	static Node3* node = nullptr;

	static Bloom bloom = { 1.f, 1.5, 0.f, 0.f };

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 100.f;
		camera.m_eye = vec3(-5.f, 2.5f, -3.5f);

		//scene.add(new THREE.AmbientLight(0x404040));

		//pointLight = new THREE.PointLight(0xffffff, 1);
		//camera.add(pointLight);

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);
			pass_unreal_bloom(gfx, render, bloom);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);

		Model& model = *app.m_gfx.models().file("PrimaryIonDrive.glb");

		Node3& n = gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(n, model));

		// Mesh contains self-intersecting semi-transparent faces, which display
		// z-fighting unless depthWrite is disabled.
		//var core = model.getObjectByName('geo1_HoloFillDark_0');
		//core.material.depthWrite = false;

		//mixer = new THREE.AnimationMixer(model);
		//var clip = gltf.animations[ 0 ];
		//mixer.clipAction(clip.optimize()).play();

		//var gui = new dat.GUI();
		//
		//gui.add(params, 'exposure', 0.1, 2).onChange(function (value) {
		//	renderer.toneMappingExposure = Math.pow(value, 4.0);
		//});
		//
		//gui.add(params, 'bloomThreshold', 0.0, 1.0).onChange(function (value) {
		//	bloomPass.threshold = Number(value);
		//});
		//
		//gui.add(params, 'bloomStrength', 0.0, 3.0).onChange(function (value) {
		//	bloomPass.strength = Number(value);
		//});
		//
		//gui.add(params, 'bloomRadius', 0.0, 1.0).step(0.01).onChange(function (value) {
		//	bloomPass.radius = Number(value);
		//});


	}

	//const float delta = clock.getDelta();

	//mixer.update(delta);
}
