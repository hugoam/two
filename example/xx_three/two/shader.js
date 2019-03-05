//#include <mud/frame.h>
#include <frame/Api.h>
#include <ui/Edit/Lang.h>

#include <09_live_shader/09_live_shader.h>

using namespace mud;

string create_shader()
{
	string shader =

		'$input v_texcoord0\n'
		'\n'
		'#include \'filter/filter.sh\'\n'
		'\n'
		'void main() {\n'
		'\n'
		'	var p = - 1.0 + 2.0 * v_texcoord0.xy;\n'
		'	var a = u_time * 40.0;\n'
		'	var d, e, f, g = 1.0 / 40.0 ,h ,i ,r ,q;\n'
		'\n'
		'	e = 400.0 * (p.x * 0.5 + 0.5);\n'
		'	f = 400.0 * (p.y * 0.5 + 0.5);\n'
		'	i = 200.0 + Math.sin(e * g + a / 150.0) * 20.0;\n'
		'	d = 200.0 + Math.cos(f * g / 2.0) * 18.0 + Math.cos(e * g) * 7.0;\n'
		'	r = Math.sqrt(pow(abs(i - e), 2.0) + pow(abs(d - f), 2.0));\n'
		'	q = f / r;\n'
		'	e = (r * Math.cos(q)) - a / 2.0;\n'
		'	f = (r * Math.sin(q)) - a / 2.0;\n'
		'	d = Math.sin(e * g) * 176.0 + Math.sin(e * g) * 164.0 + r;\n'
		'	h = ((f + d) + a / 2.0) * g;\n'
		'	i = Math.cos(h + r * p.x / 1.3) * (e + e + a) + Math.cos(q * g * 6.0) * (r + h / 3.0);\n'
		'	h = Math.sin(f * g) * 144.0 - Math.sin(e * g) * 212.0 * p.x;\n'
		'	h = (h + (f - e) * q + Math.sin(r - (a + h) / 7.0) * 10.0 + i / 4.0) * g;\n'
		'	i += Math.cos(h * 2.3 * Math.sin(a / 350.0 - q)) * 184.0 * Math.sin(q - (r * 4.3 + a / 12.0) * g) + tan(r * g + h) * 184.0 * Math.cos(r * g + h);\n'
		'	i = mod(i / 5.6, 256.0) / 64.0;\n'
		'	if (i < 0.0) i += 4.0;\n'
		'	if (i >= 2.0) i = 4.0 - i;\n'
		'	d = r / 350.0;\n'
		'	d += Math.sin(d * d * 8.0) * 0.52;\n'
		'	f = (Math.sin(a * g) + 1.0) / 2.0;\n'
		'	gl_FragColor = new two.vec4(new two.vec3(f * i / 1.6, i / 2.0 + d / 13.0, i) * d * p.x + new two.vec3(i / 1.3 + d / 8.0, i / 2.0 + d / 18.0, i) * d * (1.0 - p.x), 1.0);\n'
		'\n'
		'}\n';

	return shader;
}

void xx_shader(Shell app, Widget parent, Dockbar dockbar)
{
	UNUSED(app);
	var viewer = two.ui.scene_viewer(app.ui.begin());
	two.ui.orbit_controller(viewer);

	Gnode scene = viewer.scene.begin();

	static string source = create_shader();

	static Program program = { 'custoprogram', {}, { nullptr, source.c_str(), nullptr, nullptr } };

	function draw_quad = [](Render render, Pass render_pass)
	{
		BlockFilter filter = render.scene.gfx.pipeline->block<BlockFilter>();
		filter.submit_quad(*render_pass.target, render_pass.index, render_pass.target->fbo, program.default_version(), { render_pass.viewport->rect });
	};

	two.gfx.manual_job(scene, PassType::Solid, draw_quad);


	//static bool once = false;
	//if(!once)
	//{
	//	once = true;
	//
	//	camera = new THREE.OrthographicCamera(-1, 1, 1, -1, 0, 1);
	//
	//	scene = new THREE.Scene();
	//
	//	var geometry = new THREE.PlaneBufferGeometry(2, 2);
	//
	//	uniforms = {
	//		'time': { value: 1.0 }
	//	};
	//
	//	var material = new THREE.ShaderMaterial({
	//
	//		uniforms: uniforms,
	//		vertexShader : document.getElementById('vertexShader').textContent,
	//		fragmentShader : document.getElementById('fragmentShader').textContent
	//
	//		});
	//
	//	var mesh = new THREE.Mesh(geometry, material);
	//	scene.add(mesh);
	//}
	//
	//uniforms['time'].value = timestamp / 1000;
}