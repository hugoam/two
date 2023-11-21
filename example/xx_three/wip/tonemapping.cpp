module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;
//
//<script src = "js/postprocessing/EffectComposer.js">< / script>
//<script src = "js/postprocessing/RenderPass.js">< / script>
//<script src = "js/postprocessing/MaskPass.js">< / script>
//<script src = "js/postprocessing/ShaderPass.js">< / script>
//<script src = "js/shaders/CopyShader.js">< / script>

EX(xx_tonemapping)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	struct Params {
		float opacity = 1.0;
		float roughness = 1.0;
		float bumpScale = 1.0;
		float exposure = 3.0;
		float whitePoint = 5.0;
		//toneMapping : "Uncharted2",
		//renderMode : "Renderer"
	};

	static Params params;
	
	static Texture& diffuse = *app.m_gfx.textures().file("brick_diffuse.jpg");
	//map.encoding = THREE.sRGBEncoding;

	static Texture& bump = *app.m_gfx.textures().file("brick_bump.jpg");
	static Texture& rough = *app.m_gfx.textures().file("brick_roughness.jpg");

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	static Texture& hdrenv = *app.m_gfx.textures().file("pisaHDR.hdr.cube");

	static Material* material = nullptr;
	static Node3* mesh = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 2000.f;
		camera.m_eye = vec3(0.f, 40.f, 40.f * 3.5f);
		
		Material& mat = app.m_gfx.materials().create("tonemapping",  [&](Material& m) {
			m.m_program = &pbr;
			m.m_pbr.m_albedo = rgb(0xffffff);
			m.m_pbr.m_albedo = &diffuse;
			m.m_lit.m_normal = -0.05f;
			m.m_lit.m_normal = &bump;
			m.m_pbr.m_metallic = 0.9f;
			m.m_pbr.m_roughness = 0.8f;
			m.m_pbr.m_roughness = &rough;
			m.m_base.m_uv0_scale = vec2(9.f, 0.5f);
			m.m_base.m_anisotropy = 4.f; // texture filtering anisotropy
			//	premultipliedAlpha : true,
			//	transparent : true
		});
		material = &mat;

		Material& matfloor = app.m_gfx.materials().create("floor", [&](Material& m) {
			m.m_program = &pbr;
			m.m_pbr.m_albedo = rgb(0x888888);
			m.m_pbr.m_metallic = 0.f;
			m.m_pbr.m_roughness = 1.f;
			m.m_base.m_cull_mode = CullMode::Front;
		});

		Model& geometry = app.m_gfx.shape(TorusKnot(18.f, 8.f)); // new THREE.TorusKnotBufferGeometry(18, 8, 150, 20);

		Node3& n = gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(n, geometry, 0U, &mat));
		mesh = &n;

		Model& geomfloor = app.m_gfx.shape(Cube(100.f));

		Node3& nfloor = gfx::nodes(scene).add(Node3(vec3(0.f, 50.f, 0.f), quat(vec3(-c_pi2, 0.f, 0.f))));
		gfx::items(scene).add(Item(n, geomfloor, 0U, &matfloor));

		// Lights

		//scene.add(new THREE.HemisphereLight(0x111111, 0x000000));

		Node3& ln = gfx::nodes(scene).add(Node3(vec3(50.f, 100.f, 50.f)));
		Light& spot = gfx::lights(scene).add(Light(ln, LightType::Spot, true, rgb(0xffffff), 1.f, 300.f));
		spot.m_spot_angle = c_pi / 7.f;
		spot.m_attenuation = 2.f;
		spot.m_spot_attenuation = 0.8f;
		//spot.m_penumbra = 0.8;

		//composer = new THREE.EffectComposer(renderer);
		//composer.setSize(window.innerWidth, window.innerHeight);
		//
		//var renderScene = new THREE.RenderPass(scene, camera);
		//composer.addPass(renderScene);
		//
		//var copyPass = new THREE.ShaderPass(THREE.CopyShader);
		//copyPass.renderToScreen = true;
		//composer.addPass(copyPass);
	}

	//var gui = new dat.GUI();
	//
	//gui.add(params, 'toneMapping', Object.keys(toneMappingOptions));
	//gui.add(params, 'exposure', 0, 10);
	//gui.add(params, 'whitePoint', 0, 10);
	//gui.add(params, 'opacity', 0, 1);
	//gui.add(params, 'renderMode', ['Renderer', 'Composer']);
	//gui.open();

	material->m_pbr.m_roughness = params.roughness;
	material->m_lit.m_normal = -0.05 * params.bumpScale;
	material->m_alpha.m_alpha = params.opacity;

	//if(renderer.toneMapping != toneMappingOptions[params.toneMapping]) {
	//
	//	renderer.toneMapping = toneMappingOptions[params.toneMapping];
	//	standardMaterial.needsUpdate = true;
	//	floorMaterial.needsUpdate = true;
	//
	//}

	//renderer.toneMappingExposure = params.exposure;
	//renderer.toneMappingWhitePoint = params.whitePoint;

	static vec3 rotation = vec3(0.f);
	rotation.y += 0.005f;

	mesh->apply(vec3(0.f), quat(rotation));

	//if(params.renderMode == "Composer") {
	//	composer.render();
	//}
	//else {
	//	renderer.render(scene, camera);
	//}
}
