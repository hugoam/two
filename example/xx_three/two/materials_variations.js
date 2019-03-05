//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

//<script src = 'js/pmrem/PMREMCubeUVPacker.js'>< / script>

void xx_materials_variations(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	//var loader = new THREE.FontLoader();
	//loader.load('fonts/gentilis_regular.typeface.json', function(font) {

	this.pbr = app.gfx.programs().file('pbr/pbr');

	this.light = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 40.0; camera.near = 1.0; camera.far = 2000.0;
		camera.eye = new two.vec3(0.0, 400.0, 400.0 * 3.5);

		//scene.background = textureCube;

		//scene.add(new THREE.AmbientLight(0x222222));

		//var hdrUrls = genCubeUrls('./textures/cube/pisaHDR/', '.hdr');
		//var hdrCubeRenderTarget = null;

		// Materials

		Texture texture = app.gfx.textures().file('planets/moon_1024.jpg');
		//imgTexture.anisotropy = 16;

		var subdiv = 5;
		var width = 400.0;
		var radius = (width / float(subdiv)) * 0.8 * 0.5;
		var step = 1.0 / float(subdiv);

		var geometry = app.gfx.shape(new two.Sphere(radius));

		var index = 0;

		for(var alpha = 0.0; alpha <= 1.0; alpha += step)
			for(var beta = 0.0; beta <= 1.0; beta += step)
				for(var gamma = 0.0; gamma <= 1.0; gamma += step)
				{
					// basic monochromatic energy preservation
					Colour diffuse = two.hsl(alpha, 0.5, gamma * 0.5 + 0.1);

					this.material = app.gfx.materials().create('material', [](var m) {
						m.program = pbr;
						m.pbr.albedo = diffuse;
						m.pbr.albedo = texture;
						m.pbr.normal = texture;
						m.pbr.normal.value = 1.0;
						m.pbr.metallic = beta;
						m.pbr.roughness = 1.0 - alpha;
						m.pbr.scene_environment = index % 2 == 0 ? false : true;
					});

					index++;

					var p = new two.vec3(alpha, beta, gamma) * 400.0 - 200.0;

					var node = two.gfx.nodes(scene).add(new two.Node3());
					two.gfx.items(scene).add(new two.Item(node, geometry, 0U, material));
				}


		//function addLabel(name, location) {
		//
		//	var textGeo = new THREE.TextBufferGeometry(name, {
		//
		//		font: font,
		//
		//		size : 20,
		//		height : 1,
		//		curveSegments : 1
		//
		//		});
		//
		//	var textMaterial = new THREE.MeshBasicMaterial({ color: 0xffffff });
		//	var textMesh = new THREE.Mesh(textGeo, textMaterial);
		//	textMesh.position.copy(location);
		//	scene.add(textMesh);
		//
		//}
		//
		//addLabel('+roughness', new THREE.Vector3(-350, 0, 0));
		//addLabel('-roughness', new THREE.Vector3(350, 0, 0));
		//
		//addLabel('-metalness', new THREE.Vector3(0, -300, 0));
		//addLabel('+metalness', new THREE.Vector3(0, 300, 0));
		//
		//addLabel('-diffuse', new THREE.Vector3(0, 0, -300));
		//addLabel('+diffuse', new THREE.Vector3(0, 0, 300));

		var sphere = app.gfx.shape(new two.Sphere(4.0));
		var l = two.gfx.nodes(scene).add(new two.Node3());
		var il = two.gfx.items(scene).add(new two.Item(l, sphere, 0U, two.gfx.solid_material(app.gfx, 'light', new two.Colour(1.0))));
		Light ll = two.gfx.lights(scene).add(Light(l, LightType::Point, false, two.rgba(0xffffff), 2.0, 800.0));
		light = l;

		var dl = two.gfx.nodes(scene).add(new two.Node3(new two.vec3(0.0), facing(normalize(new two.vec3(-1.0, -1.0, -1.0)))));
		two.gfx.lights(scene).add(Light(dl, LightType::Direct, false, two.rgba(0xffffff)));

		//renderer.toneMapping = THREE.Uncharted2ToneMapping;
		//renderer.toneMappingExposure = 0.75;
	}

	var time = app.gfx.time;

	//camera.position.x = Math.cos(timer) * 800;
	//camera.position.z = Math.sin(timer) * 800;

	//camera.lookAt(scene.position);

	var p = new two.vec3(Math.sin(time * 7.0) * 300.0, Math.cos(time * 5.0) * 400.0, Math.cos(time * 3.0) * 300.0);
	light->transform = bxTRS(new two.vec3(1.0), ZeroQuat, p);
}