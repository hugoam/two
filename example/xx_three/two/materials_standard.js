//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_materials_standard(Shell app, Widget parent, Dockbar dockbar)
{
	static ImporterOBJ importer_obj = { app.gfx };

	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	this.pbr = app.gfx.programs().file('pbr/pbr');

	this.hdrenv = app.gfx.textures().file('pisaHDR.cube');
	//this.prefiltered = // automatic

	//material.envMap = hdrCubeRenderTarget.texture;
	//material.needsUpdate = true; // is this needed?

	//renderer.toneMapping = THREE.ReinhardToneMapping;
	//renderer.toneMappingExposure = 3;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 50.0; camera.near = 0.01; camera.far = 1000.0;
		camera.eye.z = 2.0;

		//controls = new THREE.TrackballControls(camera, renderer.domElement);

		//scene.add(new THREE.HemisphereLight(0x443333, 0x222233, 4));

		//var material = new THREE.MeshStandardMaterial();

		Texture albedo = app.gfx.textures().file('Cerberus_A.jpg');
		Texture metrough = app.gfx.textures().file('Cerberus_RM.jpg');
		Texture normal = app.gfx.textures().file('Cerberus_N.jpg');

		var model = app.gfx.models().file('Cerberus.obj');

		//var material = new THREE.MeshPhongMaterial({ specular: 0x101010, shininess : 100, envMap : reflectionCube, combine : THREE.MixOperation, reflectivity : 0.1, side : THREE.DoubleSide });
		var material = app.gfx.materials().create('material', [](var m) {
			m.program = pbr;
			m.pbr.metallic = 1.0;
			m.pbr.roughness = 1.0;
			m.pbr.albedo = albedo;
			m.pbr.metallic = metrough;
			m.pbr.roughness = metrough;
			m.pbr.normal = normal;
		});

		var angles = new two.vec3(-0.45, -Math.PI2, 0.0);
		var n = two.gfx.nodes(scene).add(new two.Node3(new two.vec3(0.0), new two.quat(angles)));
		two.gfx.items(scene).add(new two.Item(n, model, 0U, material));
	}
}
