//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_material_cubemap(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterOBJ obj_importer = { app.m_gfx };

	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	OrbitControls& controls = ui::orbit_controls(viewer);
	//controls.enableZoom = false;
	//controls.enablePan = false;
	//controls.minPolarAngle = Math.PI / 4;
	//controls.maxPolarAngle = Math.PI / 1.5;

	Scene& scene = viewer.m_scene;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 5000.f;
		camera.m_eye.z = 2000.f;

		Texture& envmap = *app.m_gfx.textures().file("cube/royal.jpg.cube");
		scene.m_env.m_radiance.m_texture = &envmap;
		scene.m_env.m_radiance.m_energy = 1.f;
		//scene.background = envmap;

		//lights
		//var ambient = new THREE.AmbientLight(0xffffff);
		//scene.add(ambient);
		//
		//pointLight = new THREE.PointLight(0xffffff, 2);
		//scene.add(pointLight);

		//materials
		Material& material3 = app.m_gfx.materials().create("material"); //new THREE.MeshLambertMaterial({ color: 0xff6600, envMap : reflectionCube, combine : THREE.MixOperation, reflectivity : 0.3 });
		Material& material2 = app.m_gfx.materials().create("material"); //new THREE.MeshLambertMaterial({ color: 0xffee00, envMap : refractionCube, refractionRatio : 0.95 });
		Material& material1 = app.m_gfx.materials().create("material"); //new THREE.MeshLambertMaterial({ color: 0xffffff, envMap : reflectionCube });

		Model& model = *app.m_gfx.models().file("WaltHead");

		Node3& n0 = gfx::nodes(scene).add(Node3(vec3(0.f, -500.f, 0.f), ZeroQuat, vec3(15.f)));
		gfx::items(scene).add(Item(n0, model, 0U, &material1));

		Node3& n1 = gfx::nodes(scene).add(Node3(vec3(-900.f, -500.f, 0.f), ZeroQuat, vec3(15.f)));
		gfx::items(scene).add(Item(n1, model, 0U, &material2));

		Node3& n2 = gfx::nodes(scene).add(Node3(vec3(900.f, -500.f, 0.f), ZeroQuat, vec3(15.f)));
		gfx::items(scene).add(Item(n2, model, 0U, &material3));
	}
}
