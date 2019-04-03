//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

static string skydome_vertex()
{
	string shader =

		"$input a_position, a_texcoord0\n"
		"$output v_world\n"
		"\n"
		"#include <common.sh>\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));\n"
		"	v_world = world.xyz;\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		"}\n";

	return shader;
}

static string skydome_fragment()
{
	string shader =

		"$input v_world\n"

		"#include <common.sh>\n"

		"#define u_top_color u_user_p0.xyz\n"
		"#define u_bottom_color u_user_p1.xyz\n"
		"#define u_offset u_user_p2.x\n"
		"#define u_exponent u_user_p2.y\n"

		"void main()\n"
		"{\n"
		"	float h = normalize(v_world + u_offset).y;\n"
		"	gl_FragColor = vec4(mix(u_bottom_color, u_top_color, max(pow(max(h, 0.0), u_exponent), 0.0)), 1.0);\n"
		"}\n";

	return shader;
}

void xx_light_hemisphere(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterGltf importer_gltf = { app.m_gfx };

	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 30.f; camera.m_near = 1.f; camera.m_far = 5000.f;
		camera.m_eye = vec3(0.f, 0.f, 250.f);

		viewer.m_viewport.m_clear_colour = hsl(0.6f, 0.f, 1.f);
		scene.m_env.m_background.m_colour = hsl(0.6f, 0.f, 1.f);
		scene.m_env.m_radiance.m_ambient = 0.f;

		//scene.fog = new THREE.Fog( scene.background, 1, 5000 );

		// LIGHTS

		Colour skylight = hsl(0.6f, 1.f, 0.6f);
		scene.m_env.m_skylight = { true, 0.6f, vec3(0.f, 50.f, 0.f), vec3(0.f), skylight, hsl(0.095f, 1.f, 0.75f) };

		//hemiLightHelper = new THREE.HemisphereLightHelper( hemiLight, 10 );
		//scene.add( hemiLightHelper );

		const bool shadows = true;
		const vec3 dir = vec3(-1.f, 1.75f, 1.f) * 30.f;
		const quat q = look_dir(-normalize(dir));

		Node3& nl = gfx::nodes(scene).add(Node3(vec3(0.f), q));
		Light& l = gfx::lights(scene).add(Light(nl, LightType::Direct, shadows, hsl(0.1f, 1.f, 0.95f), 1.f));

		// shadow.camera.extent = 50;
		l.m_shadow_range = 3500.f;
		//l.m_shadow_bias = -0.0001f;
		l.m_shadow_bias = 0.5f;

		//dirLightHeper = new THREE.DirectionalLightHelper( dirLight, 10 );
		//scene.add( dirLightHeper );

		// GROUND

		Program& pbr = *app.m_gfx.programs().file("pbr/pbr");
		Program& phong = *app.m_gfx.programs().file("pbr/phong");

		//var groundMat = new THREE.MeshLambertMaterial({ color: 0xffffff });
		Material& groundmat = app.m_gfx.materials().create("ground", [&](Material& m) {
			m.m_program = &phong;
			//m.m_program = &pbr;
			m.m_phong.m_diffuse = hsl(0.095, 1, 0.75);
			//m.m_pbr.m_albedo = hsl(0.095, 1, 0.75);
		});

		Model& ground = app.m_gfx.shape(Rect(vec2(0.f), vec2(10000.f)));
		Node3& nground = gfx::nodes(scene).add(Node3(vec3(0.f, -33.f, 0.f)));
		gfx::items(scene).add(Item(nground, ground, 0, &groundmat));

		// SKYDOME

		Program& skydome = app.m_gfx.programs().create("skydome");
		skydome.set_block(MaterialBlock::Solid);
		skydome.set_block(MaterialBlock::User);
		skydome.set_source(ShaderType::Vertex, skydome_vertex());
		skydome.set_source(ShaderType::Fragment, skydome_fragment());

		struct Skydome
		{
			Colour top = rgb(0x0077ff);
			Colour bottom = rgb(0xffffff);
			float offset = 33;
			float exponent = 0.6f;
		};

		Skydome dome;
		dome.top = skylight;

		//scene.fog.color.copy( uniforms[ "bottomColor" ].value );

		Model& skysphere = app.m_gfx.shape(Sphere(4000.f)); //  new THREE.SphereBufferGeometry(4000, 32, 15);
		Material& skymat = app.m_gfx.materials().create("skydome", [&](Material& m) {
			m.m_program = &skydome;
			m.m_base.m_cull_mode = CullMode::Front;
			m.m_user.m_attr0 = { to_vec3(dome.top), 0.f };
			m.m_user.m_attr1 = { to_vec3(dome.bottom), 0.f };
			m.m_user.m_attr2 = { dome.offset, dome.exponent, 0.f, 0.f };
		});

		Node3& nsky = gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(nsky, skysphere, 0, &skymat));

		// MODEL

		Model& model = *app.m_gfx.models().file("Flamingo"); // .glb
		
		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f, -1.f, 0.f), quat(vec3(0.f, -1.f, 0.f)), vec3(0.35f)));
		Item& it = gfx::items(scene).add(Item(n, model));
		Mime& mi = gfx::mimes(scene).add(Mime(n));
		mi.add_item(it);

		string anim = mi.m_rig.m_skeleton.m_animations[0]->m_name;
		mi.start(anim, true);
		//mixer.clipAction( gltf.animations[ 0 ] ).setDuration( 1 ).play();
		//mixers.push( mixer );
	}

	scene.update();

	//function onKeyDown( event ) {
	//	switch ( event.keyCode ) {
	//		case 72: // h
	//			hemiLight.visible = ! hemiLight.visible;
	//			hemiLightHelper.visible = ! hemiLightHelper.visible;
	//			break;
	//		case 68: // d
	//			dirLight.visible = ! dirLight.visible;
	//			dirLightHeper.visible = ! dirLightHeper.visible;
	//			break;
	//	}
	//}

	//var delta = clock.getDelta();
	//
	//for ( var i = 0; i < mixers.length; i ++ ) {
	//	mixers[ i ].update( delta );
	//}
}
