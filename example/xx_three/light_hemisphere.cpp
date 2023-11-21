module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

static string skydome_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_world\n"
		
	"#include <common.sh>\n"
		
	"void main()\n"
	"{\n"
	"	vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));\n"
	"	v_world = world.xyz;\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string skydome_fragment =

	"$input v_world\n"

	"#include <common.sh>\n"

	"void main()\n"
	"{\n"
		"int material_index = int(u_state_material);\n"
		"UserMaterial mat = read_user_material(material_index);\n"

		"vec3 top_color    = mat.p0.xyz;\n"
		"vec3 bottom_color = mat.p1.xyz;\n"
		"float offset      = mat.p2.x;\n"
		"float exponent    = mat.p2.y;\n"

		"float h = normalize(v_world + offset).y;\n"
		"gl_FragColor = vec4(mix(bottom_color, top_color, max(pow(max(h, 0.0), exponent), 0.0)), 1.0);\n"
		"gl_FragColor = vec4(pow(gl_FragColor.rgb, vec3_splat(2.0)), 1.0);\n"
	"}\n";

EX(xx_light_hemisphere)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	static ImporterGltf importer_gltf = { app.m_gfx };

#if UI
	ui::orbit_controls(viewer);
#endif

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 30.f; camera.m_near = 1.f; camera.m_far = 5000.f;
		camera.m_eye = vec3(0.f, 0.f, 250.f);

		Colour colour = hsl(0.6f, 0.f, 1.f);

		viewer.m_viewport.m_to_gamma = true;
		viewer.m_viewport.m_clear_colour = colour;

		scene.m_env.m_background.m_colour = colour;

		scene.m_env.m_fog.m_enabled = true;
		scene.m_env.m_fog.m_colour = colour;
		scene.m_env.m_fog.m_depth_begin = 1.f;
		scene.m_env.m_fog.m_depth_end = 5000.f;

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
		skydome.set_source(ShaderType::Vertex, skydome_vertex);
		skydome.set_source(ShaderType::Fragment, skydome_fragment);

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
		gfx::items(scene).add(Item(nsky, skysphere, ItemFlag::Render | ItemFlag::LodAll, &skymat));

		// MODEL

		Program& three = *app.m_gfx.programs().file("pbr/three");

		Model& model = *app.m_gfx.models().file("Flamingo"); // .glb

		model.get_mesh(0).m_material->m_base.m_shader_color = ShaderColor::Vertex;
		model.get_mesh(0).m_material->m_base.m_flat_shaded = true;
		model.get_mesh(0).m_material->m_program = &three;

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f, 15.f, 0.f), quat(vec3(0.f, -1.f, 0.f)), vec3(0.35f)));
		Item& it = gfx::items(scene).add(Item(n, model));
		Mime& mi = gfx::mimes(scene).add(Mime());
		mi.add_item(it);

		//Animation& anim = *mi.m_anims[0];
		//mi.play(anim, true, 0.f, 1.2f);
		mi.start("flamingo_flyA_", true, 0.f, 1.2f);
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
}
