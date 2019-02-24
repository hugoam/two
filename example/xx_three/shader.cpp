//#include <mud/frame.h>
#include <frame/Api.h>
#include <ui/Edit/Lang.h>

#include <09_live_shader/09_live_shader.h>

using namespace mud;

string create_shader()
{
	string shader =

		"$input v_texcoord0\n"
		"\n"
		"#include \"filter/filter.sh\"\n"
		"\n"
		"void main() {\n"
		"\n"
		"	vec2 p = - 1.0 + 2.0 * v_texcoord0.xy;\n"
		"	float a = u_time * 40.0;\n"
		"	float d, e, f, g = 1.0 / 40.0 ,h ,i ,r ,q;\n"
		"\n"
		"	e = 400.0 * ( p.x * 0.5 + 0.5 );\n"
		"	f = 400.0 * ( p.y * 0.5 + 0.5 );\n"
		"	i = 200.0 + sin( e * g + a / 150.0 ) * 20.0;\n"
		"	d = 200.0 + cos( f * g / 2.0 ) * 18.0 + cos( e * g ) * 7.0;\n"
		"	r = sqrt( pow( abs( i - e ), 2.0 ) + pow( abs( d - f ), 2.0 ) );\n"
		"	q = f / r;\n"
		"	e = ( r * cos( q ) ) - a / 2.0;\n"
		"	f = ( r * sin( q ) ) - a / 2.0;\n"
		"	d = sin( e * g ) * 176.0 + sin( e * g ) * 164.0 + r;\n"
		"	h = ( ( f + d ) + a / 2.0 ) * g;\n"
		"	i = cos( h + r * p.x / 1.3 ) * ( e + e + a ) + cos( q * g * 6.0 ) * ( r + h / 3.0 );\n"
		"	h = sin( f * g ) * 144.0 - sin( e * g ) * 212.0 * p.x;\n"
		"	h = ( h + ( f - e ) * q + sin( r - ( a + h ) / 7.0 ) * 10.0 + i / 4.0 ) * g;\n"
		"	i += cos( h * 2.3 * sin( a / 350.0 - q ) ) * 184.0 * sin( q - ( r * 4.3 + a / 12.0 ) * g ) + tan( r * g + h ) * 184.0 * cos( r * g + h );\n"
		"	i = mod( i / 5.6, 256.0 ) / 64.0;\n"
		"	if ( i < 0.0 ) i += 4.0;\n"
		"	if ( i >= 2.0 ) i = 4.0 - i;\n"
		"	d = r / 350.0;\n"
		"	d += sin( d * d * 8.0 ) * 0.52;\n"
		"	f = ( sin( a * g ) + 1.0 ) / 2.0;\n"
		"	gl_FragColor = vec4( vec3( f * i / 1.6, i / 2.0 + d / 13.0, i ) * d * p.x + vec3( i / 1.3 + d / 8.0, i / 2.0 + d / 18.0, i ) * d * ( 1.0 - p.x ), 1.0 );\n"
		"\n"
		"}\n";

	return shader;
}

void xx_shader(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene.begin();

	static string source = create_shader();

	static Program program = { "custom_program", {}, { nullptr, source.c_str(), nullptr, nullptr } };

	auto draw_quad = [](Render& render, const Pass& render_pass)
	{
		BlockFilter& filter = *render.m_scene.m_gfx_system.m_pipeline->block<BlockFilter>();
		filter.submit_quad(*render_pass.m_target, render_pass.m_index, render_pass.m_target->m_fbo, program.default_version(), { render_pass.m_viewport->m_rect });
	};

	gfx::manual_job(scene, PassType::Unshaded, draw_quad);


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
	//		"time": { value: 1.0 }
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
	//uniforms["time"].value = timestamp / 1000;
}