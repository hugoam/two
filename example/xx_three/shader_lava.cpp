//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

static string vertex_shader()
{
	string shader =

		"$input a_position, a_texcoord0\n"
		"$output v_position, v_texcoord0\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
		"{\n"
		"	int material_index = int(u_state_material);\n"
		"	BaseMaterial basic = read_base_material(material_index);\n"
		"	\n"
		"   v_texcoord0 = vec4((a_texcoord0.xy * basic.uv0_scale) + basic.uv0_offset, 0.0, 0.0);\n"
		"	vec4 view = mul(u_modelView, vec4(a_position, 1.0));\n"
		"	v_position = mul(u_proj, view);\n"
		"	gl_Position = v_position;\n"
		"}\n";

	return shader;
}

static string fragment_shader()
{
	string shader =

		"$input v_position, v_texcoord0\n"
		"\n"
		"#include <common.sh>\n"
		"#include <pbr/fog.sh>\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec2 uv = v_texcoord0.xy;"
		"	vec2 position = - 1.0 + 2.0 * uv;\n"
		"\n"
		"	vec4 noise = texture2D(s_user0, uv);\n"
		"	vec2 T1 = uv + vec2(1.5, - 1.5) * u_time * 0.02;\n"
		"	vec2 T2 = uv + vec2(- 0.5, 2.0) * u_time * 0.01;\n"
		"\n"
		"	T1.x += noise.x * 2.0;\n"
		"	T1.y += noise.y * 2.0;\n"
		"	T2.x -= noise.y * 0.2;\n"
		"	T2.y += noise.z * 0.2;\n"
		"\n"
		"	float p = texture2D(s_user0, T1 * 2.0).a;\n"
		"\n"
		"	vec4 lava = texture2D(s_user1, T2 * 2.0);\n"
		"	vec4 color = lava * (vec4(p, p, p, p) * 2.0) + (lava * lava - 0.1);\n"
		"\n"
		"	if(color.r > 1.0) { color.bg += clamp(color.r - 2.0, 0.0, 100.0); }\n"
		"	if(color.g > 1.0) { color.rb += color.g - 1.0; }\n"
		"	if(color.b > 1.0) { color.rg += color.b - 1.0; }\n"
		"\n"
		"	gl_FragColor = color;\n"
		"\n"
		"#if BGFX_SHADER_LANGUAGE_HLSL\n"
		//"	float depth = v_position.z;\n"
		"	float depth = gl_FragCoord.z * gl_FragCoord.w;\n"
		"#else\n"
		//"	float depth = (v_position.z + v_position.w) * 0.5;\n"
		"	float depth = gl_FragCoord.z / gl_FragCoord.w;\n"
		"#endif\n"
		"	const float LOG2 = 1.442695;\n"
		"	float fogFactor = exp2(-u_fog_density * u_fog_density * depth * depth * LOG2);\n"
		"	fogFactor = 1.0 - clamp(fogFactor, 0.0, 1.0);\n"
		"\n"
		"	gl_FragColor = mix(color, vec4(vec3(0.0, 0.0, 0.0), color.w), fogFactor);\n"
		"}\n";

	return shader;
}

void xx_shader_lava(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static vec3 angles = vec3(0.3f, 0.f, 0.f);
	static Node3* node = nullptr;
	
	static Program program = { "lava" };
	program.m_blocks[MaterialBlock::Solid] = true;
	program.m_blocks[MaterialBlock::User] = true;
	program.m_sources[ShaderType::Vertex] = vertex_shader();
	program.m_sources[ShaderType::Fragment] = fragment_shader();

	static Texture& cloud = *app.m_gfx.textures().file("lava/cloud.png");
	static Texture& lava = *app.m_gfx.textures().file("lava/lavatile.png");

	//static bgfx::UniformHandle u_fog_params = bgfx::createUniform("u_fog_params", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);

	static const float fog_density = 0.45f;
	static const Colour fog_color = Colour(0.f);
	//static const Colour fog_color = Colour(1.f, 0.f, 1.f);

	scene.m_env.m_fog.m_density = fog_density;
	scene.m_env.m_fog.m_colour = fog_color;

	auto submit = [](bgfx::Encoder& encoder)
	{
		//vec4 fog_params = { fog_density, fog_color.r, fog_color.g, fog_color.b };
		//bgfx::setViewUniform(0, u_fog_params, &fog_params);
	};

	static Material& material = app.m_gfx.materials().create("lava", [&](Material& m) {
		m.m_program = &program;
		m.m_base.m_uv0_scale = { 3.f, 1.f };
		m.m_submit = submit;
		m.m_user.m_attr0.m_texture = &cloud;
		m.m_user.m_attr1.m_texture = &lava;
	});

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 35.f; camera.m_near = 1.f; camera.m_far = 3000.f;
		camera.m_eye.z = 4.f;

		const float size = 0.65f;

		static Model& model = app.m_gfx.shape(Torus(size, 0.3f));
		//static Model& model = app.m_gfx.shape(Sphere(size));

		node = &gfx::nodes(scene).add(Node3(vec3(0.f), quat(angles)));
		Item& it = gfx::items(scene).add(Item(*node, model, 0U, &material));

		//var renderModel = new THREE.RenderPass(scene, camera);
		//var effectBloom = new THREE.BloomPass(1.25);
		//var effectFilm = new THREE.FilmPass(0.35, 0.95, 2048, false);
		//effectFilm.renderToScreen = true;

		//composer = new THREE.EffectComposer(renderer);
		//
		//composer.addPass(renderModel);
		//composer.addPass(effectBloom);
		//composer.addPass(effectFilm);
	}

	const float delta = 5.f * app.m_gfx.m_frame_time;

	//uniforms["time"].value += 0.2 * delta;

	angles.y += 0.0125 * delta;
	angles.x += 0.05 * delta;

	node->apply(vec3(0.f), quat(angles));

	//renderer.clear();
	//composer.render(0.01);
}
