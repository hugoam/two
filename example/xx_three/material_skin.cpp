//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>

#include <xx_three/xx_three.h>
#include <xx_three/code/bloom_pass.h>

#include <stl/vector.hpp>

#include <cstdio>

using namespace mud;

// @author alteredq / http://alteredqualia.com/

//	Simple skin shader
//		- per-pixel Blinn-Phong diffuse term mixed with half-Lambert wrap-around term (per color component)
//		- physically based specular term (Kelemen/Szirmay-Kalos specular reflectance)

#if 0
	"enableBump": { value: 0 },
	"enableSpecular": { value: 0 },

	"tDiffuse": { value: null },
	"tBeckmann": { value: null },

	"diffuse": { value: new THREE.Color(0xeeeeee) },
	"specular": { value: new THREE.Color(0x111111) },
	"opacity": { value: 1 },

	"uRoughness": { value: 0.15 },
	"uSpecularBrightness": { value: 0.75 },

	"bumpMap": { value: null },
	"bumpScale": { value: 1 },

	"specularMap": { value: null },

	"offsetRepeat": { value: new THREE.Vector4(0, 0, 1, 1) },

	"uWrapRGB": { value: new THREE.Vector3(0.75, 0.375, 0.1875) }
#endif

static string skin_simple_fragment =

	"#define USE_BUMPMAP\n"

	"uniform bool enableBump;\n"
	"uniform bool enableSpecular;\n"

	"uniform float uRoughness;\n"
	"uniform float uSpecularBrightness;\n"

	"uniform vec3 uWrapRGB;\n"

	"uniform sampler2D tBeckmann;\n"

	//THREE.ShaderChunk["common"],
	//THREE.ShaderChunk["bsdfs"],
	//THREE.ShaderChunk["packing"],
	//THREE.ShaderChunk["lights_pars_begin"],
	//THREE.ShaderChunk["fog_pars_fragment"],
	//THREE.ShaderChunk["bumpmap_pars_fragment"],

	// Fresnel term

	"float fresnelReflectance(vec3 H, vec3 V, float F0) {\n"

		"float base = 1.0 - dot(V, H);\n"
		"float exponential = pow(base, 5.0);\n"

		"return exponential + F0 * (1.0 - exponential);\n"

	"}\n"

	// Kelemen/Szirmay-Kalos specular BRDF

	"float KS_Skin_Specular(vec3 N,\n" 		// Bumped surface normal
							"vec3 L,\n" 		// Points to light
							"vec3 V,\n" 		// Points to eye
							"float m,\n"  	// Roughness
							"float rho_s\n" 	// Specular brightness
							") {\n"

		"float result = 0.0;\n"
		"float ndotl = dot(N, L);\n"

		"if(ndotl > 0.0) {\n"

			"vec3 h = L + V;\n" // Unnormalized half-way vector
			"vec3 H = normalize(h);\n"

			"float ndoth = dot(N, H);\n"

			"float PH = pow(2.0 * texture2D(tBeckmann, vec2(ndoth, m)).x, 10.0);\n"

			"float F = fresnelReflectance(H, V, 0.028);\n"
			"float frSpec = max(PH * F / dot(h, h), 0.0);\n"

			"result = ndotl * rho_s * frSpec;\n" // BRDF * dot(N,L) * rho_s

		"}\n"

		"return result;\n"

	"}\n"

	"void main() {\n"

		"vec3 light = vec3(0.0);\n"	// outgoing light does not have an alpha, the surface does
		"vec4 diffuseColor = vec4(material.diffuse, opacity);\n"

		"vec4 texDiffuse = texture2D(tDiffuse, v_uv0);\n"
		"texDiffuse.rgb *= texDiffuse.rgb;\n"

		"diffuseColor = diffuseColor * texDiffuse;\n"

		"vec3 normal = normalize(vNormal);\n"
		"vec3 viewerDirection = normalize(vViewPosition);\n"

		"float specularStrength;\n"

		"if (enableSpecular) {\n"

			"vec4 texelSpecular = texture2D(specularMap, v_uv0);\n"
			"specularStrength = texelSpecular.r;\n"

		"} else {\n"

			"specularStrength = 1.0;\n"

		"}\n"

		"#ifdef USE_BUMPMAP\n"

			"if (enableBump) normal = perturbNormalArb(-vViewPosition, normal, dHdxy_fwd());\n"

		"#endif\n"

		// point lights

		"vec3 specular = vec3(0.0);\n"
		"vec3 diffuse = vec3(0.0);\n"

		"#if NUM_POINT_LIGHTS > 0\n"

			"for (int i = 0; i < NUM_POINT_LIGHTS; i ++) {\n"

				"vec3 lVector = pointLights[i].position + vViewPosition.xyz;\n"

				"float attenuation = calcLightAttenuation(length(lVector), pointLights[i].distance, pointLights[i].decay);\n"

				"lVector = normalize(lVector);\n"

				"float pointDiffuseWeightFull = max(dot(normal, lVector), 0.0);\n"
				"float pointDiffuseWeightHalf = max(0.5 * dot(normal, lVector) + 0.5, 0.0);\n"
				"vec3 pointDiffuseWeight = mix(vec3 (pointDiffuseWeightFull), vec3(pointDiffuseWeightHalf), uWrapRGB);\n"

				"float pointSpecularWeight = KS_Skin_Specular(normal, lVector, viewerDirection, uRoughness, uSpecularBrightness);\n"

				"diffuse += pointLight[i].color * (pointDiffuseWeight * attenuation);\n"
				"specular += pointLight[i].color * specular * (pointSpecularWeight * specularStrength * attenuation);\n"

			"}\n"

		"#endif\n"

		// directional lights

		"#if NUM_DIR_LIGHTS > 0\n"

			"for(int i = 0; i < NUM_DIR_LIGHTS; i++) {\n"

				"vec3 dirVector = directionalLights[i].direction;\n"

				"float dirDiffuseWeightFull = max(dot(normal, dirVector), 0.0);\n"
				"float dirDiffuseWeightHalf = max(0.5 * dot(normal, dirVector) + 0.5, 0.0);\n"
				"vec3 dirDiffuseWeight = mix(vec3 (dirDiffuseWeightFull), vec3(dirDiffuseWeightHalf), uWrapRGB);\n"

				"float dirSpecularWeight = KS_Skin_Specular(normal, dirVector, viewerDirection, uRoughness, uSpecularBrightness);\n"

				"diffuse += directionalLights[i].color * dirDiffuseWeight;\n"
				"specular += directionalLights[i].color * (dirSpecularWeight * specularStrength);\n"

			"}\n"

		"#endif\n"

		// hemisphere lights

		"#if NUM_HEMI_LIGHTS > 0\n"

			"for (int i = 0; i < NUM_HEMI_LIGHTS; i ++) {\n"

				"vec3 lVector = hemisphereLightDirection[i];\n"

				"float dotProduct = dot(normal, lVector);\n"
				"float hemiDiffuseWeight = 0.5 * dotProduct + 0.5;\n"

				"diffuse += mix(hemisphereLightGroundColor[i], hemisphereLightSkyColor[i], hemiDiffuseWeight);\n"

				// specular (sky light)

				"float hemiSpecularWeight = 0.0;\n"
				"hemiSpecularWeight += KS_Skin_Specular(normal, lVector, viewerDirection, uRoughness, uSpecularBrightness);\n"

				// specular (ground light)

				"vec3 lVectorGround = -lVector;\n"
				"hemiSpecularWeight += KS_Skin_Specular(normal, lVectorGround, viewerDirection, uRoughness, uSpecularBrightness);\n"

				"vec3 hemiSpecularColor = mix(hemisphereLightGroundColor[i], hemisphereLightSkyColor[i], hemiDiffuseWeight);\n"

				"specular += hemiSpecularColor * specular * (hemiSpecularWeight * specularStrength);\n"

			"}\n"

		"#endif\n"

		"light += diffuseColor.rgb * (diffuse + ambientLightColor * material.diffuse) + specular;\n"

		"gl_FragColor = linearToOutputTexel(vec4(light, diffuseColor.a));\n"	// TODO, this should be pre-multiplied to allow for bright highlights on very transparent objects

		//THREE.ShaderChunk["fog_fragment"],

	"}\n";

static string skin_simple_vertex =

	"#include <geometry_vs.sc>\n";

//	Skin shader
//		- Blinn-Phong diffuse term (using normal + diffuse maps)
//		- subsurface scattering approximation by four blur layers
//		- physically based specular term (Kelemen/Szirmay-Kalos specular reflectance)
//
//		- point and directional lights (use with "lights: true" material option)
//
//		- based on Nvidia Advanced Skin Rendering GDC 2007 presentation
//		  and GPU Gems 3 Chapter 14. Advanced Techniques for Realistic Real-Time Skin Rendering
//
//			http://developer.download.nvidia.com/presentations/2007/gdc/Advanced_Skin.pdf
//			http://http.developer.nvidia.com/GPUGems3/gpugems3_ch14.html

static string skin_fragment = 

	"$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal\n"

	"#include <encode.sh>\n"
	"#include <pbr/pbr.sh>\n"
	"#include <pbr/light.sh>\n"
	"#include <pbr/light_brdf_three.sh>\n"
	"#include <pbr/radiance.sh>\n"

	"#define s_blur1 s_user0\n"
	"#define s_blur2 s_user1\n"
	"#define s_blur3 s_user2\n"
	"#define s_blur4 s_user3\n"

	"#define s_beckmann s_user4\n"

	"float fresnelReflectance(vec3 H, vec3 V, float F0)\n"
	"{\n"
		"float base = 1.0 - dot(V, H);\n"
		"float exponential = pow(base, 5.0);\n"

		"return exponential + F0 * (1.0 - exponential);\n"
	"}\n"

	// Kelemen/Szirmay-Kalos specular BRDF

	// Bumped surface normal, Points to light, Points to eye, Roughness, Specular brightness
	"float KS_Skin_Specular(vec3 N, vec3 L, vec3 V, float m, float rho_s)\n"
	"{\n"
		"float result = 0.0;\n"
		"float ndotl = dot(N, L);\n"

		"if(ndotl > 0.0)\n"
		"{\n"
			"vec3 h = L + V;\n" // Unnormalized half-way vector
			"vec3 H = normalize(h);\n"

			"float ndoth = dot(N, H);\n"

			"float PH = pow(2.0 * texture2D(s_beckmann, vec2(ndoth, m)).x, 10.0);\n"
			"float F = fresnelReflectance(H, V, 0.028);\n"
			"float frSpec = max(PH * F / dot(h, h), 0.0);\n"

			"result = ndotl * rho_s * frSpec;\n" // BRDF * dot(N,L) * rho_s
		"}\n"

		"return result;\n"
	"}\n"

	"struct SkinMaterial\n"
	"{\n"
	"	PhongMaterial phong;\n"
	"	UserMaterial skin;\n"
	"};\n"

	"void direct_skin(vec3 energy, vec3 l, Fragment fragment, SkinMaterial mat, inout vec3 diffuse, inout vec3 specular)\n"
	"{\n"
		"float diffuseWeight = max(dot(fragment.normal, l), 0.0);\n"
		"diffuse += energy * diffuseWeight;\n"

	"#ifndef PASS_DIFFUSE\n"
			"float roughness  = mat.skin.p0.x;\n"
			"float brightness = mat.skin.p0.y;\n"

			"float specularWeight = KS_Skin_Specular(fragment.normal, l, fragment.view, roughness, brightness);\n"
			"specular += energy * mat.phong.specular * specularWeight;\n"
	"#endif\n"
	"}\n"

	"#define direct_brdf direct_skin\n"

	"void main() {\n"

	"#include <pbr/fs_fragment.sh>\n"

	"#include <pbr/fs_phong_material.sh>\n"
		"SkinMaterial material;\n"
		"material.phong = matphong;\n"
		"material.skin = matuser;\n"

		"vec4 texDiffuse = sample_material_texture(s_diffuse, fragment.uv);\n"
		"texDiffuse *= texDiffuse;\n"
		"vec4 diffuseColor = vec4(matphong.diffuse, 1.0) * texDiffuse;\n"

	"#include <pbr/fs_phong.sh>\n"

	"vec3 light = diffuseColor.rgb * (diffuse + specular);\n"

	"#ifdef PASS_DIFFUSE\n"
			"light = sqrt(light);\n"
	"#else\n"
			//"#define VERSION1\n"
			"#ifdef VERSION1\n"
				"vec3 color = sqrt(light);\n"
			"#else\n"
				"vec3 color = light;\n"
			"#endif\n"

			"light = vec3(vec3(0.22,  0.437, 0.635) * color + \n"
						 "vec3(0.101, 0.355, 0.365) * texture2D(s_blur1, v_uv0).rgb + \n"
						 "vec3(0.119, 0.208, 0.0)   * texture2D(s_blur2, v_uv0).rgb + \n"
						 "vec3(0.114, 0.0,   0.0)   * texture2D(s_blur3, v_uv0).rgb + \n"
						 "vec3(0.444, 0.0,   0.0)   * texture2D(s_blur4, v_uv0).rgb);\n"

			"light *= sqrt(texDiffuse.xyz);\n"

			"vec3 ambient = zone.ambient;\n"
			"light += ambient * matphong.diffuse * texDiffuse.xyz + specular;\n"

			"#ifndef VERSION1\n"
				"light = sqrt(light);\n"
			"#endif\n"
	"#endif\n"

		"gl_FragColor = vec4(light, diffuseColor.a);\n"
		// TODO, this should be pre-multiplied to allow for bright highlights on very transparent objects

		//"#include <pbr/fs_out_pbr.sh>\n"
		//"gl_FragColor = LinearToGamma(gl_FragColor, 2.0);\n"

		//THREE.ShaderChunk["fog_fragment"],

	"}\n";

static string skin_vertex =

	"#include <geometry_vs.sc>\n";


static string skin_vertex_uv =

	"#define RENDER_UV\n"
	"#include <geometry_vs.sc>\n";
	//"gl_Position = vec4(uv.x * 2.0 - 1.0, uv.y * 2.0 - 1.0, 0.0, 1.0);\n"

// Beckmann distribution function
// to be used in specular term of skin shader
// from http://developer.nvidia.com/node/171

static string beckmann_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"

	"#include <filter.sh>\n"

	"void main() {\n"
	"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string beckmann_fragment =

	"$input v_uv0\n"

	"#include <filter.sh>\n"

	"float PHBeckmann(float ndoth, float m)\n"
	"{\n"
		"float alpha = acos(ndoth);\n"
		"float ta = tan(alpha);\n"
		"float val = 1.0 / (m * m * pow(ndoth, 4.0)) * exp(-(ta * ta) / (m * m));\n"
		"return val;\n"
	"}\n"

	"float KSTextureCompute(vec2 tex)\n"
	"{\n"
		// Scale the value to fit within [0,1]  invert upon lookup.
		"return 0.5 * pow(PHBeckmann(tex.x, tex.y), 0.1);\n"
	"}\n"

	"void main()\n"
	"{\n"
		"float x = KSTextureCompute(v_uv0);\n"
		"gl_FragColor = vec4(x, x, x, 1.0);\n"
	"}\n";

Texture& render_beckmann(GfxSystem& gfx, uvec2 size)
{
	static FrameBuffer fbo = { size, TextureFormat::RGBA8 };

	static Program& beckmann = gfx.programs().create("beckmann");
	beckmann.set_source(ShaderType::Vertex, beckmann_vertex);
	beckmann.set_source(ShaderType::Fragment, beckmann_fragment);

	gfx.m_filter->quad(Pass(), fbo, beckmann, 0U, true);

	// @todo should copy it to a normal texture
	return fbo.m_tex;
}

#define PAD 0.f

void xx_material_skin(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	static ImporterGltf importer_gltf = { app.m_gfx };

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);
	viewer.m_viewport.m_autorender = false;

	Scene& scene = viewer.m_scene;

	bool firstPass = true;

	static Node3* mesh = nullptr;
	static Item* item = nullptr;
	static vec3 rotation = vec3(0.f);

	static Material* material = nullptr;
	static Material* material_uv = nullptr;

	static FrameBuffer uv = { uvec2(512U), TextureFormat::RGBA8 };
	static FrameBuffer blur1 = { uvec2(512U), TextureFormat::RGBA8 };
	static FrameBuffer blur2 = { uvec2(512U), TextureFormat::RGBA8 };
	static FrameBuffer blur3 = { uvec2(512U), TextureFormat::RGBA8 };

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 35.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye.z = 900.f;

		//scene.background = new THREE.Color(0x050505);

		Node3& ln0 = gfx::nodes(scene).add(Node3(vec3(0.f), look_dir(vec3(-1.f, -0.5f, -1.f))));
		Light& l0 = gfx::lights(scene).add(Light(ln0, LightType::Direct, false, rgb(0xffeedd), 1.5f));

		Node3& ln1 = gfx::nodes(scene).add(Node3(vec3(0.f), look_dir(vec3(1.f, -0.5f, 1.f))));
		Light& l1 = gfx::lights(scene).add(Light(ln1, LightType::Direct, false, rgb(0xddddff), 0.5f));

		// MATERIALS

		Program& pbr = app.m_gfx.programs().fetch("pbr/pbr");
		Program& phong = app.m_gfx.programs().fetch("pbr/phong");

		Program& program = app.m_gfx.programs().create("skin");
		program.set_blocks({ MaterialBlock::Lit, MaterialBlock::Phong, MaterialBlock::User });
		program.set_source(ShaderType::Vertex, skin_vertex);
		program.set_source(ShaderType::Fragment, skin_fragment);
		program.register_blocks(pbr);

		Program& program_uv = app.m_gfx.programs().create("skin_uv");
		program_uv.set_blocks({ MaterialBlock::Lit, MaterialBlock::Phong, MaterialBlock::User });
		program_uv.set_source(ShaderType::Vertex, skin_vertex_uv);
		program_uv.set_source(ShaderType::Fragment, skin_fragment);
		program_uv.register_blocks(pbr);

		program_uv.m_defines.push_back({ "PASS_DIFFUSE", "" });

		material = &app.m_gfx.materials().create("skin", [&](Material& m)
		{
			//m.m_program = &phong;
			m.m_program = &program;
			m.m_base.m_uv0_scale = vec2(1.f, -1.f);
			m.m_lit.m_normal = app.m_gfx.textures().file("LeePerrySmith/Norm.jpg");
			m.m_lit.m_normal = -1.5f;
			m.m_phong.m_diffuse = app.m_gfx.textures().file("LeePerrySmith/Diff.jpg");
			m.m_phong.m_diffuse = rgb(0xbbbbbb);
			m.m_phong.m_specular = rgb(0x555555);
			float roughness = 0.185f;
			float specular_brightness = 0.7f;
			m.m_user.m_attr0 = { roughness, specular_brightness, PAD, PAD };
		});

		material_uv = &app.m_gfx.materials().create("skin_uv", [&](Material& m)
		{
			m = *material;
			m.m_name = "skin_uv";
			m.m_program = &program_uv;
		});

		Model& model = *app.m_gfx.models().file("LeePerrySmith"); // .glb

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f, -50.f, 0.f), ZeroQuat, vec3(100.f)));
		Item& it = gfx::items(scene).add(Item(n, model, 0U, material));
		mesh = &n;
		item = &it;

		Texture& beckmann = render_beckmann(app.m_gfx, uvec2(512U));
		material->m_user.m_tex4 = &beckmann;

		material->m_user.m_tex0 = &uv.m_tex;
		material->m_user.m_tex1 = &blur1.m_tex;
		material->m_user.m_tex2 = &blur2.m_tex;
		material->m_user.m_tex3 = &blur3.m_tex;
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = event.m_relative - viewer.m_frame.m_size / 2.f;
	}

	const vec2 target = mouse * 0.001f;

	rotation.y += 0.05f * (target.x - rotation.y);
	rotation.x += 0.05f * (target.y - rotation.x);

	mesh->apply(vec3(0.f, -50.f, 0.f), quat(rotation), vec3(100.f));

	Render render = { Shading::Shaded, viewer.m_viewport, app.m_gfx.main_target(), app.m_gfx.m_render_frame };
	app.m_gfx.m_renderer.gather(render);
	app.m_gfx.m_renderer.begin(render);

	Viewport viewport = Viewport(*render.m_camera, *render.m_scene, Rect4);
	Render subrender = Render(Shading::Shaded, viewport, *render.m_target, uv, app.m_gfx.m_render_frame);
	subrender.m_shot = render.m_shot;
	subrender.m_vflip = true;

	item->m_material = material_uv;
	//var renderModelUV = new THREE.RenderPass(scene, camera, materialUV, new THREE.Color(0x575757));
	app.m_gfx.m_renderer.subrender(render, subrender, render_pbr_forward);

	pass_bloom(app.m_gfx, render, uv.m_tex, blur1, true, 1.f, 15, 2.f, uvec2(512U));
	pass_bloom(app.m_gfx, render, uv.m_tex, blur2, true, 1.f, 25, 3.f, uvec2(512U));
	pass_bloom(app.m_gfx, render, uv.m_tex, blur3, true, 1.f, 25, 4.f, uvec2(512U));

	item->m_material = material;
	render_pbr_forward(app.m_gfx, render);

	app.m_gfx.m_renderer.end(render);
}
