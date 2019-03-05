//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

static string vertex_shader()
{
	string shader =

		'$input a_position, a_texcoord0\n'
		'$output v_texcoord0\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'uniform vec4 u_lava_params;\n'
		'#define u_lava_uv_scale u_lava_params.xy\n'
		'\n'
		'void main()\n'
		'{\n'
		'	v_texcoord0 = new two.vec4(u_lava_uv_scale * a_texcoord0.xy, 0.0, 0.0);\n'
		'	var view = mul(u_modelView, new two.vec4(a_position, 1.0)).xyz;\n'
		'	gl_Position = mul(u_proj, new two.vec4(view, 1.0));\n'
		'}\n';

	return shader;
}

static string fragment_shader()
{
	string shader =

		'$input v_texcoord0\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		//'uniform vec4 u_fog_params;\n'
		//'#define u_fog_density u_fog_params.x\n'
		//'#define u_fog_color u_fog_params.yzw\n'
		//'\n'
		'SAMPLER2D(s_texture_1, 0);\n'
		'SAMPLER2D(s_texture_2, 1);\n'
		'\n'
		'void main()\n'
		'{\n'
		'   var uv = v_texcoord0.xy;'
		'	var position = - 1.0 + 2.0 * uv;\n'
		'\n'
		'	vec4 noise = texture2D(s_texture_1, uv);\n'
		'	var T1 = uv + new two.vec2(1.5, - 1.5) * u_time * 0.02;\n'
		'	var T2 = uv + new two.vec2(- 0.5, 2.0) * u_time * 0.01;\n'
		'\n'
		'	T1.x += noise.x * 2.0;\n'
		'	T1.y += noise.y * 2.0;\n'
		'	T2.x -= noise.y * 0.2;\n'
		'	T2.y += noise.z * 0.2;\n'
		'\n'
		'	var p = texture2D(s_texture_1, T1 * 2.0).a;\n'
		'\n'
		'	vec4 color = texture2D(s_texture_2, T2 * 2.0);\n'
		'	vec4 temp = color * (new two.vec4(p, p, p, p) * 2.0) + (color * color - 0.1);\n'
		'\n'
		'	if(temp.r > 1.0) { temp.bg += clamp(temp.r - 2.0, 0.0, 100.0); }\n'
		'	if(temp.g > 1.0) { temp.rb += temp.g - 1.0; }\n'
		'	if(temp.b > 1.0) { temp.rg += temp.b - 1.0; }\n'
		'\n'
		'	gl_FragColor = temp;\n'
		'\n'
		//'	var depth = gl_FragCoord.z / gl_FragCoord.w;\n'
		//'	var LOG2 = 1.442695;\n'
		//'	var fogFactor = exp2(-u_fog_density * u_fog_density * depth * depth * LOG2);\n'
		//'	fogFactor = 1.0 - clamp(fogFactor, 0.0, 1.0);\n'
		//'\n'
		//'	gl_FragColor = mix(gl_FragColor, new two.vec4(u_fog_color, gl_FragColor.w), fogFactor);\n'
		//'\n'
		'}\n';

	return shader;
}

void xx_shader_lava(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(parent);
	two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	this.angles = new two.vec3(0.3, 0.0, 0.0);
	this.node = nullptr;

	this.cloud = app.gfx.textures().file('lava/cloud.png');
	this.lava = app.gfx.textures().file('lava/lavatile.jpg');

	static btwo.gfx.UniformHandle u_fog_params = btwo.gfx.createUniform('u_fog_params', btwo.gfx.UniformType::Vec4, 1U, btwo.gfx.UniformFreq::View);
	//static btwo.gfx.UniformHandle u_uv_scale = btwo.gfx.createUniform('u_uv_scale', btwo.gfx.UniformType::Vec4, 1U, btwo.gfx.UniformFreq::View);

	static btwo.gfx.UniformHandle s_texture_1 = btwo.gfx.createUniform('s_texture_1', btwo.gfx.UniformType::Sampler, 1U, btwo.gfx.UniformFreq::View);
	static btwo.gfx.UniformHandle s_texture_2 = btwo.gfx.createUniform('s_texture_2', btwo.gfx.UniformType::Sampler, 1U, btwo.gfx.UniformFreq::View);

	var fog_density = 0.45;
	Colour fog_color = new two.Colour(0.0);
	var uv_scale = { 3.0, 1.0 };

	vec4 fog_params = { fog_density, fog_color.r, fog_color.g, fog_color.b };
	btwo.gfx.setViewUniform(0, u_fog_params, fog_params);

	//vec4 uv_scale = { new two.vec2(3.0, 1.0), new two.vec2(0.0) };
	//btwo.gfx.setViewUniform(0, u_uv_scale, uv_scale);

	uint32_t stage_1 = 0;
	btwo.gfx.setViewUniform(0, s_texture_1, stage_1);
	
	uint32_t stage_2 = 1;
	btwo.gfx.setViewUniform(0, s_texture_2, stage_2);

	function submit = [](btwo.gfx.Encoder encoder)
	{
		encoder.setTexture(uint8_t(0), cloud.texture);
		encoder.setTexture(uint8_t(1), lava.texture);
	};

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 35.0; camera.near = 1.0; camera.far = 3000.0;
		camera.eye.z = 4.0;

		static string vertex = vertex_shader();
		static string fragment = fragment_shader();

		static Program program = { 'lava', {}, { nullptr, fragment.c_str(), nullptr, vertex.c_str() } };
		program.blocks[MaterialBlock::Solid] = true;

		this.material = app.gfx.materials().create('lava', [](var m) {
			m.program = program;
			m.base.uv0_scale = uv_scale;
		});
		// material.submit = submit;

		var size = 0.65;

		this.model = app.gfx.shape(Torus(size, 0.3));

		node = two.gfx.nodes(scene).add(new two.Node3(new two.vec3(0.0), new two.quat(angles)));
		var it = two.gfx.items(scene).add(new two.Item(*node, model, 0U, material));

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

	var delta = 5.0 * app.gfx.frame_time;

	//uniforms['time'].value += 0.2 * delta;

	angles.y += 0.0125 * delta;
	angles.x += 0.05 * delta;

	node->transform = bxSRT(new two.vec3(1.0), new two.quat(angles), new two.vec3(0.0));

	//renderer.clear();
	//composer.render(0.01);
}
