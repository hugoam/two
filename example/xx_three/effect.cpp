//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

//<script src="js/shaders/DotScreenShader.js"></script>
//<script src="js/shaders/RGBShiftShader.js"></script>

void pass_dotscreen(GfxSystem& gfx, Render& render)
{
	//var effect = new THREE.ShaderPass(THREE.DotScreenShader);
	//effect.uniforms['scale'].value = 4;
	//composer.addPass(effect);
}

void pass_rgbshift(GfxSystem& gfx, Render& render)
{
	//var effect = new THREE.ShaderPass(THREE.RGBShiftShader);
	//effect.uniforms['amount'].value = 0.0015;
	//effect.renderToScreen = true;
	//composer.addPass(effect);
}

void xx_effect(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);

	Scene& scene = viewer.m_scene;

	static Node3* node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye.z = 400.f;

		//scene.fog = new THREE.Fog(0x000000, 1, 1000);

		Node3& object = gfx::nodes(scene).add(Node3());
		//node = &object;

		Model& geometry = app.m_gfx.shape(Sphere(1.f));

		Program& pbr = app.m_gfx.programs().fetch("pbr/pbr");

		Material& material = app.m_gfx.materials().create("material", [&](Material& m) {
			m.m_program = &pbr;
			m.m_pbr.m_albedo = rgb(0xffffff);
			// flatShading : true
		});

		for(size_t i = 0; i < 100; i++)
		{
			const vec3 p = normalize(vec3(randf(), randf(), randf()) - 0.5f) * randf() * 400.f;
			const vec3 a = vec3(randf(), randf(), randf()) * 2.f;
			const vec3 s = vec3(randf()) * 50.f;

			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
		}

		//scene.add(new THREE.AmbientLight(0x222222));

		//light = new THREE.DirectionalLight(0xffffff);
		//light.position.set(1, 1, 1);
		//scene.add(light);

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);
			pass_dotscreen(gfx, render);
			pass_rgbshift(gfx, render);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

	static vec3 angles = vec3(0.f);
	angles.x += 0.005;
	angles.y += 0.01;

	node->apply(vec3(0.f), quat(angles));
}