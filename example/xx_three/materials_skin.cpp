//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

//<script src = "js/ShaderSkin.js">< / script>
//
//<script src = "js/shaders/BleachBypassShader.js">< / script>
//<script src = "js/shaders/ConvolutionShader.js">< / script>
//<script src = "js/shaders/CopyShader.js">< / script>
//
//<script src = "js/postprocessing/EffectComposer.js">< / script>
//<script src = "js/postprocessing/RenderPass.js">< / script>
//<script src = "js/postprocessing/BloomPass.js">< / script>
//<script src = "js/postprocessing/TexturePass.js">< / script>
//<script src = "js/postprocessing/ShaderPass.js">< / script>
//<script src = "js/postprocessing/MaskPass.js">< / script>

void xx_materials_skin(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	static ImporterGltf importer_gltf = { app.m_gfx };

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	bool firstPass = true;

	static Node3* mesh = nullptr;
	static vec3 rotation = vec3(0.f);

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 35.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye.z = 900.f;

		//scene.background = new THREE.Color(0x050505);

		Node3& ln0 = gfx::nodes(scene).add(Node3(vec3(0.f), facing(normalize(vec3(-1.f, -0.5f, -1.f)))));
		Light& l0 = gfx::lights(scene).add(Light(ln0, LightType::Direct, false, rgb(0xffeedd), 1.5f));

		Node3& ln1 = gfx::nodes(scene).add(Node3(vec3(0.f), facing(normalize(vec3(1.f, -0.5f, 1.f)))));
		Light& l1 = gfx::lights(scene).add(Light(ln0, LightType::Direct, false, rgb(0xddddff), 0.5f));

		// MATERIALS

		const Colour diffuse = rgb(0xbbbbbb);
		const Colour specular = rgb(0x555555);

		//var shader = THREE.ShaderSkin["skin"];

		//var uniformsUV = THREE.UniformsUtils.clone(shader.uniforms);

		//uniformsUV["tNormal"].value = textureLoader.load("models/gltf/LeePerrySmith/Infinite-Level_02_Tangent_SmoothUV.jpg");
		//uniformsUV["uNormalScale"].value = -1.5;
		//
		//uniformsUV["tDiffuse"].value = textureLoader.load("models/gltf/LeePerrySmith/Map-COL.jpg");
		//
		//uniformsUV["passID"].value = 0;
		//
		//uniformsUV["diffuse"].value.setHex(diffuse);
		//uniformsUV["specular"].value.setHex(specular);
		//
		//uniformsUV["uRoughness"].value = 0.185;
		//uniformsUV["uSpecularBrightness"].value = 0.7;


		//var uniforms = THREE.UniformsUtils.clone(uniformsUV);
		//uniforms["tDiffuse"].value = uniformsUV["tDiffuse"].value;
		//uniforms["tNormal"].value = uniformsUV["tNormal"].value;
		//uniforms["passID"].value = 1;

		//var parameters = { fragmentShader: shader.fragmentShader, vertexShader : shader.vertexShader, uniforms : uniforms, lights : true };
		//var parametersUV = { fragmentShader: shader.fragmentShader, vertexShader : shader.vertexShaderUV, uniforms : uniformsUV, lights : true };
		//
		//var material = new THREE.ShaderMaterial(parameters);
		//material.extensions.derivatives = true;
		//
		//var materialUV = new THREE.ShaderMaterial(parametersUV);
		//materialUV.extensions.derivatives = true;


		Model& model = *app.m_gfx.models().file("LeePerrySmith.glb");
		//.then(createScene(gltf.scene.children[0].geometry, 100, material);

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f, -50.f, 0.f), ZeroQuat, vec3(100.f)));
		//gfx::items(scene).add(Item(n, model, 0U, &material));

		// POSTPROCESSING
		//var renderModelUV = new THREE.RenderPass(scene, camera, materialUV, new THREE.Color(0x575757));
		//
		//var effectCopy = new THREE.ShaderPass(THREE.CopyShader);
		//
		//var effectBloom1 = new THREE.BloomPass(1, 15, 2, 512);
		//var effectBloom2 = new THREE.BloomPass(1, 25, 3, 512);
		//var effectBloom3 = new THREE.BloomPass(1, 25, 4, 512);
		//
		//effectBloom1.clear = true;
		//effectBloom2.clear = true;
		//effectBloom3.clear = true;
		//
		//effectCopy.renderToScreen = true;

		//

		//var pars = {
		//	generateMipmaps: true,
		//	minFilter : THREE.LinearMipmapLinearFilter,
		//	magFilter : THREE.LinearFilter,
		//	format : THREE.RGBFormat,
		//	stencilBuffer : false
		//};
		//
		//var rtwidth = 512;
		//var rtheight = 512;
		//
		////
		//
		//composer = new THREE.EffectComposer(renderer, new THREE.WebGLRenderTarget(rtwidth, rtheight, pars));
		//composer.addPass(renderModelUV);
		//
		//var renderScene = new THREE.TexturePass(composer.renderTarget2.texture);

		//

		//composerUV1 = new THREE.EffectComposer(renderer, new THREE.WebGLRenderTarget(rtwidth, rtheight, pars));
		//
		//composerUV1.addPass(renderScene);
		//composerUV1.addPass(effectBloom1);
		//
		//composerUV2 = new THREE.EffectComposer(renderer, new THREE.WebGLRenderTarget(rtwidth, rtheight, pars));
		//
		//composerUV2.addPass(renderScene);
		//composerUV2.addPass(effectBloom2);
		//
		//composerUV3 = new THREE.EffectComposer(renderer, new THREE.WebGLRenderTarget(rtwidth, rtheight, pars));
		//
		//composerUV3.addPass(renderScene);
		//composerUV3.addPass(effectBloom3);

		//

		//var effectBeckmann = new THREE.ShaderPass(THREE.ShaderSkin["beckmann"]);
		//composerBeckmann = new THREE.EffectComposer(renderer, new THREE.WebGLRenderTarget(rtwidth, rtheight, pars));
		//composerBeckmann.addPass(effectBeckmann);

		//

		//uniforms["tBlur1"].value = composer.renderTarget2.texture;
		//uniforms["tBlur2"].value = composerUV1.renderTarget2.texture;
		//uniforms["tBlur3"].value = composerUV2.renderTarget2.texture;
		//uniforms["tBlur4"].value = composerUV3.renderTarget2.texture;
		//
		//uniforms["tBeckmann"].value = composerBeckmann.renderTarget1.texture;
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = event.m_relative - viewer.m_frame.m_size / 2.f;
	}

	const vec2 target = mouse * 0.001f;

	rotation.x += 0.05f * (target.x - rotation.y);
	rotation.y += 0.05f * (target.y - rotation.y);

	mesh->apply(vec3(0.f, -50.f, 0.f), quat(rotation), vec3(100.f));


	//renderer.clear();
	//
	//if(firstPass) {
	//
	//	composerBeckmann.render();
	//	firstPass = false;
	//
	//}
	//
	//composer.render();
	//
	//composerUV1.render();
	//composerUV2.render();
	//composerUV3.render();
	//
	//renderer.render(scene, camera);
}
