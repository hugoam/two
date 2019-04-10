//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <ecs/ECS.hpp>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_material_variations(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");
	static Program& three = *app.m_gfx.programs().file("pbr/three");

	static Node3* light = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 2000.f;
		camera.m_eye = vec3(0.f, 400.f, 400.f * 3.5f);

		viewer.m_viewport.m_to_gamma = true;

		Tonemap& tonemap = viewer.m_viewport.comp<Tonemap>();
		//tonemap.m_enabled = true;
		//tonemap.m_mode = TonemapMode::Reinhardt;
		//tonemap.m_mode = TonemapMode::Uncharted2;
		//tonemap.m_exposure = 0.75f;

		Texture& hdrenv = *app.m_gfx.textures().file("cube/pisaHDR.hdr.cube");

		Zone& env = scene.m_env;
		env.m_radiance.m_texture = &hdrenv;
		env.m_background.m_texture = &hdrenv;
		env.m_background.m_mode = BackgroundMode::Panorama;
		env.m_radiance.m_ambient = rgb(0x222222);


		Model& sphere = app.m_gfx.shape(Sphere(4.f));
		Node3& l = gfx::nodes(scene).add(Node3());
		//Item& il = gfx::items(scene).add(Item(l, sphere, 0U, &gfx::solid_material(app.m_gfx, "light", Colour(1.f))));
		Light& ll = gfx::lights(scene).add(Light(l, LightType::Point, false, rgb(0xffffff), 2.f, 800.f));
		light = &l;

		Node3& dl = gfx::nodes(scene).add(Node3(vec3(0.f), facing(normalize(vec3(-1.f, -1.f, -1.f)))));
		gfx::lights(scene).add(Light(dl, LightType::Direct, false, rgb(0xffffff)));

		// Materials

		//Texture& texture = *app.m_gfx.textures().file("planets/moon_1024.jpg");
		//imgTexture.anisotropy = 16;

		const size_t subdiv = 5;
		const float width = 400.f;
		const float radius = (width / float(subdiv)) * 0.8f * 0.5f;
		const float step = 1.0f / float(subdiv);

		Model& geometry = app.m_gfx.shape(Sphere(radius));

		size_t index = 0;

		for(float alpha = 0.f; alpha <= 1.0f; alpha += step)
			for(float beta = 0.f; beta <= 1.0f; beta += step)
				for(float gamma = 0.f; gamma <= 1.0f; gamma += step)
				{
					// basic monochromatic energy preservation
					const Colour diffuse = hsl(alpha, 0.5f, gamma * 0.5f + 0.1f);

					const string name = "variation" + to_string(index);
					Material& material = app.m_gfx.materials().create(name, [&](Material& m) {
						m.m_program = &pbr;
						m.m_program = &three;
						m.m_pbr.m_albedo = diffuse;
						//m.m_pbr.m_albedo = &texture;
						//m.m_pbr.m_normal = &texture;
						m.m_lit.m_normal.m_value = 1.f;
						m.m_lit.m_no_envmap = index % 2 == 0 ? true : false;
						m.m_pbr.m_metallic = beta;
						m.m_pbr.m_roughness = 1.f - alpha;
					});

					index++;

					vec3 p = vec3(alpha, beta, gamma) * 400.f - 200.f;

					Node3& node = gfx::nodes(scene).add(Node3(p));
					gfx::items(scene).add(Item(node, geometry, 0U, &material));
				}

		//var loader = new THREE.FontLoader();
		//loader.load('fonts/gentilis_regular.typeface.Json', function(font) {

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
		//addLabel("+roughness", new THREE.Vector3(-350, 0, 0));
		//addLabel("-roughness", new THREE.Vector3(350, 0, 0));
		//
		//addLabel("-metalness", new THREE.Vector3(0, -300, 0));
		//addLabel("+metalness", new THREE.Vector3(0, 300, 0));
		//
		//addLabel("-diffuse", new THREE.Vector3(0, 0, -300));
		//addLabel("+diffuse", new THREE.Vector3(0, 0, 300));

	}

	const float time = app.m_gfx.m_time * 0.1f;

	//camera.position.x = cos(timer) * 800;
	//camera.position.z = sin(timer) * 800;

	//camera.lookAt(scene.position);

	vec3 p = vec3(sin(time * 7.f) * 300.f, cos(time * 5.f) * 400.f, cos(time * 3.f) * 300.f);
	light->apply(p);
}