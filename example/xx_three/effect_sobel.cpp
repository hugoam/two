//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

//<script src="js/shaders/LuminosityShader.js"></script>
//<script src="js/shaders/SobelOperatorShader.js"></script>

void pass_grayscale(GfxSystem& gfx, Render& render)
{
	// color to grayscale conversion

	//var effectGrayScale = new THREE.ShaderPass(THREE.LuminosityShader);
	//composer.addPass(effectGrayScale);
}

void pass_sobel(GfxSystem& gfx, Render& render)
{
	// you might want to use a gaussian blur filter before
	// the next pass to improve the result of the Sobel operator

	// Sobel operator

	//effectSobel = new THREE.ShaderPass(THREE.SobelOperatorShader);
	//effectSobel.renderToScreen = true;
	//effectSobel.uniforms["resolution"].value.x = window.innerWidth;
	//effectSobel.uniforms["resolution"].value.y = window.innerHeight;
	//composer.addPass(effectSobel);

}

void xx_effect_sobel(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Node3* node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		//var params = {
		//	enable: true
		//};

		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye = vec3(0.f, 10.f, 25.f);

		//var geometry = new THREE.TorusKnotBufferGeometry(8, 3, 256, 32, 2, 3);
		Model& geometry = app.m_gfx.shape(TorusKnot(8.f, 3.f));

		Program& pbr = app.m_gfx.programs().fetch("pbr/pbr");

		//var material = new THREE.MeshPhongMaterial({ color: 0xffff00 });
		Material& material = app.m_gfx.materials().create("material", [&](Material& m) {
			m.m_program = &pbr;
			m.m_pbr.m_albedo = rgb(0xffff00);
			});

		Node3& n = gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(n, geometry, 0U, &material));

		//var ambientLight = new THREE.AmbientLight(0xcccccc, 0.4);
		//scene.add(ambientLight);
		//
		//var pointLight = new THREE.PointLight(0xffffff, 0.8);
		//camera.add(pointLight);
		//scene.add(camera);

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);
			pass_grayscale(gfx, render);
			pass_sobel(gfx, render);
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

	//gui.add(params, 'enable');
}
