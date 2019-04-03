//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#include <cstdio>

using namespace mud;

/**
 * @author alteredq / http://alteredqualia.com/
 *
 * Convolution shader
 * ported from o3d sample to WebGL / GLSL
 * http://o3d.googlecode.com/svn/trunk/samples/convolution.html
 */

#if 0
	'KERNEL_SIZE': '25'

	'uImageIncrement': { value: new THREE.Vector2(0.001953125, 0.0) },
	'cKernel':         { value: [] }
#endif

string convolution_vertex()
{
	string shader =

		'$input a_position, a_texcoord0\n'
		'$output v_uv0\n'

		'#include <filter.sh>\n'

		'uniform vec4 u_blooblur_p0;\n'
		'#define u_increment u_blooblur_p0.xy\n'

		'void main() {\n'
			'v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n'
			'v_uv0 = v_uv0 - ((float(KERNEL_SIZE) - 1.0) / 2.0) * u_increment;\n'
			'gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n'
		'}\n';

	return shader;
}

string convolution_fragment()
{
	string shader =

		'$input v_uv0\n'

		'#include <filter.sh>\n'

		//'uniform vec4 u_kernel[KERNEL_SIZE/4];\n'
		'uniform vec4 u_kernel[8];\n'

		'uniform vec4 u_blooblur_p0;\n'
		'#define u_increment u_blooblur_p0.xy\n'

		'void main()\n'
		'{\n'
			'vec2 uv = v_uv0;\n'
			'vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);\n'

			'for(int i = 0; i < KERNEL_SIZE; i++)\n'
			'{\n'
				'sum += texture2D(s_source_0, uv) * u_kernel[i/4][i%4];\n'
				'uv += u_increment;\n'
			'}\n'

			'gl_FragColor = sum;\n'
		'}\n';

	return shader;
}

enum BlurOptions { KERNEL_SIZE };

var convolution_program(GfxSystem gfx)
{
	var program = gfx.programs.create('convolution');
	program.set_source(two.ShaderType.Vertex, convolution_vertex());
	program.set_source(two.ShaderType.Fragment, convolution_fragment());

	program.register_modes(0, { 'KERNEL_SIZE' });
	return program;
}

vector<float> blur_kernel(float sigma)
{
	// We lop off the sqrt(2 * pi) * sigma term, since we're going to normalize anyway.

	auto gauss = [](float x, float sigma) { return exp(-sq(x) / (2.0 * sq(sigma))); };

	constexpr int kMaxKernelSize = 25;
	int kernelSize = 2.0 * ceil(sigma * 3.f) + 1;

	if (kernelSize > kMaxKernelSize) kernelSize = kMaxKernelSize;
	float halfWidth = (kernelSize - 1) * 0.5;

	vector<float> values(kernelSize); 
	float sum = 0.0;
	for (int i = 0; i < kernelSize; ++i)
	{
		values[i] = gauss(i - halfWidth, sigma);
		sum += values[i];
	}

	// normalize the kernel
	for (int i = 0; i < kernelSize; ++ i) values[i] /= sum;

	return values;
}

/**
 * @author alteredq / http://alteredqualia.com/
 *
 */

/* ------------------------------------------------------------------------------------------
//	Simple skin shader
//		- per-pixel Blinn-Phong diffuse term mixed with half-Lambert wrap-around term (per color component)
//		- physically based specular term (Kelemen/Szirmay-Kalos specular reflectance)
//
//		- diffuse map
//		- bump map
//		- specular map
//		- point, directional and hemisphere lights (use with 'lights: true' material option)
//		- fog (use with 'fog: true' material option)
//
// ------------------------------------------------------------------------------------------ */

#if 0
	'enableBump': { value: 0 },
	'enableSpecular': { value: 0 },

	'tDiffuse': { value: null },
	'tBeckmann': { value: null },

	'diffuse': { value: new THREE.Color(0xeeeeee) },
	'specular': { value: new THREE.Color(0x111111) },
	'opacity': { value: 1 },

	'uRoughness': { value: 0.15 },
	'uSpecularBrightness': { value: 0.75 },

	'bumpMap': { value: null },
	'bumpScale': { value: 1 },

	'specularMap': { value: null },

	'offsetRepeat': { value: new THREE.Vector4(0, 0, 1, 1) },

	'uWrapRGB': { value: new THREE.Vector3(0.75, 0.375, 0.1875) }
#endif

string skin_simple_fragment()
{
	string shader =

		'#define USE_BUMPMAP\n'

		'uniform bool enableBump;\n'
		'uniform bool enableSpecular;\n'

		'uniform float uRoughness;\n'
		'uniform float uSpecularBrightness;\n'

		'uniform vec3 uWrapRGB;\n'

		'uniform sampler2D tBeckmann;\n'

		//THREE.ShaderChunk['common'],
		//THREE.ShaderChunk['bsdfs'],
		//THREE.ShaderChunk['packing'],
		//THREE.ShaderChunk['lights_pars_begin'],
		//THREE.ShaderChunk['fog_pars_fragment'],
		//THREE.ShaderChunk['bumpmap_pars_fragment'],

		// Fresnel term

		'float fresnelReflectance(vec3 H, vec3 V, float F0) {\n'

			'float base = 1.0 - dot(V, H);\n'
			'float exponential = pow(base, 5.0);\n'

			'return exponential + F0 * (1.0 - exponential);\n'

		'}\n'

		// Kelemen/Szirmay-Kalos specular BRDF

		'float KS_Skin_Specular(vec3 N,\n' 		// Bumped surface normal
								'vec3 L,\n' 		// Points to light
								'vec3 V,\n' 		// Points to eye
								'float m,\n'  	// Roughness
								'float rho_s\n' 	// Specular brightness
								') {\n'

			'float result = 0.0;\n'
			'float ndotl = dot(N, L);\n'

			'if(ndotl > 0.0) {\n'

				'vec3 h = L + V;\n' // Unnormalized half-way vector
				'vec3 H = normalize(h);\n'

				'float ndoth = dot(N, H);\n'

				'float PH = pow(2.0 * texture2D(tBeckmann, vec2(ndoth, m)).x, 10.0);\n'

				'float F = fresnelReflectance(H, V, 0.028);\n'
				'float frSpec = max(PH * F / dot(h, h), 0.0);\n'

				'result = ndotl * rho_s * frSpec;\n' // BRDF * dot(N,L) * rho_s

			'}\n'

			'return result;\n'

		'}\n'

		'void main() {\n'

			'vec3 light = vec3(0.0);\n'	// outgoing light does not have an alpha, the surface does
			'vec4 diffuseColor = vec4(material.diffuse, opacity);\n'

			'vec4 texDiffuse = texture2D(tDiffuse, v_uv0);\n'
			'texDiffuse.rgb *= texDiffuse.rgb;\n'

			'diffuseColor = diffuseColor * texDiffuse;\n'

			'vec3 normal = normalize(vNormal);\n'
			'vec3 viewerDirection = normalize(vViewPosition);\n'

			'float specularStrength;\n'

			'if (enableSpecular) {\n'

				'vec4 texelSpecular = texture2D(specularMap, v_uv0);\n'
				'specularStrength = texelSpecular.r;\n'

			'} else {\n'

				'specularStrength = 1.0;\n'

			'}\n'

			'#ifdef USE_BUMPMAP\n'

				'if (enableBump) normal = perturbNormalArb(-vViewPosition, normal, dHdxy_fwd());\n'

			'#endif\n'

			// point lights

			'vec3 specular = vec3(0.0);\n'
			'vec3 diffuse = vec3(0.0);\n'

			'#if NUPOINT_LIGHTS > 0\n'

				'for (int i = 0; i < NUPOINT_LIGHTS; i ++) {\n'

					'vec3 lVector = pointLights[i].position + vViewPosition.xyz;\n'

					'float attenuation = calcLightAttenuation(length(lVector), pointLights[i].distance, pointLights[i].decay);\n'

					'lVector = normalize(lVector);\n'

					'float pointDiffuseWeightFull = max(dot(normal, lVector), 0.0);\n'
					'float pointDiffuseWeightHalf = max(0.5 * dot(normal, lVector) + 0.5, 0.0);\n'
					'vec3 pointDiffuseWeight = mix(vec3 (pointDiffuseWeightFull), vec3(pointDiffuseWeightHalf), uWrapRGB);\n'

					'float pointSpecularWeight = KS_Skin_Specular(normal, lVector, viewerDirection, uRoughness, uSpecularBrightness);\n'

					'diffuse += pointLight[i].color * (pointDiffuseWeight * attenuation);\n'
					'specular += pointLight[i].color * specular * (pointSpecularWeight * specularStrength * attenuation);\n'

				'}\n'

			'#endif\n'

			// directional lights

			'#if NUDIR_LIGHTS > 0\n'

				'for(int i = 0; i < NUDIR_LIGHTS; i++) {\n'

					'vec3 dirVector = directionalLights[i].direction;\n'

					'float dirDiffuseWeightFull = max(dot(normal, dirVector), 0.0);\n'
					'float dirDiffuseWeightHalf = max(0.5 * dot(normal, dirVector) + 0.5, 0.0);\n'
					'vec3 dirDiffuseWeight = mix(vec3 (dirDiffuseWeightFull), vec3(dirDiffuseWeightHalf), uWrapRGB);\n'

					'float dirSpecularWeight = KS_Skin_Specular(normal, dirVector, viewerDirection, uRoughness, uSpecularBrightness);\n'

					'diffuse += directionalLights[i].color * dirDiffuseWeight;\n'
					'specular += directionalLights[i].color * (dirSpecularWeight * specularStrength);\n'

				'}\n'

			'#endif\n'

			// hemisphere lights

			'#if NUHEMI_LIGHTS > 0\n'

				'for (int i = 0; i < NUHEMI_LIGHTS; i ++) {\n'

					'vec3 lVector = hemisphereLightDirection[i];\n'

					'float dotProduct = dot(normal, lVector);\n'
					'float hemiDiffuseWeight = 0.5 * dotProduct + 0.5;\n'

					'diffuse += mix(hemisphereLightGroundColor[i], hemisphereLightSkyColor[i], hemiDiffuseWeight);\n'

					// specular (sky light)

					'float hemiSpecularWeight = 0.0;\n'
					'hemiSpecularWeight += KS_Skin_Specular(normal, lVector, viewerDirection, uRoughness, uSpecularBrightness);\n'

					// specular (ground light)

					'vec3 lVectorGround = -lVector;\n'
					'hemiSpecularWeight += KS_Skin_Specular(normal, lVectorGround, viewerDirection, uRoughness, uSpecularBrightness);\n'

					'vec3 hemiSpecularColor = mix(hemisphereLightGroundColor[i], hemisphereLightSkyColor[i], hemiDiffuseWeight);\n'

					'specular += hemiSpecularColor * specular * (hemiSpecularWeight * specularStrength);\n'

				'}\n'

			'#endif\n'

			'light += diffuseColor.rgb * (diffuse + ambientLightColor * material.diffuse) + specular;\n'

			'gl_FragColor = linearToOutputTexel(vec4(light, diffuseColor.a));\n'	// TODO, this should be pre-multiplied to allow for bright highlights on very transparent objects

			//THREE.ShaderChunk['fog_fragment'],

		'}\n';

	return shader;
}

string skin_simple_vertex()
{
	string shader =

		'#include <geometry_vs.sc>\n';

	return shader;
}

/* ------------------------------------------------------------------------------------------
//	Skin shader
//		- Blinn-Phong diffuse term (using normal + diffuse maps)
//		- subsurface scattering approximation by four blur layers
//		- physically based specular term (Kelemen/Szirmay-Kalos specular reflectance)
//
//		- point and directional lights (use with 'lights: true' material option)
//
//		- based on Nvidia Advanced Skin Rendering GDC 2007 presentation
//		  and GPU Gems 3 Chapter 14. Advanced Techniques for Realistic Real-Time Skin Rendering
//
//			http://developer.download.nvidia.com/presentations/2007/gdc/Advanced_Skin.pdf
//			http://http.developer.nvidia.com/GPUGems3/gpugems3_ch14.html
// ------------------------------------------------------------------------------------------ */

#if 0
	'passID': { value: 0 },

	'diffuse':  { value: new THREE.Color(0xeeeeee) },
	'specular': { value: new THREE.Color(0x111111) },
	'opacity': 	  { value: 1 },

	'uRoughness': 	  		{ value: 0.15 },
	'uSpecularBrightness': 	{ value: 0.75 }
#endif

string skin_fragment()
{
	string shader =

		'$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal\n'

		'#include <encode.sh>\n'
		'#include <pbr/pbr.sh>\n'
		'#include <pbr/light.sh>\n'
		'#include <pbr/light_brdf_three.sh>\n'
		'#include <pbr/radiance.sh>\n'

		//'uniform vec4 u_skin_p0;\n'
		'#define u_roughness u_user_p0.x\n'
		'#define u_spec_brightness u_user_p0.y\n'

		'#define s_blur1 s_user0\n'
		'#define s_blur2 s_user1\n'
		'#define s_blur3 s_user2\n'
		'#define s_blur4 s_user3\n'

		'#define s_beckmann s_user4\n'

		'float fresnelReflectance(vec3 H, vec3 V, float F0)\n'
		'{\n'
			'float base = 1.0 - dot(V, H);\n'
			'float exponential = pow(base, 5.0);\n'

			'return exponential + F0 * (1.0 - exponential);\n'
		'}\n'

		// Kelemen/Szirmay-Kalos specular BRDF

		// Bumped surface normal, Points to light, Points to eye, Roughness, Specular brightness
		'float KS_Skin_Specular(vec3 N, vec3 L, vec3 V, float m, float rho_s)\n'
		'{\n'
			'float result = 0.0;\n'
			'float ndotl = dot(N, L);\n'

			'if(ndotl > 0.0)\n'
			'{\n'
				'vec3 h = L + V;\n' // Unnormalized half-way vector
				'vec3 H = normalize(h);\n'

				'float ndoth = dot(N, H);\n'

				'float PH = pow(2.0 * texture2D(s_beckmann, vec2(ndoth, m)).x, 10.0);\n'
				'float F = fresnelReflectance(H, V, 0.028);\n'
				'float frSpec = max(PH * F / dot(h, h), 0.0);\n'

				'result = ndotl * rho_s * frSpec;\n' // BRDF * dot(N,L) * rho_s
			'}\n'

			'return result;\n'
		'}\n'

		'void direct_skin(vec3 energy, vec3 l, Fragment fragment, Phongvar material, inout vec3 diffuse, inout vec3 specular)\n'
		'{\n'
			'float diffuseWeight = max(dot(fragment.normal, l), 0.0);\n'
			'diffuse += energy * diffuseWeight;\n'

		'#ifndef PASS_DIFFUSE\n'
				'float specularWeight = KS_Skin_Specular(fragment.normal, l, fragment.view, u_roughness, u_spec_brightness);\n'
				'specular += energy * material.specular * specularWeight;\n'
		'#endif\n'
		'}\n'

		'#define direct_brdf direct_skin\n'

		'void main() {\n'

		'#include <pbr/fs_fragment.sh>\n'

		'#include <pbr/fs_phong_material.sh>\n'
			'vec4 texDiffuse = sample_material_texture(s_diffuse, fragment.uv);\n'
			'texDiffuse *= texDiffuse;\n'
			'vec4 diffuseColor = vec4(material.diffuse, 1.0) * texDiffuse;\n'

		'#include <pbr/fs_phong.sh>\n'

		'vec3 light = diffuseColor.rgb * (diffuse + specular);\n'

		'#ifdef PASS_DIFFUSE\n'
				'light = sqrt(light);\n'
		'#else\n'
				//'#define VERSION1\n'
				'#ifdef VERSION1\n'
					'vec3 color = sqrt(light);\n'
				'#else\n'
					'vec3 color = light;\n'
				'#endif\n'

				'vec3 blur1 = texture2D(s_blur1, v_uv0).xyz;\n'
				'vec3 blur2 = texture2D(s_blur2, v_uv0).xyz;\n'
				'vec3 blur3 = texture2D(s_blur3, v_uv0).xyz;\n'
				'vec3 blur4 = texture2D(s_blur4, v_uv0).xyz;\n'


				//'gl_FragColor = vec4(blur1, gl_FragColor.w);\n'

				//'gl_FragColor = vec4(vec3(0.22, 0.5, 0.7) * color + vec3(0.2, 0.5, 0.3) * blur1 + vec3(0.58, 0.0, 0.0) * blur2, gl_FragColor.w);\n'

				//'gl_FragColor = vec4(vec3(0.25, 0.6, 0.8) * color + vec3(0.15, 0.25, 0.2) * blur1 + vec3(0.15, 0.15, 0.0) * blur2 + vec3(0.45, 0.0, 0.0) * blur3, gl_FragColor.w);\n'


				'light = vec3(vec3(0.22,  0.437, 0.635) * color + \n'
							 'vec3(0.101, 0.355, 0.365) * blur1 + \n'
							 'vec3(0.119, 0.208, 0.0)   * blur2 + \n'
							 'vec3(0.114, 0.0,   0.0)   * blur3 + \n'
							 'vec3(0.444, 0.0,   0.0)   * blur4);\n'

				'light *= sqrt(texDiffuse.xyz);\n'

				//'light += ambientLightColor * diffuse * texDiffuse.xyz + specular;\n'
				'vec3 ambient = vec3_splat(0.0); //zone.radiance_color * zone.ambient;'
				'light += ambient * material.diffuse * texDiffuse.xyz + specular;\n'

				'#ifndef VERSION1\n'
					'light = sqrt(light);\n'
				'#endif\n'
		'#endif\n'

			'gl_FragColor = vec4(light, diffuseColor.a);\n'
			// TODO, this should be pre-multiplied to allow for bright highlights on very transparent objects

			//'#include <pbr/fs_out_pbr.sh>\n'
			//'gl_FragColor = LinearToGamma(gl_FragColor, 2.0);\n'

			//THREE.ShaderChunk['fog_fragment'],

		'}\n';

	return shader;
}

string skin_vertex()
{
	string shader =

		'#include <geometry_vs.sc>\n';

	return shader;
}

string skin_vertex_uv()
{
	string shader =

		'#define RENDER_UV\n'
		'#include <geometry_vs.sc>\n';
		//'gl_Position = vec4(uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0, 0.0, 1.0);\n'

	return shader;
}

/* ------------------------------------------------------------------------------------------
// Beckmann distribution function
//	- to be used in specular term of skin shader
//	- render a screen-aligned quad to precompute a 512 x 512 texture
//
//		- from http://developer.nvidia.com/node/171
	------------------------------------------------------------------------------------------ */

string beckmann_vertex()
{
	string shader =

		'$input a_position, a_texcoord0\n'
		'$output v_uv0\n'
		'\n'
		'#include <filter.sh>\n'
		'\n'
		'void main() {\n'
		'	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n'
		'	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n'
		'}\n';

	return shader;
}

string beckmann_fragment()
{
	string shader =

		'$input v_uv0\n'

		'#include <filter.sh>\n'

		'float PHBeckmann(float ndoth, float m)\n'
		'{\n'
			'float alpha = acos(ndoth);\n'
			'float ta = tan(alpha);\n'
			'float val = 1.0 / (m * m * pow(ndoth, 4.0)) * exp(-(ta * ta) / (m * m));\n'
			'return val;\n'
		'}\n'

		'float KSTextureCompute(vec2 tex)\n'
		'{\n'
			// Scale the value to fit within [0,1]  invert upon lookup.
			'return 0.5 * pow(PHBeckmann(tex.x, tex.y), 0.1);\n'
		'}\n'

		'void main()\n'
		'{\n'
			'float x = KSTextureCompute(v_uv0);\n'
			'gl_FragColor = vec4(x, x, x, 1.0);\n'
		'}\n';

	return shader;
}

function render_beckmann(gfx, size) {
    
    var fbo = new two.FrameBuffer(size, two.TextureFormat.RGBA8);

    var beckmann = gfx.programs.create('beckmann');
    beckmann.set_source(two.ShaderType.Vertex, beckmann_vertex);
    beckmann.set_source(two.ShaderType.Fragment, beckmann_fragment);

    gfx.filter.quad(new two.Pass(), fbo, beckmann, 0, true);

    // @todo should copy it to a normal texture
    return fbo.tex;
}

function pass_bloom(gfx, render, source, fbo, clear = true, strength = 1.0, kernel_size = 25, sigma = 4.0, resolution = 256) {
    
    var targetX = new two.FrameBuffer(new two.uvec2(resolution), two.TextureFormat.RGBA8);
    var targetY = new two.FrameBuffer(new two.uvec2(resolution), two.TextureFormat.RGBA8);

    var blurX = new two.vec2(0.001953125, 0.0);
    var blurY = new two.vec2(0.0, 0.001953125);

    var convolution = convolution_program(gfx);

    var max_kernel = 8;
    vec4 kernel[max_kernel] = {};

    //printf('pass bloom\n');
    const vector<float> kernel_values = blur_kernel(sigma);
    const uint32_t nuvalues = uint32_t(kernel_values.size());
    //assert(nuvalues >= kernel_size);
    for(var i = 0; i < kernel_values.size(); ++i) {
        kernel[i/4][i%4] = kernel_values[i];
    }

    var program = new two.ProgramVersion(convolution);
    program.set_mode(0, KERNEL_SIZE, min(nuvalues, kernel_size));

    function blur_pass(gfx, render, target, source, program, increment)
    {
        var pass = render.next_pass('bloom_blur', two.PassType.PostProcess);

        gfx.filter.uniforms(pass, 'u_kernel', kernel, max_kernel);

        gfx.filter.uniform(pass, 'u_bloom_blur_p0', new two.vec4(increment.x, increment.y, 0.0, 0.0));
        gfx.filter.source0(source);
        //renderer.clear();
        gfx.filter.quad(pass, target, program);
    }

    blur_pass(gfx, render, targetX, source, program, blurX);
    blur_pass(gfx, render, targetY, targetX.tex, program, blurY);

    var pass = render.next_pass('bloom_merge', two.PassType.PostProcess);
    //if(clear) renderer.clear();

    if(strength != 1.0)
    {
        //this.copyUniforms['opacity'].value = strength;
        //transparent: true
        gfx.copy.quad(pass, fbo, targetY.tex, BGFX_STATE_BLEND_ADD);
    }
    else
        gfx.copy.quad(pass, fbo, targetY.tex);
}

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);
viewer.viewport.active = false;

var scene = viewer.scene;

var firstPass = true;

if(init) {
    this.importerGltf = new two.ImporterGltf(app.gfx);
        
    this.uv = new two.FrameBuffer(uvec2(512U), two.TextureFormat.RGBA8);
    this.blur1 = new two.FrameBuffer(uvec2(512U), two.TextureFormat.RGBA8);
    this.blur2 = new two.FrameBuffer(uvec2(512U), two.TextureFormat.RGBA8);
    this.blur3 = new two.FrameBuffer(uvec2(512U), two.TextureFormat.RGBA8);

    this.mouse = new two.vec2(0.0);
    
    var camera = viewer.camera;
    camera.fov = 35.f; camera.near = 1.0; camera.far = 10000.0;
    camera.eye.z = 900.0;

    //scene.background = new THREE.Color(0x050505);

    var ln0 = scene.nodes().add(new two.Node3(vec3(0.0), look_dir(normalize(vec3(-1.0, -0.5, -1.0)))));
    var l0 = scene.lights().add(new two.Light(ln0, two.LightType.Direct, false, two.rgb(0xffeedd), 1.5));

    var ln1 = scene.nodes().add(new two.Node3(vec3(0.0), look_dir(normalize(vec3(1.0, -0.5, 1.0)))));
    var l1 = scene.lights().add(new two.Light(ln0, two.LightType.Direct, false, two.rgb(0xddddff), 0.5));

    // MATERIALS

    var pbr = app.gfx.programs.fetch('pbr/pbr');
    var phong = app.gfx.programs.fetch('pbr/phong');

    var program = app.gfx.programs.create('skin');
    program.set_block(two.MaterialBlock.Lit);
    program.set_block(two.MaterialBlock.Phong);
    program.set_block(two.MaterialBlock.User);
    program.set_source(two.ShaderType.Vertex, skin_vertex);
    program.set_source(two.ShaderType.Fragment, skin_fragment);
    program.register_blocks(pbr.registered_blocks);

    var program_uv = app.gfx.programs.create('skin_uv');
    program_uv.set_block(two.MaterialBlock.Lit);
    program_uv.set_block(two.MaterialBlock.Phong);
    program_uv.set_block(two.MaterialBlock.User);
    program_uv.set_source(two.ShaderType.Vertex, skin_vertex_uv);
    program_uv.set_source(two.ShaderType.Fragment, skin_fragment);
    program_uv.register_blocks(pbr.registered_blocks);

    // @todo
    //program_uv.defines.push_back({ 'PASS_DIFFUSE', '' });

    this.material = app.gfx.materials.create('skin'); var m = material;
        //m.program = phong;
        m.program = program;
        //m.base.uv0_scale = vec2(1.0, -1.0);
        m.lit.normal.texture = app.gfx.textures.file('LeePerrySmith/Norm.jpg');
        m.lit.normal.value = -1.5;
        m.phong.diffuse.value = app.gfx.textures.file('LeePerrySmith/Diff.jpg');
        m.phong.diffuse.value = two.rgb(0xbbbbbb);
        m.phong.specular.value = two.rgb(0x555555);
        var roughness = 0.185;
        var specular_brightness = 0.7;
        m.user.attr0 = new two.vec4(roughness, specular_brightness, 0.0, 0.0);

    this.material_uv = app.gfx.materials.create('skin_uv'); m = material_uv;
        // @todo
        m = material;
        m.name = 'skin_uv';
        m.program = program_uv;

    var model = app.gfx.models.file('LeePerrySmith'); // .glb

    var n = scene.nodes().add(new two.Node3(vec3(0.0, -50.0, 0.0), ZeroQuat, vec3(100.0)));
    var it = scene.items().add(new two.Item(n, model, 0, material));
    this.mesh = n;
    this.item = it;

    var beckmann = render_beckmann(app.gfx, uvec2(512U));
    material.user.tex4 = beckmann;

    material.user.tex0 = uv.tex;
    material.user.tex1 = blur1.tex;
    material.user.tex2 = blur2.tex;
    material.user.tex3 = blur3.tex;
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved)
if(event.valid())
{
    mouse.x = event.relative.x - viewer.frame.size.x / 2.0;
    mouse.y = event.relative.y - viewer.frame.size.y / 2.0;
}

rotation.y += 0.05 * (mouse.x * 0.001 - rotation.y);
rotation.x += 0.05 * (mouse.y * 0.001 - rotation.x);

mesh.apply(new two.vec3(0.0, -50.0, 0.0), new two.quat(rotation), new two.vec3(100.0));

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);

var viewport = new two.Viewport(render.camera, render.scene, new two.uvec4(new two.uvec2(0), new two.uvec2(512)));
Render subrender = new two.Render(two.Shading.Shaded, viewport, render.target, uv, app.gfx.render_frame);
subrender.shot = render.shot;

item.material = material_uv;
//var renderModelUV = new THREE.RenderPass(scene, camera, materialUV, new THREE.Color(0x575757));
app.gfx.renderer.subrender(render, subrender, render_pbr_forward);

pass_bloom(app.gfx, render, uv.tex, blur1, true, 1.0, 15, 2.0, 512);
pass_bloom(app.gfx, render, uv.tex, blur2, true, 1.0, 25, 3.f, 512);
pass_bloom(app.gfx, render, uv.tex, blur3, true, 1.0, 25, 4.0, 512);

item.material = material;
render_pbr_forward(app.gfx, render);

app.gfx.renderer.end(render);

