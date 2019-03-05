//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

void xx_lights_point(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);
	TrackballController controls = two.ui.trackball_controller(viewer);
	controls.dynamicDampingFactor = 0.15;
	
	//controls.keys = [65, 83, 68];

	var scene = viewer.scene;

	static vector<Node3*> lights;

	static bool once = false;
	if(!once)
	{
		once = true;

		// MATERIALS

#if 0
		Texture* texture = app.gfx.textures().file('disturb.jpg');
		//texture.repeat.set(20, 10);
		//texture.wrapS = texture.wrapT = THREE.RepeatWrapping;
		//texture.0ormat = THREE.RGBFormat;

		var ground_material = app.gfx.materials().fetch('ground'); //new THREE.MeshPhongMaterial({ color: 0xffffff, map: texture });
		var material = two.gfx.pbr_material(app.gfx, 'object', two.rgba(0xffffff), 0.5, 1.0); //new THREE.MeshStandardMaterial({ color: 0xffffff, roughness: 0.5, metalness: 1.0 });

		// GROUND

		var model = app.gfx.shape(new two.Rect()); //new THREE.Mesh(new THREE.PlaneBufferGeometry(800, 400, 2, 2), groundMaterial);
		var node = two.gfx.nodes(scene) += new two.Node3(new two.vec3(0, -5, 0), new two.quat(-Math.PI / 2.0, 0, 0, 1)));
		two.gfx.items(scene) += new two.Item(node, model, 0, ground_material));
#endif

		// OBJECTS
		var material = two.gfx.pbr_material(app.gfx, 'object', new two.Colour(1.0));//, 0.5, 1.0); //new THREE.MeshStandardMaterial({ color: 0xffffff, roughness: 0.5, metalness: 1.0 });

		//var torus = Torus();
		var torus_model = app.gfx.shape(new two.Torus(1.0, 0.1)); //new THREE.TorusBufferGeometry(1.5, 0.4, 8, 16);

		for(int i = 0; i < 5000; i++) {

			var x = 400.0 * (0.5 - Math.random());
			var y = 50.0 * (0.5 - Math.random()) + 25;
			var z = 200.0 * (0.5 - Math.random());

			var a = 3.14f * (0.5 - Math.random());
			var b = 3.14f * (0.5 - Math.random());

			uint32_t flags = ItemFlag::Default;// | ItemFlag::NoCull;
			var n = two.gfx.nodes(scene).add(new two.Node3(new two.vec3(x, y, z), new two.quat(a, b, 0, 1)));
			var it = two.gfx.items(scene).add(new two.Item(n, torus_model, flags, material));

			//Gnode n = two.gfx.node(root, {}, new two.vec3(x, y, z));
			//two.gfx.item(n, torus_model, 0, material);
		}

		// LIGHTS

		var intensity = 2.5;
		var distance = 100;
		var decay = 2.0;

		uint32_t colours[] = { 0xff0040f, 0x0040fff, 0x80f80f, 0xffaa00f, 0x00faaff, 0xff1100f };

		Sphere sphere = new two.Sphere(2.5); //THREE.SphereBufferGeometry(0.25, 16, 8);
		var sphere_model = app.gfx.shape(sphere, DrawMode::PLAIN);

		for(int i = 0; i < 6; ++i)
		{
			Colour c = two.rgba(colours[i]);
			var m = two.gfx.solid_material(app.gfx, ('light' + to_string(i)).c_str(), c); //Material({ color: colours[i] }));
			var n = two.gfx.nodes(scene).add(new two.Node3());
			Light l = two.gfx.lights(scene).add(Light(n, LightType::Point, false));
			l.colour = c;
			l.energy = intensity;
			l.range = distance;
			l.attenuation = 2.0;
			//l.decay = decay;
			var it = two.gfx.items(scene).add(new two.Item(n, sphere_model, ItemFlag::Default, m));
			UNUSED(it);

			lights.push(n);
		}

		//var direct_node = two.gfx.nodes(scene) += new two.Node3());
		//Light direct_light = two.gfx.lights(scene) += Light(direct_node, LightType::Direct)); //THREE.DirectionalLight(0xffffff, 0.05);
		//dlight.position.set(0.5, 1, 0).normalize();
	}

	Gnode root = viewer.scene.begin();
	two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', BackgroundMode::Radiance);

	var coef0[] = { 0.7, 0.3, 0.7, 0.3, 0.3, 0.7 };
	var coef1[] = { 0.3, 0.7, 0.5, 0.5, 0.5, 0.5 };

	//var time = Date.now() * 0.00025;
	var d = 150;

	static var time = 0.0;
	time += 0.01;

	for(int i = 0; i < 6; ++i)
	{
		var pos = { Math.sin(time * coef0[i]) * d, Math.cos(time * coef1[i]) * d };
		lights[i]->transform = bxSRT(new two.vec3(1.0), ZeroQuat, new two.vec3(pos.x, 0.0, pos.y));
	}
}
