//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

string fragment_shader()
{
	string shader =

		"$input v_texcoord0\n"
		"\n"
		"#include \"filter/filter.sh\"\n"
		"\n"
		"uniform uvec4 u_fog_params;\n"
		"#define u_fog_density u_fog_params.x\n"
		"#define u_fog_color u_fog_params.yz\n"
		"\n"
		"SAMPLER2D(s_texture_1, 0);\n"
		"SAMPLER2D(s_texture_2, 1);\n"
		"\n"
		"varying vec2 vUv;\n"
		"\n"
		"void main( void ) {\n"
		"\n"
		"	vec2 position = - 1.0 + 2.0 * v_texcoord0.xy;\n"
		"\n"
		"	vec4 noise = texture2D( s_texture_1, v_texcoord0.xy );\n"
		"	vec2 T1 = vUv + vec2( 1.5, - 1.5 ) * u_time * 0.02;\n"
		"	vec2 T2 = vUv + vec2( - 0.5, 2.0 ) * u_time * 0.01;\n"
		"\n"
		"	T1.x += noise.x * 2.0;\n"
		"	T1.y += noise.y * 2.0;\n"
		"	T2.x -= noise.y * 0.2;\n"
		"	T2.y += noise.z * 0.2;\n"
		"\n"
		"	float p = texture2D( s_texture_1, T1 * 2.0 ).a;\n"
		"\n"
		"	vec4 color = texture2D( s_texture_2, T2 * 2.0 );\n"
		"	vec4 temp = color * ( vec4( p, p, p, p ) * 2.0 ) + ( color * color - 0.1 );\n"
		"\n"
		"	if( temp.r > 1.0 ) { temp.bg += clamp( temp.r - 2.0, 0.0, 100.0 ); }\n"
		"	if( temp.g > 1.0 ) { temp.rb += temp.g - 1.0; }\n"
		"	if( temp.b > 1.0 ) { temp.rg += temp.b - 1.0; }\n"
		"\n"
		"	gl_FragColor = temp;\n"
		"\n"
		"	float depth = gl_FragCoord.z / gl_FragCoord.w;\n"
		"	const float LOG2 = 1.442695;\n"
		"	float fogFactor = exp2( - fogDensity * fogDensity * depth * depth * LOG2 );\n"
		"	fogFactor = 1.0 - clamp( fogFactor, 0.0, 1.0 );\n"
		"\n"
		"	gl_FragColor = mix( gl_FragColor, vec4( fogColor, gl_FragColor.w ), fogFactor );\n"
		"\n"
		"}\n";

	return shader;
}

string vertex_shader()
{
	string shader =

		"uniform vec2 uvScale;\n"
		"varying vec2 vUv;\n"
		"\n"
		"void main()\n"
		"{\n"
		"\n"
		"	vUv = uvScale * uv;\n"
		"	vec4 mvPosition = modelViewMatrix * vec4( position, 1.0 );\n"
		"	gl_Position = projectionMatrix * mvPosition;\n"
		"\n"
		"}\n";
	
	return shader;
}

void xx_shader_lava(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	//camera = new THREE.PerspectiveCamera(35, window.innerWidth / window.innerHeight, 1, 3000);
	//camera.position.z = 4;

	Scene& scene = viewer.m_scene;

	static vec3 angles = vec3(0.3f, 0.f, 0.f);
	static Node3* node = nullptr;

	static Texture& cloud = *app.m_gfx_system.textures().file("lava/cloud.png");
	static Texture& lava = *app.m_gfx_system.textures().file("lava/lavatile.jpg");

	static bgfx::UniformHandle u_fog_params = bgfx::createUniform("u_fog_params", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);
	static bgfx::UniformHandle u_uv_scale = bgfx::createUniform("u_uv_scale", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);

	static bgfx::UniformHandle s_texture_1 = bgfx::createUniform("s_texture_1", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);
	static bgfx::UniformHandle s_texture_2 = bgfx::createUniform("s_texture_2", bgfx::UniformType::Sampler, 1U, bgfx::UniformFreq::View);

	float fog_density = 0.45f;
	Colour fog_color = Colour(0.f);

	vec4 fog_params = { fog_density, fog_color.r, fog_color.g, fog_color.b };
	bgfx::setViewUniform(0, u_fog_params, &fog_params);

	vec4 uv_scale = { vec2(3.0, 1.0), vec2(0.f) };
	bgfx::setViewUniform(0, u_uv_scale, &uv_scale);

	uint32_t stage_1 = 0;
	bgfx::setViewUniform(0, s_texture_1, &stage_1);
	
	uint32_t stage_2 = 1;
	bgfx::setViewUniform(0, s_texture_2, &stage_2);

	auto submit = [](bgfx::Encoder& encoder)
	{
		encoder.setTexture(uint8_t(0), cloud.m_texture);
		encoder.setTexture(uint8_t(1), lava.m_texture);
	};

	static bool once = false;
	if(!once)
	{
		once = true;

		//var textureLoader = new THREE.TextureLoader();
		//
		//uniforms = {
		//
		//	"fogDensity": { value: 0.45 },
		//	"fogColor" : { value: new THREE.Vector3(0, 0, 0) },
		//	"time" : { value: 1.0 },
		//	"uvScale" : { value: new THREE.Vector2(3.0, 1.0) },
		//	"texture1" : { value: textureLoader.load('textures/lava/cloud.png') },
		//	"texture2" : { value: textureLoader.load('textures/lava/lavatile.jpg') }
		//
		//};
		//
		//uniforms["texture1"].value.wrapS = uniforms["texture1"].value.wrapT = THREE.RepeatWrapping;
		//uniforms["texture2"].value.wrapS = uniforms["texture2"].value.wrapT = THREE.RepeatWrapping;

		static string fragment = fragment_shader();
		static string vertex = vertex_shader();

		static Program program = { "lava", {}, { nullptr, fragment.c_str(), nullptr, nullptr } };

		static Material& material = app.m_gfx_system.materials().create("lava", [](Material& m) { m.m_program = &program; });
		// material.m_submit = submit;

		const float size = 0.65f;

		static Model& model = app.m_gfx_system.fetch_symbol(Symbol(), Torus(size, 0.3f), PLAIN);

		node = &gfx::nodes(scene).add(Node3(vec3(0.f), quat(angles)));
		Item& it = gfx::items(scene).add(Item(*node, model, 0U, &material));

		gfx::update_item_aabb(it);

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

	const float delta = 5.f * app.m_gfx_system.m_frame_time;

	//uniforms["time"].value += 0.2 * delta;

	angles.y += 0.0125 * delta;
	angles.x += 0.05 * delta;

	node->m_transform = bxSRT(vec3(1.f), quat(angles), vec3(0.f));

	//renderer.clear();
	//composer.render(0.01);
}
