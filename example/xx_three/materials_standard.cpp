//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_materials_standard(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterOBJ importer_obj = { app.m_gfx };

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	static Texture& hdrenv = *app.m_gfx.textures().file("pisaHDR.cube");
	//static Texture& prefiltered = // automatic

	//material.envMap = hdrCubeRenderTarget.texture;
	//material.needsUpdate = true; // is this needed?

	//renderer.toneMapping = THREE.ReinhardToneMapping;
	//renderer.toneMappingExposure = 3;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 50.f; camera.m_near = 0.01f; camera.m_far = 1000.f;
		camera.m_eye.z = 2.f;

		//controls = new THREE.TrackballControls(camera, renderer.domElement);

		//scene.add(new THREE.HemisphereLight(0x443333, 0x222233, 4));

		//Material& material = new THREE.MeshStandardMaterial();

		Texture& albedo = *app.m_gfx.textures().file("Cerberus_A.jpg");
		Texture& metrough = *app.m_gfx.textures().file("Cerberus_RM.jpg");
		Texture& normal = *app.m_gfx.textures().file("Cerberus_N.jpg");

		Model& model = *app.m_gfx.models().file("Cerberus.obj");

		//var material = new THREE.MeshPhongMaterial({ specular: 0x101010, shininess : 100, envMap : reflectionCube, combine : THREE.MixOperation, reflectivity : 0.1, side : THREE.DoubleSide });
		Material& material = app.m_gfx.materials().create("material", [&](Material& m) {
			m.m_program = &pbr;
			m.m_pbr.m_metallic = 1.f;
			m.m_pbr.m_roughness = 1.f;
			m.m_pbr.m_albedo = &albedo;
			m.m_pbr.m_metallic = &metrough;
			m.m_pbr.m_roughness = &metrough;
			m.m_pbr.m_normal = &normal;
		});

		vec3 angles = vec3(-0.45f, -c_pi2, 0.f);
		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f), quat(angles)));
		gfx::items(scene).add(Item(n, model, 0U, &material));
	}
}
